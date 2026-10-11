#include "LibrariesDialog.h"
#include "LibraryResolver.h"
#include "Toolchain.h"
#include <QDialogButtonBox>
#include <QDir>
#include <QJsonArray>
#include <QJsonDocument>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSaveFile>
#include <QTreeWidget>
#include <QVBoxLayout>
#include <QSignalBlocker>
#include <QProgressBar>

namespace {
class LibraryItem : public QTreeWidgetItem
{
public:
    using QTreeWidgetItem::QTreeWidgetItem;
    bool operator<(const QTreeWidgetItem& other) const override
    {
        if (treeWidget()->sortColumn() == 0) {
            if (checkState(0) != other.checkState(0)) return checkState(0) < other.checkState(0);
            return text(1) < other.text(1);
        }
        return QTreeWidgetItem::operator<(other);
    }
};
}

LibrariesDialog::LibrariesDialog(const QStringList& selected, QWidget* parent, const QString& catalogDestination)
    : QDialog(parent), selected_(selected), catalogDestination_(catalogDestination.isEmpty() ? LibraryResolver::catalogPath() : catalogDestination), catalog_(LibraryResolver::catalog())
{
    setWindowTitle("Libraries"); setObjectName("librariesDialog"); resize(760, 560);
    auto* layout = new QVBoxLayout(this);
    hint_ = new QLabel("Choose libraries for this program. Missing libraries are installed when you build.");
    hint_->setWordWrap(true); layout->addWidget(hint_);
    progress_ = new QProgressBar; progress_->setObjectName("libraryUpdateProgress");
    progress_->setRange(0, 0); progress_->hide(); layout->addWidget(progress_);
    search_ = new QLineEdit; search_->setPlaceholderText("Search libraries, for example fmt or opencv"); search_->setObjectName("librarySearch"); layout->addWidget(search_);
    list_ = new QTreeWidget; list_->setObjectName("libraryList"); list_->setHeaderLabels({"Use", "Library", "Package", "Installed"});
    list_->setRootIsDecorated(false); list_->setAlternatingRowColors(true); layout->addWidget(list_);
    list_->setSortingEnabled(true); list_->sortItems(1, Qt::AscendingOrder);
    auto* buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    update_ = buttons->addButton("Update List", QDialogButtonBox::ActionRole); update_->setObjectName("updateLibraryList");
    layout->addWidget(buttons);
    connect(buttons, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttons, &QDialogButtonBox::rejected, this, &QDialog::reject);
    connect(search_, &QLineEdit::textChanged, this, [this] { populate(); });
    connect(list_, &QTreeWidget::itemChanged, this, [this](QTreeWidgetItem* item, int) {
        const auto module = item->text(1);
        if (item->checkState(0) == Qt::Checked) { if (!selected_.contains(module)) selected_ << module; }
        else selected_.removeAll(module);
    });
    connect(&process_, &QProcess::readyReadStandardOutput, this, [this] { bytes_ += process_.readAllStandardOutput(); });
    connect(&process_, &QProcess::readyReadStandardError, this, [this] { const QString message = QString::fromUtf8(process_.readAllStandardError()).trimmed(); if (!message.isEmpty()) hint_->setText(message); });
    connect(&process_, &QProcess::errorOccurred, this, [this](QProcess::ProcessError error) { if (error == QProcess::FailedToStart) { hint_->setText(process_.errorString()); progress_->hide(); update_->setEnabled(true); } });
    connect(&process_, &QProcess::finished, this, [this](int code, QProcess::ExitStatus status) {
        bytes_ += process_.readAllStandardOutput();
        progress_->hide();
        if (code || status != QProcess::NormalExit) { hint_->setText("Could not query libraries. Use MSYS2 Terminal to check the environment."); update_->setEnabled(true); return; }
        if (step_ == 0) {
            installed_.clear();
            for (const auto& line : QString::fromUtf8(bytes_).split('\n')) {
                const auto module = line.section(' ', 0, 0).trimmed(); if (!module.isEmpty()) installed_ << module;
            }
            populate();
        } else if (step_ == 1) { step_ = 2; hint_->setText("Reading packages and building the library list..."); progress_->show(); run(LibraryResolver::pacman(), {"-Fl"}); return; }
        else {
            auto next = LibraryResolver::scanCatalog(bytes_);
            QSaveFile file(catalogDestination_); QDir().mkpath(QFileInfo(file.fileName()).absolutePath());
            const auto json = QJsonDocument(next).toJson();
            if (next.isEmpty() || !file.open(QIODevice::WriteOnly) || file.write(json) != json.size() || !file.commit()) {
                hint_->setText("List update failed. The previous list was kept."); update_->setEnabled(true); return;
            }
            catalog_ = next; populate(); hint_->setText(QString("Updated: %1 libraries. Packages were not upgraded.").arg(catalog_.size()));
        }
        update_->setEnabled(true);
    });
    connect(update_, &QPushButton::clicked, this, [this] {
        if (process_.state() != QProcess::NotRunning) return;
        update_->setEnabled(false); hint_->setText("Downloading the latest package lists..."); progress_->show(); step_ = 1; run(LibraryResolver::pacman(), {"-Fy"});
    });
    populate();
    update_->setEnabled(false); run(LibraryResolver::pkgConfig(), {"--list-all"});
}
void LibrariesDialog::run(const QString& program, const QStringList& args)
{
    bytes_.clear(); auto env = Toolchain::environment();
    const QDir bin(QFileInfo(Toolchain::compiler()).absolutePath());
    env.insert("PKG_CONFIG_LIBDIR", bin.absoluteFilePath("../lib/pkgconfig") + QDir::listSeparator() + bin.absoluteFilePath("../share/pkgconfig"));
    env.remove("PKG_CONFIG_PATH"); env.remove("PKG_CONFIG_SYSROOT_DIR"); process_.setProcessEnvironment(env); process_.start(program, args);
}
void LibrariesDialog::populate()
{
    QSignalBlocker block(list_); list_->clear();
    list_->setSortingEnabled(false);
    QStringList modules = catalog_.keys(); modules << selected_ << installed_; modules.removeDuplicates(); modules.sort();
    for (const auto& module : modules) {
        const auto value = catalog_.value(module);
        QStringList providers;
        if (value.isString()) providers << value.toString(); else for (const auto& item : value.toArray()) providers << item.toString();
        const QString packages = providers.join(", ");
        if (!search_->text().isEmpty() && !module.contains(search_->text(), Qt::CaseInsensitive) && !packages.contains(search_->text(), Qt::CaseInsensitive)) continue;
        auto* item = new LibraryItem(list_, {"", module, packages, installed_.contains(module) ? "Yes" : ""});
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable); item->setCheckState(0, selected_.contains(module) ? Qt::Checked : Qt::Unchecked);
        item->setToolTip(2, packages);
    }
    list_->setSortingEnabled(true);
    list_->resizeColumnToContents(0); list_->resizeColumnToContents(1);
}

LibrariesDialog::~LibrariesDialog() { if (process_.state() != QProcess::NotRunning) { process_.terminate(); process_.waitForFinished(3000); } }
