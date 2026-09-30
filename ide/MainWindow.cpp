#include "MainWindow.h"
#include "BuildController.h"
#include "DebugController.h"
#include "EditorDocument.h"
#include "ExamplesBrowser.h"
#include "ApiBrowser.h"
#include "TutorialBrowser.h"
#include "Diagnostics.h"
#include "Highlighter.h"
#include "RuntimeDiagnostics.h"

#include <QAction>
#include <QActionGroup>
#include <QCloseEvent>
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QFontDialog>
#include <QHBoxLayout>
#include <QKeySequence>
#include <QLabel>
#include <QList>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QPlainTextEdit>
#include <QSaveFile>
#include <QSettings>
#include "SmallSettings.h"
#include <QSignalBlocker>
#include <QSplitter>
#include <QStandardPaths>
#include <QStatusBar>
#include <QTabWidget>
#include <QTextCursor>
#include <QTextDocument>
#include <QTimer>
#include <QToolBar>
#include <QToolButton>
#include <QTreeWidget>
#include <QVBoxLayout>

namespace
{
const char* DefaultProgram = R"(void SmallMain()
{
    Window window;
    window.Open(640, 480);

    double x = 320;
    StopWatch timer;

    while (window.IsOpen())
    {
        double dt = timer.Elapsed();
        timer.Reset();

        if (window.KeyDown(Key::Left) || window.KeyDown('A'))
            x = x - 200 * dt;

        if (window.KeyDown(Key::Right) || window.KeyDown('D'))
            x = x + 200 * dt;

        if (window.KeyPressed(Key::Space))
            PlaySound(Sound::Pop);

        window.Clear(Black);
        window.FillCircle(x, 240, 20, Yellow);
        window.DrawText(20, 20, "Small C++");
        window.DrawText(20, 50, "Arrow keys: move   Space: Pop");
        window.Show();
        Sleep(0.005);
    }
}
)";
}

