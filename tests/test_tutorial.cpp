#include "MainWindow.h"
#include "WindowTestSupport.h"
#include "LearnWindowTestHelpers.h"
#include "BuildController.h"
#include "EditorDocument.h"
#include "CodeEditor.h"
#include "ExampleCatalog.h"
#include "TutorialCatalog.h"
#include "TutorialBrowser.h"

#include <QAbstractButton>
#include <QAction>
#include <QApplication>
#include <QClipboard>
#include <QDir>
#include <QFontDatabase>
#include <QGroupBox>
#include <QLabel>
#include <QMenu>
#include <QMessageBox>
#include <QPushButton>
#include <QRegularExpression>
#include <QScrollArea>
#include <QScrollBar>
#include <QSet>
#include <QSettings>
#include "SmallSettings.h"
#include <QSignalSpy>
#include <QTabWidget>
#include <QTemporaryDir>
#include <QTest>
#include <QTextDocument>
#include <QTextBlock>
#include <QTextLayout>
#include <QFile>
#include <QTimer>
#include <QTreeWidget>

class TutorialTests : public QObject
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
    static TutorialBrowser* browse(MainWindow& window)
    {
        action(window, "actionTutorial")->trigger();
        return learnWindow<TutorialBrowser>();
    }
    static QPushButton* button(TutorialBrowser& browser, const char* name)
    {
        return browser.findChild<QPushButton*>(QString::fromLatin1(name));
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

    void catalogContainsCompleteCoreAndExtensionLessons()
    {
        TutorialCatalog catalog;
        QVERIFY2(catalog.isValid(), qPrintable(catalog.errorString()));
        QCOMPARE(catalog.parts().size(), 9);
        QCOMPARE(catalog.lessons().size(), 100);
        QCOMPARE(catalog.availableIds().size(), 100);
        QVERIFY(catalog.find("text_files_1"));
        QVERIFY(catalog.find("binary_files_2"));
        QVERIFY(catalog.find("publish"));
        QVERIFY(catalog.find("extra_files"));
        QVERIFY(catalog.find("share"));
        QVERIFY(catalog.find("project_folder"));
        QVERIFY(catalog.find("project_headers"));
        QVERIFY(catalog.find("project_share"));
        int count = 0;
        for (const auto& lesson : catalog.lessons())
        {
            QVERIFY(!lesson.title.isEmpty());
            if (!lesson.available) { QVERIFY(lesson.exercises.isEmpty()); continue; }
            QVERIFY(!lesson.exercises.isEmpty());
            for (const auto& exercise : lesson.exercises)
            {
                ++count;
                QVERIFY(!exercise.hint.isEmpty());
                QVERIFY(!exercise.prompt.isEmpty());
                QVERIFY(exercise.starter.contains("small_main") || exercise.starter.contains("main("));
                QVERIFY(exercise.solution.contains("small_main") || exercise.solution.contains("main("));
            }
        }
        QCOMPARE(count, 103);
    }

    void catalogLoadsWithoutSourceFolderAsWorkingDirectory()
    {
        QTemporaryDir empty;
        const QString previous = QDir::currentPath();
        QVERIFY(QDir::setCurrent(empty.path()));
        TutorialCatalog catalog;
        const bool valid = catalog.isValid();
        const bool restored = QDir::setCurrent(previous);
        QVERIFY(restored);
        QVERIFY(valid);
        QVERIFY(catalog.find("hello"));
    }

    void sharingScreenshotsLoadAndFitTheLessonWidth()
    {
        const QString output = qEnvironmentVariable("SMALL_TUTORIAL_PREVIEW_DIR");
        if (!output.isEmpty()) {
            QFontDatabase::addApplicationFont(qEnvironmentVariable("SystemRoot") + "/Fonts/segoeui.ttf");
            QFontDatabase::addApplicationFont(qEnvironmentVariable("SystemRoot") + "/Fonts/segoeuib.ttf");
            QFontDatabase::addApplicationFont(qEnvironmentVariable("SystemRoot") + "/Fonts/malgun.ttf");
            QFontDatabase::addApplicationFont(qEnvironmentVariable("SystemRoot") + "/Fonts/malgunbd.ttf");
            QVERIFY(QDir().mkpath(output));
        }
        for (const QString& language : {QString("ko"), QString("en")}) {
            SmallSettings().setValue("tutorial/language", language);
            for (bool dark : {false, true}) {
                QCoreApplication::sendPostedEvents(nullptr, QEvent::DeferredDelete);
                SmallSettings().setValue("appearance/dark", dark);
                MainWindow parent;
                TutorialBrowser& browser = *browse(parent);
                if (!output.isEmpty()) browser.setFont(QFont("Malgun Gothic", 11));
                browser.resize(1000, 850);
                browser.show();
                browser.findChild<QTreeWidget*>("tutorialList")->collapseAll();
                for (const QString& id : {QString("publish"), QString("extra_files"), QString("share"),
                                          QString("project_headers"), QString("project_roles")}) {
                    QVERIFY(browser.selectLesson(id));
                    QTest::qWait(10);
                    auto* screenshot = browser.findChild<QLabel*>("tutorialScreenshot");
                    QVERIFY(screenshot);
                    QVERIFY(!screenshot->pixmap().isNull());
                    QVERIFY(!screenshot->accessibleName().isEmpty());
                    QVERIFY(screenshot->pixmap().width() <= screenshot->width());
                    QCOMPARE(screenshot->height(), screenshot->pixmap().height());
                    browser.resize(720, 850);
                    QTest::qWait(10);
                    QVERIFY(screenshot->pixmap().width() <= screenshot->width());
                    browser.resize(1000, 850);
                    if (!output.isEmpty()) {
                        QTest::qWait(10);
                        auto* scroll = browser.findChild<QScrollArea*>("tutorialScroll");
                        scroll->verticalScrollBar()->setValue(screenshot->mapTo(scroll->widget(), QPoint()).y() - 80);
                        QTest::qWait(10);
                        QVERIFY(browser.grab().save(QDir(output).filePath(
                            id + "-" + language + (dark ? "-dark.png" : "-light.png"))));
                    }
                }
                browser.close();
            }
        }
        SmallSettings().setValue("appearance/dark", false);
    }

    void englishLessonsAreTranslatedAndUnknownLanguageFallsBack()
    {
        TutorialCatalog korean("ko");
        TutorialCatalog english("en");
        TutorialCatalog unavailable("zz");
        QVERIFY2(english.isValid(), qPrintable(english.errorString()));
        for (const auto& part : korean.parts())
        {
            if (part.id.startsWith("extension")) continue;
            if (part.id == "sharing" || part.id == "algorithms" || part.id == "projects")
                QVERIFY(part.title.contains(QRegularExpression("[가-힣]")));
        }
        for (const auto& lesson : korean.lessons())
        {
            if (lesson.sourceDirectory.contains("/extensions/")) continue;
            const auto* translated = english.find(lesson.id);
            QVERIFY(translated);
            QVERIFY(translated->title != lesson.title);
            QVERIFY(!translated->title.contains(QRegularExpression("[가-힣]")));
            QCOMPARE(translated->exercises.size(), lesson.exercises.size());
            QCOMPARE(translated->exercises.first().solution, lesson.exercises.first().solution);
            const auto* fallback = unavailable.find(lesson.id);
            QVERIFY(fallback);
            QCOMPARE(fallback->title, lesson.title);
            QCOMPARE(fallback->exercises.size(), lesson.exercises.size());
            QCOMPARE(fallback->exercises.first().solution, lesson.exercises.first().solution);
        }
    }

    void learnMenuContainsBothBrowsers()
    {
        MainWindow window;
        OpenNewProgram(window);
        auto* learn = window.findChild<QMenu*>("menuLearn");
        QVERIFY(learn);
        QVERIFY(learn->actions().contains(action(window, "actionTutorial")));
        QVERIFY(learn->actions().contains(action(window, "actionExamples")));
        QVERIFY(!learnWindow<TutorialBrowser>());
    }

    void englishCanBeSelectedAndPreferenceIsSaved()
    {
        MainWindow window;
        OpenNewProgram(window);
        auto* menu = window.findChild<QMenu*>("menuTutorialLanguage");
        QVERIFY(menu);
        QAction* english = nullptr;
        for (auto* choice : menu->actions())
            if (choice->data().toString() == "en") english = choice;
        QVERIFY(english);
        english->trigger();
        QCOMPARE(SmallSettings().value("tutorial/language").toString(), QString("en"));
        auto* browser = browse(window);
        QVERIFY(browser->selectLesson("hello"));
        bool hasEnglishTitle = false;
        for (auto* label : browser->findChildren<QLabel*>())
            hasEnglishTitle |= label->text().contains("Showing text on the screen");
        QVERIFY(hasEnglishTitle);
        TutorialCatalog korean("ko");
        QString sharedCode;
        for (const auto& block : korean.find("hello")->blocks)
            if (block.kind == TutorialBlock::Kind::Code) { sharedCode = block.content; break; }
        QVERIFY(!sharedCode.isEmpty());
        QCOMPARE(browser->findChild<CodeEditor*>("tutorialExample1")->toPlainText(), sharedCode);
    }

    void browserIsLazyModelessAndReused()
    {
        MainWindow window;
        OpenNewProgram(window);
        auto* browser = browse(window);
        QVERIFY(browser);
        QVERIFY(!browser->isModal());
        QVERIFY(browser->selectLesson("if"));
        browser->reject();
        QCOMPARE(browse(window), browser);
        QCOMPARE(browser->selectedId(), QString("if"));
        QCOMPARE(learnWindowCount<TutorialBrowser>(), 1);
    }

    void projectListingsUseHighlightedCopyableCode()
    {
        const QString output = qEnvironmentVariable("SMALL_TUTORIAL_SNIPPET_PREVIEW_DIR");
        if (!output.isEmpty()) {
            QFontDatabase::addApplicationFont(qEnvironmentVariable("SystemRoot") + "/Fonts/segoeui.ttf");
            QFontDatabase::addApplicationFont(qEnvironmentVariable("SystemRoot") + "/Fonts/segoeuib.ttf");
            QFontDatabase::addApplicationFont(qEnvironmentVariable("SystemRoot") + "/Fonts/consola.ttf");
            QFontDatabase::addApplicationFont(qEnvironmentVariable("SystemRoot") + "/Fonts/malgun.ttf");
            QVERIFY(QDir().mkpath(output));
        }
        for (const QString& language : {QString("ko"), QString("en")}) {
            QCoreApplication::sendPostedEvents(nullptr, QEvent::DeferredDelete);
            SmallSettings().setValue("tutorial/language", language);
            MainWindow window;
            TutorialBrowser& browser = *browse(window);
            browser.setFont(QFont("Segoe UI", 11));
            browser.resize(1120, 900); browser.show();
            for (bool dark : {false, true}) {
                action(window, dark ? "actionThemeDark" : "actionThemeLight")->trigger();
                QVERIFY(browser.selectLesson("project_headers"));
                const QPalette colors = browser.findChild<CodeEditor*>("tutorialExample1")->palette();
                browser.setAppearance(QFont("Consolas", 14), colors, dark);
                const auto snippets = browser.findChildren<CodeEditor*>("tutorialSnippet");
                const auto copies = browser.findChildren<QPushButton*>("copyTutorialSnippet");
                QCOMPARE(snippets.size(), 3); QCOMPARE(copies.size(), 3);
                QSignalSpy tried(&browser, &TutorialBrowser::tryRequested);
                const QString sample = QFINDTESTDATA("../examples/projects/Greeting");
                const QStringList names{"greeting.h", "greeting.cpp", "main.cpp"};
                for (int i = 0; i < snippets.size(); ++i) {
                    QFile file(QDir(sample).filePath(names[i])); QVERIFY(file.open(QIODevice::ReadOnly));
                    QCOMPARE(snippets[i]->toPlainText(), QString::fromUtf8(file.readAll()).trimmed());
                    QVERIFY(snippets[i]->isReadOnly());
                    QCOMPARE(snippets[i]->font().pointSize(), 14);
                    QCOMPARE(snippets[i]->palette().color(QPalette::Base), colors.color(QPalette::Base));
                    QCoreApplication::processEvents();
                    bool highlighted = false;
                    for (auto block = snippets[i]->document()->begin(); block.isValid(); block = block.next())
                        for (const auto& range : block.layout()->formats())
                            highlighted |= range.format.foreground().color() != colors.color(QPalette::Text);
                    QVERIFY2(highlighted, "C++ listings need actual syntax highlighting.");
                    copies[i]->click();
                    QCOMPARE(QApplication::clipboard()->text(), snippets[i]->toPlainText());
                }
                QCOMPARE(tried.size(), 0); // Fragments cannot be tried as standalone programs.
                QCOMPARE(browser.findChildren<QPushButton*>("tryTutorialExample1").size(), 1);
                if (!output.isEmpty()) {
                    auto* scroll = browser.findChild<QScrollArea*>("tutorialScroll");
                    scroll->verticalScrollBar()->setValue(snippets.first()->mapTo(scroll->widget(), QPoint()).y() - 50);
                    QTest::qWait(30);
                    QVERIFY(browser.grab().save(QDir(output).filePath(language + (dark ? "-dark.png" : "-light.png"))));
                }
            }
            QVERIFY(browser.selectLesson("split_files"));
            QCOMPARE(browser.findChildren<CodeEditor*>("tutorialSnippet").size(), 2);
            QVERIFY(browser.selectLesson("project_roles"));
            QCOMPARE(browser.findChildren<CodeEditor*>("tutorialSnippet").size(), 3);
        }
    }
    void allPublishedPreviewsMatchCatalogAndStayReadOnly()
    {
        TutorialCatalog catalog;
        TutorialBrowser browser(catalog);
        for (const QString& id : catalog.availableIds())
        {
            QVERIFY(browser.selectLesson(id));
            const auto* lesson = catalog.find(id);
            int index = 0;
            for (const auto& block : lesson->blocks)
                if (block.kind == TutorialBlock::Kind::Code)
                {
                    auto* editor = browser.findChild<CodeEditor*>(QString("tutorialExample%1").arg(++index));
                    QVERIFY(editor);
                    QVERIFY(editor->isReadOnly());
                    QCOMPARE(editor->toPlainText(), block.content);
                }
            QCOMPARE(browser.findChildren<QGroupBox*>(QRegularExpression("^tutorialExercise[0-9]+$")).size(), lesson->exercises.size());
            for (int i = 0; i < lesson->exercises.size(); ++i)
            {
                auto* answer = browser.findChild<CodeEditor*>(QString("tutorialSolutionCode%1").arg(i + 1));
                QVERIFY(answer);
                QVERIFY(answer->isReadOnly());
                QCOMPARE(answer->toPlainText(), lesson->exercises[i].solution);
            }
        }
    }

    void everyLessonCanBeSelectedWithoutFinishingPreviousOnes()
    {
        TutorialCatalog catalog;
        TutorialBrowser browser(catalog);
        QVERIFY(browser.selectLesson("for"));
        QVERIFY(!browser.isRead("hello"));
        QVERIFY(button(browser, "tryTutorialExample1"));
        QVERIFY(browser.selectLesson("binary_files_1"));
        QVERIFY(!browser.findChild<QLabel*>("tutorialNotAvailable"));
        QVERIFY(button(browser, "tutorialNext")->isEnabled());
        QVERIFY(button(browser, "tryTutorialExample1"));
        QVERIFY(browser.selectLesson("hello"));
        QVERIFY(button(browser, "tryTutorialExample1")->isEnabled());
    }

    void invalidSelectionDoesNotChangeLesson()
    {
        TutorialCatalog catalog;
        TutorialBrowser browser(catalog);
        const QString before = browser.selectedId();
        QVERIFY(!browser.selectLesson("../../file"));
        QCOMPARE(browser.selectedId(), before);
    }

    void tryExampleCreatesNewDirtyTabAndKeepsExistingWork()
    {
        MainWindow window;
        OpenNewProgram(window);
        auto* original = current(window);
        original->appendPlainText("// keep my work");
        const QString snapshot = original->toPlainText();
        auto* browser = browse(window);
        QVERIFY(browser->selectLesson("hello"));
        const QString example = browser->findChild<CodeEditor*>("tutorialExample1")->toPlainText();
        button(*browser, "tryTutorialExample1")->click();
        QCOMPARE(tabs(window)->count(), 2);
        auto* copy = current(window);
        QVERIFY(copy != original);
        QVERIFY(copy->filePath().isEmpty());
        QVERIFY(copy->document()->isModified());
        QVERIFY(!copy->isReadOnly());
        QVERIFY(!copy->isExample());
        QCOMPARE(copy->toPlainText(), example);
        QCOMPARE(original->toPlainText(), snapshot);
        QVERIFY(original->document()->isModified());
        QVERIFY(browser->isVisible());
        QVERIFY(!window.findChild<BuildController*>()->isBusy());
    }

    void repeatedTryMakesIndependentCopies()
    {
        MainWindow window;
        OpenNewProgram(window);
        auto* browser = browse(window);
        button(*browser, "tryTutorialExample1")->click();
        auto* first = current(window);
        first->appendPlainText("// changed");
        button(*browser, "tryTutorialExample1")->click();
        QVERIFY(current(window) != first);
        QCOMPARE(tabs(window)->count(), 3);
        QVERIFY(!current(window)->toPlainText().contains("// changed"));
    }

    void allStartersForEveryPublishedLessonAreCopiedExactly()
    {
        MainWindow window;
        OpenNewProgram(window);
        TutorialCatalog catalog;
        auto* browser = browse(window);
        for (const QString& id : catalog.availableIds())
        {
            QVERIFY(browser->selectLesson(id));
            const auto* lesson = catalog.find(id);
            for (int i = 0; i < lesson->exercises.size(); ++i)
            {
                auto* tryButton = browser->findChild<QPushButton*>(QString("tryTutorialExercise%1").arg(i + 1));
                QVERIFY(tryButton);
                tryButton->click();
                QCOMPARE(current(window)->toPlainText(), lesson->exercises[i].starter);
                QVERIFY(current(window)->document()->isModified());
            }
        }
        int exercises = 0;
        for (const auto& lesson : catalog.lessons()) exercises += lesson.exercises.size();
        QCOMPARE(tabs(window)->count(), 1 + exercises);
    }

    void hintAndSolutionStartHiddenAndDoNotCreateTabsOrMarkRead()
    {
        MainWindow window;
        OpenNewProgram(window);
        auto* browser = browse(window);
        QVERIFY(browser->selectLesson("variables"));
        auto* hint = browser->findChild<QLabel*>("tutorialHint1");
        auto* answer = browser->findChild<QWidget*>("tutorialSolution1");
        QVERIFY(hint->isHidden());
        QVERIFY(answer->isHidden());
        button(*browser, "tutorialHintButton1")->click();
        button(*browser, "tutorialSolutionButton1")->click();
        QVERIFY(!hint->isHidden());
        QVERIFY(!answer->isHidden());
        QCOMPARE(tabs(window)->count(), 1);
        QVERIFY(!browser->isRead("variables"));
        button(*browser, "tutorialHintButton1")->click();
        button(*browser, "tutorialSolutionButton1")->click();
        QVERIFY(hint->isHidden());
        QVERIFY(answer->isHidden());
    }

    void trySolutionCreatesEditableCopyOfCompleteAnswer()
    {
        MainWindow window;
        OpenNewProgram(window);
        TutorialCatalog catalog;
        auto* browser = browse(window);
        QVERIFY(browser->selectLesson("if"));
        button(*browser, "tutorialSolutionButton1")->click();
        button(*browser, "tryTutorialSolution1")->click();
        QCOMPARE(current(window)->toPlainText(), catalog.find("if")->exercises[0].solution);
        QVERIFY(!current(window)->isReadOnly());
        QVERIFY(current(window)->document()->isModified());
    }

    void nextMarksReadAndPreviousDoesNotLockAnything()
    {
        TutorialCatalog catalog;
        TutorialBrowser browser(catalog);
        QVERIFY(browser.selectLesson("hello"));
        button(browser, "tutorialNext")->click();
        QVERIFY(browser.isRead("hello"));
        QCOMPARE(browser.selectedId(), QString("lines"));
        QVERIFY(!browser.isRead("variables"));
        button(browser, "tutorialPrevious")->click();
        QCOMPARE(browser.selectedId(), QString("hello"));
        QVERIFY(!button(browser, "tutorialPrevious")->isEnabled());
    }

    void readAndLastLessonPersistAcrossBrowserInstances()
    {
        TutorialCatalog catalog;
        {
            TutorialBrowser first(catalog);
            first.selectLesson("hello");
            button(first, "tutorialNext")->click();
        }
        TutorialBrowser second(catalog);
        QVERIFY(second.isRead("hello"));
        QCOMPARE(second.selectedId(), QString("lines"));
        QVERIFY(!second.isRead("variables"));
    }

    void finishOnlyMarksTheCurrentLesson()
    {
        TutorialCatalog catalog;
        TutorialBrowser browser(catalog);
        const QString last = catalog.availableIds().last();
        QVERIFY(browser.selectLesson(last));
        QCOMPARE(button(browser, "tutorialNext")->text(), QString("Finish"));
        button(browser, "tutorialNext")->click();
        QVERIFY(browser.isRead(last));
        QVERIFY(!browser.isRead("hello"));
        QCOMPARE(browser.selectedId(), last);
    }

    void unknownStoredIdsAreIgnored()
    {
        auto settings = SmallSettings();
        settings.setValue("tutorial/curriculumV2/lastLesson", "missing");
        settings.setValue("tutorial/curriculumV2/readLessons", QStringList{"missing", "hello", "binary_files_1"});
        TutorialCatalog catalog;
        TutorialBrowser browser(catalog);
        QCOMPARE(browser.selectedId(), QString("hello"));
        QVERIFY(browser.isRead("hello"));
        QVERIFY(!browser.isRead("missing"));
        QVERIFY(browser.isRead("binary_files_1"));
    }

    void fontAndThemeReachVisibleAndHiddenCodeWithoutResettingHint()
    {
        MainWindow window;
        OpenNewProgram(window);
        auto* browser = browse(window);
        button(*browser, "tutorialHintButton1")->click();
        action(window, "actionThemeDark")->trigger();
        QVERIFY(!browser->findChild<QLabel*>("tutorialHint1")->isHidden());
        auto* code = browser->findChild<CodeEditor*>("tutorialExample1");
        QCOMPARE(code->palette().color(QPalette::Base), QColor("#1e1f22"));
        QFont large("Consolas", 18);
        browser->setAppearance(large, code->palette(), true);
        QCOMPARE(code->font().pointSize(), 18);
        QCOMPARE(browser->findChild<CodeEditor*>("tutorialSolutionCode1")->font().pointSize(), 18);
        browser->selectLesson("variables");
        QCOMPARE(browser->findChild<CodeEditor*>("tutorialExample1")->font().pointSize(), 18);
    }

    void relatedExampleOpensReadOnlyWithoutClosingTutorial()
    {
        MainWindow window;
        OpenNewProgram(window);
        auto* browser = browse(window);
        button(*browser, "tutorialRelatedExample")->click();
        QVERIFY(current(window)->isExample());
        QCOMPARE(current(window)->exampleId(), QString("reference/console"));
        QVERIFY(browser->isVisible());
        QCOMPARE(tabs(window)->count(), 2);
    }

    void tutorialCodeResistsEditingAndClosingBrowserKeepsCopies()
    {
        MainWindow window;
        OpenNewProgram(window);
        auto* browser = browse(window);
        auto* code = browser->findChild<CodeEditor*>("tutorialExample1");
        const QString original = code->toPlainText();
        QTest::keyClicks(code, "oops");
        QTest::keyClick(code, Qt::Key_Tab);
        QTest::keyClick(code, Qt::Key_Return);
        QApplication::clipboard()->setText("replacement");
        code->selectAll();
        code->paste();
        QCOMPARE(code->toPlainText(), original);
        button(*browser, "tryTutorialExample1")->click();
        auto* copy = current(window);
        browser->reject();
        QCOMPARE(current(window), copy);
        QCOMPARE(tabs(window)->count(), 2);
    }

    void copiedExerciseUsesExistingSaveCancelProtection()
    {
        MainWindow window;
        OpenNewProgram(window);
        window.show();
        auto* browser = browse(window);
        button(*browser, "tryTutorialExercise1")->click();
        auto* copy = current(window);
        browser->reject();
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
};

QTEST_MAIN(TutorialTests)
#include "test_tutorial.moc"
