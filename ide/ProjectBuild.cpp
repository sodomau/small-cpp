#include "BuildController.h"
#include "EntryPoint.h"
#include "SmallBuildConfig.h"
#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QFileInfo>

QStringList BuildController::projectSourcePaths() const
{
    QStringList paths;
    for (const auto& source : project_.sources) paths << project_.absolute(source);
    return paths;
}

bool BuildController::planPackage(QString* error)
{
    return ProgramPackage::plan(QCoreApplication::applicationDirPath(), publishResources_, extensions_,
                                &packageFiles_, error, publishExecutableName_, projectActive_ ? project_.root : QString());
}

void BuildController::startProject(const ProjectFolder& project, bool debugBuild,
                                    const QString& destination, const QStringList& resources)
{
    if (isBusy()) return;
    project_ = project;
    projectActive_ = true;
    debugBuild_ = debugBuild;
    cancelled_ = false;
    projectObjects_.clear(); projectLibraries_.clear(); projectSnapshots_.clear();
    projectSourceIndex_ = 0; compileMs_ = 0;
    sourceSnapshot_.clear(); sourcePath_.clear(); buildOutput_.clear();
    publishDestination_ = destination.isEmpty() ? QString() : QFileInfo(destination).absoluteFilePath();
    publishExecutableName_ = ProgramPackage::executableName(project_.name + ".cpp");
    publishResources_ = resources;
    if (publishResources_.isEmpty())
        for (const auto& resource : project_.resources) publishResources_ << project_.absolute(resource);
    if (!publishDestination_.isEmpty()) {
#ifndef Q_OS_WIN
        fail("Publish currently supports Windows only."); return;
#endif
        const QFileInfo target(publishDestination_);
        if (target.exists() || target.isSymLink() || !QFileInfo(target.absolutePath()).isDir() ||
            publishDestination_.compare(project_.root, Qt::CaseInsensitive) == 0) {
            fail("Choose a new destination folder. Existing folders are never overwritten."); return;
        }
    }
    if (project_.sources.isEmpty()) { fail("This project has no included .cpp files. Add a source file or include an excluded file."); return; }
    QString combined, entrySource;
    QStringList entries;
    for (const auto& relative : project_.sources + project_.headers) {
        QFile file(project_.absolute(relative));
        if (!file.open(QIODevice::ReadOnly)) { fail("Cannot read project file: " + file.fileName()); return; }
        const QString text = QString::fromUtf8(file.readAll());
        projectSnapshots_.insert(file.fileName(), text);
        combined += text + "\n";
        if (ProjectFolder::isSource(relative)) {
            for (const auto& entry : DefinedEntryPoints(text)) {
                entries << relative + " (" + entry + ")";
                entrySource = file.fileName();
                usesOwnMain_ = entry == "main";
            }
        }
    }
    if (entries.size() != 1) {
        fail(entries.isEmpty() ? "No program start function was found. Add SmallMain() or main() to one .cpp file."
            : "Program start functions were found in more than one place:\n" + entries.join("\n") +
              "\n\nKeep one start function. Exclude the other program file or turn it into helper functions."); return;
    }
    sourcePath_ = entrySource;
    sourceSnapshot_ = projectSnapshots_.value(sourcePath_);
    originalDirectory_ = project_.root;
    sdkDirectory_ = QDir(QCoreApplication::applicationDirPath()).filePath("runtime");
    extensionsDirectory_ = QDir(QCoreApplication::applicationDirPath()).filePath("extensions");
    runtimePath_ = QDir(sdkDirectory_).filePath(QString::fromUtf8(SmallBuildConfig::RuntimeFile));
    entryPath_ = QDir(sdkDirectory_).filePath(QString::fromUtf8(SmallBuildConfig::EntryFile));
    idePausePath_ = QDir(sdkDirectory_).filePath(QString::fromUtf8(SmallBuildConfig::IdePauseFile));
    installedExtensions_ = ExtensionRegistry::discover(extensionsDirectory_);
    extensions_ = ExtensionRegistry::detect(combined, installedExtensions_);
    if (!QFileInfo::exists(compiler()) || !QFileInfo::exists(runtimePath_) || !QFileInfo::exists(entryPath_) || !QFileInfo::exists(idePausePath_)) {
        fail("The compiler or prebuilt Small runtime is missing. Use a prepared Small C++ installation."); return;
    }
    // Resolve explicit external libraries once, so Publish can preserve them for relinking.
    for (const auto& library : project_.libraries) {
        QString resolved;
        if (library.contains('/') || library.contains('\\') || library.endsWith(".a") || library.endsWith(".lib"))
            resolved = QDir(project_.root).absoluteFilePath(library);
        else {
            for (const auto& directory : project_.libraryPaths)
                for (const auto& filename : {"lib" + library + ".a", "lib" + library + ".dll.a", library + ".lib"})
                    if (resolved.isEmpty() && QFileInfo(QDir(directory).filePath(filename)).isFile()) resolved = QDir(directory).filePath(filename);
        }
        if (resolved.isEmpty() || !QFileInfo(resolved).isFile()) { fail("External library not found: " + library + "\nAdd its folder to library_paths or provide the library file path."); return; }
        projectLibraries_ << resolved;
    }
    if (!publishDestination_.isEmpty()) {
        QString error;
        if (!planPackage(&error)) { fail(error); return; }
    }
    directory_ = std::make_unique<QTemporaryDir>(QDir::tempPath() + "/SmallCpp-project-XXXXXX");
    if (!directory_->isValid()) { fail("Cannot create a project build folder."); return; }
    executablePath_ = directory_->filePath("program.exe");
    runtimeErrorPath_ = directory_->filePath("runtime_error.txt");
    for (int index = 0; index < project_.sources.size(); ++index)
        projectObjects_ << directory_->filePath(QString("program%1.o").arg(index));
    configureEnvironment(build_);
    build_.setWorkingDirectory(project_.root);
    compile();
}