namespace
{
const char* EmptyProgram = "void SmallMain()\n{\n    \n}\n";

QString normalizedPath(const QString& path)
{
    if (path.isEmpty()) return {};
    const QFileInfo info(path);
    const QString canonical = info.canonicalFilePath();
    if (!canonical.isEmpty()) return QDir::cleanPath(canonical);
    // Resolve the directory even for a new file that does not exist yet.
    const QFileInfo parent(info.absolutePath());
    const QString directory = parent.canonicalFilePath();
    return QDir::cleanPath(directory.isEmpty() ? info.absoluteFilePath()
                                              : QDir(directory).filePath(info.fileName()));
}

bool samePath(const QString& left, const QString& right)
{
    if (left.isEmpty() || right.isEmpty()) return false;
#ifdef Q_OS_WIN
    return normalizedPath(left).compare(normalizedPath(right), Qt::CaseInsensitive) == 0;
#else
    return normalizedPath(left) == normalizedPath(right);
#endif
}

QPalette editorPalette(QPalette palette, bool dark)
{
    palette.setColor(QPalette::Base, QColor(dark ? "#1e1f22" : "#ffffff"));
    palette.setColor(QPalette::Text, QColor(dark ? "#e6e6e6" : "#202124"));
    palette.setColor(QPalette::Window, QColor(dark ? "#292b2f" : "#f0f1f3"));
    palette.setColor(QPalette::AlternateBase, QColor(dark ? "#292b2f" : "#f3f4f6"));
    palette.setColor(QPalette::PlaceholderText, QColor(dark ? "#9ba0a8" : "#686868"));
    palette.setColor(QPalette::Highlight, QColor(dark ? "#35577b" : "#c5def5"));
    palette.setColor(QPalette::HighlightedText, QColor(dark ? "#ffffff" : "#162b40"));
    return palette;
}
}

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    editorFont_ = QFont("Consolas", 14);
    editorFont_.setStyleHint(QFont::Monospace);
    build_ = new BuildController(this);
    debug_ = new DebugController(this);
    tutorials_ = TutorialCatalog(SmallSettings().value(
        "tutorial/language", TutorialCatalog::defaultLanguage()).toString());

    // Small C++ is a learning environment, not a space-maximized professional IDE.
    // Keep navigation and actions comfortably readable/clickable.
    setStyleSheet(
        "QMenuBar { font-size: 11pt; spacing: 8px; }"
        "QMenuBar::item { padding: 5px 9px; }"
        "QMenu { font-size: 11pt; }"
        "QMenu::item { padding: 6px 24px 6px 12px; }"
        "QToolBar { spacing: 5px; }"
        "QToolBar QToolButton { font-size: 10.5pt; min-height: 30px; padding: 2px 7px; }"
        "QTabBar::tab { min-height: 28px; padding-left: 10px; padding-right: 10px; }"
        "#exampleActionBar { border-bottom: 1px solid palette(mid); }"
        "#exampleActionLabel { font-size: 11pt; font-weight: bold; }"
        "#exampleActionHint { font-size: 10pt; }"
        "#tryExampleButton { font-size: 11pt; font-weight: bold; padding: 5px 14px; }"
    );
    createUi();
    loadAppearance();
    addDocument(QString::fromUtf8(DefaultProgram));
    resize(1000, 750);
    updateTitle();

    connect(build_, &BuildController::busyChanged, this, [this](bool busy) {
        updateDebugActions();
        if (closing_ && !busy && !debug_->isBusy()) QTimer::singleShot(0, this, [this] { close(); });
    });
    connect(build_, &BuildController::phaseChanged, this, [this](const QString& text) {
        statusBar()->showMessage(text);
    });
    connect(build_, &BuildController::textOutput, this, &MainWindow::appendOutput);
    connect(build_, &BuildController::buildTiming, this, [this](qint64 compile, qint64 link) {
        timing_->setText(QString("Compile %1 s  |  Link %2 s  |  Runtime prebuilt")
            .arg(compile / 1000.0, 0, 'f', 2).arg(link / 1000.0, 0, 'f', 2));
    });
    connect(build_, &BuildController::buildError, this,
        [this](const QString& raw, const QString& snapshot, const QString& file) {
            const SmallDiagnostic diagnostic = ExplainDiagnostic(raw, snapshot, file);
            showDiagnostic(raw, diagnostic.text, snapshot, diagnostic.line, false);
        });
    connect(build_, &BuildController::runtimeError, this,
        [this](const QString& raw, const QString& snapshot) {
            const SmallRuntimeDiagnostic diagnostic = ExplainRuntimeError(raw, snapshot);
            showDiagnostic(raw, diagnostic.text, snapshot, diagnostic.line, true);
            statusBar()->showMessage("Runtime error");
        });
    connect(build_, &BuildController::finished, this, [this](int code, bool stopped) {
        if (stopped) statusBar()->showMessage("Stopped");
        else if (code == 0) statusBar()->showMessage("Finished");
    });
    connect(debug_, &DebugController::busyChanged, this, [this](bool) { updateDebugActions(); });
    connect(debug_, &DebugController::phaseChanged, this, [this](const QString& text) {
        statusBar()->showMessage(text);
        // Debug startup can involve compile, link, and GDB startup.  Keep the
        // current phase visible in Diagnostics so a learner never sees an
        // apparently unresponsive Debug button.
        if (!text.isEmpty()) {
            output_->appendPlainText(text);
        }
    });
    connect(debug_, &DebugController::buildError, this,
        [this](const QString& raw, const QString& snapshot, const QString& file) {
            const SmallDiagnostic diagnostic = ExplainDiagnostic(raw, snapshot, file);
            showDiagnostic(raw, diagnostic.text, snapshot, diagnostic.line, false);
        });
    connect(debug_, &DebugController::stoppedAt, this, [this](int line) {
        if (runDocument_) runDocument_->setDebugLine(line);
        updateDebugActions();
    });
    connect(debug_, &DebugController::variablesChanged, this,
        [this](const QList<DebugVariable>& locals, const QList<DebugVariable>& globals) {
            variables_->clear();
            auto* l = new QTreeWidgetItem(variables_, {"Locals", ""});
            for (const auto& v : locals) new QTreeWidgetItem(l, {v.name, v.value});
            auto* g = new QTreeWidgetItem(variables_, {"Globals", ""});
            for (const auto& v : globals) new QTreeWidgetItem(g, {v.name, v.value});
            variables_->expandAll();
        });
    connect(debug_, &DebugController::finished, this, [this] {
        if (runDocument_) runDocument_->clearDebugLine();
        updateDebugActions();
        if (closing_ && !build_->isBusy()) QTimer::singleShot(0, this, [this] { close(); });
    });
}

