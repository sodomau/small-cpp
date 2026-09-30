#include "MainWindow.h"
#include "EditorDocument.h"
#include "BuildController.h"

#include <QAbstractButton>
#include <QAction>
#include <QApplication>
#include <QFile>
#include <QFileDialog>
#include <QFontDialog>
#include <QFontDatabase>
#include <QLabel>
#include <QMessageBox>
#include <QMenuBar>
#include <QToolBar>
#include <QPlainTextEdit>
#include <QPointer>
#include <QPixmap>
#include <QSettings>
#include "SmallSettings.h"
#include <QSignalSpy>
#include <QTabBar>
#include <QTabWidget>
#include <QTemporaryDir>
#include <QTest>
#include <QTextDocument>
#include <QTimer>

#include <memory>

class TabTests : public QObject
{
    Q_OBJECT
private:
    std::unique_ptr<QTemporaryDir> settingsDirectory_;

    static QTabWidget* tabs(MainWindow& window)
    {
        return window.findChild<QTabWidget*>("documentTabs");
    }
    static EditorDocument* current(MainWindow& window)
    {
        return qobject_cast<EditorDocument*>(tabs(window)->currentWidget());
    }
    static QAction* action(MainWindow& window, const char* name)
    {
        return window.findChild<QAction*>(name);
    }
    static void writeFile(const QString& path, const QByteArray& bytes)
    {
        QFile file(path);
        QVERIFY(file.open(QIODevice::WriteOnly));
        QCOMPARE(file.write(bytes), qint64(bytes.size()));
    }
    static QByteArray readFile(const QString& path)
    {
        QFile file(path);
        if (!file.open(QIODevice::ReadOnly)) return {};
        return file.readAll();
    }
    static bool hasError(EditorDocument* document)
    {
        // CodeEditor has one selection for the current line and an extra one
        // for the error. We test visible behavior, not private data members.
        return document->extraSelections().size() > 1;
    }
    static void closeWith(MainWindow& window, QMessageBox::StandardButton choice)
    {
        QTimer response;
        response.setInterval(5);
        connect(&response, &QTimer::timeout, &window, [&] {
            if (auto* box = qobject_cast<QMessageBox*>(QApplication::activeModalWidget()))
            {
                response.stop();
                if (auto* button = box->button(choice)) button->click();
            }
        });
        response.start();
        action(window, "actionCloseTab")->trigger();
    }

private slots:
    void aboutShowsProjectOrigin()
    {
        MainWindow window;
        auto* about = action(window, "actionAboutSmallCpp");
        QVERIFY(about);
        QString text;
        QTimer::singleShot(0, &window, [&] {
            if (auto* box = qobject_cast<QMessageBox*>(QApplication::activeModalWidget())) {
                text = box->text();
                box->accept();
            }
        });
        about->trigger();
        QVERIFY(text.contains("Sunghyun Cho"));
        QVERIFY(text.contains("POSTECH"));
        QVERIFY(text.contains("GW-BASIC"));
        QVERIFY(text.contains("Small Basic"));
        QVERIFY(text.contains("MIT License"));
    }

    void initTestCase()
    {
        QApplication::setQuitOnLastWindowClosed(false);
        qputenv("SMALL_TEST_DIALOGS", "1");
        qputenv("SMALL_TEST_NO_CONSOLE_PAUSE", "1");
        if (!qEnvironmentVariable("SMALL_THEME_PREVIEW_DIR").isEmpty())
        {
            QFontDatabase::addApplicationFont("C:/Windows/Fonts/segoeui.ttf");
            QFontDatabase::addApplicationFont("C:/Windows/Fonts/consola.ttf");
        }
        // Do not change the developer's font/theme while running the tests.
        settingsDirectory_ = std::make_unique<QTemporaryDir>();
        QVERIFY(settingsDirectory_->isValid());
        QSettings::setDefaultFormat(QSettings::IniFormat);
        QSettings::setPath(QSettings::IniFormat, QSettings::UserScope, settingsDirectory_->path());
    }
    void init()
    {
        SmallSettings().clear();
    }

