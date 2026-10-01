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
#include <QFileDialog>
#include <QFileSystemModel>
#include <QFontDatabase>
#include <QJsonDocument>
#include <QJsonArray>
#include <QInputDialog>
#include <QLabel>
#include <QMessageBox>
#include <QMenu>
#include <QPlainTextEdit>
#include <QProcess>
#include <QProcessEnvironment>
#include <QSignalSpy>
#include <QTabWidget>
#include <QTabBar>
#include <QTemporaryDir>
#include <QTest>
#include <QTextDocument>
#include <QTimer>
#include <QToolButton>
#include <QPushButton>
#include <QTreeWidget>
#include <QTreeView>

class FileLocationWindow : public MainWindow
{
public:
    QStringList locations;
protected:
    bool showInFileExplorer(const QString& path) override { locations << path; return true; }
};

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
        QFontDatabase::addApplicationFont(qEnvironmentVariable("SystemRoot") + "/Fonts/segoeui.ttf");
        QFontDatabase::addApplicationFont(qEnvironmentVariable("SystemRoot") + "/Fonts/segoeuib.ttf");
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
    void emptyDirectoriesAppearWithoutBecomingResources()
    {
        QTemporaryDir directory; fixture(directory.path());
        QVERIFY(QDir().mkpath(directory.filePath("Empty/Nested")));
        QVERIFY(QDir().mkpath(directory.filePath("build/Empty")));
        auto project = load(directory.path());
        QVERIFY(project.directories.contains("Empty"));
        QVERIFY(project.directories.contains("Empty/Nested"));
        QVERIFY(!project.directories.contains("build"));
        QCOMPARE(project.sources.size(), 2); QCOMPARE(project.resources.size(), 1);
        MainWindow window; QVERIFY(window.openProject(directory.path()));
        auto* tree = window.findChild<QTreeWidget*>("projectFiles");
        QCOMPARE(tree->findItems("Nested", Qt::MatchExactly | Qt::MatchRecursive).size(), 1);
        QVERIFY(QDir().mkdir(directory.filePath("Added")));
        QTRY_COMPARE_WITH_TIMEOUT(tree->findItems("Added", Qt::MatchExactly | Qt::MatchRecursive).size(), 1, 3000);
        QVERIFY(QDir().rmdir(directory.filePath("Added")));
        QTRY_VERIFY_WITH_TIMEOUT(tree->findItems("Added", Qt::MatchExactly | Qt::MatchRecursive).isEmpty(), 3000);
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
    void projectPickerShowsFilesAndAcceptsFolder()
    {
        QTemporaryDir directory; fixture(directory.filePath("MyGame"));
        MainWindow window;
        QCOMPARE(action(window, "actionOpenProject")->text(), QString("Open Project (Folder)..."));
        action(window, "actionThemeDark")->trigger();
        bool foldersOnly = false, filesShown = false, iconsHaveSpace = false, fileClickAllowsOpening = false, fileClicked = false;
        QTimer::singleShot(100, &window, [&] {
            auto* dialog = window.findChild<QFileDialog*>("openProjectFolderDialog");
            if (!dialog) return;
            foldersOnly = dialog->fileMode() == QFileDialog::Directory;
            auto* model = dialog->findChild<QFileSystemModel*>();
            filesShown = !dialog->testOption(QFileDialog::ShowDirsOnly) && model && (model->filter() & QDir::Files);
            iconsHaveSpace = true;
            for (auto* button : dialog->findChildren<QToolButton*>())
                iconsHaveSpace &= !button->icon().isNull() && button->width() >= button->iconSize().width() + 10;
            dialog->setDirectory(directory.filePath("MyGame"));
            QTimer::singleShot(200, dialog, [&, dialog] {
                auto* view = dialog->findChild<QTreeView*>("treeView");
                if (view) for (int row = 0; row < view->model()->rowCount(view->rootIndex()); ++row) {
                    const auto index = view->model()->index(row, 0, view->rootIndex());
                    if (index.data().toString() != "main.cpp") continue;
                    QTest::mouseClick(view->viewport(), Qt::LeftButton, Qt::NoModifier, view->visualRect(index).center());
                    fileClicked = view->selectionModel()->isSelected(index);
                }
                auto* open = dialog->findChild<QPushButton*>("openCurrentProjectFolder");
                fileClickAllowsOpening = open && open->isEnabled();
                const QString output = qEnvironmentVariable("SMALL_PROJECT_PREVIEW_DIR");
                if (!output.isEmpty()) dialog->grab().save(QDir(output).filePath("project-picker.png"));
                if (open) open->click(); else dialog->reject();
            });
        });
        action(window, "actionOpenProject")->trigger();
        QVERIFY(foldersOnly); QVERIFY(filesShown); QVERIFY(iconsHaveSpace); QVERIFY(fileClicked); QVERIFY(fileClickAllowsOpening);
        QCOMPARE(window.projectRoot(), QFileInfo(directory.filePath("MyGame")).canonicalFilePath());
    }
    void excludedFilesLookDifferentInBothThemes()
    {
        QTemporaryDir directory; fixture(directory.path());
        auto project = load(directory.path()); QString error;
        QVERIFY(project.setExcluded("logic", true, &error));
        MainWindow window; QVERIFY(window.openProject(directory.path()));
        auto* tree = window.findChild<QTreeWidget*>("projectFiles");
        window.show(); tree->expandAll();
        for (bool dark : {false, true}) {
            action(window, dark ? "actionThemeDark" : "actionThemeLight")->trigger();
            const auto items = tree->findItems("value.cpp (Excluded)", Qt::MatchExactly | Qt::MatchRecursive);
            QCOMPARE(items.size(), 1);
            QTRY_COMPARE_WITH_TIMEOUT(items.first()->foreground(0).color(), QColor(dark ? "#8993a3" : "#929aa6"), 3000);
            QVERIFY(items.first()->font(0).italic());
            tree->setCurrentItem(items.first()); tree->setFocus(); QTest::qWait(50);
            const QColor expected(dark ? "#8993a3" : "#929aa6");
            const QImage image = tree->viewport()->grab().toImage();
            const QRect row = tree->visualItemRect(items.first()).intersected(image.rect());
            int grayPixels = 0;
            for (int y = row.top(); y <= row.bottom(); ++y)
                for (int x = row.left(); x <= row.right(); ++x)
                    if (image.pixelColor(x, y).rgb() == expected.rgb()) ++grayPixels;
            QVERIFY2(grayPixels > 5, "Focused excluded text must actually render in gray, not only store a gray model value.");
            for (int repeat = 0; repeat < 2; ++repeat) {
                project = load(directory.path());
                QVERIFY(project.setExcluded("logic", false, &error));
                QTRY_COMPARE_WITH_TIMEOUT(tree->findItems("value.cpp", Qt::MatchExactly | Qt::MatchRecursive).size(), 1, 3000);
                auto* included = tree->findItems("value.cpp", Qt::MatchExactly | Qt::MatchRecursive).first();
                QCOMPARE(included->foreground(0).color(), tree->palette().color(QPalette::Text));
                QVERIFY(included->foreground(0).style() != Qt::NoBrush);
                QVERIFY(!included->font(0).italic());
                project = load(directory.path());
                QVERIFY(project.setExcluded("logic", true, &error));
                QTRY_COMPARE_WITH_TIMEOUT(tree->findItems("value.cpp (Excluded)", Qt::MatchExactly | Qt::MatchRecursive).size(), 1, 3000);
                auto* excluded = tree->findItems("value.cpp (Excluded)", Qt::MatchExactly | Qt::MatchRecursive).first();
                QCOMPARE(excluded->foreground(0).color(), QColor(dark ? "#8993a3" : "#929aa6"));
            }
        }
    }
    void contextMenuUpdatesExcludedLabelImmediately()
    {
        QTemporaryDir directory; fixture(directory.path());
        MainWindow window; QVERIFY(window.openProject(directory.path()));
        auto* tree = window.findChild<QTreeWidget*>("projectFiles");
        window.show(); tree->expandAll();
        QVERIFY(window.openDocument(directory.filePath("logic/value.cpp")));
        for (bool exclude : {true, false, true, false}) {
            const QString before = exclude ? "value.cpp" : "value.cpp (Excluded)";
            const auto items = tree->findItems(before, Qt::MatchExactly | Qt::MatchRecursive);
            QCOMPARE(items.size(), 1);
            const QPoint position = tree->visualItemRect(items.first()).center();
            bool triggered = false;
            QTimer::singleShot(0, &window, [&] {
                auto* menu = qobject_cast<QMenu*>(QApplication::activePopupWidget());
                if (!menu) return;
                for (auto* entry : menu->actions()) {
                    if (entry->text() != (exclude ? "Exclude from Project" : "Include in Project")) continue;
                    entry->trigger(); triggered = true; break;
                }
                menu->close();
            });
            QMetaObject::invokeMethod(tree, "customContextMenuRequested", Qt::DirectConnection, Q_ARG(QPoint, position));
            QVERIFY(triggered);
            const auto updated = tree->findItems(exclude ? "value.cpp (Excluded)" : "value.cpp", Qt::MatchExactly | Qt::MatchRecursive);
            QCOMPARE(updated.size(), 1);
            QCOMPARE(updated.first()->data(0, Qt::UserRole + 1).toBool(), exclude);
            QCOMPARE(updated.first()->font(0).italic(), exclude);
            QCOMPARE(load(directory.path()).excludes("logic/value.cpp"), exclude);
            QCOMPARE(tabs(window)->tabText(tabs(window)->currentIndex()).contains("[Excluded]"), exclude);
        }
    }
    void explorerMenusUseClickedLocationAndDisableUnsavedTabs()
    {
        QTemporaryDir directory; fixture(directory.filePath("My Project"));
        const QString root = directory.filePath("My Project");
        const QString outside = directory.filePath("outside file.cpp");
        write(outside, "void SmallMain() {}\n");
        FileLocationWindow window; QVERIFY(window.openProject(root));
        window.show();
        auto* tree = window.findChild<QTreeWidget*>("projectFiles"); tree->expandAll();
        auto invoke = [&](QWidget* target, const QPoint& position, const QString& label, bool enabled) {
            bool found = false;
            QTimer::singleShot(0, &window, [&] {
                auto* menu = qobject_cast<QMenu*>(QApplication::activePopupWidget());
                if (!menu) return;
                for (auto* entry : menu->actions()) {
                    if (entry->text() != label) continue;
                    found = true; QCOMPARE(entry->isEnabled(), enabled);
                    if (enabled) entry->trigger();
                    break;
                }
                menu->close();
            });
            QMetaObject::invokeMethod(target, "customContextMenuRequested", Qt::DirectConnection, Q_ARG(QPoint, position));
            QVERIFY(found);
        };
        invoke(window.findChild<QLabel*>("projectHeading"), QPoint(10,10), "Show Project in File Explorer", true);
        QCOMPARE(window.locations.takeLast(), root);
        invoke(tree, QPoint(tree->viewport()->width()/2, tree->viewport()->height()-5), "Show Project in File Explorer", true);
        QCOMPARE(window.locations.takeLast(), root);
        const auto files = tree->findItems("value.cpp", Qt::MatchExactly | Qt::MatchRecursive);
        QCOMPARE(files.size(), 1);
        invoke(tree, tree->visualItemRect(files.first()).center(), "Show in File Explorer", true);
        QCOMPARE(window.locations.takeLast(), QDir(root).filePath("logic/value.cpp"));
        const auto folders = tree->findItems("logic", Qt::MatchExactly | Qt::MatchRecursive);
        QCOMPARE(folders.size(), 1);
        invoke(tree, tree->visualItemRect(folders.first()).center(), "Show in File Explorer", true);
        QCOMPARE(window.locations.takeLast(), QDir(root).filePath("logic"));
        QVERIFY(window.openDocument(outside));
        auto* tabBar = tabs(window)->tabBar();
        const int outsideIndex = tabs(window)->currentIndex();
        QVERIFY(window.openDocument(QDir(root).filePath("logic/value.cpp")));
        invoke(tabBar, tabBar->tabRect(outsideIndex).center(), "Show in File Explorer", true);
        QCOMPARE(window.locations.takeLast(), outside);
        QCOMPARE(qobject_cast<EditorDocument*>(tabs(window)->currentWidget())->filePath(), QDir(root).filePath("logic/value.cpp"));
        QVERIFY(window.closeProject());
        action(window, "actionNew")->trigger();
        invoke(tabBar, tabBar->tabRect(tabs(window)->currentIndex()).center(), "Show in File Explorer", false);
        QVERIFY(window.locations.isEmpty());
    }
    void newFolderUsesContextAndAcceptsAFileInside_data()
    {
        QTest::addColumn<QString>("context");
        QTest::addColumn<QString>("expected");
        QTest::newRow("folder") << "logic" << "logic/NewFolder";
        QTest::newRow("file") << "value.cpp" << "logic/NewFolder";
        QTest::newRow("blank") << "" << "NewFolder";
    }
    void newFolderUsesContextAndAcceptsAFileInside()
    {
        QFETCH(QString, context); QFETCH(QString, expected);
        QTemporaryDir directory; fixture(directory.path());
        MainWindow window; QVERIFY(window.openProject(directory.path())); window.show();
        auto* tree = window.findChild<QTreeWidget*>("projectFiles"); tree->expandAll();
        QPoint position(tree->viewport()->width()/2, tree->viewport()->height()-5);
        if (!context.isEmpty()) {
            const auto items = tree->findItems(context, Qt::MatchExactly | Qt::MatchRecursive);
            QCOMPARE(items.size(), 1); position = tree->visualItemRect(items.first()).center();
        }
        auto create = [&](const QPoint& point, const QString& label, const char* dialogName, const QString& name) {
            bool entered = false;
            QTimer::singleShot(0, &window, [&] {
                auto* menu = qobject_cast<QMenu*>(QApplication::activePopupWidget());
                if (!menu) return;
                for (auto* entry : menu->actions()) {
                    if (entry->text() != label) continue;
                    QTimer::singleShot(0, &window, [&] {
                        auto* dialog = window.findChild<QInputDialog*>(dialogName);
                        if (dialog) { entered = true; dialog->setTextValue(name); dialog->accept(); }
                    });
                    entry->trigger(); break;
                }
                menu->close();
            });
            QMetaObject::invokeMethod(tree, "customContextMenuRequested", Qt::DirectConnection, Q_ARG(QPoint, point));
            QVERIFY(entered);
        };
        create(position, "New Folder...", "newProjectFolderDialog", "NewFolder");
        QVERIFY(QFileInfo(directory.filePath(expected)).isDir());
        QVERIFY(load(directory.path()).directories.contains(expected));
        QVERIFY(tree->currentItem());
        QCOMPARE(tree->currentItem()->data(0, Qt::UserRole).toString(), expected);
        create(tree->visualItemRect(tree->currentItem()).center(), "New Source File...", "newProjectFileDialog", "helper");
        QVERIFY(load(directory.path()).sources.contains(expected + "/helper.cpp"));
        QCOMPARE(tree->currentItem()->data(0, Qt::UserRole).toString(), expected + "/helper.cpp");
        QVERIFY(tree->currentItem()->parent()->isExpanded());
        QCOMPARE(qobject_cast<EditorDocument*>(tabs(window)->currentWidget())->filePath(), directory.filePath(expected + "/helper.cpp"));
        QVERIFY(window.closeProject()); QVERIFY(window.openProject(directory.path()));
        QCOMPARE(tree->findItems("NewFolder", Qt::MatchExactly | Qt::MatchRecursive).size(), 1);
    }
    void newFolderCancellationAndInvalidNames_data()
    {
        QTest::addColumn<QString>("name"); QTest::addColumn<bool>("cancel");
        QTest::newRow("cancel") << "Cancelled" << true;
        QTest::newRow("existing") << "logic" << false;
        QTest::newRow("outside") << "../Outside" << false;
        QTest::newRow("reserved") << "build" << false;
    }
    void newFolderCancellationAndInvalidNames()
    {
        QFETCH(QString, name); QFETCH(bool, cancel);
        QTemporaryDir directory; fixture(directory.path());
        MainWindow window; QVERIFY(window.openProject(directory.path())); window.show();
        auto* tree = window.findChild<QTreeWidget*>("projectFiles");
        const auto before = load(directory.path());
        bool entered = false, warned = false;
        QTimer::singleShot(0, &window, [&] {
            auto* menu = qobject_cast<QMenu*>(QApplication::activePopupWidget());
            if (!menu) return;
            for (auto* entry : menu->actions()) {
                if (entry->text() != "New Folder...") continue;
                QTimer::singleShot(0, &window, [&] {
                    auto* dialog = window.findChild<QInputDialog*>("newProjectFolderDialog");
                    if (!dialog) return;
                    entered = true; dialog->setTextValue(name);
                    if (cancel) dialog->reject();
                    else {
                        QTimer::singleShot(0, &window, [&] {
                            if (auto* box = qobject_cast<QMessageBox*>(QApplication::activeModalWidget())) {
                                warned = true; box->accept();
                            }
                        });
                        dialog->accept();
                    }
                });
                entry->trigger(); break;
            }
            menu->close();
        });
        const QPoint position(tree->viewport()->width()/2, tree->viewport()->height()-5);
        QMetaObject::invokeMethod(tree, "customContextMenuRequested", Qt::DirectConnection, Q_ARG(QPoint, position));
        QVERIFY(entered); QCOMPARE(warned, !cancel);
        QCOMPARE(load(directory.path()).directories, before.directories);
        QCOMPARE(read(directory.filePath("logic/value.cpp")), QByteArray("#include \"value.h\"\nint Value()\n{\n    int value = 42;\n    return value;\n}\n"));
    }
    void newFilesUseContextFolder_data()
    {
        QTest::addColumn<QString>("context");
        QTest::addColumn<QString>("suffix");
        QTest::addColumn<QString>("expected");
        QTest::newRow("folder-source") << "logic" << "cpp" << "logic/created.cpp";
        QTest::newRow("file-header") << "value.cpp" << "h" << "logic/created.h";
        QTest::newRow("blank-root") << "" << "cpp" << "created.cpp";
        QTest::newRow("toolbar-root") << "toolbar" << "cpp" << "created.cpp";
    }
    void newFilesUseContextFolder()
    {
        QFETCH(QString, context); QFETCH(QString, suffix); QFETCH(QString, expected);
        QTemporaryDir directory; fixture(directory.path());
        MainWindow window; QVERIFY(window.openProject(directory.path()));
        auto* tree = window.findChild<QTreeWidget*>("projectFiles");
        window.show(); tree->expandAll();
        bool accepted = false;
        auto enterName = [&] {
            auto* dialog = window.findChild<QInputDialog*>("newProjectFileDialog");
            if (!dialog) return;
            dialog->setTextValue("created"); // The appropriate extension is supplied.
            accepted = true; dialog->accept();
        };
        if (context == "toolbar") {
            QTimer::singleShot(0, &window, enterName);
            action(window, "actionNew")->trigger();
        } else {
            QPoint position(tree->viewport()->width() / 2, tree->viewport()->height() - 5);
            if (!context.isEmpty()) {
                const auto items = tree->findItems(context, Qt::MatchExactly | Qt::MatchRecursive);
                QCOMPARE(items.size(), 1);
                position = tree->visualItemRect(items.first()).center();
            }
            QTimer::singleShot(0, &window, [&] {
                auto* menu = qobject_cast<QMenu*>(QApplication::activePopupWidget());
                if (!menu) return;
                for (auto* entry : menu->actions()) {
                    if (entry->text() != (suffix == "h" ? "New Header File..." : "New Source File...")) continue;
                    QTimer::singleShot(0, &window, enterName);
                    entry->trigger(); break;
                }
                menu->close();
            });
            QMetaObject::invokeMethod(tree, "customContextMenuRequested", Qt::DirectConnection, Q_ARG(QPoint, position));
        }
        QVERIFY(accepted);
        QVERIFY(QFileInfo::exists(directory.filePath(expected)));
        const auto project = load(directory.path());
        QVERIFY((suffix == "h" ? project.headers : project.sources).contains(expected));
        QCOMPARE(qobject_cast<EditorDocument*>(tabs(window)->currentWidget())->filePath(), directory.filePath(expected));
        if (suffix == "h") QCOMPARE(read(directory.filePath(expected)), QByteArray("#pragma once\n"));
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
    void tutorialProjectsRun_data()
    {
        QTest::addColumn<QString>("name");
        QTest::addColumn<QByteArray>("output");
        QTest::newRow("greeting") << "Greeting" << QByteArray("Hello from another file!\n");
        QTest::newRow("score") << "ScoreCard" << QByteArray("30\n");
    }
    void tutorialProjectsRun()
    {
        QFETCH(QString, name); QFETCH(QByteArray, output);
        const QString samples = QFINDTESTDATA("../examples/projects");
        QVERIFY(!samples.isEmpty());
        QTemporaryDir directory;
        const QString projectPath = directory.filePath(name);
        QVERIFY(QDir().mkpath(projectPath));
        const QDir sample(QDir(samples).filePath(name));
        for (const auto& file : sample.entryList(QDir::Files))
            QVERIFY(QFile::copy(sample.filePath(file), QDir(projectPath).filePath(file)));
        const QString preview = qEnvironmentVariable("SMALL_PROJECT_TUTORIAL_PREVIEW_DIR");
        if (!preview.isEmpty()) {
            QFontDatabase::addApplicationFont(qEnvironmentVariable("SystemRoot") + "/Fonts/consola.ttf");
            const QFont previous = QApplication::font();
            QApplication::setFont(QFont("Segoe UI", 11));
            SmallSettings().setValue("appearance/dark", false);
            MainWindow window; QVERIFY(window.openProject(projectPath));
            window.resize(1120, 720); window.show(); QTest::qWait(100);
            QVERIFY(QDir().mkpath(preview));
            QVERIFY(window.grab().save(QDir(preview).filePath(name + ".png")));
            QApplication::setFont(previous);
        }
        BuildController build;
        QSignalSpy built(&build, &BuildController::projectBuilt);
        QSignalSpy failed(&build, &BuildController::buildError);
        build.startProject(load(projectPath), true);
        QTRY_VERIFY_WITH_TIMEOUT(!built.isEmpty() || !failed.isEmpty(), 30000);
        QVERIFY2(failed.isEmpty(), qPrintable(failed.isEmpty() ? QString() : failed.first().first().toString()));
        QProcess program;
        auto environment = QProcessEnvironment::systemEnvironment();
        const QString separator(QDir::listSeparator());
        environment.insert("PATH", QFileInfo(QString::fromUtf8(SmallBuildConfig::Compiler)).absolutePath()
                           + separator + QCoreApplication::applicationDirPath()
                           + separator + QString::fromUtf8(SmallBuildConfig::QtBin)
                           + separator + environment.value("PATH"));
        program.setProcessEnvironment(environment);
        program.setWorkingDirectory(projectPath);
        program.start(built.first().first().toString(), QStringList{});
        QVERIFY(program.waitForFinished(10000));
        QCOMPARE(program.exitCode(), 0);
        QCOMPARE(program.readAllStandardOutput().replace("\r\n", "\n"), output);
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
    void publishNestedResourcesWithoutBuildFiles()
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
        QVERIFY(!QFileInfo::exists(destination + "/source"));
        QVERIFY(!QFileInfo::exists(destination + "/relink"));
        QVERIFY(QFileInfo::exists(destination + "/data/message.txt"));
        QVERIFY(QFileInfo::exists(destination + "/.smallcpp-package"));
        QCOMPARE(load(directory.filePath("MyGame")).sources.size(), 2);
        QProcess program; auto env=QProcessEnvironment::systemEnvironment(); env.insert("PATH", "C:/Windows/System32"); env.remove("QT_PLUGIN_PATH"); env.remove("QT_QPA_PLATFORM_PLUGIN_PATH"); env.remove("SMALL_TEST_NO_CONSOLE_PAUSE");
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
            QSKIP("External library Run passed; prepare portable files to test Publish.");
        QSignalSpy published(&build,&BuildController::published); build.startProject(project,false,directory.filePath("published"));
        QTRY_VERIFY_WITH_TIMEOUT(!published.isEmpty() || !failed.isEmpty(),30000);
        QVERIFY2(failed.isEmpty(),qPrintable(failed.isEmpty()?QString():failed.first().first().toString()));
        QVERIFY(!QFileInfo::exists(directory.filePath("published/relink")));
        QVERIFY(!QFileInfo::exists(directory.filePath("published/source")));
        QProcess program;
        auto env = QProcessEnvironment::systemEnvironment();
        env.insert("PATH", "C:/Windows/System32");
        env.remove("QT_PLUGIN_PATH"); env.remove("QT_QPA_PLATFORM_PLUGIN_PATH");
        env.remove("SMALL_TEST_NO_CONSOLE_PAUSE");
        program.setProcessEnvironment(env); program.setWorkingDirectory(directory.filePath("published"));
        program.start(directory.filePath("published/project.exe"), {});
        QVERIFY(program.waitForFinished(15000)); QCOMPARE(program.exitCode(), 0);
        QCOMPARE(read(directory.filePath("published/result.txt")).trimmed(), QByteArray("60"));
    }
    void projectPreview()
    {
        const QString output=qEnvironmentVariable("SMALL_PROJECT_PREVIEW_DIR"); if(output.isEmpty()) return;
        QFontDatabase::addApplicationFont(qEnvironmentVariable("SystemRoot")+"/Fonts/segoeui.ttf");
        QFontDatabase::addApplicationFont(qEnvironmentVariable("SystemRoot")+"/Fonts/segoeuib.ttf");
          QVERIFY(QDir().mkpath(output)); QTemporaryDir directory; fixture(directory.filePath("MyGame"));
          write(directory.filePath("MyGame/practice.cpp"), "void SmallMain() {}\n");
          QString error; auto project = load(directory.filePath("MyGame"));
          QVERIFY(project.setExcluded("practice.cpp", true, &error));
        write(directory.filePath("outside.cpp"), "// A separate program, outside MyGame.\nvoid SmallMain()\n{\n    Print(\"Hello!\");\n}\n");
        for(bool dark:{false,true}) {
            MainWindow window;
            window.findChild<QAction*>(dark ? "actionThemeDark" : "actionThemeLight")->trigger();
            QVERIFY(window.openProject(directory.filePath("MyGame")));
            QVERIFY(window.openDocument(directory.filePath("MyGame/logic/value.cpp"))); QVERIFY(window.openDocument(directory.filePath("outside.cpp")));
              window.findChild<QTreeWidget*>("projectFiles")->expandAll(); window.resize(1200,800); window.show(); QTest::qWait(50);
              auto* tree = window.findChild<QTreeWidget*>("projectFiles");
              tree->setCurrentItem(tree->findItems("practice.cpp (Excluded)", Qt::MatchExactly).first());
              tree->setFocus();
            QVERIFY(window.grab().save(QDir(output).filePath(dark?"project-dark.png":"project-light.png")));
        }
    }
};
QTEST_MAIN(ProjectTests)
#include "test_project.moc"