void MainWindow::createUi()
{
    auto* toolbar = addToolBar("Main");
    toolbar->setMovable(false);
    auto* fileMenu = menuBar()->addMenu("&File");
    auto* learnMenu = menuBar()->addMenu("&Learn");
    learnMenu->setObjectName("menuLearn");
    auto* tutorialAction = learnMenu->addAction("Tutorial...");
    tutorialAction->setObjectName("actionTutorial");
    tutorialAction->setToolTip("Read a lesson and try its code in a new tab.");
    connect(tutorialAction, &QAction::triggered, this, &MainWindow::browseTutorial);
    auto* examplesAction = learnMenu->addAction("Examples...");
    auto* settingsMenu = menuBar()->addMenu("&Settings");
    examplesAction->setObjectName("actionExamples");
    examplesAction->setToolTip("Browse built-in reference examples and small programs.");
    connect(examplesAction, &QAction::triggered, this, &MainWindow::browseExamples);
    auto* apiAction = learnMenu->addAction("API Reference...");
    apiAction->setObjectName("actionApiReference");
    apiAction->setToolTip("Browse the Small API using learner-friendly parameters and return values.");
    connect(apiAction, &QAction::triggered, this, &MainWindow::browseApi);
    auto* themeMenu = settingsMenu->addMenu("Theme");
    auto* lightAction = themeMenu->addAction("Light");
    auto* darkAction = themeMenu->addAction("Dark");
    lightAction->setObjectName("actionThemeLight");
    darkAction->setObjectName("actionThemeDark");
    lightAction->setCheckable(true);
    darkAction->setCheckable(true);
    auto* themeGroup = new QActionGroup(this);
    themeGroup->setExclusive(true);
    themeGroup->addAction(lightAction);
    themeGroup->addAction(darkAction);
    auto* fontAction = settingsMenu->addAction("Font...");
    fontAction->setObjectName("actionFont");
    auto* languageMenu = settingsMenu->addMenu("Tutorial Language");
    languageMenu->setObjectName("menuTutorialLanguage");
    auto* languageGroup = new QActionGroup(this);
    languageGroup->setExclusive(true);
    const QString currentTutorialLanguage = SmallSettings().value(
        "tutorial/language", TutorialCatalog::defaultLanguage()).toString();
    for (const auto& language : TutorialCatalog::languages())
    {
        auto* action = languageMenu->addAction(language.second);
        action->setCheckable(true);
        action->setData(language.first);
        action->setChecked(language.first == currentTutorialLanguage);
        languageGroup->addAction(action);
        connect(action, &QAction::triggered, this,
                [this, code=language.first] { setTutorialLanguage(code); });
    }
    connect(lightAction, &QAction::triggered, this, [this] { applyTheme(false); });
    connect(darkAction, &QAction::triggered, this, [this] { applyTheme(true); });
    connect(fontAction, &QAction::triggered, this, &MainWindow::chooseFont);
    connect(settingsMenu, &QMenu::aboutToShow, this, [this, lightAction, darkAction] {
        lightAction->setChecked(!darkTheme_);
        darkAction->setChecked(darkTheme_);
    });

    auto addFileAction = [&](const QString& label, const QString& name, QKeySequence key,
                             bool onToolbar) {
        auto* action = new QAction(label, this);
        action->setObjectName(name);
        action->setShortcut(key);
        action->setShortcutContext(Qt::WindowShortcut);
        fileMenu->addAction(action);
        if (onToolbar) toolbar->addAction(action);
        return action;
    };
    auto* newAction = addFileAction("New", "actionNew", QKeySequence::New, true);
    auto* openAction = addFileAction("Open", "actionOpen", QKeySequence::Open, true);
    auto* saveAction = addFileAction("Save", "actionSave", QKeySequence::Save, true);
    auto* saveAsAction = addFileAction("Save As...", "actionSaveAs", QKeySequence::SaveAs, false);
    auto* closeAction = addFileAction("Close Tab", "actionCloseTab", QKeySequence::Close, false);
    saveAction_ = saveAction;
    saveAsAction_ = saveAsAction;
    fileMenu->addSeparator();
    auto* quitAction = fileMenu->addAction("Exit");
    quitAction->setShortcut(QKeySequence::Quit);
    quitAction->setObjectName("actionQuit");

    toolbar->addSeparator();
    runAction_ = toolbar->addAction("Run");
    runAction_->setObjectName("actionRun");
    runAction_->setShortcut(QKeySequence(Qt::Key_F5));
    runAction_->setToolTip("Run the current tab (F5). Each tab is a separate program.");
    debugAction_ = toolbar->addAction("Debug");
    debugAction_->setObjectName("actionDebug");
    debugAction_->setShortcut(QKeySequence(Qt::Key_F6));
    debugAction_->setToolTip("Start debugging the current tab (F6).");
    continueAction_ = toolbar->addAction("Continue");
    stepOverAction_ = toolbar->addAction("Over");
    stepIntoAction_ = toolbar->addAction("Into");
    stepOutAction_ = toolbar->addAction("Out");
    continueAction_->setShortcut(QKeySequence(Qt::Key_F5));
    stepOverAction_->setShortcut(QKeySequence(Qt::Key_F10));
    stepIntoAction_->setShortcut(QKeySequence(Qt::Key_F11));
    stepOutAction_->setShortcut(QKeySequence(Qt::SHIFT | Qt::Key_F11));
    stopAction_ = toolbar->addAction("Stop");
    stopAction_->setObjectName("actionStop");
    stopAction_->setShortcut(QKeySequence(Qt::SHIFT | Qt::Key_F5));
    stopAction_->setEnabled(false);
    toolbar->addSeparator();
    rawAction_ = toolbar->addAction("Show C++ Error");
    rawAction_->setObjectName("actionRawDiagnostic");
    rawAction_->setEnabled(false);

    tabs_ = new QTabWidget;
    tabs_->setObjectName("documentTabs");
    tabs_->setDocumentMode(true);
    tabs_->setTabsClosable(true);
    tabs_->setMovable(true);
    tabs_->setUsesScrollButtons(true);
    tabs_->setElideMode(Qt::ElideMiddle);

    // This compact corner appears only for a read-only example tab. Normal
    // files keep the same uncluttered editor layout as before.
    tryAction_ = new QAction("Try", this);
    tryAction_->setObjectName("actionTryExample");
    tryAction_->setToolTip("Make an editable copy in a new, unsaved tab. The example is not changed.");
    connect(tryAction_, &QAction::triggered, this, &MainWindow::tryExample);
    exampleTools_ = new QWidget;
    exampleTools_->setObjectName("exampleTabTools");
    auto* toolsLayout = new QHBoxLayout(exampleTools_);
    toolsLayout->setContentsMargins(8, 0, 4, 0);
    toolsLayout->addWidget(new QLabel("Read-only example"));
    auto* tryButton = new QToolButton;
    tryButton->setObjectName("tryExampleButton");
    tryButton->setDefaultAction(tryAction_);
    tryButton->setToolButtonStyle(Qt::ToolButtonTextOnly);
    toolsLayout->addWidget(tryButton);
    tabs_->setCornerWidget(exampleTools_, Qt::TopRightCorner);
    exampleTools_->hide();

    // Actions, not editor key handlers: Ctrl+Tab must never insert spaces.
    auto* nextAction = new QAction("Next Tab", this);
    nextAction->setObjectName("actionNextTab");
    nextAction->setShortcut(QKeySequence("Ctrl+Tab"));
    addAction(nextAction);
    auto* previousAction = new QAction("Previous Tab", this);
    previousAction->setObjectName("actionPreviousTab");
    previousAction->setShortcut(QKeySequence("Ctrl+Shift+Tab"));
    addAction(previousAction);
    connect(nextAction, &QAction::triggered, this, [this] { switchTab(1); });
    connect(previousAction, &QAction::triggered, this, [this] { switchTab(-1); });

    output_ = new QPlainTextEdit;
    output_->setObjectName("output");
    output_->setReadOnly(true);
    output_->setFont(editorFont_);
    output_->setMaximumBlockCount(4000);
    output_->setPlaceholderText("Compile and runtime messages appear here.");
    diagnosticsLabel_ = new QLabel("Diagnostics");
    diagnosticsLabel_->setObjectName("diagnosticsLabel");
    diagnosticsLabel_->setTextFormat(Qt::PlainText);
    auto* diagnostics = new QWidget;
    auto* layout = new QVBoxLayout(diagnostics);
    layout->setContentsMargins(0, 4, 0, 0);
    layout->addWidget(diagnosticsLabel_);
    layout->addWidget(output_);
    auto* documentArea = new QWidget;
    auto* documentLayout = new QVBoxLayout(documentArea);
    documentLayout->setContentsMargins(0, 0, 0, 0);
    documentLayout->setSpacing(0);
    documentLayout->addWidget(exampleTools_);
    documentLayout->addWidget(tabs_, 1);

    variables_ = new QTreeWidget;
    variables_->setObjectName("debugVariables");
    variables_->setHeaderLabels({"Variable", "Value"});
    variables_->setRootIsDecorated(true);
    auto* bottomTabs = new QTabWidget;
    bottomTabs->setObjectName("bottomTabs");
    bottomTabs->addTab(diagnostics, "Diagnostics");
    bottomTabs->addTab(variables_, "Variables");
    auto* splitter = new QSplitter(Qt::Vertical);
    splitter->addWidget(documentArea);
    splitter->addWidget(bottomTabs);
    splitter->setSizes({510, 170});
    setCentralWidget(splitter);
    timing_ = new QLabel;
    timing_->setObjectName("buildTiming");
    statusBar()->addPermanentWidget(timing_);
    statusBar()->showMessage("Ready — Small C++ IDE v0.66");

    connect(tabs_, &QTabWidget::currentChanged, this, [this](int) { updateTitle(); });
    connect(tabs_, &QTabWidget::tabCloseRequested, this, &MainWindow::closeTab);
    connect(newAction, &QAction::triggered, this, &MainWindow::newFile);
    connect(openAction, &QAction::triggered, this, &MainWindow::openFile);
    connect(saveAction, &QAction::triggered, this, [this] { saveFile(currentDocument()); });
    connect(saveAsAction, &QAction::triggered, this, [this] { saveFileAs(currentDocument()); });
    connect(closeAction, &QAction::triggered, this, [this] { closeTab(tabs_->currentIndex()); });
    connect(quitAction, &QAction::triggered, this, [this] { close(); });
    connect(runAction_, &QAction::triggered, this, &MainWindow::run);
    connect(debugAction_, &QAction::triggered, this, &MainWindow::debug);
    connect(continueAction_, &QAction::triggered, debug_, &DebugController::continueRun);
    connect(stepOverAction_, &QAction::triggered, debug_, &DebugController::stepOver);
    connect(stepIntoAction_, &QAction::triggered, debug_, &DebugController::stepInto);
    connect(stepOutAction_, &QAction::triggered, debug_, &DebugController::stepOut);
    connect(stopAction_, &QAction::triggered, this, [this]{ if(debug_->isBusy()) debug_->stop(); else build_->stop(); });
    updateDebugActions();
    connect(rawAction_, &QAction::triggered, this, &MainWindow::toggleDiagnostics);
}

