#include "MainWindow.h"
#include "BuildController.h"
#include "ProgramPackage.h"
#include "PublishDialog.h"
#include "DebugController.h"
#include "CodeEditor.h"
#include "Diagnostics.h"
#include "EntryPoint.h"
#include "SmallSettings.h"
#include "small.h"

#include <QAbstractButton>
#include <QAction>
#include <QApplication>
#include <QDateTime>
#include <QFile>
#include <QFileDialog>
#include <QFocusEvent>
#include <QFontDatabase>
#include <QImage>
#include <QKeyEvent>
#include <QMessageBox>
#include <QMouseEvent>
#include <QPushButton>
#include <QTreeWidget>
#include <QSignalSpy>
#include <QSettings>
#include <QTemporaryDir>
#include <QTest>
#include <QTimer>
#include <QWidget>

using namespace Small;

namespace
{
int timerCallbackCount = 0;
void TestTimerCallback() { ++timerCallbackCount; }
}

class RegressionTests : public QObject
{
    Q_OBJECT
private:
    QTemporaryDir testSettings_;
private slots:
    void initTestCase()
    {
        QVERIFY(testSettings_.isValid());
        QSettings::setDefaultFormat(QSettings::IniFormat);
        QSettings::setPath(QSettings::IniFormat, QSettings::UserScope, testSettings_.path());
        QApplication::setQuitOnLastWindowClosed(false);
        qputenv("SMALL_TEST_DIALOGS", "1");
        qputenv("SMALL_TEST_NO_CONSOLE_PAUSE", "1");
    }

    void settingsUseIsolatedConfiguredBackend()
    {
        auto settings = SmallSettings();
        QCOMPARE(settings.format(), QSettings::IniFormat);
        QVERIFY(settings.fileName().startsWith(testSettings_.path()));
        settings.setValue("tests/roundTrip", 42);
        settings.sync();
        QCOMPARE(settings.status(), QSettings::NoError);
        QCOMPARE(SmallSettings().value("tests/roundTrip").toInt(), 42);
    }

    void diagnosticsUsesPreviousDeclaration()
    {
        const QString source = "void SmallMain()\n{\n    Window window\n    window.Open(10, 10);\n}\n";
        auto error = ExplainDiagnostic("/tmp/program.cpp:4:5: error: expected initializer before 'window'\n",
                                       source, "/tmp/program.cpp");
        QCOMPARE(error.line, 3);
        QVERIFY(error.text.contains("Missing semicolon"));
    }

    void shortcutsAndDirtyTitle()
    {
        MainWindow window;
        auto* editor = window.findChild<CodeEditor*>("codeEditor");
        QVERIFY(editor);
        QCOMPARE(window.findChild<QAction*>("actionSave")->shortcut(), QKeySequence(QKeySequence::Save));
        QCOMPARE(window.findChild<QAction*>("actionOpen")->shortcut(), QKeySequence(QKeySequence::Open));
        QVERIFY(window.windowTitle().contains("Untitled.cpp"));
        QVERIFY(!window.windowTitle().contains('*'));
        editor->appendPlainText("// changed");
        QVERIFY(window.windowTitle().contains('*'));
    }

    void closeCancelRetainsDocument()
    {
        MainWindow window;
        window.show();
        auto* editor = window.findChild<CodeEditor*>("codeEditor");
        editor->appendPlainText("// unsaved");
        QTimer choose;
        choose.setInterval(5);
        bool asked = false;
        connect(&choose, &QTimer::timeout, &window, [&] {
            if (auto* box = qobject_cast<QMessageBox*>(QApplication::activeModalWidget()))
            {
                asked = true;
                choose.stop();
                box->button(QMessageBox::Cancel)->click();
            }
        });
        choose.start();
        QVERIFY(!window.close());
        QVERIFY(asked);
        QVERIFY(window.isVisible());
        QVERIFY(editor->document()->isModified());
        QVERIFY(editor->toPlainText().contains("// unsaved"));
    }