    void externalStyleSheetReloadRestoreAndFailure()
    {
        QTemporaryDir directory;
        QVERIFY(directory.isValid());
        const QString path = directory.filePath("custom.qss");
        writeFile(path, "QPlainTextEdit { background-color: #123456; color: #ffffff; }");
        MainWindow window;
        auto* document = current(window);
        document->appendPlainText("// keep my work");
        const QString source = document->toPlainText();
        QString error;
        QVERIFY(window.loadStyleSheet(path, &error));
        QVERIFY(error.isEmpty());
        QCOMPARE(document->palette().color(QPalette::Base), QColor("#123456"));
        QCOMPARE(SmallSettings().value("appearance/styleSheetPath").toString(), path);
        action(window, "actionThemeDark")->trigger();
        QCOMPARE(document->palette().color(QPalette::Base), QColor("#123456"));
        action(window, "actionNew")->trigger();
        QCOMPARE(current(window)->palette().color(QPalette::Base), QColor("#123456"));
        action(window, "actionApiReference")->trigger();
        QPointer<QWidget> api;
        for (auto* widget : QApplication::topLevelWidgets())
            if (widget->objectName() == "apiBrowser") api = widget;
        QVERIFY(api);
        QVERIFY(api->styleSheet().contains("#123456"));
        {
            MainWindow restored;
            QCOMPARE(current(restored)->palette().color(QPalette::Base), QColor("#123456"));
        }
        writeFile(path, "QPlainTextEdit { background-color: #654321; }");
        action(window, "actionReloadStyleSheet")->trigger();
        QCOMPARE(document->palette().color(QPalette::Base), QColor("#654321"));
        QVERIFY(api->styleSheet().contains("#654321"));
        const QString loadedStyle = window.styleSheet();
        QVERIFY(!window.loadStyleSheet(directory.filePath("missing.qss"), &error));
        QVERIFY(!error.isEmpty());
        QCOMPARE(window.styleSheet(), loadedStyle);
        QVERIFY(QFile::remove(path));
        {
            MainWindow missing;
            QVERIFY(!missing.styleSheet().contains("#654321"));
            QCOMPARE(missing.palette().color(QPalette::Window), QColor("#171d29"));
        }
        action(window, "actionResetStyleSheet")->trigger();
        QVERIFY(!window.styleSheet().contains("#654321"));
        QVERIFY(!api->styleSheet().contains("#654321"));
        QVERIFY(api->styleSheet().contains("QMenuBar"));
        QCOMPARE(document->palette().color(QPalette::Base), QColor("#1e1f22"));
        QVERIFY(!SmallSettings().contains("appearance/styleSheetPath"));
        QCOMPARE(document->toPlainText(), source);
        QVERIFY(document->document()->isModified());
    }

    void newTabsHaveIndependentState()
    {
        MainWindow window;
        QCOMPARE(tabs(window)->count(), 1);
        auto* first = current(window);
        first->appendPlainText("// first edit");
        const QString text = first->toPlainText();
        action(window, "actionNew")->trigger();
        QCOMPARE(tabs(window)->count(), 2);
        auto* second = current(window);
        QVERIFY(first != second);
        QCOMPARE(first->displayName(), QString("Untitled.cpp"));
        QCOMPARE(second->displayName(), QString("Untitled-2.cpp"));
        QVERIFY(!second->document()->isModified());
        second->appendPlainText("// second edit");
        QCOMPARE(first->toPlainText(), text);
        QVERIFY(tabs(window)->tabText(0).contains('*'));
        QVERIFY(tabs(window)->tabText(1).contains('*'));
        second->undo();
        QVERIFY(!second->toPlainText().contains("second edit"));
        QCOMPARE(first->toPlainText(), text);
    }