EditorDocument* MainWindow::documentAt(int index) const
{
    return tabs_ ? qobject_cast<EditorDocument*>(tabs_->widget(index)) : nullptr;
}

EditorDocument* MainWindow::currentDocument() const
{
    return tabs_ ? qobject_cast<EditorDocument*>(tabs_->currentWidget()) : nullptr;
}

EditorDocument* MainWindow::addDocument(const QString& text, const QString& path,
                                        const ExampleEntry* example)
{
    QString untitledName;
    if (path.isEmpty() && !example)
    {
        untitledName = nextUntitledNumber_ == 1 ? "Untitled.cpp"
            : QString("Untitled-%1.cpp").arg(nextUntitledNumber_);
        ++nextUntitledNumber_;
    }
    auto* document = new EditorDocument(text, path, untitledName);
    if (example) document->markAsExample(example->id, example->title, example->sourceName);
    applyAppearance(document);
    connect(document->document(), &QTextDocument::modificationChanged, this,
        [this, document](bool) { updateTabTitle(document); updateTitle(); });
    connect(document, &QPlainTextEdit::textChanged, this, [this, document] {
        document->clearError();
        if (runDocument_ == document && !friendlyDiagnostics_.isEmpty()) renderDiagnostics();
    });
    connect(document, &CodeEditor::breakpointsChanged, this, [this, document] {
        if (!debug_->isBusy() || runDocument_ != document) return;
        const QSet<int> now = document->breakpoints();
        for (int line : now - debugBreakpoints_)
            debug_->setBreakpoint(line, true);
        for (int line : debugBreakpoints_ - now)
            debug_->setBreakpoint(line, false);
        debugBreakpoints_ = now;
    });
    tabs_->addTab(document, document->displayName());
    updateTabTitle(document);
    tabs_->setCurrentWidget(document);
    document->setFocus();
    updateTitle();
    return document;
}

