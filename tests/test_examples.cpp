#include "MainWindow.h"
#include "WindowTestSupport.h"
#include "LearnWindowTestHelpers.h"
#include "BuildController.h"
#include "EditorDocument.h"
#include "ExampleCatalog.h"
#include "ExamplesBrowser.h"

#include <QAbstractButton>
#include <QAction>
#include <QApplication>
#include <QClipboard>
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QFont>
#include <QLabel>
#include <QMessageBox>
#include <QPointer>
#include <QPushButton>
#include <QSet>
#include <QSettings>
#include "SmallSettings.h"
#include <QSignalSpy>
#include <QTabBar>
#include <QTabWidget>
#include <QTemporaryDir>
#include <QTest>
#include <QTextCursor>
#include <QTextDocument>
#include <QTimer>
#include <QTreeWidget>

class ExampleTests : public QObject
{
    Q_OBJECT
private:
    QTemporaryDir settingsDirectory_;
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
        return window.findChild<QAction*>(QString::fromLatin1(name));
    }
    static QByteArray read(const QString& path)
    {
        QFile file(path);
        return file.open(QIODevice::ReadOnly) ? file.readAll() : QByteArray{};
    }
    static ExamplesBrowser* browse(MainWindow& window)
    {
        action(window, "actionExamples")->trigger();
        return learnWindow<ExamplesBrowser>();
    }