    void shortcutsSwitchWithoutEditing()
    {
        MainWindow window;
        window.show();
        auto* first = current(window);
        action(window, "actionNew")->trigger();
        auto* second = current(window);
        const QString firstText = first->toPlainText(), secondText = second->toPlainText();
        window.activateWindow();
        second->setFocus();
        QTest::qWait(50);
        QTest::keyClick(second, Qt::Key_Tab, Qt::ControlModifier);
        QTRY_COMPARE(current(window), first);
        QTest::keyClick(first, Qt::Key_Tab, Qt::ControlModifier | Qt::ShiftModifier);
        QTRY_COMPARE(current(window), second);
        QCOMPARE(first->toPlainText(), firstText);
        QCOMPARE(second->toPlainText(), secondText);
        QCOMPARE(action(window, "actionSave")->shortcut(), QKeySequence(QKeySequence::Save));
        QCOMPARE(action(window, "actionCloseTab")->shortcut(), QKeySequence(QKeySequence::Close));
    }

    void duplicateOpenKeepsUnsavedEdits()
    {
        QTemporaryDir folder;
        const QString path = folder.filePath("same.cpp");
        writeFile(path, "void SmallMain() {}\n");
        MainWindow window;
        QVERIFY(window.openDocument(path));
        auto* document = current(window);
        document->appendPlainText("// unsaved");
        const int count = tabs(window)->count();
        QVERIFY(window.openDocument(folder.filePath("./same.cpp")));
        QCOMPARE(tabs(window)->count(), count);
        QCOMPARE(current(window), document);
        QVERIFY(document->toPlainText().contains("// unsaved"));
        QVERIFY(document->document()->isModified());
    }

    void reorderedTabsSaveAndCloseCorrectFile()
    {
        QTemporaryDir folder;
        const QString a = folder.filePath("a.cpp"), b = folder.filePath("b.cpp");
        writeFile(a, "// A\n"); writeFile(b, "// B\n");
        MainWindow window;
        QVERIFY(window.openDocument(a)); auto* first = current(window);
        QVERIFY(window.openDocument(b)); QPointer<EditorDocument> second = current(window);
        first->appendPlainText("// changed A"); second->appendPlainText("// changed B");
        tabs(window)->tabBar()->moveTab(tabs(window)->indexOf(second), 0);
        tabs(window)->setCurrentWidget(second);
        action(window, "actionSave")->trigger();
        QVERIFY(readFile(b).contains("// changed B"));
        QVERIFY(!readFile(a).contains("// changed A"));
        QVERIFY(first->document()->isModified());
        QVERIFY(!second->document()->isModified());
        action(window, "actionCloseTab")->trigger();
        QVERIFY(second.isNull());
        QVERIFY(tabs(window)->indexOf(first) >= 0);
    }

    void sameBasenameDifferentFoldersRemainSeparate()
    {
        QTemporaryDir a, b;
        const QString first = a.filePath("game.cpp"), second = b.filePath("game.cpp");
        writeFile(first, "// first\n"); writeFile(second, "// second\n");
        MainWindow window;
        QVERIFY(window.openDocument(first)); auto* docA = current(window);
        QVERIFY(window.openDocument(second)); auto* docB = current(window);
        QVERIFY(docA != docB);
        QVERIFY(tabs(window)->tabToolTip(tabs(window)->indexOf(docA)) !=
                tabs(window)->tabToolTip(tabs(window)->indexOf(docB)));
    }

    void cancelTabCloseKeepsText()
    {
        MainWindow window;
        window.show();
        auto* document = current(window);
        document->appendPlainText("// keep me");
        closeWith(window, QMessageBox::Cancel);
        QCOMPARE(current(window), document);
        QVERIFY(document->document()->isModified());
        QVERIFY(document->toPlainText().contains("keep me"));
    }