void MainWindow::updateTabTitle(EditorDocument* document)
{
    if (!document) return;
    const int index = tabs_->indexOf(document);
    if (index < 0) return;
    QString text = document->displayName();
    if (!document->isExample() && document->document()->isModified()) text += " *";
    tabs_->setTabText(index, text.replace('&', "&&"));
    if (document->isExample())
        tabs_->setTabToolTip(index, document->displayName() +
            "\nBuilt-in source (read-only). Run it, or choose Try to make your own copy.");
    else
        tabs_->setTabToolTip(index, document->filePath().isEmpty()
            ? document->displayName() + " — not saved yet" : document->filePath());
}

void MainWindow::updateTitle()
{
    EditorDocument* document = currentDocument();
    QString title = "Small C++";
    if (document)
    {
        title = document->displayName();
        if (!document->isExample() && document->document()->isModified()) title += " *";
        title += " - Small C++";
    }
    setWindowTitle(title);
    if (runAction_) updateDebugActions();
    const bool example = document && document->isExample();
    if (saveAction_) saveAction_->setEnabled(document && !example && !closing_);
    if (saveAsAction_)
    {
        saveAsAction_->setEnabled(document && !closing_);
        saveAsAction_->setText(example ? "Save a Copy..." : "Save As...");
    }
    if (tryAction_) tryAction_->setEnabled(example && !closing_ && !confirmingClose_);
    if (exampleTools_) exampleTools_->setVisible(example);
    if (exampleToolsLabel_)
        exampleToolsLabel_->setText(example ? "Example: " + document->exampleTitle() : QString{});
}

void MainWindow::switchTab(int offset)
{
    const int count = tabs_->count();
    if (count < 2) return;
    tabs_->setCurrentIndex((tabs_->currentIndex() + offset + count) % count);
    if (auto* document = currentDocument()) document->setFocus();
}

QString MainWindow::initialDirectory(const EditorDocument* document) const
{
    if (document && !document->filePath().isEmpty())
        return QFileInfo(document->filePath()).absolutePath();
    const QString last = SmallSettings().value("files/lastDirectory").toString();
    if (!last.isEmpty() && QDir(last).exists()) return last;
    const QString path = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    return QDir(path).exists() ? path : QDir::homePath();
}

EditorDocument* MainWindow::findOpenDocument(const QString& path, const EditorDocument* except) const
{
    for (int index = 0; index < tabs_->count(); ++index)
    {
        auto* document = documentAt(index);
        if (document && document != except && samePath(document->filePath(), path))
            return document;
    }
    return nullptr;
}

bool MainWindow::saveTo(EditorDocument* document, const QString& path)
{
    if (!document || tabs_->indexOf(document) < 0 || path.isEmpty()) return false;
    const QString destination = normalizedPath(path);
    if (findOpenDocument(destination, document))
    {
        QMessageBox::warning(this, "File already open",
            "This file is already open in another tab:\n" + destination +
            "\n\nSwitch to that tab, or choose another filename. No file was changed.");
        return false;
    }
    QSaveFile file(destination);
    const QByteArray bytes = document->toPlainText().toUtf8();
    if (!file.open(QIODevice::WriteOnly) || file.write(bytes) != bytes.size() || !file.commit())
    {
        QMessageBox::critical(this, "Could not save", destination + "\n\n" + file.errorString());
        return false;
    }
    if (document->isExample())
    {
        // Save a Copy never turns the built-in tab into a writable file.
        document = addDocument(document->toPlainText(), normalizedPath(destination));
    }
    else
    {
        document->setFilePath(normalizedPath(destination));
        document->document()->setModified(false);
        updateTabTitle(document);
        updateTitle();
    }
    SmallSettings().setValue("files/lastDirectory",
                                                  QFileInfo(destination).absolutePath());
    statusBar()->showMessage("Saved " + document->displayName(), 3000);
    return true;
}

bool MainWindow::saveFile(EditorDocument* document)
{
    if (!document || document->isExample()) return false;
    return document->filePath().isEmpty() ? saveFileAs(document)
                                         : saveTo(document, document->filePath());
}

