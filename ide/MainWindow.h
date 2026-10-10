#pragma once

#include "ExampleCatalog.h"
#include "TutorialCatalog.h"
#include "ProjectFolder.h"
#include <QMap>

#include <QFont>
#include <QMainWindow>
#include <QPointer>
#include <QSet>

class QAction;
class QCloseEvent;
class QLabel;
class QPlainTextEdit;
class QTabWidget;
class BuildController;
class DebugController;
class QTreeWidget;
class EditorDocument;
class ExamplesBrowser;
class ApiBrowser;
class TutorialBrowser;
class CodeEditor;
class Highlighter;
class QDockWidget;
class QTimer;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);

    // Opens one independent program. Used by the Open action and tests; a
    // future example browser can open/copy documents without a project model.
    bool openDocument(const QString& path);
    bool openExample(const QString& id);
    bool loadStyleSheet(const QString& path, QString* error = nullptr);
    bool openProject(const QString& folder);
    bool closeProject();
    QString projectRoot() const { return project_.root; }

protected:
    void closeEvent(QCloseEvent* event) override;
    virtual bool showInFileExplorer(const QString& path);
    virtual bool showMsys2Terminal(const QString& directory);

private:
    QTabWidget* tabs_ = nullptr;
    QPlainTextEdit* output_ = nullptr;
    QLabel* diagnosticsLabel_ = nullptr;
    QLabel* timing_ = nullptr;
    BuildController* build_ = nullptr;
    DebugController* debug_ = nullptr;
    QTreeWidget* variables_ = nullptr;
    QAction* runAction_ = nullptr;
    QAction* publishAction_ = nullptr;
    QAction* stopAction_ = nullptr;
    QAction* debugAction_ = nullptr;
    QAction* continueAction_ = nullptr;
    QAction* stepOverAction_ = nullptr;
    QAction* stepIntoAction_ = nullptr;
    QAction* stepOutAction_ = nullptr;
    QAction* rawAction_ = nullptr;
    QAction* saveAction_ = nullptr;
    QAction* saveAsAction_ = nullptr;
    QAction* tryAction_ = nullptr;
    QWidget* exampleTools_ = nullptr;
    QLabel* exampleToolsLabel_ = nullptr;
    ExampleCatalog examples_;
    QPointer<ExamplesBrowser> examplesBrowser_;
    QPointer<ApiBrowser> apiBrowser_;
    TutorialCatalog tutorials_;
    QPointer<TutorialBrowser> tutorialBrowser_;
    QPointer<QWidget> welcome_;
    QPointer<CodeEditor> welcomePreview_;
    QPointer<Highlighter> welcomeHighlighter_;
    bool closing_ = false;
    bool confirmingClose_ = false;
    bool darkTheme_ = false;
    QFont editorFont_;
    QString styleSheetPath_;
    QString customStyleSheet_;
    int nextUntitledNumber_ = 1;
    ProjectFolder project_;
    QDockWidget* projectDock_ = nullptr;
    QTreeWidget* projectTree_ = nullptr;
    QLabel* projectHeading_ = nullptr;
    QLabel* projectStatus_ = nullptr;
    QAction* closeProjectAction_ = nullptr;
    QAction* openProjectAction_ = nullptr;
    QAction* newProjectAction_ = nullptr;
    QAction* projectSettingsAction_ = nullptr;
    QTimer* projectRefresh_ = nullptr;
    bool refreshingProject_ = false;
    bool projectRun_ = false;
    QMap<QString, QSet<int>> projectDebugBreakpoints_;
    void createProjectUi();
    void refreshProject();
    void openProjectDialog();
    void newProject();
    void newProjectFile(const QString& suffix, const QString& directory = QString());
    void newProjectFolder(const QString& directory);
    void addProjectFiles();
    void editProjectSettings();
    bool prepareProject();
    void projectDiagnostic(const QString& raw, const QString& snapshot, const QString& file);

    // Diagnostics belong to the document/snapshot passed to Run, NEVER to
    // whichever tab happens to be selected when a QProcess signal arrives.
    QPointer<EditorDocument> runDocument_;
    QSet<int> debugBreakpoints_;
    QString runName_;
    QString runSnapshot_;
    QString rawDiagnostics_;
    QString friendlyDiagnostics_;
    QString diagnosticRawLabel_ = "Show C++ Error";
    bool showingRaw_ = false;

    void createUi();
    void loadAppearance();
    void applyTheme(bool dark);
    void applyAppearance(EditorDocument* document);
    void chooseFont();
    void chooseStyleSheet();
    void refreshStyleSheets();
    void applyStyleSheetTo(QWidget* widget);
    void setTutorialLanguage(const QString& language);

    EditorDocument* currentDocument() const;
    EditorDocument* documentAt(int index) const;
    EditorDocument* addDocument(const QString& text, const QString& path = {},
                                const ExampleEntry* example = nullptr);
    void browseExamples();
    void browseApi();
    void browseTutorial();
    void tryTutorialCode(const QString& code, const QString& description);
    void tryExample();
    void closeTab(int index);
    void switchTab(int offset);
    void updateTitle();
    void updateTabTitle(EditorDocument* document);
    QString initialDirectory(const EditorDocument* document) const;
    QString documentsDirectory() const;
    QString creationDirectory(const QString& category);
    bool maybeSave(EditorDocument* document);
    bool maybeSaveAll();
    bool saveFile(EditorDocument* document);
    bool saveFileAs(EditorDocument* document);
    bool saveTo(EditorDocument* document, const QString& path);
    EditorDocument* findOpenDocument(const QString& path,
                                     const EditorDocument* except = nullptr) const;
    void newFile();
    void showWelcome();
    void updateWelcomeAppearance();
    void openFile();
    void run();
    void publish();
    void debug();
    void updateDebugActions();
    void updateDiagnosticsLabel();
    void showDiagnostic(const QString& raw, const QString& friendly,
                        const QString& snapshot, int line, bool runtime);
    void renderDiagnostics();
    void toggleDiagnostics();
    void appendOutput(const QString& text);
};
