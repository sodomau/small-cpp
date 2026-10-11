#include <QtTest>
#include "FileBuildOptions.h"
#include "LibraryResolver.h"
#include "LibrariesDialog.h"
#include "BuildController.h"
#include "DebugController.h"
#include "MainWindow.h"
#include "EditorDocument.h"
#include <QAction>
#include <QDialog>
#include "PeDependencies.h"
#include "Toolchain.h"
#include <QTemporaryDir>
#include <QFile>
#include <QTreeWidget>
#include <QLineEdit>
#include <QTimer>
#include <QSettings>
#include <QPushButton>
#include <QJsonDocument>

class LibraryTests : public QObject
{
    Q_OBJECT
    QTemporaryDir settingsDirectory_;
private slots:
    void initTestCase()
    {
        QVERIFY(settingsDirectory_.isValid());
        QSettings::setDefaultFormat(QSettings::IniFormat);
        QSettings::setPath(QSettings::IniFormat, QSettings::UserScope, settingsDirectory_.path());
        qputenv("SMALL_TEST_DIALOGS", "1");
        qputenv("SMALL_TEST_NO_CONSOLE_PAUSE", "1");
        QApplication::setQuitOnLastWindowClosed(false);
    }
    void metadata()
    {
        FileBuildOptions options; QString error;
        QVERIFY(FileBuildOptions::parse("//@ {\n//@ \"libraries\":[\"fmt\"],\n//@ \"compiler_options\":[\"-O2\"]\n//@ }\n\n//@ ignored\nvoid small_main() {}", QDir::tempPath(), &options, &error));
        QCOMPARE(options.lines, 4); QCOMPARE(options.libraries, QStringList{"fmt"});
        QCOMPARE(options.compilerOptions, QStringList{"-O2"});
        QVERIFY(FileBuildOptions::parse("\n//@ invalid\n", "", &options, &error)); QCOMPARE(options.lines, 0);
        QVERIFY(!FileBuildOptions::parse("//@ {bad}\n", "", &options, &error)); QVERIFY(error.contains("line 1"));
        QVERIFY(!FileBuildOptions::parse("//@ {\"compiler_options\":[\"-oelse.exe\"]}", "", &options, &error));
        QVERIFY(!FileBuildOptions::parse("//@ {\"libraries\":[4]}", "", &options, &error));
    }
    void updateMetadata()
    {
        QString source = "//@ {\"compiler_options\":[\"-O2\"]}\nvoid small_main() {}\n";
        FileBuildOptions options, next; QString error;
        QVERIFY(FileBuildOptions::parse(source, "", &options, &error));
        auto updated = FileBuildOptions::withLibraries(source, options, {"fmt"});
        QVERIFY(updated.endsWith("void small_main() {}\n"));
        QVERIFY(FileBuildOptions::parse(updated, "", &next, &error));
        QCOMPARE(next.compilerOptions, QStringList{"-O2"}); QCOMPARE(next.libraries, QStringList{"fmt"});
    }
    void quotedFlags()
    {
        QCOMPARE(LibraryResolver::splitFlags("-IC:/A\\ B/한글 -DFMT_SHARED -L'C:/Other Path/lib' -lfmt"),
                 (QStringList{"-IC:/A B/한글", "-DFMT_SHARED", "-LC:/Other Path/lib", "-lfmt"}));
    }
    void mapping()
    {
        const auto map = LibraryResolver::scanCatalog("mingw-w64-ucrt-x86_64-a ucrt64/lib/pkgconfig/example.pc\nmingw-w64-ucrt-x86_64-b ucrt64/share/pkgconfig/example.pc\nmingw-w64-x86_64-a mingw64/lib/pkgconfig/ignore.pc\n");
        QCOMPARE(map.size(), 1); QCOMPARE(map.value("example").toArray().size(), 2);
        LibraryResolver resolver;
        QVERIFY(LibraryResolver::catalog().value("fmt").isString());
        QVERIFY(LibraryResolver::catalog().size() > 2000);
    }
    void dialogSelection()
    {
        LibrariesDialog dialog({"fmt"});
        auto* search = dialog.findChild<QLineEdit*>("librarySearch");
        auto* list = dialog.findChild<QTreeWidget*>("libraryList");
        search->setText("fftw3"); QVERIFY(list->topLevelItemCount() >= 1);
        list->topLevelItem(0)->setCheckState(0, Qt::Checked);
        QVERIFY(dialog.libraries().contains("fmt")); QVERIFY(dialog.libraries().size() == 2);
        search->setText("fmt");
        for (int i = 0; i < list->topLevelItemCount(); ++i)
            if (list->topLevelItem(i)->text(1) == "fmt") list->topLevelItem(i)->setCheckState(0, Qt::Unchecked);
        QVERIFY(!dialog.libraries().contains("fmt"));
    }
    void unknownLibraryDoesNotBuild()
    {
        BuildController build;
        QSignalSpy failed(&build, &BuildController::buildError);
        build.start("//@ {\"libraries\":[\"smallcpp_library_does_not_exist_123\"]}\nvoid small_main() {}", "");
        QTRY_VERIFY_WITH_TIMEOUT(!failed.isEmpty(), 10000);
        QVERIFY(!build.isBusy());
    }
    void dialogSorting()
    {
        LibrariesDialog dialog({"fmt"});
        auto* list = dialog.findChild<QTreeWidget*>("libraryList");
        list->sortItems(0, Qt::DescendingOrder);
        QCOMPARE(list->topLevelItem(0)->text(1), QString("fmt"));
        list->sortItems(0, Qt::AscendingOrder);
        QCOMPARE(list->topLevelItem(list->topLevelItemCount() - 1)->text(1), QString("fmt"));
        for (int column = 1; column < 4; ++column) {
            for (auto order : {Qt::AscendingOrder, Qt::DescendingOrder}) {
                list->sortItems(column, order);
                for (int i = 1; i < list->topLevelItemCount(); ++i) {
                    const auto previous = list->topLevelItem(i - 1)->text(column);
                    const auto current = list->topLevelItem(i)->text(column);
                    const int comparison = QString::localeAwareCompare(previous, current);
                    QVERIFY(order == Qt::AscendingOrder ? comparison <= 0 : comparison >= 0);
                }
            }
        }
        list->sortItems(0, Qt::DescendingOrder);
        dialog.findChild<QLineEdit*>("librarySearch")->setText("fmt");
        QCOMPARE(list->topLevelItem(0)->text(1), QString("fmt"));
        QCOMPARE(dialog.libraries(), QStringList{"fmt"});
    }
    void mainWindowEditsMetadataWithUndo()
    {
        MainWindow window;
        window.findChild<QAction*>("actionNew")->trigger();
        auto* document = window.findChildren<EditorDocument*>().last();
        const QString source = "//@ {\"compiler_options\":[\"-O2\"]}\nvoid small_main() {}\n";
        document->setPlainText(source);
        bool selected = false;
        QTimer::singleShot(0, &window, [&] {
            for (auto* dialog : window.findChildren<QDialog*>()) {
                if (dialog->objectName() != "librariesDialog") continue;
                dialog->findChild<QLineEdit*>("librarySearch")->setText("fmt");
                auto* list = dialog->findChild<QTreeWidget*>("libraryList");
                for (int i = 0; i < list->topLevelItemCount(); ++i)
                    if (list->topLevelItem(i)->text(1) == "fmt") { list->topLevelItem(i)->setCheckState(0, Qt::Checked); selected = true; }
                dialog->accept();
            }
        });
        window.findChild<QAction*>("actionLibraries")->trigger();
        QVERIFY(selected);
        FileBuildOptions options; QString error;
        QVERIFY(FileBuildOptions::parse(document->toPlainText(), "", &options, &error));
        QCOMPARE(options.libraries, QStringList{"fmt"}); QCOMPARE(options.compilerOptions, QStringList{"-O2"});
        document->undo(); QCOMPARE(document->toPlainText(), source);
    }
    void installedLibraryRunAndPublish()
    {
        if (!qEnvironmentVariableIsSet("SMALL_TEST_INSTALL_LIBRARY")) QSKIP("Set SMALL_TEST_INSTALL_LIBRARY in an isolated prepared package to test pacman and Publish.");
        QTemporaryDir directory;
        BuildController build;
        int confirmations = 0;
        build.libraryResolver()->confirmInstall = [&](const QStringList&) { ++confirmations; return true; };
        connect(&build, &BuildController::textOutput, this, [](const QString& text) { qInfo().noquote() << text; });
        const QString source = "//@ {\n//@ \"libraries\": [\"fmt\"],\n//@ \"compiler_options\": [\"-DEXPECTED=42\"]\n//@ }\n#include <fmt/format.h>\nvoid small_main() { File f; f.open(\"result.txt\", FileMode::Write); f.print(fmt::format(\"Answer {}\", EXPECTED).c_str()); }\n";
        const QString path = directory.filePath("main.cpp");
        QFile file(path); QVERIFY(file.open(QIODevice::WriteOnly)); file.write(source.toUtf8()); file.close();
        QSignalSpy failed(&build, &BuildController::buildError), finished(&build, &BuildController::finished), published(&build, &BuildController::published);
        build.start(source, path);
        QTRY_VERIFY_WITH_TIMEOUT(!finished.isEmpty() || !failed.isEmpty(), 180000);
        QVERIFY2(failed.isEmpty(), qPrintable(failed.isEmpty() ? QString() : failed.first().first().toString()));
        QFile result(directory.filePath("result.txt")); QVERIFY(result.open(QIODevice::ReadOnly)); QCOMPARE(result.readAll().trimmed(), QByteArray("Answer 42")); result.close();
        DebugController debug;
        QSignalSpy debugFailed(&debug, &DebugController::buildError), debugFinished(&debug, &DebugController::finished);
        debug.start(source, path, "main.cpp", {});
        QTRY_VERIFY_WITH_TIMEOUT(!debugFinished.isEmpty() || !debugFailed.isEmpty(), 30000);
        QVERIFY2(debugFailed.isEmpty(), qPrintable(debugFailed.isEmpty() ? QString() : debugFailed.first().first().toString()));
        const int afterFirst = confirmations;
        const QString destination = directory.filePath("published"); build.publish(source, path, destination);
        QTRY_VERIFY_WITH_TIMEOUT(!published.isEmpty() || !failed.isEmpty(), 90000);
        QVERIFY2(failed.isEmpty(), qPrintable(failed.isEmpty() ? QString() : failed.first().first().toString()));
        QCOMPARE(confirmations, afterFirst);
        QVERIFY(QFileInfo(destination + "/licenses/installed-libraries.json").isFile());
        QVERIFY(!QDir(destination).entryList({"libfmt*.dll"}, QDir::Files).isEmpty());
        QVERIFY(QFileInfo(destination + "/licenses/msys2-installed/fmt/LICENSE").isFile());
        QProcess process; auto env = QProcessEnvironment::systemEnvironment(); env.insert("PATH", "C:/Windows/System32;C:/Windows");
        env.remove("QT_PLUGIN_PATH"); env.remove("QT_QPA_PLATFORM_PLUGIN_PATH"); process.setProcessEnvironment(env); process.setWorkingDirectory(destination);
        process.start(destination + "/main.exe", {}); QVERIFY(process.waitForFinished(20000)); QCOMPARE(process.exitCode(), 0);
        QFile exported(destination + "/result.txt"); QVERIFY(exported.open(QIODevice::ReadOnly)); QCOMPARE(exported.readAll().trimmed(), QByteArray("Answer 42"));
        const QString projectRoot = directory.filePath("project"); QVERIFY(QDir().mkpath(projectRoot));
        QFile projectSource(projectRoot + "/main.cpp"); QVERIFY(projectSource.open(QIODevice::WriteOnly)); projectSource.write(source.toUtf8()); projectSource.close();
        QFile settings(projectRoot + "/small.project"); QVERIFY(settings.open(QIODevice::WriteOnly)); settings.write("{\"libraries\":[\"fmt\"],\"compiler_options\":[\"-DEXPECTED=42\"]}"); settings.close();
        ProjectFolder project; QString error; QVERIFY(project.load(projectRoot, &error));
        finished.clear(); build.startProject(project);
        QTRY_VERIFY_WITH_TIMEOUT(!finished.isEmpty() || !failed.isEmpty(), 30000);
        QVERIFY2(failed.isEmpty(), qPrintable(failed.isEmpty() ? QString() : failed.first().first().toString()));
        QFile projectResult(projectRoot + "/result.txt"); QVERIFY(projectResult.open(QIODevice::ReadOnly)); QCOMPARE(projectResult.readAll().trimmed(), QByteArray("Answer 42"));
    }
    void declinedInstall()
    {
        if (!QFileInfo::exists(LibraryResolver::pkgConfig())) QSKIP("pkg-config is absent in this test environment.");
        LibraryResolver resolver; bool asked = false;
        resolver.confirmInstall = [&](const QStringList&) { asked = true; return false; };
        QSignalSpy failed(&resolver, &LibraryResolver::failed), ready(&resolver, &LibraryResolver::ready);
        resolver.resolve({"fftw3"});
        QTRY_VERIFY_WITH_TIMEOUT(!failed.isEmpty() || !ready.isEmpty(), 10000);
        if (!ready.isEmpty()) QSKIP("fftw3 is already installed.");
        QVERIFY(asked); QVERIFY(failed.first().first().toString().contains("cancelled"));
    }
    void malformedBinary()
    {
        QTemporaryDir directory; QFile file(directory.filePath("bad.exe")); QVERIFY(file.open(QIODevice::WriteOnly)); file.write("MZbroken"); file.close();
        QString error; PeDependencies::imports(file.fileName(), &error); QVERIFY(!error.isEmpty());
    }
    void missingDllFails()
    {
        QString error; QVector<PackageFile> files;
        QVERIFY(!PeDependencies::collect(QCoreApplication::applicationFilePath(), {}, &files, &error));
        QVERIFY(error.contains("Missing runtime DLL"));
    }
    void updateCatalogFromActualEnvironment()
    {
        if (!qEnvironmentVariableIsSet("SMALL_TEST_INSTALL_LIBRARY")) QSKIP("Enable only in an isolated prepared environment.");
        QTemporaryDir directory;
        const QString path = directory.filePath("catalog.json");
        LibrariesDialog dialog({"fmt"}, nullptr, path);
        auto* update = dialog.findChild<QPushButton*>("updateLibraryList");
        QTRY_VERIFY_WITH_TIMEOUT(update->isEnabled(), 10000);
        update->click();
        QTRY_VERIFY_WITH_TIMEOUT(QFileInfo::exists(path) || update->isEnabled(), 150000);
        QFile file(path); QVERIFY2(file.open(QIODevice::ReadOnly), "Catalog update failed; inspect the dialog's status.");
        const auto catalog = QJsonDocument::fromJson(file.readAll()).object();
        QVERIFY(catalog.size() > 1000); QVERIFY(catalog.value("fmt").isString());
        QCOMPARE(dialog.libraries(), QStringList{"fmt"});
    }
};
QTEST_MAIN(LibraryTests)
#include "test_libraries.moc"