bool MainWindow::saveFileAs(EditorDocument* document)
{
    if (!document) return false;
    // Remember the document, not the current tab index, across a modal dialog.
    QPointer<EditorDocument> target(document);
    QFileDialog dialog(this, "Save C++ program", initialDirectory(document),
                       "C++ source (*.cpp);;All files (*)");
    dialog.setObjectName("saveFileDialog");
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.setDefaultSuffix("cpp");
    if (document->isExample()) dialog.selectFile(document->exampleSourceName());
    else dialog.selectFile(document->displayName());
    if (qEnvironmentVariableIsSet("SMALL_TEST_DIALOGS"))
        dialog.setOption(QFileDialog::DontUseNativeDialog);
    if (dialog.exec() != QDialog::Accepted || dialog.selectedFiles().isEmpty() || !target)
        return false;
    return saveTo(target, dialog.selectedFiles().first());
}

bool MainWindow::maybeSave(EditorDocument* document)
{
    if (!document || document->isExample() || !document->document()->isModified()) return true;
    QPointer<EditorDocument> target(document);
    tabs_->setCurrentWidget(document);
    QMessageBox box(QMessageBox::Warning, "Unsaved changes",
        QString("Save changes to \"%1\"?").arg(document->displayName()),
        QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel, this);
    box.setObjectName("unsavedChangesDialog");
    box.setInformativeText("Your changes will be lost if you do not save them.");
    box.setDefaultButton(QMessageBox::Save);
    box.setEscapeButton(QMessageBox::Cancel);
    const auto choice = static_cast<QMessageBox::StandardButton>(box.exec());
    if (!target) return true;
    if (choice == QMessageBox::Save) return saveFile(target);
    // Do not mark Discard as clean here: a later tab may cancel app shutdown.
    return choice == QMessageBox::Discard;
}

bool MainWindow::maybeSaveAll()
{
    QList<QPointer<EditorDocument>> documents;
    for (int index = 0; index < tabs_->count(); ++index) documents.append(documentAt(index));
    // No tabs are removed until EVERY prompt succeeds. Cancel keeps all text.
    for (const auto& document : documents)
        if (document && !maybeSave(document)) return false;
    return true;
}

void MainWindow::closeTab(int index)
{
    if (closing_ || confirmingClose_) return;
    QPointer<EditorDocument> document(documentAt(index));
    if (!document) return;
    confirmingClose_ = true;
    const bool approved = maybeSave(document);
    confirmingClose_ = false;
    if (!approved || !document) return;
    // Look the position up again; the page is the stable identity.
    index = tabs_->indexOf(document);
    if (index < 0) return;
    const bool wasRunDocument = runDocument_ == document;
    tabs_->removeTab(index);
    delete document.data();
    if (tabs_->count() == 0) addDocument(QString::fromUtf8(EmptyProgram));
    updateTitle();
    if (wasRunDocument)
    {
        updateDiagnosticsLabel();
        if (!friendlyDiagnostics_.isEmpty()) renderDiagnostics();
    }
    if (auto* current = currentDocument()) current->setFocus();
}

void MainWindow::newFile()
{
    if (!closing_ && !confirmingClose_) addDocument(QString::fromUtf8(EmptyProgram));
}

bool MainWindow::openDocument(const QString& path)
{
    if (path.isEmpty() || closing_ || confirmingClose_) return false;
    const QString absolute = normalizedPath(path);
    if (auto* existing = findOpenDocument(absolute))
    {
        tabs_->setCurrentWidget(existing);
        existing->setFocus();
        return true; // Keep unsaved edits; do not reload from disk.
    }
    QFile file(absolute);
    if (!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::critical(this, "Could not open", absolute + "\n\n" + file.errorString());
        return false;
    }
    const QByteArray bytes = file.readAll();
    if (file.error() != QFileDevice::NoError)
    {
        QMessageBox::critical(this, "Could not read", absolute + "\n\n" + file.errorString());
        return false;
    }
    addDocument(QString::fromUtf8(bytes), absolute);
    SmallSettings().setValue("files/lastDirectory",
                                                  QFileInfo(absolute).absolutePath());
    return true;
}

void MainWindow::openFile()
{
    const QString path = QFileDialog::getOpenFileName(this, "Open C++ program",
        initialDirectory(currentDocument()), "C++ source (*.cpp);;All files (*)");
    if (!path.isEmpty()) openDocument(path);
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    if (confirmingClose_) { event->ignore(); return; }
    if (!closing_)
    {
        confirmingClose_ = true;
        const bool approved = maybeSaveAll();
        confirmingClose_ = false;
        if (!approved) { event->ignore(); return; }
    }
    if (build_->isBusy() || debug_->isBusy())
    {
        closing_ = true;
        setEnabled(false);
        if (debug_->isBusy()) debug_->stop();
        if (build_->isBusy()) build_->stop();
        event->ignore();
        return;
    }
    if (tutorialBrowser_) tutorialBrowser_->close();
    if (examplesBrowser_) examplesBrowser_->close();
    event->accept();
}