    void closeDiscardDoesNotSave()
    {
        MainWindow window;
        window.show();
        window.findChild<CodeEditor*>("codeEditor")->appendPlainText("// unsaved");
        QTimer choose;
        choose.setInterval(5);
        connect(&choose, &QTimer::timeout, &window, [&] {
            if (auto* box = qobject_cast<QMessageBox*>(QApplication::activeModalWidget()))
            {
                choose.stop();
                box->button(QMessageBox::Discard)->click();
            }
        });
        choose.start();
        QVERIFY(window.close());
        QVERIFY(!window.isVisible());
    }

    void cancelSaveAsAlsoCancelsClosing()
    {
        MainWindow window;
        window.show();
        auto* editor = window.findChild<CodeEditor*>("codeEditor");
        editor->appendPlainText("// unsaved");
        bool sawSaveDialog = false;
        QTimer choose;
        choose.setInterval(5);
        connect(&choose, &QTimer::timeout, &window, [&] {
            QWidget* active = QApplication::activeModalWidget();
            if (auto* box = qobject_cast<QMessageBox*>(active))
                box->button(QMessageBox::Save)->click();
            else if (auto* dialog = qobject_cast<QFileDialog*>(active))
            {
                sawSaveDialog = true;
                choose.stop();
                dialog->reject();
            }
        });
        choose.start();
        QVERIFY(!window.close());
        QVERIFY(sawSaveDialog);
        QVERIFY(window.isVisible());
        QVERIFY(editor->document()->isModified());
    }

    void saveDefaultNameAndSaveOnClose()
    {
        QTemporaryDir folder;
        QVERIFY(folder.isValid());
        const QString path = folder.filePath("saved-program.cpp");
        MainWindow window;
        window.show();
        auto* editor = window.findChild<CodeEditor*>("codeEditor");
        editor->appendPlainText("// first save");
        bool defaultNameCorrect = false;
        QTimer choose;
        choose.setInterval(5);
        connect(&choose, &QTimer::timeout, &window, [&] {
            if (auto* dialog = qobject_cast<QFileDialog*>(QApplication::activeModalWidget()))
            {
                defaultNameCorrect = dialog->selectedFiles().value(0).endsWith("Untitled.cpp");
                choose.stop();
                dialog->selectFile(path);
                QMetaObject::invokeMethod(dialog, "accept", Qt::QueuedConnection);
            }
        });
        choose.start();
        window.findChild<QAction*>("actionSave")->trigger();
        QVERIFY(defaultNameCorrect);
        QVERIFY(QFile::exists(path));
        QVERIFY(!editor->document()->isModified());
        QVERIFY(window.windowTitle().contains("saved-program.cpp"));

        editor->appendPlainText("// save on close");
        disconnect(&choose, nullptr, &window, nullptr);
        connect(&choose, &QTimer::timeout, &window, [&] {
            if (auto* box = qobject_cast<QMessageBox*>(QApplication::activeModalWidget()))
            {
                choose.stop();
                box->button(QMessageBox::Save)->click();
            }
        });
        choose.start();
        QVERIFY(window.close());
        QFile file(path);
        QVERIFY(file.open(QIODevice::ReadOnly));
        QVERIFY(file.readAll().contains("// save on close"));
    }

    void windowConstructionAndDoubleBuffer()
    {
        const auto before = QApplication::topLevelWidgets();
        Window window;
        QCOMPARE(QApplication::topLevelWidgets().size(), before.size());
        QVERIFY(!window.IsOpen());
        window.Open(64, 48);
        QWidget* surface = nullptr;
        for (QWidget* candidate : QApplication::topLevelWidgets())
            if (!before.contains(candidate)) surface = candidate;
        QVERIFY(surface);
        window.Clear(Red);
        QCOMPARE(surface->grab().toImage().pixelColor(10, 10), QColor(0, 0, 0));
        window.Show();
        QCOMPARE(surface->grab().toImage().pixelColor(10, 10), QColor(255, 0, 0));
        window.Clear(Blue);
        QCOMPARE(surface->grab().toImage().pixelColor(10, 10), QColor(255, 0, 0));
        window.Show();
        QCOMPARE(surface->grab().toImage().pixelColor(10, 10), QColor(0, 0, 255));
        window.Close();
        QVERIFY(!window.IsOpen());
    }