    void discardLastTabLeavesAnEmptyDocument()
    {
        MainWindow window;
        window.show();
        QPointer<EditorDocument> previous = current(window);
        previous->appendPlainText("// discard me");
        closeWith(window, QMessageBox::Discard);
        QVERIFY(previous.isNull());
        QCOMPARE(tabs(window)->count(), 1);
        QVERIFY(!current(window)->document()->isModified());
        QVERIFY(current(window)->toPlainText().contains("void SmallMain()"));
    }

    void cancellingSaveDialogKeepsTab()
    {
        MainWindow window;
        window.show();
        auto* document = current(window);
        document->appendPlainText("// keep after cancel Save As");
        bool sawSaveDialog = false;
        QTimer response;
        response.setInterval(5);
        connect(&response, &QTimer::timeout, &window, [&] {
            auto* active = QApplication::activeModalWidget();
            if (auto* box = qobject_cast<QMessageBox*>(active)) box->button(QMessageBox::Save)->click();
            else if (auto* dialog = qobject_cast<QFileDialog*>(active))
            {
                sawSaveDialog = true;
                response.stop();
                dialog->reject();
            }
        });
        response.start();
        action(window, "actionCloseTab")->trigger();
        QVERIFY(sawSaveDialog);
        QCOMPARE(current(window), document);
        QVERIFY(document->document()->isModified());
    }

    void saveAsUsesCurrentUntitledName()
    {
        QTemporaryDir folder;
        MainWindow window;
        window.show();
        action(window, "actionNew")->trigger();
        auto* document = current(window);
        document->appendPlainText("// save this tab");
        bool named = false;
        QTimer response;
        response.setInterval(5);
        const QString path = folder.filePath("saved.cpp");
        connect(&response, &QTimer::timeout, &window, [&] {
            if (auto* dialog = qobject_cast<QFileDialog*>(QApplication::activeModalWidget()))
            {
                named = dialog->selectedFiles().value(0).endsWith("Untitled-2.cpp");
                response.stop();
                dialog->selectFile(path);
                QMetaObject::invokeMethod(dialog, "accept", Qt::QueuedConnection);
            }
        });
        response.start();
        action(window, "actionSave")->trigger();
        QVERIFY(named);
        QVERIFY(readFile(path).contains("save this tab"));
        QVERIFY(!document->document()->isModified());
        QVERIFY(window.windowTitle().contains("saved.cpp"));
    }

    void saveAsCannotOverwriteAnotherOpenDocument()
    {
        QTemporaryDir folder;
        const QString path = folder.filePath("existing.cpp");
        const QByteArray original("// disk original\n");
        writeFile(path, original);
        MainWindow window;
        window.show();
        QVERIFY(window.openDocument(path));
        auto* existing = current(window);
        existing->appendPlainText("// unsaved in first tab");
        action(window, "actionNew")->trigger();
        auto* fresh = current(window);
        fresh->appendPlainText("// must not overwrite existing");
        bool rejected = false;
        QTimer response;
        response.setInterval(5);
        connect(&response, &QTimer::timeout, &window, [&] {
            auto* active = QApplication::activeModalWidget();
            if (auto* dialog = qobject_cast<QFileDialog*>(active))
            {
                dialog->setOption(QFileDialog::DontConfirmOverwrite);
                dialog->selectFile(path);
                QMetaObject::invokeMethod(dialog, "accept", Qt::QueuedConnection);
            }
            else if (auto* box = qobject_cast<QMessageBox*>(active))
            {
                rejected = box->windowTitle() == "File already open";
                response.stop();
                box->accept();
            }
        });
        response.start();
        action(window, "actionSaveAs")->trigger();
        QVERIFY(rejected);
        QCOMPARE(readFile(path), original);
        QVERIFY(fresh->filePath().isEmpty());
        QVERIFY(fresh->document()->isModified());
        QVERIFY(existing->document()->isModified());
    }

