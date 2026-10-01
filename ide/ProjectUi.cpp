#include "MainWindow.h"
#include "BuildController.h"
#include "DebugController.h"
#include "EditorDocument.h"
#include "Diagnostics.h"
#include "EntryPoint.h"
#include <QAction>
#include <QDockWidget>
#include <QFileDialog>
#include <QFile>
#include <QFileInfo>
#include <QInputDialog>
#include <QJsonDocument>
#include <QLabel>
#include <QLineEdit>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QPlainTextEdit>
#include <QSaveFile>
#include <QStatusBar>
#include <QTabWidget>
#include <QTextDocument>
#include <QTimer>
#include <QToolButton>
#include <QTreeWidget>
#include <QTreeWidgetItemIterator>
#include <QVBoxLayout>
#include <QDir>
#include <QApplication>
#include <QPainter>
#include <QStyledItemDelegate>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QTabBar>
#include <QDesktopServices>
#include <QUrl>
#ifdef Q_OS_WIN
#include <shlobj.h>
#endif

namespace {
class ProjectFileDelegate : public QStyledItemDelegate
{
public:
    using QStyledItemDelegate::QStyledItemDelegate;
    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override
    {
        if (!index.data(Qt::UserRole + 1).toBool()) {
            QStyledItemDelegate::paint(painter, option, index);
            return;
        }
        // Keep excluded text gray even when the theme sets selected text white.
        QStyleOptionViewItem view(option);
        initStyleOption(&view, index);
        const QRect textRect = view.rect.adjusted(6, 0, -6, 0);
        const QString text = view.fontMetrics.elidedText(view.text, view.textElideMode, textRect.width());
        painter->save();
        // Draw the excluded row directly: native focus/selection styles can
        // restore their own text color even when a delegate clears the text.
        painter->fillRect(view.rect, view.palette.brush(view.state & QStyle::State_Selected
            ? QPalette::Highlight : QPalette::Base));
        painter->setFont(view.font);
        const QBrush foreground = index.data(Qt::ForegroundRole).value<QBrush>();
        painter->setPen(foreground.style() == Qt::NoBrush ? view.palette.color(QPalette::PlaceholderText) : foreground.color());
        painter->drawText(textRect, view.displayAlignment, text);
        if (view.state & QStyle::State_HasFocus) {
            painter->setPen(QPen(view.palette.color(QPalette::Mid), 1, Qt::DotLine));
            painter->drawRect(view.rect.adjusted(1, 1, -2, -2));
        }
        painter->restore();
    }
};
}