    void keyboardEdgeAndFocusLoss()
    {
        const auto before = QApplication::topLevelWidgets();
        Window window;
        window.Open(64, 48);
        QWidget* surface = nullptr;
        for (QWidget* candidate : QApplication::topLevelWidgets())
            if (!before.contains(candidate)) surface = candidate;
        QVERIFY(surface);
        // Post the event: Show must keep this NEW edge for the next frame.
        QCoreApplication::postEvent(surface, new QKeyEvent(QEvent::KeyPress, Qt::Key_Space, Qt::NoModifier, " "));
        window.Show();
        QVERIFY(window.KeyPressed(Key::Space));
        QVERIFY(window.KeyDown(Key::Space));
        window.Show();
        QVERIFY(!window.KeyPressed(Key::Space));
        QKeyEvent release(QEvent::KeyRelease, Qt::Key_Space, Qt::NoModifier);
        QCoreApplication::sendEvent(surface, &release);
        QVERIFY(window.KeyReleased(Key::Space));
        QVERIFY(!window.KeyDown(Key::Space));
        QKeyEvent letter(QEvent::KeyPress, Qt::Key_A, Qt::ControlModifier, "");
        QCoreApplication::sendEvent(surface, &letter);
        QVERIFY(window.KeyDown('A'));
        QVERIFY(window.KeyDown('a'));
        QFocusEvent blur(QEvent::FocusOut);
        QCoreApplication::sendEvent(surface, &blur);
        QVERIFY(!window.KeyDown('A'));
    }

    void mousePositionAndButtons()
    {
        const auto before = QApplication::topLevelWidgets();
        Window window;
        window.Open(64, 48);
        QWidget* surface = nullptr;
        for (QWidget* candidate : QApplication::topLevelWidgets())
            if (!before.contains(candidate)) surface = candidate;
        QVERIFY(surface);

        QMouseEvent move(QEvent::MouseMove, QPointF(21, 17), QPointF(21, 17),
                         Qt::NoButton, Qt::NoButton, Qt::NoModifier);
        QCoreApplication::sendEvent(surface, &move);
        QCOMPARE(window.MouseX(), 21);
        QCOMPARE(window.MouseY(), 17);

        QMouseEvent press(QEvent::MouseButtonPress, QPointF(21, 17), QPointF(21, 17),
                          Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
        QCoreApplication::sendEvent(surface, &press);
        QVERIFY(window.MouseDown(MouseButton::Left));
        QVERIFY(window.MousePressed(MouseButton::Left));
        window.Show();
        QVERIFY(!window.MousePressed(MouseButton::Left));
        QVERIFY(window.MouseDown(MouseButton::Left));

        QMouseEvent release(QEvent::MouseButtonRelease, QPointF(22, 18), QPointF(22, 18),
                            Qt::LeftButton, Qt::NoButton, Qt::NoModifier);
        QCoreApplication::sendEvent(surface, &release);
        QVERIFY(window.MouseReleased(MouseButton::Left));
        QVERIFY(!window.MouseDown(MouseButton::Left));
        QCOMPARE(window.MouseX(), 22);
        QCOMPARE(window.MouseY(), 18);
    }

    void callbackTimer()
    {
        timerCallbackCount = 0;
        Timer timer;
        QVERIFY(!timer.IsRunning());
        timer.Start(0.01, TestTimerCallback);
        QVERIFY(timer.IsRunning());
        Sleep(0.06);
        QVERIFY(timerCallbackCount >= 2);
        timer.Stop();
        QVERIFY(!timer.IsRunning());
        const int stoppedAt = timerCallbackCount;
        Sleep(0.03);
        QCOMPARE(timerCallbackCount, stoppedAt);
    }

    void asynchronousCompileAndRun()
    {
        BuildController build;
        QSignalSpy failed(&build, &BuildController::buildError);
        QSignalSpy finished(&build, &BuildController::finished);
        QSignalSpy times(&build, &BuildController::buildTiming);
        QString output;
        connect(&build, &BuildController::textOutput, this, [&](const QString& part) { output += part; });
        int beats = 0;
        QTimer heartbeat;
        heartbeat.setInterval(5);
        connect(&heartbeat, &QTimer::timeout, this, [&] { ++beats; });
        heartbeat.start();
        QTemporaryDir folder;
        QVERIFY(folder.isValid());
        build.start(R"cpp(void SmallMain() {
    Array<int> a = {1, 2, 3};
    File f;
    f.Open("result.txt", FileMode::Write);
    f.Print("OK ", a.Length());
}
)cpp", folder.filePath("program.cpp"));
        QTRY_VERIFY_WITH_TIMEOUT(!finished.isEmpty() || !failed.isEmpty(), 30000);
        QVERIFY2(failed.isEmpty(), qPrintable(failed.isEmpty() ? QString{} : failed.first().first().toString()));
        QCOMPARE(finished.first().at(0).toInt(), 0);
        QFile result(folder.filePath("result.txt"));
        QVERIFY(result.open(QIODevice::ReadOnly));
        QVERIFY(result.readAll().contains("OK 3"));
        QVERIFY(!times.isEmpty());
        QVERIFY(beats > 0);
        QVERIFY(!build.isBusy());
    }