void MainWindow::loadAppearance()
{
    auto settings = SmallSettings();
    darkTheme_ = settings.value("appearance/dark", false).toBool();
    if (settings.contains("appearance/font"))
        editorFont_ = settings.value("appearance/font").value<QFont>();
    output_->setFont(editorFont_);
    applyTheme(darkTheme_);
}

void MainWindow::applyAppearance(EditorDocument* document)
{
    if (!document) return;
    const bool modified = document->document()->isModified();
    document->setFont(editorFont_);
    document->setTabStopDistance(document->fontMetrics().horizontalAdvance(' ') * 4);
    document->setPalette(editorPalette(document->palette(), darkTheme_));
    document->setDarkTheme(darkTheme_);
    document->highlighter()->setDark(darkTheme_);
    document->document()->setModified(modified);
    document->viewport()->update();
}

void MainWindow::applyTheme(bool dark)
{
    darkTheme_ = dark;
    output_->setPalette(editorPalette(output_->palette(), dark));
    for (int index = 0; index < tabs_->count(); ++index) applyAppearance(documentAt(index));
    if (examplesBrowser_)
        examplesBrowser_->setAppearance(editorFont_, editorPalette(output_->palette(), dark), dark);
    if (tutorialBrowser_)
        tutorialBrowser_->setAppearance(editorFont_, editorPalette(output_->palette(), dark), dark);
    if (apiBrowser_)
        apiBrowser_->setAppearance(editorFont_, editorPalette(output_->palette(), dark), dark);
    SmallSettings().setValue("appearance/dark", dark);
}

void MainWindow::chooseFont()
{
    bool ok = false;
    const QFont font = QFontDialog::getFont(&ok, editorFont_, this, "Editor Font",
                                           QFontDialog::MonospacedFonts);
    if (!ok) return;
    editorFont_ = font;
    output_->setFont(font);
    for (int index = 0; index < tabs_->count(); ++index) applyAppearance(documentAt(index));
    if (examplesBrowser_)
        examplesBrowser_->setAppearance(editorFont_, editorPalette(output_->palette(), darkTheme_), darkTheme_);
    if (tutorialBrowser_)
        tutorialBrowser_->setAppearance(editorFont_, editorPalette(output_->palette(), darkTheme_), darkTheme_);
    SmallSettings().setValue("appearance/font", font);
}

void MainWindow::run()
{
    auto* document = currentDocument();
    if (!document || build_->isBusy() || closing_) return;
    runDocument_ = document;
    runName_ = document->displayName();
    runSnapshot_ = document->toPlainText();
    output_->clear();
    timing_->clear();
    document->clearError();
    rawDiagnostics_.clear();
    friendlyDiagnostics_.clear();
    showingRaw_ = false;
    diagnosticRawLabel_ = "Show C++ Error";
    rawAction_->setText(diagnosticRawLabel_);
    rawAction_->setEnabled(false);
    updateDiagnosticsLabel();
    if (document->isExample())
        appendOutput("Built-in example: files created by the program are temporary. "
                     "Use Try and save your copy in your own folder to keep data files.\n\n");
    build_->start(runSnapshot_, document->filePath(),
                  document->isExample() ? document->exampleSourceName() : runName_);
}

void MainWindow::debug()
{
    auto* document=currentDocument();
    if(!document || build_->isBusy() || debug_->isBusy() || closing_) return;
    runDocument_=document; runName_=document->displayName(); runSnapshot_=document->toPlainText();
    debugBreakpoints_ = document->breakpoints();
    output_->clear(); variables_->clear(); document->clearError(); document->clearDebugLine();
    debug_->start(runSnapshot_, document->filePath(),
                  document->isExample()?document->exampleSourceName():runName_,
                  document->breakpoints());
    updateDebugActions();
}

void MainWindow::updateDebugActions()
{
    const bool building=build_->isBusy();
    const bool debugging=debug_->isBusy();
    const bool paused=debug_->isStopped();
    const bool has=currentDocument()!=nullptr;
    runAction_->setEnabled(has && !building && !debugging && !closing_);
    debugAction_->setEnabled(has && !building && !debugging && !closing_);
    stopAction_->setEnabled((building||debugging) && !closing_);
    continueAction_->setEnabled(paused && !closing_);
    stepOverAction_->setEnabled(paused && !closing_);
    stepIntoAction_->setEnabled(paused && !closing_);
    stepOutAction_->setEnabled(paused && !closing_);
}

void MainWindow::updateDiagnosticsLabel()
{
    if (runName_.isEmpty()) diagnosticsLabel_->setText("Diagnostics");
    else diagnosticsLabel_->setText("Diagnostics — " + runName_ +
        (runDocument_ ? QString(" (last run)") : QString(" (last run, closed tab)")));
}

void MainWindow::showDiagnostic(const QString& raw, const QString& friendly,
                                const QString& snapshot, int line, bool runtime)
{
    rawDiagnostics_ = raw;
    friendlyDiagnostics_ = friendly;
    runSnapshot_ = snapshot;
    showingRaw_ = false;
    diagnosticRawLabel_ = runtime ? "Show Original Error" : "Show C++ Error";
    rawAction_->setText(diagnosticRawLabel_);
    rawAction_->setEnabled(!raw.isEmpty());
    // A tab with identical text is NOT necessarily the originating document.
    if (runDocument_ && runDocument_->toPlainText() == snapshot && line > 0)
        runDocument_->markErrorLine(line);
    renderDiagnostics();
}