void MainWindow::createProjectUi()
{
    auto* menu = findChild<QMenu*>("menuFile");
    menu->addSeparator();
    newProjectAction_ = menu->addAction("New Project...");
    newProjectAction_->setObjectName("actionNewProject");
    openProjectAction_ = menu->addAction("Open Project (Folder)...");
    openProjectAction_->setObjectName("actionOpenProject");
    closeProjectAction_ = menu->addAction("Close Project");
    closeProjectAction_->setObjectName("actionCloseProject");
    projectSettingsAction_ = menu->addAction("Project Settings...");
    projectSettingsAction_->setObjectName("actionProjectSettings");
    if (auto* exit = findChild<QAction*>("actionQuit")) {
        menu->removeAction(exit);
        menu->addSeparator();
        menu->addAction(exit);
    }
    connect(newProjectAction_, &QAction::triggered, this, &MainWindow::newProject);
    connect(openProjectAction_, &QAction::triggered, this, &MainWindow::openProjectDialog);
    connect(closeProjectAction_, &QAction::triggered, this, [this] { closeProject(); });
    connect(projectSettingsAction_, &QAction::triggered, this, &MainWindow::editProjectSettings);
    projectDock_ = new QDockWidget("Project", this);
    projectDock_->setObjectName("projectDock");
    projectDock_->setFeatures(QDockWidget::NoDockWidgetFeatures);
    projectHeading_ = new QLabel;
    projectHeading_->setObjectName("projectHeading");
    projectHeading_->setTextFormat(Qt::PlainText);
    projectHeading_->setWordWrap(true);
    projectHeading_->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(projectHeading_, &QWidget::customContextMenuRequested, this, [this](const QPoint& position) {
        QMenu menu(this);
        auto* reveal = menu.addAction("Show Project in File Explorer");
        reveal->setEnabled(QFileInfo(project_.root).isDir());
        connect(reveal, &QAction::triggered, this, [this] { showInFileExplorer(project_.root); });
        menu.exec(projectHeading_->mapToGlobal(position));
    });
    projectHeading_->setStyleSheet("QLabel { font-size: 14pt; font-weight: bold; padding: 12px; }");
    projectDock_->setTitleBarWidget(projectHeading_);
    projectTree_ = new QTreeWidget;
    projectTree_->setObjectName("projectFiles");
    projectTree_->setHeaderHidden(true);
    projectTree_->setItemDelegate(new ProjectFileDelegate(projectTree_));
    projectTree_->setMinimumWidth(220);
    projectTree_->setStyleSheet("QTreeWidget { font-size: 12pt; } QTreeWidget::item { min-height: 30px; padding: 4px; }");
    projectTree_->setContextMenuPolicy(Qt::CustomContextMenu);
    projectDock_->setWidget(projectTree_);
    addDockWidget(Qt::LeftDockWidgetArea, projectDock_);
    projectDock_->hide();
    projectStatus_ = new QLabel("Single File");
    projectStatus_->setObjectName("projectStatus");
    statusBar()->addPermanentWidget(projectStatus_);
    connect(projectTree_, &QTreeWidget::itemActivated, this, [this](QTreeWidgetItem* item, int) {
        const QString path = project_.absolute(item->data(0, Qt::UserRole).toString());
        if (QFileInfo(path).isFile() && (ProjectFolder::isSource(path) || ProjectFolder::isHeader(path) ||
            QStringList{"txt", "json", "md", "csv", "qss"}.contains(QFileInfo(path).suffix().toLower()))) openDocument(path);
    });
    connect(projectTree_, &QTreeWidget::customContextMenuRequested, this, [this](const QPoint& position) {
        auto* item = projectTree_->itemAt(position);
        const QString relative = item ? item->data(0, Qt::UserRole).toString() : QString();
        const QFileInfo target(project_.absolute(relative));
        const QString directory = relative.isEmpty() ? project_.root
            : (target.isDir() ? target.absoluteFilePath() : target.absolutePath());
        QMenu menu(this);
        const bool canEdit = !build_->isBusy() && !debug_->isBusy();
        menu.addAction("New Source File...", this, [this, directory] { newProjectFile("cpp", directory); })->setEnabled(canEdit);
        menu.addAction("New Header File...", this, [this, directory] { newProjectFile("h", directory); })->setEnabled(canEdit);
        menu.addAction("Add Existing Files...", this, &MainWindow::addProjectFiles)->setEnabled(canEdit);
        menu.addSeparator();
        const QString path = relative.isEmpty() ? project_.root : target.absoluteFilePath();
        auto* reveal = menu.addAction(relative.isEmpty() ? "Show Project in File Explorer" : "Show in File Explorer");
        reveal->setEnabled(QFileInfo::exists(path));
        connect(reveal, &QAction::triggered, this, [this, path] { showInFileExplorer(path); });
        if (!relative.isEmpty()) {
            menu.addSeparator();
            const bool excluded = project_.excludes(relative);
            auto* toggle = menu.addAction(excluded ? "Include in Project" : "Exclude from Project");
            toggle->setEnabled(canEdit);
            // A child of an excluded folder is restored by including that folder.
            QString exclusion = relative;
            for (const auto& path : project_.excluded)
                if (relative.startsWith(path + "/", Qt::CaseInsensitive)) { exclusion = path; break; }
            connect(toggle, &QAction::triggered, this, [this, exclusion, excluded] {
                QString error;
                auto* settingsDocument = findOpenDocument(project_.absolute("small.project"));
                if (settingsDocument && settingsDocument->document()->isModified() && !saveFile(settingsDocument)) return;
                if (!project_.load(project_.root, &error) || !project_.setExcluded(exclusion, !excluded, &error)) {
                    QMessageBox::warning(this, "Project Settings", error);
                } else if (settingsDocument) {
                    QFile config(project_.absolute("small.project"));
                    if (config.open(QIODevice::ReadOnly)) {
                        settingsDocument->setPlainText(QString::fromUtf8(config.readAll()));
                        settingsDocument->document()->setModified(false);
                    }
                }
                refreshProject();
            });
        }
        menu.exec(projectTree_->viewport()->mapToGlobal(position));
    });
    auto* tabBar = tabs_->tabBar();
    tabBar->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(tabBar, &QWidget::customContextMenuRequested, this, [this, tabBar](const QPoint& position) {
        const int index = tabBar->tabAt(position);
        if (index < 0) return;
        auto* document = documentAt(index);
        if (!document) return; // The Welcome tab has no file location.
        const QString path = document->filePath();
        QMenu menu(this);
        auto* reveal = menu.addAction("Show in File Explorer");
        reveal->setEnabled(!path.isEmpty() && QFileInfo(path).isFile());
        connect(reveal, &QAction::triggered, this, [this, path] { showInFileExplorer(path); });
        menu.exec(tabBar->mapToGlobal(position));
    });
    projectRefresh_ = new QTimer(this);
    projectRefresh_->setInterval(1500);
    connect(projectRefresh_, &QTimer::timeout, this, &MainWindow::refreshProject);
}