    void cancelExitRetainsAllTabsEvenAfterDiscard()
    {
        MainWindow window;
        window.show();
        auto* first = current(window);
        first->appendPlainText("// keep first");
        action(window, "actionNew")->trigger();
        auto* second = current(window);
        second->appendPlainText("// keep second");
        int prompts = 0;
        QTimer response;
        response.setInterval(5);
        connect(&response, &QTimer::timeout, &window, [&] {
            if (auto* box = qobject_cast<QMessageBox*>(QApplication::activeModalWidget()))
            {
                ++prompts;
                const auto choice = prompts == 1 ? QMessageBox::Discard : QMessageBox::Cancel;
                if (prompts == 2) response.stop();
                box->button(choice)->click();
            }
        });
        response.start();
        QVERIFY(!window.close());
        QCOMPARE(prompts, 2);
        QCOMPARE(tabs(window)->count(), 2);
        QVERIFY(first->document()->isModified());
        QVERIFY(second->document()->isModified());
        QVERIFY(first->toPlainText().contains("keep first"));
    }

    void appearanceAppliesToCurrentHiddenAndFutureTabs()
    {
        MainWindow window;
        auto* first = current(window);
        QCOMPARE(first->font().pointSize(), 14);
        QCOMPARE(first->font().family(), QString("Consolas"));
        action(window, "actionNew")->trigger();
        auto* second = current(window);
        action(window, "actionThemeDark")->trigger();
        QCOMPARE(window.palette().color(QPalette::Window), QColor("#171d29"));
        QCOMPARE(window.menuBar()->palette().color(QPalette::WindowText), QColor("#e6e6e6"));
        const QString previewDirectory = qEnvironmentVariable("SMALL_THEME_PREVIEW_DIR");
        if (!previewDirectory.isEmpty())
        {
            window.resize(1000, 750);
            window.show();
            QApplication::processEvents();
            window.grab().save(previewDirectory + "/theme-dark.png");
        }
        QCOMPARE(first->palette().base().color(), QColor("#1e1f22"));
        QCOMPARE(first->palette().alternateBase().color(), QColor("#292b2f"));
        QCOMPARE(second->palette().base().color(), QColor("#1e1f22"));
        action(window, "actionNew")->trigger();
        QCOMPARE(current(window)->palette().base().color(), QColor("#1e1f22"));
        action(window, "actionThemeLight")->trigger();
        QCOMPARE(window.palette().color(QPalette::Window), QColor("#f3f5f9"));
        QCOMPARE(window.menuBar()->palette().color(QPalette::WindowText), QColor("#202124"));
        if (!previewDirectory.isEmpty())
        {
            QApplication::processEvents();
            window.grab().save(previewDirectory + "/theme-light.png");
        }
        QCOMPARE(first->palette().base().color(), QColor("#ffffff"));
        QCOMPARE(first->palette().alternateBase().color(), QColor("#f3f4f6"));
        QCOMPARE(second->palette().base().color(), QColor("#ffffff"));
        QCOMPARE(window.findChild<QPlainTextEdit*>("output")->font().pointSize(), 14);
    }

    void compileErrorTargetsOriginNotCurrentTab()
    {
        MainWindow window;
        auto* origin = current(window);
        const QString bad = "void SmallMain()\n{\n    Print(noSuchName);\n}\n";
        origin->setPlainText(bad);
        auto* build = window.findChild<BuildController*>();
        QSignalSpy errors(build, &BuildController::buildError);
        action(window, "actionRun")->trigger();
        action(window, "actionNew")->trigger();
        auto* other = current(window);
        other->setPlainText(bad); // Same text, different document identity.
        QTRY_VERIFY_WITH_TIMEOUT(!errors.isEmpty(), 30000);
        QCOMPARE(current(window), other);
        QVERIFY(hasError(origin));
        QVERIFY(!hasError(other));
        QVERIFY(window.findChild<QLabel*>("diagnosticsLabel")->text().contains("Untitled.cpp"));
    }

