#include "MainWindow.h"
#include "BuildController.h"
#include "CodeEditor.h"
#include "Diagnostics.h"
#include "EntryPoint.h"
#include "small.h"

#include <QAbstractButton>
#include <QAction>
#include <QApplication>
#include <QDateTime>
#include <QFile>
#include <QFileDialog>
#include <QFocusEvent>
#include <QImage>
#include <QKeyEvent>
#include <QMessageBox>
#include <QMouseEvent>
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
        build.start(R"cpp(int main(int argc, char* argv[])
{
    InitializeSmall(argc, argv);
    Print("manual main");
    return 0;
}
)cpp", folder.filePath("program.cpp"));
        QTRY_VERIFY_WITH_TIMEOUT(!finished.isEmpty() || !failed.isEmpty(), 30000);
        QVERIFY2(failed.isEmpty(), qPrintable(failed.isEmpty() ? QString{} : failed.first().first().toString()));
        QCOMPARE(finished.first().at(0).toInt(), 0);
        QVERIFY(!started.isEmpty());
        QVERIFY(!build.isBusy());
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