bool MainWindow::showInFileExplorer(const QString& path)
{
    const QFileInfo file(path);
    if (!file.exists()) return false;
    if (file.isDir()) return QDesktopServices::openUrl(QUrl::fromLocalFile(file.absoluteFilePath()));
#ifdef Q_OS_WIN
    // Select the exact Unicode path without command-line quoting or a shell.
    const HRESULT initialized = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
    if (FAILED(initialized) && initialized != RPC_E_CHANGED_MODE) return false;
    PIDLIST_ABSOLUTE item = nullptr;
    const QString native = QDir::toNativeSeparators(file.absoluteFilePath());
    HRESULT result = SHParseDisplayName(reinterpret_cast<LPCWSTR>(native.utf16()), nullptr, &item, 0, nullptr);
    if (SUCCEEDED(result)) result = SHOpenFolderAndSelectItems(item, 0, nullptr, 0);
    CoTaskMemFree(item);
    if (SUCCEEDED(initialized)) CoUninitialize();
    return SUCCEEDED(result);
#else
    return QDesktopServices::openUrl(QUrl::fromLocalFile(file.absolutePath()));
#endif
}

bool MainWindow::openProject(const QString& folder)
{
    if (build_->isBusy() || debug_->isBusy() || closing_ || confirmingClose_) return false;
    ProjectFolder next;
    QString error;
    if (!next.load(folder, &error)) { QMessageBox::warning(this, "Open Project", error); return false; }
    if (next.root == project_.root) return true;
    if (!closeProject()) return false;
    project_ = next;
    projectDock_->show();
    projectRefresh_->start();
    refreshProject();
    // Opening a folder opens its start file, not every source in the folder.
    QString first;
    for (const QString& relative : project_.sources) {
        QFile file(project_.absolute(relative));
        if (file.open(QIODevice::ReadOnly) && !DefinedEntryPoints(QString::fromUtf8(file.readAll())).isEmpty()) { first = relative; break; }
    }
    if (first.isEmpty() && !project_.sources.isEmpty()) first = project_.sources.first();
    if (!first.isEmpty()) openDocument(project_.absolute(first));
    updateTitle();
    return true;
}