    void changedOriginDoesNotReceiveStaleHighlight()
    {
        MainWindow window;
        auto* origin = current(window);
        origin->setPlainText("void SmallMain(){ Print(noSuchName); }\n");
        auto* build = window.findChild<BuildController*>();
        QSignalSpy errors(build, &BuildController::buildError);
        action(window, "actionRun")->trigger();
        origin->setPlainText("void SmallMain() {}\n");
        QTRY_VERIFY_WITH_TIMEOUT(!errors.isEmpty(), 30000);
        QVERIFY(!hasError(origin));
        QVERIFY(window.findChild<QPlainTextEdit*>("output")->toPlainText().contains("earlier snapshot"));
    }

    void closedOriginDoesNotMarkReplacementTab()
    {
        MainWindow window;
        QPointer<EditorDocument> origin = current(window);
        const QString bad = "void SmallMain(){ Print(noSuchName); }\n";
        origin->setPlainText(bad);
        origin->document()->setModified(false);
        auto* build = window.findChild<BuildController*>();
        QSignalSpy errors(build, &BuildController::buildError);
        action(window, "actionRun")->trigger();
        action(window, "actionCloseTab")->trigger();
        QVERIFY(origin.isNull());
        auto* replacement = current(window);
        replacement->setPlainText(bad);
        QTRY_VERIFY_WITH_TIMEOUT(!errors.isEmpty(), 30000);
        QVERIFY(!hasError(replacement));
        QVERIFY(window.findChild<QLabel*>("diagnosticsLabel")->text().contains("closed tab"));
    }

    void runUsesOnlySelectedFileAndItsWorkingDirectory()
    {
        QTemporaryDir folder;
        const QString invalidPath = folder.filePath("other.cpp");
        const QString validPath = folder.filePath("run-me.cpp");
        writeFile(invalidPath, "this is deliberately not C++;\n");
        writeFile(validPath,
            "void SmallMain(){ File f; f.Open(\"selected.txt\", FileMode::Write); f.Print(42); }\n");
        MainWindow window;
        QVERIFY(window.openDocument(invalidPath));
        auto* other = current(window);
        QVERIFY(window.openDocument(validPath));
        auto* build = window.findChild<BuildController*>();
        QSignalSpy errors(build, &BuildController::buildError);
        QSignalSpy finished(build, &BuildController::finished);
        action(window, "actionRun")->trigger();
        tabs(window)->setCurrentWidget(other);
        QTRY_VERIFY_WITH_TIMEOUT(!finished.isEmpty() || !errors.isEmpty(), 30000);
        QVERIFY2(errors.isEmpty(), qPrintable(errors.isEmpty() ? QString{} : errors.first()[0].toString()));
        QCOMPARE(finished.first()[0].toInt(), 0);
        QVERIFY(readFile(folder.filePath("selected.txt")).startsWith("42"));
        QCOMPARE(current(window), other);
    }

    void runtimeErrorRemainsBoundToOrigin()
    {
        MainWindow window;
        auto* origin = current(window);
        origin->setPlainText("void SmallMain(){ Array<int> a(2); Print(a[5]); }\n");
        auto* build = window.findChild<BuildController*>();
        QSignalSpy failed(build, &BuildController::buildError);
        QSignalSpy runtime(build, &BuildController::runtimeError);
        QSignalSpy finished(build, &BuildController::finished);
        action(window, "actionRun")->trigger();
        action(window, "actionNew")->trigger();
        auto* other = current(window);
        QTRY_VERIFY_WITH_TIMEOUT(!runtime.isEmpty() || !failed.isEmpty(), 30000);
        QVERIFY2(failed.isEmpty(), qPrintable(failed.isEmpty() ? QString{} : failed.first()[0].toString()));
        QVERIFY(!runtime.isEmpty());
        QCOMPARE(current(window), other);
        QVERIFY(!hasError(other));
        QVERIFY(window.findChild<QLabel*>("diagnosticsLabel")->text().contains("Untitled.cpp"));
    }
};

QTEST_MAIN(TabTests)
#include "test_tabs.moc"