    void publishRejectsExistingDestination()
    {
        QTemporaryDir folder;
        QVERIFY(folder.isValid());
        QFile marker(folder.filePath("keep.txt"));
        QVERIFY(marker.open(QIODevice::WriteOnly));
        marker.write("keep"); marker.close();
        BuildController build;
        QSignalSpy failed(&build, &BuildController::buildError);
        build.publish("void SmallMain() {}", {}, folder.path());
        QCOMPARE(failed.size(), 1);
        QVERIFY(!build.isBusy());
        QVERIFY(marker.open(QIODevice::ReadOnly));
        QCOMPARE(marker.readAll(), QByteArray("keep"));
    }

    void publishFilesCanBeAddedAndRemoved()
    {
        QTemporaryDir folder;
        QVERIFY(folder.isValid());
        PublishDialog dialog(folder.path(), "MyGame");
        dialog.addFiles({folder.filePath("cat.png")});
        dialog.addFiles({folder.filePath("music.wav"), folder.filePath("cat.png")});
        QCOMPARE(dialog.resources().size(), 2);
        dialog.show();
        QTest::qWait(20);
        auto* files = dialog.findChild<QTreeWidget*>("publishFiles");
        QVERIFY(files);
        auto* remove = qobject_cast<QPushButton*>(files->itemWidget(files->topLevelItem(0), 1));
        QVERIFY(remove);
        QTest::mouseClick(remove, Qt::LeftButton);
        QCOMPARE(dialog.resources(), QStringList{folder.filePath("music.wav")});
        dialog.close();
    }

    void publishExecutableUsesSafeEnglishName()
    {
        QCOMPARE(ProgramPackage::executableName("MyGame.cpp"), QString("MyGame.exe"));
        QCOMPARE(ProgramPackage::executableName("My Game.cpp"), QString("My_Game.exe"));
        QCOMPARE(ProgramPackage::executableName(QString::fromUtf8("나의 작품.cpp")), QString("Program.exe"));
        QCOMPARE(ProgramPackage::executableName("CON.cpp"), QString("Program-CON.exe"));
    }

    void publishDialogPreview()
    {
        const QString output = qEnvironmentVariable("SMALL_PUBLISH_PREVIEW_DIR");
        if (output.isEmpty()) return;
        QFontDatabase::addApplicationFont(qEnvironmentVariable("SystemRoot") + "/Fonts/segoeui.ttf");
        QFontDatabase::addApplicationFont(qEnvironmentVariable("SystemRoot") + "/Fonts/segoeuib.ttf");
        QVERIFY(QDir().mkpath(output));
        for (bool dark : {false, true}) {
            SmallSettings().setValue("appearance/dark", dark);
            MainWindow parent;
            PublishDialog dialog("C:/Users/Student/Documents", "MyGame", &parent);
            dialog.addFiles({"C:/Pictures/cat.png", "C:/Sounds/music.wav"});
            dialog.show();
            QTest::qWait(30);
            QVERIFY(dialog.grab().save(QDir(output).filePath(dark ? "publish-dark.png" : "publish-light.png")));
            dialog.close();
            bool captured = false;
            QTimer::singleShot(0, this, [&] {
                auto* complete = qobject_cast<QDialog*>(QApplication::activeModalWidget());
                if (complete) {
                    captured = complete->grab().save(QDir(output).filePath(
                        dark ? "publish-complete-dark.png" : "publish-complete-light.png"));
                    complete->reject();
                }
            });
            ShowPublishComplete("C:/Users/Student/Documents/MyGame-published", "MyGame.exe", &parent);
            QVERIFY(captured);
        }
        SmallSettings().setValue("appearance/dark", false);
    }

