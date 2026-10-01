#include "PublishDialog.h"
#include <QDesktopServices>
#include <QDir>
#include <QFileDialog>
#include <QFileInfo>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QTreeWidget>
#include <QUrl>
#include <QVBoxLayout>

namespace {
void styleDialog(QDialog& dialog)
{
    QFont font = dialog.font();
    font.setFamily("Segoe UI");
    font.setPointSize(13);
    dialog.setFont(font);
    dialog.setStyleSheet("QDialog, QLabel, QLineEdit, QTreeWidget, QPushButton { font-family: 'Segoe UI'; font-size: 13pt; }"
                        "QLabel#publishHeading { font-size: 18pt; font-weight: bold; }"
                        "QPushButton { min-height: 44px; padding: 0 16px; }"
                        "QPushButton#publishConfirm { background: palette(highlight); color: palette(highlighted-text); }"
                        "QLineEdit { min-height: 42px; padding: 0 8px; }"
                        "QTreeWidget::item { min-height: 44px; }");
    dialog.setMinimumWidth(640);
}
QLabel* title(const QString& text, QWidget* parent)
{
    auto* label = new QLabel(text, parent);
    label->setObjectName("publishHeading");
    QFont font = parent->font(); font.setPointSize(18); font.setBold(true);
    label->setFont(font);
    return label;
}
}

PublishDialog::PublishDialog(const QString& initialFolder, const QString& programName, QWidget* parent)
    : QDialog(parent)
{
    setObjectName("publishDialog");
    setWindowTitle("Publish Your Program");
    styleDialog(*this);
    auto* layout = new QVBoxLayout(this);
    layout->setContentsMargins(24, 24, 24, 24);
    layout->setSpacing(16);
    layout->addWidget(title("Publish Your Program", this));
    layout->addWidget(new QLabel("Make a copy your friends can run.\nThey don't need Small C++.", this));
    layout->addWidget(new QLabel("Save to", this));
    auto* location = new QHBoxLayout;
    destination_ = new QLineEdit(QDir(initialFolder).filePath(programName + "-published"), this);
    destination_->setObjectName("publishDestination");
    location->addWidget(destination_, 1);
    auto* browse = new QPushButton("Browse...", this);
    location->addWidget(browse);
    layout->addLayout(location);
    connect(browse, &QPushButton::clicked, this, [this, programName] {
        const QString folder = QFileDialog::getExistingDirectory(this, "Save to",
                                                                 QFileInfo(destination()).absolutePath());
        if (!folder.isEmpty()) destination_->setText(QDir(folder).filePath(programName + "-published"));
    });
    layout->addWidget(new QLabel("Extra Files — Optional", this));
    auto* explanation = new QLabel("Add pictures, sounds, or other files your program uses.", this);
    explanation->setWordWrap(true);
    layout->addWidget(explanation);
    auto* add = new QPushButton("Add Files...", this);
    add->setObjectName("publishAddFiles");
    layout->addWidget(add, 0, Qt::AlignLeft);
    files_ = new QTreeWidget(this);
    files_->setObjectName("publishFiles");
    files_->setHeaderHidden(true);
    files_->setColumnCount(2);
    files_->setRootIsDecorated(false);
    files_->setMinimumHeight(150);
    files_->header()->setSectionResizeMode(0, QHeaderView::Stretch);
    files_->header()->setSectionResizeMode(1, QHeaderView::Fixed);
    files_->header()->setStretchLastSection(false);
    files_->setColumnWidth(1, 140);
    layout->addWidget(files_);
    connect(add, &QPushButton::clicked, this, [this, initialFolder] {
        addFiles(QFileDialog::getOpenFileNames(this, "Add Files", initialFolder));
    });
    layout->addWidget(new QLabel("Your code will also be included.", this));
    auto* buttons = new QHBoxLayout;
    buttons->addStretch();
    auto* cancel = new QPushButton("Cancel", this);
    auto* publish = new QPushButton("Publish", this);
    publish->setObjectName("publishConfirm");
    publish->setDefault(true);
    buttons->addWidget(cancel);
    buttons->addWidget(publish);
    layout->addLayout(buttons);
    connect(cancel, &QPushButton::clicked, this, &QDialog::reject);
    connect(publish, &QPushButton::clicked, this, [this] {
        const QFileInfo target(destination());
        if (destination().isEmpty() || target.exists() || target.isSymLink() ||
            !QFileInfo(target.absolutePath()).isDir()) {
            QMessageBox::warning(this, "Save to", "Choose a new folder inside an existing folder.\n"
                                "Your existing files will not be overwritten.");
            return;
        }
        accept();
    });
}

QString PublishDialog::destination() const { return destination_->text().trimmed(); }
QStringList PublishDialog::resources() const
{
    QStringList paths;
    for (int i = 0; i < files_->topLevelItemCount(); ++i)
        paths << files_->topLevelItem(i)->data(0, Qt::UserRole).toString();
    return paths;
}
void PublishDialog::addFiles(const QStringList& paths)
{
    for (const QString& path : paths) {
        const QString absolute = QFileInfo(path).absoluteFilePath();
        if (resources().contains(absolute)) continue;
        auto* item = new QTreeWidgetItem(files_, {QFileInfo(path).fileName()});
        item->setData(0, Qt::UserRole, absolute);
        item->setToolTip(0, absolute);
        auto* remove = new QPushButton("Remove", files_);
        files_->setItemWidget(item, 1, remove);
        connect(remove, &QPushButton::clicked, this, [this, item] {
            delete files_->takeTopLevelItem(files_->indexOfTopLevelItem(item));
        });
    }
}

void ShowPublishComplete(const QString& folder, const QString& executable, QWidget* parent)
{
    QDialog dialog(parent);
    dialog.setObjectName("publishCompleteDialog");
    dialog.setWindowTitle("Your program is ready!");
    styleDialog(dialog);
    auto* layout = new QVBoxLayout(&dialog);
    layout->setContentsMargins(24, 24, 24, 24);
    layout->setSpacing(16);
    layout->addWidget(title("Your program is ready!", &dialog));
    auto* message = new QLabel("Open the folder and run " + executable + ".\n"
                              "Share the whole folder with your friends.", &dialog);
    message->setWordWrap(true);
    layout->addWidget(message);
    auto* buttons = new QHBoxLayout;
    buttons->addStretch();
    auto* done = new QPushButton("Done", &dialog);
    auto* open = new QPushButton("Open Folder", &dialog);
    open->setObjectName("publishConfirm");
    buttons->addWidget(done);
    buttons->addWidget(open);
    layout->addLayout(buttons);
    QObject::connect(done, &QPushButton::clicked, &dialog, &QDialog::reject);
    QObject::connect(open, &QPushButton::clicked, &dialog, [&] {
        QDesktopServices::openUrl(QUrl::fromLocalFile(folder));
        dialog.accept();
    });
    dialog.exec();
}
