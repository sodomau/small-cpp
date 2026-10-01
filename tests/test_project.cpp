#include "ProjectFolder.h"
#include "BuildController.h"
#include "DebugController.h"
#include "MainWindow.h"
#include "EditorDocument.h"
#include "SmallSettings.h"
#include "SmallBuildConfig.h"
#include <QAction>
#include <QApplication>
#include <QDir>
#include <QDockWidget>
#include <QFile>
#include <QFontDatabase>
#include <QJsonDocument>
#include <QJsonArray>
#include <QLabel>
#include <QMessageBox>
#include <QPlainTextEdit>
#include <QProcess>
#include <QProcessEnvironment>
#include <QSignalSpy>
#include <QTabWidget>
#include <QTemporaryDir>
#include <QTest>
#include <QTextDocument>
#include <QTimer>
#include <QTreeWidget>

class ProjectTests : public QObject
{
    Q_OBJECT
    QTemporaryDir settings_;
    static void write(const QString& path, const QByteArray& contents)
    {
        QVERIFY(QDir().mkpath(QFileInfo(path).absolutePath()));
        QFile file(path); QVERIFY(file.open(QIODevice::WriteOnly)); QCOMPARE(file.write(contents), qint64(contents.size()));
    }
    static QByteArray read(const QString& path) { QFile file(path); if (!file.open(QIODevice::ReadOnly)) return {}; return file.readAll(); }
    static ProjectFolder load(const QString& root)
    {
        ProjectFolder folder; QString error;
        if (!folder.load(root, &error)) QTest::qFail(qPrintable(error), __FILE__, __LINE__);
        return folder;
    }
    static QTabWidget* tabs(MainWindow& window) { return window.findChild<QTabWidget*>("documentTabs"); }
    static QAction* action(MainWindow& window, const char* name) { return window.findChild<QAction*>(name); }
    static void fixture(const QString& folder)
    {
        write(QDir(folder).filePath("main.cpp"),
              "#include \"logic/value.h\"\nvoid SmallMain() { File f; f.Open(\"result.txt\", FileMode::Write); f.Print(Value()); }\n");
        write(QDir(folder).filePath("logic/value.h"), "#pragma once\nint Value();\n");
        write(QDir(folder).filePath("logic/value.cpp"), "#include \"value.h\"\nint Value()\n{\n    int value = 42;\n    return value;\n}\n");
        write(QDir(folder).filePath("data/message.txt"), "nested resource\n");
    }
private slots:
    void initTestCase()
    {
        QVERIFY(settings_.isValid());
        QSettings::setDefaultFormat(QSettings::IniFormat);
        QSettings::setPath(QSettings::IniFormat, QSettings::UserScope, settings_.path());
        qputenv("SMALL_TEST_DIALOGS", "1"); qputenv("SMALL_TEST_NO_CONSOLE_PAUSE", "1");
    }
    void init() { SmallSettings().clear(); }
    void cleanup() { QCoreApplication::sendPostedEvents(nullptr, QEvent::DeferredDelete); }