private slots:
    void initTestCase()
    {
        QVERIFY(settingsDirectory_.isValid());
        QSettings::setDefaultFormat(QSettings::IniFormat);
        QSettings::setPath(QSettings::IniFormat, QSettings::UserScope, settingsDirectory_.path());
        QApplication::setQuitOnLastWindowClosed(false);
        qputenv("SMALL_TEST_DIALOGS", "1");
        qputenv("SMALL_TEST_NO_CONSOLE_PAUSE", "1");
    }
    void init() { SmallSettings().clear(); }
    void cleanup() { QCoreApplication::sendPostedEvents(nullptr, QEvent::DeferredDelete); }

    void catalogContainsCoreAndExtensionPrograms()
    {
        ExampleCatalog catalog;
        QVERIFY2(catalog.isValid(), qPrintable(catalog.errorString()));
        QCOMPARE(catalog.entries().size(), 24);
        int reference = 0, programs = 0, extensions = 0;
        QSet<QString> ids;
        for (const auto& entry : catalog.entries())
        {
            QVERIFY(!ids.contains(entry.id));
            ids.insert(entry.id);
            QVERIFY(!entry.title.isEmpty());
            QVERIFY(!entry.description.isEmpty());
            QVERIFY(!entry.concepts.isEmpty());
            QVERIFY(!entry.notes.isEmpty());
            QVERIFY(entry.code.contains("void small_main()"));
            const QString path = entry.group.startsWith("Extensions / ")
                ? QCoreApplication::applicationDirPath() + "/extensions/image/examples/" + entry.sourceName
                : ":/small/examples/" + entry.sourceName;
            QCOMPARE(entry.code, QString::fromUtf8(read(path)));
            if (entry.group.startsWith("Extensions / ")) ++extensions;
            QCOMPARE(catalog.find(entry.id), &entry);
            if (entry.group == "Reference") ++reference;
            if (entry.group == "Programs") ++programs;
        }
        QCOMPARE(reference, 14);
        QCOMPARE(extensions, 3);
        QCOMPARE(programs, 7);
    }

    void catalogDoesNotDependOnWorkingDirectory()
    {
        QTemporaryDir empty;
        const QString previous = QDir::currentPath();
        QVERIFY(QDir::setCurrent(empty.path()));
        ExampleCatalog catalog;
        const bool valid = catalog.isValid();
        const auto* entry = catalog.find("programs/pong");
        const bool found = entry && !entry->code.isEmpty();
        const bool restored = QDir::setCurrent(previous);
        QVERIFY(restored);
        QVERIFY(valid);
        QVERIFY(found);
    }

    void browserIsCreatedOnlyWhenRequestedAndIsReused()
    {
        MainWindow window;
        OpenNewProgram(window);
        QVERIFY(!learnWindow<ExamplesBrowser>());
        auto* browser = browse(window);
        QVERIFY(browser);
        QVERIFY(!browser->isModal());
        QVERIFY(browser->selectExample("programs/pong"));
        browser->reject();
        QCOMPARE(browse(window), browser);
        QCOMPARE(browser->selectedId(), QString("programs/pong"));
        QCOMPARE(learnWindowCount<ExamplesBrowser>(), 1);
    }

    void browserPreviewMatchesEveryCatalogEntry()
    {
        ExampleCatalog catalog;
        ExamplesBrowser browser(catalog);
        auto* preview = browser.findChild<CodeEditor*>("examplePreview");
        auto* open = browser.findChild<QPushButton*>("openExampleButton");
        QVERIFY(preview);
        QVERIFY(preview->isReadOnly());
        for (const auto& entry : catalog.entries())
        {
            QVERIFY(browser.selectExample(entry.id));
            QCOMPARE(preview->toPlainText(), entry.code);
            QCOMPARE(browser.findChild<QLabel*>("exampleTitle")->text(), entry.title);
            QCOMPARE(browser.findChild<QLabel*>("exampleDescription")->text(), entry.description);
            QVERIFY(open->isEnabled());
        }
    }

    void categorySelectionCannotOpenADocument()
    {
        ExampleCatalog catalog;
        ExamplesBrowser browser(catalog);
        auto* tree = browser.findChild<QTreeWidget*>("exampleList");
        auto* open = browser.findChild<QPushButton*>("openExampleButton");
        QCOMPARE(tree->topLevelItemCount(), 3);
        tree->setCurrentItem(tree->topLevelItem(0));
        QVERIFY(browser.selectedId().isEmpty());
        QVERIFY(!open->isEnabled());
        QSignalSpy requested(&browser, &ExamplesBrowser::exampleRequested);
        open->click();
        QCOMPARE(requested.size(), 0);
    }

    void openFromBrowserKeepsDirtyUserTab()
    {
        MainWindow window;
        OpenNewProgram(window);
        auto* user = current(window);
        user->appendPlainText("// do not replace this code");
        const QString original = user->toPlainText();
        auto* browser = browse(window);
        QVERIFY(browser->selectExample("programs/bouncing_ball"));
        browser->findChild<QPushButton*>("openExampleButton")->click();
        QCOMPARE(tabs(window)->count(), 2);
        QVERIFY(current(window)->isExample());
        QCOMPARE(current(window)->exampleId(), QString("programs/bouncing_ball"));
        QCOMPARE(user->toPlainText(), original);
        QVERIFY(user->document()->isModified());
        QVERIFY(!browser->isVisible());
    }

    void repeatedOpenUsesExistingExampleEvenAfterReorder()
    {
        MainWindow window;
        OpenNewProgram(window);
        QVERIFY(window.openExample("reference/string"));
        auto* example = current(window);
        QVERIFY(window.openExample("programs/pong"));
        tabs(window)->tabBar()->moveTab(tabs(window)->indexOf(example), 0);
        const int count = tabs(window)->count();
        QVERIFY(window.openExample("reference/string"));
        QCOMPARE(tabs(window)->count(), count);
        QCOMPARE(current(window), example);
    }

    void invalidExampleIdLeavesDocumentsAlone()
    {
        MainWindow window;
        OpenNewProgram(window);
        auto* original = current(window);
        const int count = tabs(window)->count();
        QVERIFY(!window.openExample("../../runtime/small.h"));
        QVERIFY(!window.openExample("missing"));
        QCOMPARE(current(window), original);
        QCOMPARE(tabs(window)->count(), count);
    }

    void exampleDoesNotConsumeAnUntitledName()
    {
        MainWindow window;
        OpenNewProgram(window);
        QVERIFY(window.openExample("reference/array"));
        action(window, "actionNew")->trigger();
        QCOMPARE(current(window)->displayName(), QString("Untitled-2.cpp"));
    }

    void exampleSourceResistsTypingIndentAndPaste()
    {
        MainWindow window;
        OpenNewProgram(window);
        window.show();
        QVERIFY(window.openExample("reference/string"));
        auto* example = current(window);
        const QString original = example->toPlainText();
        QVERIFY(example->isReadOnly());
        QVERIFY(example->filePath().isEmpty());
        QTest::keyClicks(example, "oops");
        QTest::keyClick(example, Qt::Key_Tab);
        QTest::keyClick(example, Qt::Key_Return);
        QTest::keyClick(example, Qt::Key_Backspace);
        QApplication::clipboard()->setText("replacement");
        example->selectAll();
        example->paste();
        example->cut();
        example->undo();
        QCOMPARE(example->toPlainText(), original);
        QVERIFY(!example->document()->isModified());
    }

    void tryCreatesADirtyIndependentCopy()
    {
        MainWindow window;
        OpenNewProgram(window);
        QVERIFY(window.openExample("reference/string"));
        auto* example = current(window);
        const QString original = example->toPlainText();
        action(window, "actionTryExample")->trigger();
        auto* copy = current(window);
        QVERIFY(copy != example);
        QVERIFY(!copy->isExample());
        QVERIFY(!copy->isReadOnly());
        QVERIFY(copy->filePath().isEmpty());
        QCOMPARE(copy->displayName(), QString("Untitled-2.cpp"));
        QCOMPARE(copy->toPlainText(), original);
        QVERIFY(copy->document()->isModified());
        copy->appendPlainText("// my version");
        QCOMPARE(example->toPlainText(), original);
        QVERIFY(!example->document()->isModified());
        QVERIFY(tabs(window)->tabText(tabs(window)->indexOf(copy)).contains('*'));
    }

    void exampleControlsAreContextual()
    {
        MainWindow window;
        OpenNewProgram(window);
        window.show();
        auto* user = current(window);
        auto* controls = window.findChild<QWidget*>("exampleTabTools");
        QVERIFY(controls->isHidden());
        QVERIFY(window.openExample("programs/pong"));
        QVERIFY(!controls->isHidden());
        QVERIFY(action(window, "actionTryExample")->isEnabled());
        QVERIFY(action(window, "actionRun")->isEnabled());
        QVERIFY(!action(window, "actionSave")->isEnabled());
        QCOMPARE(action(window, "actionSaveAs")->text(), QString("Save a Copy..."));
        tabs(window)->setCurrentWidget(user);
        QVERIFY(controls->isHidden());
        QVERIFY(!action(window, "actionTryExample")->isEnabled());
        QVERIFY(action(window, "actionSave")->isEnabled());
        QCOMPARE(action(window, "actionSaveAs")->text(), QString("Save As..."));
    }

    void closingExampleDoesNotAskToSave()
    {
        MainWindow window;
        OpenNewProgram(window);
        auto* user = current(window);
        QVERIFY(window.openExample("reference/console"));
        QPointer<EditorDocument> example = current(window);
        action(window, "actionCloseTab")->trigger();
        QVERIFY(example.isNull());
        QCOMPARE(tabs(window)->count(), 1);
        QCOMPARE(current(window), user);
    }

    void cancellingTryCloseKeepsTheCopy()
    {
        MainWindow window;
        OpenNewProgram(window);
        window.show();
        QVERIFY(window.openExample("reference/string"));
        action(window, "actionTryExample")->trigger();
        auto* copy = current(window);
        bool asked = false;
        QTimer choose;
        choose.setInterval(5);
        connect(&choose, &QTimer::timeout, &window, [&] {
            if (auto* box = qobject_cast<QMessageBox*>(QApplication::activeModalWidget()))
            {
                asked = true;
                choose.stop();
                box->button(QMessageBox::Cancel)->click();
            }
        });
        choose.start();
        action(window, "actionCloseTab")->trigger();
        QVERIFY(asked);
        QCOMPARE(current(window), copy);
        QVERIFY(copy->document()->isModified());
    }

    void cancellingSaveCopyCreatesNoFileOrTab()
    {
        MainWindow window;
        OpenNewProgram(window);
        window.show();
        QVERIFY(window.openExample("programs/pong"));
        auto* example = current(window);
        const int count = tabs(window)->count();
        bool defaultNameCorrect = false;
        QTimer choose;
        choose.setInterval(5);
        connect(&choose, &QTimer::timeout, &window, [&] {
            if (auto* dialog = qobject_cast<QFileDialog*>(QApplication::activeModalWidget()))
            {
                defaultNameCorrect = dialog->selectedFiles().value(0).endsWith("pong.cpp");
                choose.stop();
                dialog->reject();
            }
        });
        choose.start();
        action(window, "actionSaveAs")->trigger();
        QVERIFY(defaultNameCorrect);
        QCOMPARE(tabs(window)->count(), count);
        QCOMPARE(current(window), example);
        QVERIFY(example->filePath().isEmpty());
        QVERIFY(example->isReadOnly());
    }

    void saveCopyPreservesExampleAndOpensNormalSavedTab()
    {
        QTemporaryDir folder;
        const QString path = folder.filePath("my-pong.cpp");
        MainWindow window;
        OpenNewProgram(window);
        window.show();
        QVERIFY(window.openExample("programs/pong"));
        auto* example = current(window);
        const QString original = example->toPlainText();
        QTimer choose;
        choose.setInterval(5);
        connect(&choose, &QTimer::timeout, &window, [&] {
            if (auto* dialog = qobject_cast<QFileDialog*>(QApplication::activeModalWidget()))
            {
                choose.stop();
                dialog->selectFile(path);
                QMetaObject::invokeMethod(dialog, "accept", Qt::QueuedConnection);
            }
        });
        choose.start();
        action(window, "actionSaveAs")->trigger();
        auto* copy = current(window);
        QVERIFY(copy != example);
        QVERIFY(!copy->isReadOnly());
        QVERIFY(!copy->isExample());
        QCOMPARE(copy->displayName(), QString("my-pong.cpp"));
        QVERIFY(!copy->document()->isModified());
        QCOMPARE(QString::fromUtf8(read(path)), original);
        QCOMPARE(example->toPlainText(), original);
        QVERIFY(example->isReadOnly());
        QVERIFY(example->filePath().isEmpty());
        ExampleCatalog again;
        QCOMPARE(again.find("programs/pong")->code, original);
    }

    void savingCopyCannotOverwriteAnotherOpenDocument()
    {
        QTemporaryDir folder;
        const QString path = folder.filePath("keep.cpp");
        { QFile f(path); QVERIFY(f.open(QIODevice::WriteOnly)); f.write("// original file\n"); }
        MainWindow window;
        OpenNewProgram(window);
        window.show();
        QVERIFY(window.openDocument(path));
        auto* user = current(window);
        user->appendPlainText("// unsaved edit");
        const QString unsaved = user->toPlainText();
        QVERIFY(window.openExample("programs/pong"));
        auto* example = current(window);
        const int count = tabs(window)->count();
        bool conflict = false;
        QTimer choose;
        choose.setInterval(5);
        connect(&choose, &QTimer::timeout, &window, [&] {
            if (auto* dialog = qobject_cast<QFileDialog*>(QApplication::activeModalWidget()))
            {
                dialog->setOption(QFileDialog::DontConfirmOverwrite);
                dialog->selectFile(path);
                QMetaObject::invokeMethod(dialog, "accept", Qt::QueuedConnection);
            }
            else if (auto* box = qobject_cast<QMessageBox*>(QApplication::activeModalWidget()))
            {
                conflict = box->windowTitle() == "File already open";
                choose.stop();
                box->accept();
            }
        });
        choose.start();
        action(window, "actionSaveAs")->trigger();
        QVERIFY(conflict);
        QCOMPARE(tabs(window)->count(), count);
        QCOMPARE(current(window), example);
        QCOMPARE(user->toPlainText(), unsaved);
        QCOMPARE(read(path), QByteArray("// original file\n"));
    }

    void appearanceFollowsHiddenTabsAndPreview()
    {
        MainWindow window;
        OpenNewProgram(window);
        QVERIFY(window.openExample("reference/string"));
        auto* example = current(window);
        auto* browser = browse(window);
        auto* preview = browser->findChild<CodeEditor*>("examplePreview");
        QCOMPARE(preview->font().pointSize(), 14);
        QCOMPARE(preview->font().family(), QString("Consolas"));
        action(window, "actionThemeDark")->trigger();
        QCOMPARE(preview->palette().base().color(), QColor("#1e1f22"));
        QCOMPARE(example->palette().base().color(), QColor("#1e1f22"));
        QVERIFY(!example->document()->isModified());
        action(window, "actionTryExample")->trigger();
        QCOMPARE(current(window)->palette().base().color(), QColor("#1e1f22"));
        QVERIFY(current(window)->document()->isModified());
        action(window, "actionThemeLight")->trigger();
        QCOMPARE(preview->palette().base().color(), QColor("#ffffff"));
        QCOMPARE(example->palette().base().color(), QColor("#ffffff"));
        QVERIFY(!example->document()->isModified());
        QVERIFY(current(window)->document()->isModified());
    }

    void rememberedFontAppliesToBrowserAndCopies()
    {
        const QFont font("Consolas", 18);
        SmallSettings().setValue("appearance/font", font);
        MainWindow window;
        OpenNewProgram(window);
        auto* browser = browse(window);
        QCOMPARE(browser->findChild<CodeEditor*>("examplePreview")->font().pointSize(), 18);
        QVERIFY(window.openExample("reference/array"));
        action(window, "actionTryExample")->trigger();
        QCOMPARE(current(window)->font().pointSize(), 18);
    }

    void readOnlyExampleRunsWithoutTurningIntoAFile()
    {
        MainWindow window;
        OpenNewProgram(window);
        auto* user = current(window);
        const QString userText = user->toPlainText();
        QVERIFY(window.openExample("reference/array"));
        auto* example = current(window);
        auto* build = window.findChild<BuildController*>();
        QSignalSpy errors(build, &BuildController::buildError);
        QSignalSpy finished(build, &BuildController::finished);
        action(window, "actionRun")->trigger();
        QCOMPARE(build->sourceSnapshot(), example->toPlainText());
        tabs(window)->setCurrentWidget(user);
        QTRY_VERIFY_WITH_TIMEOUT(!finished.isEmpty() || !errors.isEmpty(), 45000);
        QVERIFY2(errors.isEmpty(), qPrintable(errors.isEmpty() ? QString{} : errors.first()[0].toString()));
        QCOMPARE(finished.first()[0].toInt(), 0);
        QVERIFY(example->isReadOnly());
        QVERIFY(example->filePath().isEmpty());
        QVERIFY(!example->document()->isModified());
        QCOMPARE(current(window), user);
        QCOMPARE(user->toPlainText(), userText);
        QVERIFY(window.findChild<QLabel*>("diagnosticsLabel")->text().contains("Array [Example]"));
    }
};

QTEST_MAIN(ExampleTests)
#include "test_examples.moc"