bool MainWindow::closeProject()
{
    if (project_.root.isEmpty()) return true;
    if (build_->isBusy() || debug_->isBusy() || closing_ || confirmingClose_) return false;
    QList<QPointer<EditorDocument>> documents;
    for (int i = 0; i < tabs_->count(); ++i)
        if (auto* document = documentAt(i); document && project_.contains(document->filePath())) documents << document;
    confirmingClose_ = true;
    for (const auto& document : documents) {
        if (document && !maybeSave(document)) { confirmingClose_ = false; updateTitle(); return false; }
    }
    confirmingClose_ = false;
    for (const auto& document : documents) {
        if (!document) continue;
        if (runDocument_ == document) runDocument_.clear();
        const int index = tabs_->indexOf(document);
        if (index >= 0) tabs_->removeTab(index);
        delete document.data();
    }
    project_ = ProjectFolder{};
    projectRefresh_->stop();
    projectTree_->clear(); projectDock_->hide();
    for (int i = 0; i < tabs_->count(); ++i) updateTabTitle(documentAt(i));
    if (tabs_->count() == 0) showWelcome();
    updateTitle(); updateDiagnosticsLabel();
    return true;
}

void MainWindow::refreshProject()
{
    if (project_.root.isEmpty() || refreshingProject_ || build_->isBusy() || debug_->isBusy() || confirmingClose_) return;
    refreshingProject_ = true;
    ProjectFolder next;
    QString error;
    if (!next.load(project_.root, &error)) { statusBar()->showMessage(error); refreshingProject_ = false; return; }
    const bool same = next.files == project_.files && next.excluded == project_.excluded && projectTree_->topLevelItemCount() > 0;
    project_ = next;
    projectHeading_->setText("PROJECT\n" + project_.name);
    projectHeading_->setToolTip(project_.root);
    if (!same) {
        QSet<QString> expanded;
        QTreeWidgetItemIterator iterator(projectTree_);
        while (*iterator) { if ((*iterator)->isExpanded()) expanded.insert((*iterator)->data(0, Qt::UserRole).toString()); ++iterator; }
        projectTree_->clear();
        QMap<QString, QTreeWidgetItem*> items;
        for (const QString& file : project_.files) {
            QString path;
            QTreeWidgetItem* parent = nullptr;
            const auto segments = file.split('/');
            for (const QString& segment : segments) {
                path = path.isEmpty() ? segment : path + "/" + segment;
                if (!items.contains(path)) {
                    auto* item = parent ? new QTreeWidgetItem(parent) : new QTreeWidgetItem(projectTree_);
                    item->setForeground(0, QBrush(project_.excludes(path)
                        ? QColor(darkTheme_ ? "#8993a3" : "#929aa6") : projectTree_->palette().color(QPalette::Text)));
                    item->setText(0, segment + (project_.excludes(path) ? " (Excluded)" : ""));
                    item->setData(0, Qt::UserRole, path);
                    item->setData(0, Qt::UserRole + 1, project_.excludes(path));
                    item->setToolTip(0, project_.absolute(path) + (project_.excludes(path) ? "\nExcluded; the file is still on disk." : ""));
                    item->setExpanded(expanded.contains(path));
                    items.insert(path, item);
                }
                parent = items.value(path);
            }
        }
    }
    QTreeWidgetItemIterator iterator(projectTree_);
    while (*iterator) {
        auto* item = *iterator;
        const QString relative = item->data(0, Qt::UserRole).toString();
        const bool excluded = project_.excludes(relative);
        // The context menu updates project_ before refreshProject(), so the tree
        // can retain its structure while all exclusion presentation must refresh.
        item->setText(0, QFileInfo(relative).fileName() + (excluded ? " (Excluded)" : ""));
        item->setData(0, Qt::UserRole + 1, excluded);
        item->setToolTip(0, project_.absolute(relative) + (excluded ? "\nExcluded; the file is still on disk." : ""));
        item->setForeground(0, QBrush(excluded ? QColor(darkTheme_ ? "#8993a3" : "#929aa6")
                                              : projectTree_->palette().color(QPalette::Text)));
        QFont font = item->font(0);
        font.setItalic(excluded);
        item->setFont(0, font);
        ++iterator;
    }
    for (int i = 0; i < tabs_->count(); ++i) updateTabTitle(documentAt(i));
    updateTitle();
    refreshingProject_ = false;
}