    void recursiveFolderAndExclusions()
    {
        QTemporaryDir directory; fixture(directory.path());
        write(directory.filePath("build/old.cpp"), "invalid build product");
        write(directory.filePath(".git/objects/old.cpp"), "invalid git object");
        write(directory.filePath("published/.smallcpp-package"), "package");
        write(directory.filePath("published/source/main.cpp"), "invalid old source");
        auto project = load(directory.path());
        QCOMPARE(project.sources.size(), 2); QCOMPARE(project.headers.size(), 1); QCOMPARE(project.resources.size(), 1);
        QVERIFY(!QFileInfo::exists(directory.filePath("small.project")));
        QString error;
        QVERIFY2(project.setExcluded("logic", true, &error), qPrintable(error));
        QCOMPARE(project.sources.size(), 1); QCOMPARE(project.headers.size(), 0);
        QVERIFY(project.files.contains("logic/value.cpp")); QVERIFY(QFileInfo::exists(directory.filePath("logic/value.cpp")));
        QVERIFY2(project.setExcluded("logic", false, &error), qPrintable(error)); QCOMPARE(project.sources.size(), 2);
        write(directory.filePath("more/helper.cpp"), "int Another() { return 1; }\n");
        QVERIFY(project.scan(&error)); QCOMPARE(project.sources.size(), 3);
        QVERIFY(QFile::remove(directory.filePath("more/helper.cpp")));
        QVERIFY(project.scan(&error)); QCOMPARE(project.sources.size(), 2);
    }
    void settingsAreStrictAndPreserved()
    {
        QTemporaryDir directory; fixture(directory.path());
        write(directory.filePath("small.project"), "{\"version\":1,\"name\":\"My Game\",\"compiler_options\":[\"-DVALUE=7\"],\"include_paths\":[\"includes\"]}");
        auto project = load(directory.path()); QCOMPARE(project.name, QString("My Game"));
        QCOMPARE(project.includePaths.first(), directory.filePath("includes"));
        QString error; QVERIFY(project.setExcluded("data", true, &error));
        QCOMPARE(project.compilerOptions, QStringList{"-DVALUE=7"});
        write(directory.filePath("small.project"), "{\"exclude\":[\"../outside\"]}"); QVERIFY(!project.load(directory.path(), &error));
        write(directory.filePath("small.project"), "{\"compiler_options\":[\"-o\",\"outside.exe\"]}"); QVERIFY(!project.load(directory.path(), &error));
        write(directory.filePath("small.project"), "{\"exclude\":\"data\"}"); QVERIFY(!project.load(directory.path(), &error));
    }
    void projectUiAndClosePreserveOutsideFile()
    {
        QTemporaryDir directory; fixture(directory.filePath("MyGame"));
        write(directory.filePath("outside.cpp"), "void SmallMain() {}\n");
        MainWindow window; QVERIFY(window.openProject(directory.filePath("MyGame")));
        QCOMPARE(action(window, "actionRun")->text(), QString("Run Project"));
        QVERIFY(window.windowTitle().contains("MyGame"));
        QVERIFY(!window.findChild<QDockWidget*>("projectDock")->isHidden());
        QVERIFY(window.openDocument(directory.filePath("outside.cpp")));
        QVERIFY(tabs(window)->tabText(tabs(window)->currentIndex()).contains("Outside Project"));
        auto* outside = qobject_cast<EditorDocument*>(tabs(window)->currentWidget());
        QVERIFY(window.closeProject());
        QVERIFY(tabs(window)->indexOf(outside) >= 0); QVERIFY(!tabs(window)->tabText(tabs(window)->indexOf(outside)).contains("Outside Project"));
        QCOMPARE(action(window, "actionRun")->text(), QString("Run"));
        QVERIFY(window.findChild<QDockWidget*>("projectDock")->isHidden());
    }
    void cancellingCloseKeepsProjectAndText()
    {
        QTemporaryDir directory; fixture(directory.path()); MainWindow window; QVERIFY(window.openProject(directory.path()));
        auto* document = qobject_cast<EditorDocument*>(tabs(window)->currentWidget()); QVERIFY(document);
        document->appendPlainText("// my changes");
        QTimer::singleShot(0, this, [] { if (auto* box = qobject_cast<QMessageBox*>(QApplication::activeModalWidget())) box->done(QMessageBox::Cancel); });
        QVERIFY(!window.closeProject()); QVERIFY(!window.projectRoot().isEmpty()); QVERIFY(document->toPlainText().contains("my changes"));
        QTimer::singleShot(0, this, [] { if (auto* box = qobject_cast<QMessageBox*>(QApplication::activeModalWidget())) box->done(QMessageBox::Discard); });
        QVERIFY(window.closeProject()); QCOMPARE(tabs(window)->count(), 1); QCOMPARE(tabs(window)->tabText(0), QString("Welcome"));
    }
    void runProjectFromOutsideTabSavesProjectChanges()
    {
        QTemporaryDir directory; fixture(directory.filePath("project"));
        write(directory.filePath("outside.cpp"), "deliberately invalid;\n");
        MainWindow window; QVERIFY(window.openProject(directory.filePath("project")));
        QVERIFY(window.openDocument(directory.filePath("project/logic/value.cpp")));
        auto* helper = qobject_cast<EditorDocument*>(tabs(window)->currentWidget()); helper->selectAll(); helper->insertPlainText("int Value() { return 73; }\n");
        QVERIFY(window.openDocument(directory.filePath("outside.cpp")));
        auto* build = window.findChild<BuildController*>(); QSignalSpy finished(build, &BuildController::finished); QSignalSpy failed(build, &BuildController::buildError);
        action(window, "actionRun")->trigger();
        QTRY_VERIFY_WITH_TIMEOUT(!finished.isEmpty() || !failed.isEmpty(), 30000);
        QVERIFY2(failed.isEmpty(), qPrintable(failed.isEmpty() ? QString() : failed.first().first().toString()));
        QCOMPARE(read(directory.filePath("project/result.txt")).trimmed(), QByteArray("73"));
        QVERIFY(!helper->document()->isModified()); QVERIFY(read(helper->filePath()).contains("73"));
    }
    void startFunctionsAndDiagnosticFile()
    {
        QTemporaryDir directory; fixture(directory.path());
        write(directory.filePath("practice.cpp"), "void SmallMain() {}\n");
        BuildController build; QSignalSpy failed(&build, &BuildController::buildError);
        build.startProject(load(directory.path())); QCOMPARE(failed.size(), 1);
        QVERIFY(failed.first().first().toString().contains("practice.cpp")); QVERIFY(failed.first().first().toString().contains("Exclude"));
        QVERIFY(QFile::remove(directory.filePath("practice.cpp")));
        write(directory.filePath("logic/value.cpp"), "int Value() { return missingName; }\n");
        failed.clear(); build.startProject(load(directory.path()), true);
        QTRY_VERIFY_WITH_TIMEOUT(!failed.isEmpty(), 30000);
        QCOMPARE(failed.first().at(2).toString(), directory.filePath("logic/value.cpp"));
    }
    void publishNestedResourcesAndRelink()
    {
        if (!QFileInfo::exists(QCoreApplication::applicationDirPath() + "/licenses/SOURCE_ACCESS.md"))
            QSKIP("Prepare the matching Windows portable runtime and notices for Publish tests.");
        QTemporaryDir directory; fixture(directory.filePath("MyGame"));
        write(directory.filePath("MyGame/main.cpp"), "#include \"logic/value.h\"\nvoid SmallMain() { File f; f.Open(\"data/message.txt\"); String text=f.Input(); f.Close(); f.Open(\"result.txt\",FileMode::Write); f.Print(text); f.Print(Value()); }\n");
        BuildController build; QSignalSpy published(&build, &BuildController::published); QSignalSpy failed(&build, &BuildController::buildError);
        const QString destination = directory.filePath("MyGame/shared");
        build.startProject(load(directory.filePath("MyGame")), false, destination);
        QTRY_VERIFY_WITH_TIMEOUT(!published.isEmpty() || !failed.isEmpty(), 30000);
        QVERIFY2(failed.isEmpty(), qPrintable(failed.isEmpty() ? QString() : failed.first().first().toString()));
        QVERIFY(QFileInfo::exists(destination + "/source/logic/value.h"));
        QVERIFY(QFileInfo::exists(destination + "/data/message.txt"));
        QVERIFY(QFileInfo::exists(destination + "/.smallcpp-package"));
        QCOMPARE(load(directory.filePath("MyGame")).sources.size(), 2);
        QProcess relink; auto env=QProcessEnvironment::systemEnvironment(); env.insert("PATH", QFileInfo(QString::fromUtf8(SmallBuildConfig::Compiler)).absolutePath()+";"+env.value("PATH"));
        relink.setProcessEnvironment(env); relink.setWorkingDirectory(destination); relink.start("C:/Windows/System32/cmd.exe", {"/c", destination + "/relink/RELINK.cmd"});
        QVERIFY(relink.waitForFinished(15000)); QCOMPARE(relink.exitCode(), 0);
        QProcess program; env=QProcessEnvironment::systemEnvironment(); env.insert("PATH", "C:/Windows/System32"); env.remove("QT_PLUGIN_PATH"); env.remove("QT_QPA_PLATFORM_PLUGIN_PATH"); env.remove("SMALL_TEST_NO_CONSOLE_PAUSE");
        program.setProcessEnvironment(env); program.setWorkingDirectory(destination); program.start(destination+"/MyGame.exe", {});
        QVERIFY(program.waitForFinished(15000)); QCOMPARE(program.exitCode(), 0);
        QCOMPARE(read(destination+"/result.txt").replace("\r\n", "\n").trimmed(), QByteArray("nested resource\n42"));
    }
    void debuggerStopsInHelperFile()
    {
        QTemporaryDir directory; fixture(directory.path());
        auto project=load(directory.path()); DebugController debug; QSignalSpy stopped(&debug, &DebugController::stoppedAtFile); QSignalSpy failed(&debug, &DebugController::buildError); QSignalSpy finished(&debug, &DebugController::finished);
        QMap<QString,QSet<int>> breakpoints; breakpoints[directory.filePath("logic/value.cpp")].insert(5);
        debug.startProject(project, breakpoints);
        QTRY_VERIFY_WITH_TIMEOUT(!stopped.isEmpty() || !failed.isEmpty(), 30000);
        QVERIFY2(failed.isEmpty(), qPrintable(failed.isEmpty() ? QString() : failed.first().first().toString()));
        QCOMPARE(stopped.first().at(0).toString(), directory.filePath("logic/value.cpp")); QCOMPARE(stopped.first().at(1).toInt(), 5);
        debug.continueRun(); QTRY_VERIFY_WITH_TIMEOUT(!finished.isEmpty(), 15000); QVERIFY(!debug.isBusy());
    }
    void externalLibraryAndCompilerOptions()
    {
        QTemporaryDir directory;
        write(directory.filePath("vendor/answer.h"), "int Answer();\n");
        write(directory.filePath("vendor/answer.cpp"), "int Answer() { return 55; }\n");
        const QString compiler = QString::fromUtf8(SmallBuildConfig::Compiler);
        QProcess compile;
        compile.start(compiler, {"-c", directory.filePath("vendor/answer.cpp"), "-o", directory.filePath("vendor/answer.o")});
        QVERIFY(compile.waitForFinished(15000)); QCOMPARE(compile.exitCode(), 0);
        compile.start(QDir(QFileInfo(compiler).absolutePath()).filePath("ar.exe"), {"rcs", directory.filePath("vendor/libanswer.a"), directory.filePath("vendor/answer.o")});
        QVERIFY(compile.waitForFinished(15000)); QCOMPARE(compile.exitCode(), 0);
        write(directory.filePath("project/main.cpp"), "#include <answer.h>\nvoid SmallMain() { File f; f.Open(\"result.txt\",FileMode::Write); f.Print(Answer()+BONUS); }\n");
        write(directory.filePath("project/small.project"), "{\"include_paths\":[\"../vendor\"],\"library_paths\":[\"../vendor\"],\"libraries\":[\"answer\"],\"compiler_options\":[\"-DBONUS=5\"],\"linker_options\":[\"-Wl,--as-needed\"]}");
        auto project=load(directory.filePath("project")); BuildController build; QSignalSpy failed(&build, &BuildController::buildError); QSignalSpy finished(&build, &BuildController::finished);
        build.startProject(project);
        QTRY_VERIFY_WITH_TIMEOUT(!finished.isEmpty() || !failed.isEmpty(), 30000);
        QVERIFY2(failed.isEmpty(), qPrintable(failed.isEmpty() ? QString() : failed.first().first().toString()));
        QCOMPARE(read(directory.filePath("project/result.txt")).trimmed(), QByteArray("60"));
        if (!QFileInfo::exists(QCoreApplication::applicationDirPath() + "/licenses/SOURCE_ACCESS.md"))
            QSKIP("External library Run passed; prepare portable files to test Publish and relinking.");
        QSignalSpy published(&build,&BuildController::published); build.startProject(project,false,directory.filePath("published"));
        QTRY_VERIFY_WITH_TIMEOUT(!published.isEmpty() || !failed.isEmpty(),30000);
        QVERIFY2(failed.isEmpty(),qPrintable(failed.isEmpty()?QString():failed.first().first().toString()));
        QVERIFY(QFileInfo::exists(directory.filePath("published/relink/external/0/libanswer.a")));
        QProcess relink; auto env=QProcessEnvironment::systemEnvironment();env.insert("PATH",QFileInfo(compiler).absolutePath()+";"+env.value("PATH"));relink.setProcessEnvironment(env);
        relink.start("C:/Windows/System32/cmd.exe",{"/c",directory.filePath("published/relink/RELINK.cmd")});
        QVERIFY(relink.waitForFinished(15000));QCOMPARE(relink.exitCode(),0);
    }
    void projectPreview()
    {
        const QString output=qEnvironmentVariable("SMALL_PROJECT_PREVIEW_DIR"); if(output.isEmpty()) return;
        QFontDatabase::addApplicationFont(qEnvironmentVariable("SystemRoot")+"/Fonts/segoeui.ttf");
        QFontDatabase::addApplicationFont(qEnvironmentVariable("SystemRoot")+"/Fonts/segoeuib.ttf");
        QVERIFY(QDir().mkpath(output)); QTemporaryDir directory; fixture(directory.filePath("MyGame"));
        write(directory.filePath("outside.cpp"), "// A separate program, outside MyGame.\nvoid SmallMain()\n{\n    Print(\"Hello!\");\n}\n");
        for(bool dark:{false,true}) {
            MainWindow window;
            window.findChild<QAction*>(dark ? "actionThemeDark" : "actionThemeLight")->trigger();
            QVERIFY(window.openProject(directory.filePath("MyGame")));
            QVERIFY(window.openDocument(directory.filePath("MyGame/logic/value.cpp"))); QVERIFY(window.openDocument(directory.filePath("outside.cpp")));
            window.findChild<QTreeWidget*>("projectFiles")->expandAll(); window.resize(1200,800); window.show(); QTest::qWait(50);
            QVERIFY(window.grab().save(QDir(output).filePath(dark?"project-dark.png":"project-light.png")));
        }
    }
};
QTEST_MAIN(ProjectTests)
#include "test_project.moc"