    void publishStandalone_data()
    {
        QTest::addColumn<QString>("source");
        QTest::newRow("SmallMain") << QString(
            "void SmallMain() { File f; f.Open(\"result.txt\", FileMode::Write); f.Print(\"published\"); }");
        QTest::newRow("manual-main") << QString(
            "#include <fstream>\nint main() { std::ofstream(\"result.txt\") << \"published\"; }");
        QTest::newRow("Image") << QString(
            "#include <small/image.h>\nvoid SmallMain() { Image image(8, 8); "
            "Window window; window.Open(64, 64); DrawImage(window, image, 0, 0); window.Close(); "
            "File f; f.Open(\"result.txt\", FileMode::Write); f.Print(\"published\"); }");
    }

    void publishStandalone()
    {
#ifndef Q_OS_WIN
        QSKIP("Windows Publish integration test");
#endif
        if (!QFileInfo::exists(QCoreApplication::applicationDirPath() + "/licenses/SOURCE_ACCESS.md"))
            QSKIP("Prepare the matching portable runtime and notices beside the test executable first.");
        QFETCH(QString, source);
        QTemporaryDir parent(QDir::tempPath() + "/SmallCpp publish-XXXXXX");
        QVERIFY(parent.isValid());
        const QString target = parent.filePath(QString::fromUtf8("나의 작품"));
        QFile resource(parent.filePath("data.txt"));
        QVERIFY(resource.open(QIODevice::WriteOnly));
        resource.write("student data"); resource.close();
        BuildController build;
        QSignalSpy failed(&build, &BuildController::buildError);
        QSignalSpy published(&build, &BuildController::published);
        QSignalSpy started(&build, &BuildController::programStarted);
        build.publish(source, {}, target, {resource.fileName()}, "My Game.cpp");
        QTRY_VERIFY_WITH_TIMEOUT(!published.isEmpty() || !failed.isEmpty(), 45000);
        QVERIFY2(failed.isEmpty(), qPrintable(failed.isEmpty() ? QString{} : failed.first().first().toString()));
        QCOMPARE(published.size(), 1);
        QVERIFY(started.isEmpty());
        QVERIFY(!build.isBusy());
        QVERIFY(QFileInfo::exists(target + "/data.txt"));
        QVERIFY(QFileInfo::exists(target + "/source/program.cpp"));
        QVERIFY(QFileInfo::exists(target + "/relink/program.o"));
        QVERIFY(QFileInfo::exists(target + "/licenses/SOURCE_ACCESS.md"));
        QVERIFY(!QFileInfo::exists(target + "/compiler"));
        QVERIFY(!QFileInfo::exists(target + "/SmallCppIDE.exe"));
        QVERIFY(QFileInfo::exists(target + "/My_Game.exe"));
        QVERIFY(!QFileInfo::exists(target + "/START.cmd"));
        QProcess relink;
        relink.setWorkingDirectory(target + "/relink");
        relink.start(qEnvironmentVariable("SystemRoot") + "/System32/cmd.exe",
                     {"/d", "/c", "RELINK.cmd"});
        QVERIFY(relink.waitForFinished(15000));
        QCOMPARE(relink.exitStatus(), QProcess::NormalExit);
        QCOMPARE(relink.exitCode(), 0);
        QProcess program;
        auto env = QProcessEnvironment::systemEnvironment();
        env.insert("PATH", env.value("SystemRoot") + "/System32");
        env.remove("QT_PLUGIN_PATH"); env.remove("QT_QPA_PLATFORM_PLUGIN_PATH");
        env.remove("QT_QPA_PLATFORM"); env.remove("SMALL_TEST_NO_CONSOLE_PAUSE");
        program.setProcessEnvironment(env);
        program.setWorkingDirectory(target);
        program.start(target + "/My_Game.exe", {});
        QVERIFY(program.waitForFinished(15000));
        QCOMPARE(program.exitStatus(), QProcess::NormalExit);
        QCOMPARE(program.exitCode(), 0);
        QFile result(target + "/result.txt");
        QVERIFY(result.open(QIODevice::ReadOnly));
        QVERIFY(result.readAll().contains("published"));
    }