void MainWindow::renderDiagnostics()
{
    QString text = showingRaw_ ? rawDiagnostics_ : friendlyDiagnostics_;
    if (!showingRaw_ && !friendlyDiagnostics_.isEmpty())
    {
        if (!runDocument_)
            text += "\n\nThe source tab was closed. This message refers to the snapshot used by Run.";
        else if (runDocument_->toPlainText() != runSnapshot_)
            text += "\n\nThis document changed after Run was pressed. The message refers to the earlier snapshot; no line is highlighted.";
    }
    updateDiagnosticsLabel();
    output_->setPlainText(text);
}

void MainWindow::toggleDiagnostics()
{
    showingRaw_ = !showingRaw_;
    rawAction_->setText(showingRaw_ ? "Show Simple Error" : diagnosticRawLabel_);
    renderDiagnostics();
}

void MainWindow::appendOutput(const QString& text)
{
    output_->moveCursor(QTextCursor::End);
    output_->insertPlainText(text);
    output_->ensureCursorVisible();
}

void MainWindow::browseApi()
{
    if (closing_ || confirmingClose_) return;
    if (!apiBrowser_)
    {
        apiBrowser_ = new ApiBrowser(nullptr);
        connect(this, &QObject::destroyed, apiBrowser_.data(), &QObject::deleteLater);
    }
    apiBrowser_->setAppearance(editorFont_, editorPalette(output_->palette(), darkTheme_), darkTheme_);
    apiBrowser_->show();
    apiBrowser_->raise();
    apiBrowser_->activateWindow();
}

void MainWindow::browseExamples()
{
    if (closing_ || confirmingClose_) return;
    if (!examplesBrowser_)
    {
        examplesBrowser_ = new ExamplesBrowser(examples_, nullptr);
        connect(this, &QObject::destroyed, examplesBrowser_.data(), &QObject::deleteLater);
        connect(examplesBrowser_.data(), &ExamplesBrowser::exampleRequested, this,
                [this](const QString& id) { openExample(id); });
    }
    examplesBrowser_->setAppearance(editorFont_, editorPalette(output_->palette(), darkTheme_), darkTheme_);
    examplesBrowser_->show();
    examplesBrowser_->raise();
    examplesBrowser_->activateWindow();
}

bool MainWindow::openExample(const QString& id)
{
    if (closing_ || confirmingClose_) return false;
    const ExampleEntry* entry = examples_.find(id);
    if (!entry) return false;
    for (int index = 0; index < tabs_->count(); ++index)
    {
        auto* document = documentAt(index);
        if (document && document->exampleId() == id)
        {
            tabs_->setCurrentWidget(document);
            document->setFocus();
            return true;
        }
    }
    addDocument(entry->code, {}, entry);
    return true;
}

void MainWindow::tryExample()
{
    if (closing_ || confirmingClose_) return;
    const auto* example = currentDocument();
    if (!example || !example->isExample()) return;
    const QString code = example->toPlainText();
    const QString name = example->displayName();
    auto* copy = addDocument(code);
    // A new copy has not been saved; closing it should offer to save it even
    // before the first keystroke. No file is written by Try itself.
    copy->document()->setModified(true);
    statusBar()->showMessage("Editable copy of " + name, 4000);
}

void MainWindow::setTutorialLanguage(const QString& language)
{
    SmallSettings().setValue("tutorial/language", language);
    tutorials_ = TutorialCatalog(language);
    if (tutorialBrowser_) {
        tutorialBrowser_->close();
        tutorialBrowser_->deleteLater();
        tutorialBrowser_.clear();
    }
    statusBar()->showMessage("Tutorial language changed", 2500);
}

void MainWindow::browseTutorial()
{
    if (closing_ || confirmingClose_) return;
    if (!tutorialBrowser_)
    {
        tutorialBrowser_ = new TutorialBrowser(tutorials_, nullptr);
        connect(this, &QObject::destroyed, tutorialBrowser_.data(), &QObject::deleteLater);
        connect(tutorialBrowser_.data(), &TutorialBrowser::tryRequested,
                this, &MainWindow::tryTutorialCode);
        connect(tutorialBrowser_.data(), &TutorialBrowser::exampleRequested,
                this, [this](const QString& id) {
                    if (openExample(id)) { raise(); activateWindow(); }
                });
    }
    tutorialBrowser_->setAppearance(editorFont_, editorPalette(output_->palette(), darkTheme_), darkTheme_);
    tutorialBrowser_->show();
    tutorialBrowser_->raise();
    tutorialBrowser_->activateWindow();
}

void MainWindow::tryTutorialCode(const QString& code, const QString& description)
{
    if (closing_ || confirmingClose_ || code.trimmed().isEmpty()) return;
    // A lesson is a textbook, not a document. Each Try creates a new unsaved
    // workspace; never overwrite a learner's work or mutate embedded content.
    auto* copy = addDocument(code);
    copy->document()->setModified(true);
    statusBar()->showMessage("Tutorial copy: " + description, 6000);
    raise();
    activateWindow();
    copy->setFocus();
}