void MainWindow::openProjectDialog()
{
    // Qt's directory picker can show files as context while accepting folders only.
    QFileDialog dialog(this, "Open Project (Folder)", initialDirectory(currentDocument()));
    dialog.setObjectName("openProjectFolderDialog");
    dialog.setPalette(palette());
    dialog.setOption(QFileDialog::DontUseNativeDialog);
    dialog.setFileMode(QFileDialog::Directory);
    dialog.setOption(QFileDialog::ShowDirsOnly, false);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setLabelText(QFileDialog::Accept, "Open Project");
    dialog.setLabelText(QFileDialog::FileName, "Project folder:");
    QString chosenFolder;
    auto* buttons = dialog.findChild<QDialogButtonBox*>();
    if (auto* original = buttons->button(QDialogButtonBox::Open)) {
        original->setDefault(false);
        original->setAutoDefault(false);
        original->hide();
    }
    auto* openCurrent = buttons->addButton("Open This Folder", QDialogButtonBox::ActionRole);
    openCurrent->setObjectName("openCurrentProjectFolder");
    openCurrent->setDefault(true);
    connect(openCurrent, &QPushButton::clicked, &dialog, [&] {
        chosenFolder = dialog.directory().absolutePath();
        static_cast<QDialog&>(dialog).done(QDialog::Accepted);
    });
    // QFileDialog fixes its navigation buttons to icon size. The IDE's generous
    // general button padding otherwise consumes their entire icon area.
    dialog.setStyleSheet(QString("QToolButton { padding: 4px; } QAbstractItemView, QComboBox { background: %1; color: %2; }")
        .arg(darkTheme_ ? "#1e1f22" : "#ffffff", darkTheme_ ? "#e6e6e6" : "#202124"));
    for (auto* button : dialog.findChildren<QToolButton*>()) {
        button->setFixedSize(36, 36);
        button->setIconSize(QSize(20, 20));
        if (!QStringList{"backButton", "forwardButton", "toParentButton"}.contains(button->objectName())) continue;
        QIcon icon;
        for (auto mode : {QIcon::Normal, QIcon::Disabled}) {
            QPixmap glyph = button->icon().pixmap(QSize(20, 20), mode);
            QPainter painter(&glyph);
            painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
            painter.fillRect(glyph.rect(), palette().color(mode == QIcon::Disabled ? QPalette::Mid : QPalette::WindowText));
            painter.end();
            icon.addPixmap(glyph, mode);
        }
        button->setIcon(icon);
    }
    dialog.resize(850, 560);
    if (dialog.exec() == QDialog::Accepted) {
        if (chosenFolder.isEmpty() && !dialog.selectedFiles().isEmpty()) {
            const QString selected = dialog.selectedFiles().first();
            chosenFolder = QFileInfo(selected).isDir() ? selected : dialog.directory().absolutePath();
        }
        if (!chosenFolder.isEmpty()) openProject(chosenFolder);
    }
}
void MainWindow::newProject()
{
    const QString parent = QFileDialog::getExistingDirectory(this, "Choose Where to Create Your Project", initialDirectory(currentDocument()));
    if (parent.isEmpty()) return;
    bool accepted = false;
    const QString name = QInputDialog::getText(this, "New Project", "Project name", QLineEdit::Normal, "MyProject", &accepted).trimmed();
    if (!accepted || name.isEmpty()) return;
    if (name == "." || name == ".." || name.contains('/') || name.contains('\\')) { QMessageBox::warning(this, "New Project", "Use a folder name without slashes."); return; }
    const QString folder = QDir(parent).filePath(name);
    if (QFileInfo::exists(folder) || !QDir().mkpath(folder)) { QMessageBox::warning(this, "New Project", "Choose a new project name. Existing folders are kept."); return; }
    QSaveFile file(QDir(folder).filePath("main.cpp"));
    const QByteArray text("void SmallMain()\n{\n    Print(\"Hello!\");\n}\n");
    if (!file.open(QIODevice::WriteOnly) || file.write(text) != text.size() || !file.commit()) { QMessageBox::warning(this, "New Project", "Cannot create main.cpp."); return; }
    openProject(folder);
}
void MainWindow::newProjectFile(const QString& suffix, const QString& directory)
{
    const QString folder = directory.isEmpty() ? project_.root : directory;
    QInputDialog dialog(this);
    dialog.setObjectName("newProjectFileDialog");
    dialog.setWindowTitle(suffix == "h" ? "New Header File" : "New Source File");
    const QString relative = QDir(project_.root).relativeFilePath(folder);
    dialog.setLabelText("File name\nFolder: " + (relative == "." ? project_.name : relative));
    dialog.setTextValue("NewFile." + suffix);
    if (dialog.exec() != QDialog::Accepted) return;
    const QString name = dialog.textValue().trimmed();
    if (name.isEmpty()) return;
    if (name == "." || name == ".." || name.contains('/') || name.contains('\\')) {
        QMessageBox::warning(this, "New File", "Enter a file name without slashes."); return;
    }
    QString path = QDir(folder).filePath(name);
    if (QFileInfo(path).suffix().isEmpty()) path += "." + suffix;
    if (!project_.contains(path) || QFileInfo::exists(path)) { QMessageBox::warning(this, "New File", "Choose a new file inside the project folder."); return; }
    QSaveFile file(path);
    const QByteArray contents = suffix == "h" ? QByteArray("#pragma once\n") : QByteArray("// Add your helper functions here.\n");
    if (!file.open(QIODevice::WriteOnly) || file.write(contents) != contents.size() || !file.commit()) { QMessageBox::warning(this, "New File", "Cannot create the file."); return; }
    refreshProject(); openDocument(path);
}
void MainWindow::addProjectFiles()
{
    const auto paths = QFileDialog::getOpenFileNames(this, "Add Existing Files", project_.root);
    for (const auto& path : paths) {
        if (project_.contains(path)) continue;
        const QString target = project_.absolute(QFileInfo(path).fileName());
        if (QFileInfo::exists(target) || !QFile::copy(path, target)) { QMessageBox::warning(this, "Add Files", "Could not copy without overwriting: " + target); break; }
    }
    refreshProject();
}
void MainWindow::editProjectSettings()
{
    const QString path = project_.absolute("small.project");
    if (!QFileInfo::exists(path)) {
        QSaveFile file(path);
        const QByteArray data("{\n  \"version\": 1,\n  \"exclude\": [],\n  \"include_paths\": [],\n  \"library_paths\": [],\n  \"libraries\": [],\n  \"compiler_options\": [],\n  \"linker_options\": []\n}\n");
        if (!file.open(QIODevice::WriteOnly) || file.write(data) != data.size() || !file.commit()) { QMessageBox::warning(this, "Project Settings", "Cannot create small.project."); return; }
    }
    openDocument(path);
}
bool MainWindow::prepareProject()
{
    if (build_->isBusy() || debug_->isBusy() || closing_) return false;
    for (int i = 0; i < tabs_->count(); ++i) {
        auto* document = documentAt(i);
        if (document && project_.contains(document->filePath()) && document->document()->isModified() && !saveFile(document)) return false;
    }
    ProjectFolder next;
    QString error;
    if (!next.load(project_.root, &error)) { QMessageBox::warning(this, "Project Settings", error); return false; }
    project_ = next;
    projectRun_ = true;
    runDocument_.clear(); runName_ = project_.name; runSnapshot_.clear();
    output_->clear(); timing_->clear(); variables_->clear();
    rawDiagnostics_.clear(); friendlyDiagnostics_.clear(); showingRaw_ = false; rawAction_->setEnabled(false);
    for (int i = 0; i < tabs_->count(); ++i) if (auto* document = documentAt(i)) { document->clearError(); document->clearDebugLine(); }
    updateDiagnosticsLabel();
    return true;
}
void MainWindow::projectDiagnostic(const QString& raw, const QString& snapshot, const QString& file)
{
    if (project_.contains(file) && QFileInfo(file).isFile()) {
        openDocument(file);
        runDocument_ = findOpenDocument(file);
        runName_ = project_.name + " / " + QDir(project_.root).relativeFilePath(file);
    }
    const auto diagnostic = ExplainDiagnostic(raw, snapshot, file);
    showDiagnostic(raw, diagnostic.text, snapshot, diagnostic.line, false);
}