    void publishCollisionAndCompileFailureLeaveNoFolder()
    {
        if (!QFileInfo::exists(QCoreApplication::applicationDirPath() + "/licenses/SOURCE_ACCESS.md"))
            QSKIP("Prepared Windows portable fixture required");
        QTemporaryDir parent;
        QVERIFY(parent.isValid());
        BuildController build;
        QSignalSpy failed(&build, &BuildController::buildError);
        const QString target = parent.filePath("export");
        QFile conflict(parent.filePath("PROGRAM.EXE"));
        QVERIFY(conflict.open(QIODevice::WriteOnly)); conflict.write("keep"); conflict.close();
        build.publish("void SmallMain() {}", {}, target, {conflict.fileName()});
        QCOMPARE(failed.size(), 1);
        QVERIFY(!QFileInfo::exists(target));
        failed.clear();
        build.publish("void SmallMain() { invalid syntax; }", {}, target);
        QTRY_VERIFY_WITH_TIMEOUT(!failed.isEmpty(), 30000);
        QVERIFY(!QFileInfo::exists(target));
        QVERIFY(!build.isBusy());
    }

    void publishCancellationLeavesNoFolder()
    {
        if (!QFileInfo::exists(QCoreApplication::applicationDirPath() + "/licenses/SOURCE_ACCESS.md"))
            QSKIP("Prepared Windows portable fixture required");
        QTemporaryDir parent;
        QVERIFY(parent.isValid());
        BuildController build;
        QSignalSpy failed(&build, &BuildController::buildError);
        QSignalSpy finished(&build, &BuildController::finished);
        connect(&build, &BuildController::phaseChanged, &build, [&](const QString& text) {
            if (text.startsWith("Packaging")) QTimer::singleShot(0, &build, &BuildController::stop);
        });
        build.publish("void SmallMain() {}", {}, parent.filePath("export"));
        QTRY_VERIFY_WITH_TIMEOUT(!finished.isEmpty() || !failed.isEmpty(), 30000);
        QVERIFY2(failed.isEmpty(), qPrintable(failed.isEmpty() ? QString{} : failed.first().first().toString()));
        QVERIFY(finished.first().at(1).toBool());
        QVERIFY(!QFileInfo::exists(parent.filePath("export")));
        QVERIFY(QDir(parent.path()).entryList(QDir::Dirs | QDir::Hidden | QDir::NoDotAndDotDot).isEmpty());
    }



    void detectsExtensionsFromIncludes()
    {
        const auto installed = ExtensionRegistry::discover(
            QCoreApplication::applicationDirPath() + "/extensions");
        QVERIFY(!installed.isEmpty());
        QCOMPARE(ExtensionRegistry::detect("#include <small/image.h>\nvoid SmallMain(){}", installed).size(), 1);
        QCOMPARE(ExtensionRegistry::detect(" // #include <small/image.h>\nvoid SmallMain(){}", installed).size(), 0);
        QCOMPARE(ExtensionRegistry::detect("#include <small.h>\nvoid SmallMain(){}", installed).size(), 0);
    }

    void detectsRealMainOnly()
    {
        QCOMPARE(DetectEntryPoint("void SmallMain() {}"), SmallEntryPoint::SmallMain);
        QCOMPARE(DetectEntryPoint("int main() { return 0; }"), SmallEntryPoint::Main);
        QCOMPARE(DetectEntryPoint("int main(int argc, char* argv[]) { return argc + (argv != nullptr); }"),
                 SmallEntryPoint::Main);
        QCOMPARE(DetectEntryPoint("// int main() { }\nvoid SmallMain() {}"), SmallEntryPoint::SmallMain);
        QCOMPARE(DetectEntryPoint("const char* s = \"int main() { }\";\nvoid SmallMain() {}"),
                 SmallEntryPoint::SmallMain);
        QCOMPARE(DetectEntryPoint("int main();\nvoid SmallMain() {}"), SmallEntryPoint::SmallMain);
        QCOMPARE(DetectEntryPoint("namespace Demo { int main() { return 0; } }\nvoid SmallMain() {}"),
                 SmallEntryPoint::SmallMain);
        // An explicit real main wins even if SmallMain is also present.
        QCOMPARE(DetectEntryPoint("void SmallMain() {}\nint main() { return 0; }"), SmallEntryPoint::Main);
    }


    void buildControllerRunsManualMain()
    {
        BuildController build;
        QSignalSpy finished(&build, &BuildController::finished);
        QSignalSpy failed(&build, &BuildController::buildError);
        QSignalSpy started(&build, &BuildController::programStarted);
        QTemporaryDir folder;
        QVERIFY(folder.isValid());
        build.start(R"cpp(#include <small.h>
int main(int argc, char* argv[])
{
    Small::InitializeSmall(argc, argv);
    Small::Print("manual main");
    Small::ShutdownSmall();
    return 0;
}
)cpp", folder.filePath("program.cpp"));
        QTRY_VERIFY_WITH_TIMEOUT(!finished.isEmpty() || !failed.isEmpty(), 30000);
        QVERIFY2(failed.isEmpty(), qPrintable(failed.isEmpty() ? QString{} : failed.first().first().toString()));
        QCOMPARE(finished.first().at(0).toInt(), 0);
        QVERIFY(!started.isEmpty());
        QVERIFY(!build.isBusy());
    }

    void debuggerDisplaysStringValues()
    {
        DebugController debug;
        QSignalSpy failed(&debug, &DebugController::buildError);
        QSignalSpy finished(&debug, &DebugController::finished);
        bool valuesReady = false;
        QString label, empty;
        connect(&debug, &DebugController::variablesChanged, this,
                [&](const QList<DebugVariable>& locals, const QList<DebugVariable>&) {
            if (!debug.isStopped()) return;
            for (const auto& value : locals) {
                if (value.name == "label") label = value.value;
                if (value.name == "empty") empty = value.value;
            }
            valuesReady = true;
        });
        debug.start("void SmallMain()\n{\n String label=\"hello \\\"world\\\"\";\n String empty;\n Print(label);\n}\n",
                    {}, "StringDebug.cpp", {5});
        QTRY_VERIFY_WITH_TIMEOUT(valuesReady || !failed.isEmpty(), 30000);
        QVERIFY2(failed.isEmpty(), qPrintable(failed.isEmpty() ? QString{} : failed.first().first().toString()));
        QVERIFY2(label.startsWith(QStringLiteral("\"hello ")), qPrintable(label));
        QVERIFY2(label.contains(QStringLiteral("world")), qPrintable(label));
        QVERIFY(label.endsWith(QLatin1Char('"')));
        QCOMPARE(empty, QStringLiteral("\"\""));
        debug.continueRun();
        QTRY_VERIFY_WITH_TIMEOUT(!finished.isEmpty(), 10000);
        QVERIFY(!debug.isBusy());
    }

    void stopDuringCompilation()
    {
        BuildController build;
        QSignalSpy finished(&build, &BuildController::finished);
        build.start("void SmallMain() { Print(\"hello\"); }\n", {});
        build.stop();
        QTRY_VERIFY_WITH_TIMEOUT(!build.isBusy(), 10000);
        QVERIFY(!finished.isEmpty());
        QVERIFY(finished.last().at(1).toBool());
    }
};
QTEST_MAIN(RegressionTests)
#include "test_qt.moc"
