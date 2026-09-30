#include "BuildController.h"
#include "SmallBuildConfig.h"
#include "EntryPoint.h"

#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QLibraryInfo>
#include <QProcessEnvironment>
#include <QRegularExpression>
#include <QSaveFile>

#ifdef Q_OS_WIN
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#endif

BuildController::BuildController(QObject* parent) : QObject(parent)
{
    build_.setProcessChannelMode(QProcess::MergedChannels);
    connect(&build_, &QProcess::readyReadStandardOutput, this, &BuildController::collectBuildOutput);
    connect(&build_, &QProcess::finished, this, &BuildController::onBuildFinished);
    connect(&build_, &QProcess::started, this, [this] { if (cancelled_) build_.kill(); });
    connect(&program_, &QProcess::finished, this, &BuildController::onProgramFinished);
    connect(&program_, &QProcess::started, this, [this] {
        if (cancelled_) { program_.kill(); return; }
        setStage(Stage::Running);
        emit phaseChanged("Running");
        emit programStarted();
    });
    connect(&build_, &QProcess::errorOccurred, this, [this](QProcess::ProcessError error) {
        if (error == QProcess::FailedToStart)
        {
            if (cancelled_) finishStopped();
            else fail("Could not start the compiler: " + build_.errorString());
        }
        // A crashed process emits finished() as well; handle it once there.
    });
    connect(&program_, &QProcess::errorOccurred, this, [this](QProcess::ProcessError error) {
        if (error == QProcess::FailedToStart)
        {
            if (cancelled_) finishStopped();
            else fail("Could not start the program: " + program_.errorString());
        }
    });
}

BuildController::~BuildController()
{
    // MainWindow normally waits asynchronously for Idle before destruction.
    if (build_.state() != QProcess::NotRunning) build_.kill();
    if (program_.state() != QProcess::NotRunning) program_.kill();
}

QString BuildController::compiler() const
{
#ifdef Q_OS_WIN
    const QString bundled = QDir(QCoreApplication::applicationDirPath())
                                .filePath("compiler/bin/g++.exe");
    if (QFileInfo::exists(bundled))
        return QDir::cleanPath(bundled);
#endif
    return QString::fromUtf8(SmallBuildConfig::Compiler);
}

void BuildController::setStage(Stage stage)
{
    const bool wasBusy = isBusy();
    stage_ = stage;
    if (wasBusy != isBusy()) emit busyChanged(isBusy());
}

void BuildController::configureEnvironment(QProcess& process)
{
    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    const QString compilerBin = QFileInfo(compiler()).absolutePath();
    const QString recordedQtBin = QString::fromUtf8(SmallBuildConfig::QtBin);
    const QString appBin = QCoreApplication::applicationDirPath();
    const QString separator(QDir::listSeparator());
    QString path = compilerBin + separator + appBin;
    // Development builds may use the Qt kit directly. Portable builds already
    // have the Qt runtime DLLs beside SmallCppIDE.exe and must not depend on
    // the build machine's C:/Qt path.
    if (QFileInfo::exists(recordedQtBin))
        path += separator + recordedQtBin;
    env.insert("PATH", path + separator + env.value("PATH"));
    // Portable windeployqt layout: platforms/, multimedia/, ... are
    // directly beside SmallCppIDE.exe.
    const QString portablePluginRoot = appBin;
    env.insert("QT_PLUGIN_PATH", portablePluginRoot);
    env.insert("QT_QPA_PLATFORM_PLUGIN_PATH",
               QDir(portablePluginRoot).filePath("platforms"));
    // Deterministic GCC diagnostic wording. UTF-8 source/output are explicit.
    env.insert("LC_ALL", "C");
    process.setProcessEnvironment(env);
}

void BuildController::start(const QString& source, const QString& originalFilePath,
                            const QString& unsavedName)
{
    if (isBusy()) return;
    cancelled_ = false;
    buildOutput_.clear();
    sourceSnapshot_ = source;
    compileMs_ = 0;

    sdkDirectory_ = QDir(QCoreApplication::applicationDirPath()).filePath("runtime");
    extensionsDirectory_ = QDir(QCoreApplication::applicationDirPath()).filePath("extensions");
    runtimePath_ = QDir(sdkDirectory_).filePath(QString::fromUtf8(SmallBuildConfig::RuntimeFile));
    entryPath_ = QDir(sdkDirectory_).filePath(QString::fromUtf8(SmallBuildConfig::EntryFile));
    idePausePath_ = QDir(sdkDirectory_).filePath(QString::fromUtf8(SmallBuildConfig::IdePauseFile));
    usesOwnMain_ = DetectEntryPoint(source) == SmallEntryPoint::Main;
    installedExtensions_ = ExtensionRegistry::discover(extensionsDirectory_);
    extensions_ = ExtensionRegistry::detect(source, installedExtensions_);
    if (!QFileInfo::exists(compiler()))
    {
        fail("The compiler recorded by CMake no longer exists:\n" + compiler() +
             "\nReconfigure this project with your Qt MinGW kit.");
        return;
    }
    if (!QFileInfo::exists(runtimePath_) || !QFileInfo::exists(entryPath_) ||
        !QFileInfo::exists(idePausePath_) ||
        !QFileInfo::exists(QDir(sdkDirectory_).filePath("small.h")))
    {
        fail("The precompiled Small runtime is missing. Build the SmallCppIDE target in Qt Creator first.\n" +
             runtimePath_);
        return;
    }

    // Unique per run and per IDE instance: no stale object/version collision.
    directory_ = std::make_unique<QTemporaryDir>(QDir::tempPath() + "/SmallCpp-run-XXXXXX");
    if (!directory_->isValid()) { fail("Cannot create a temporary build folder."); return; }
    QString name = originalFilePath.isEmpty() ? QFileInfo(unsavedName).fileName()
                                            : QFileInfo(originalFilePath).fileName();
    if (name.isEmpty()) name = "Untitled.cpp";
    // Store a normal .cpp even if the user saved with another extension.
    if (!name.endsWith(".cpp", Qt::CaseInsensitive)) name += ".cpp";
    sourcePath_ = directory_->filePath(name);
    objectPath_ = directory_->filePath("program.o");
#ifdef Q_OS_WIN
    executablePath_ = directory_->filePath("program.exe");
#else
    executablePath_ = directory_->filePath("program");
#endif
    originalDirectory_ = originalFilePath.isEmpty() ? directory_->path() : QFileInfo(originalFilePath).absolutePath();
    runtimeErrorPath_ = directory_->filePath("runtime_error.txt");
    QSaveFile sourceFile(sourcePath_);
    const QByteArray bytes = source.toUtf8();
    if (!sourceFile.open(QIODevice::WriteOnly) || sourceFile.write(bytes) != bytes.size() || !sourceFile.commit())
    {
        fail("Cannot write the temporary source: " + sourceFile.errorString());
        return;
    }
    configureEnvironment(build_);
    build_.setWorkingDirectory(directory_->path());
    compile();
}

void BuildController::compile()
{
    setStage(Stage::Compiling);
    emit phaseChanged("Compiling your program...");
    buildOutput_.clear();
    stageTimer_.start();
    QStringList args = {
        "-std=c++20", "-O0", "-g0", "-Wall", "-Wextra", "-Werror=parentheses",
        "-fdiagnostics-color=never", "-fmessage-length=0",
        "-I", sdkDirectory_,
        "-iquote", originalDirectory_,
        "-c", sourcePath_, "-o", objectPath_
    };

    // SmallMain is the beginner-facing path: the IDE supplies the Small
    // header and namespace shortcut. A real main() is ordinary C++ source,
    // so Small must be included and qualified explicitly by the learner.
    if (!usesOwnMain_)
    {
        args.prepend(QDir(sdkDirectory_).filePath("small.h"));
        args.prepend("-include");
        args.prepend("-DSMALL_BEGINNER_MODE");
    }
    for (const auto& extension : std::as_const(extensions_))
    {
        args << "-I" << extension.includeDirectory;
    }

    if (QString::fromUtf8(SmallBuildConfig::CompilerId) == "GNU")
    {
        args << "-finput-charset=UTF-8"
             << "-fexec-charset=UTF-8"
             << "-fmax-errors=5";
    }
    // No Qt includes, no runtime .cpp files in the learner compilation.
    build_.start(compiler(), args);
}

void BuildController::link()
{
    setStage(Stage::Linking);
    emit phaseChanged("Linking...");
    buildOutput_.clear();
    stageTimer_.start();
    QStringList args = {objectPath_};
    if (!usesOwnMain_) args << entryPath_;
    // Small IDE Run always keeps the console open at normal process exit.
    // Link the object directly so its static initializer cannot be discarded.
    // This policy is encoded by linking one tiny support object, not by
    // changing Small's public header/runtime or the learner source.
    args << idePausePath_;
    for (const auto& extension : std::as_const(extensions_))
    {
        if (!QFileInfo::exists(extension.libraryPath))
        {
            fail("The Small extension runtime is missing: " +
                 extension.id + "\n" +
                 extension.libraryPath);
            return;
        }
        args << extension.libraryPath;
    }
    args << runtimePath_;
    const QString portableQtLib =
        QDir(QCoreApplication::applicationDirPath()).filePath("qt/lib");
    for (const char* library : SmallBuildConfig::QtLibraries)
    {
        const QString recorded = QString::fromUtf8(library);
        const QString bundled = QDir(portableQtLib).filePath(QFileInfo(recorded).fileName());
        // Prefer the packaged import library. Fall back to the recorded kit
        // path only for an unpackaged developer build.
        args << (QFileInfo::exists(bundled) ? bundled : recorded);
    }
    args << "-o" << executablePath_;
    build_.start(compiler(), args);
}

void BuildController::launch()
{
    setStage(Stage::Starting);
    emit phaseChanged("Starting console...");

    configureEnvironment(program_);
    QProcessEnvironment env = program_.processEnvironment();
    env.insert("SMALL_RUNTIME_ERROR_FILE", runtimeErrorPath_);
    program_.setProcessEnvironment(env);
    program_.setWorkingDirectory(originalDirectory_);

#ifdef Q_OS_WIN
    // Give the learner program a real Windows console.  Clearing
    // STARTF_USESTDHANDLES lets Windows attach stdin/stdout/stderr to that
    // console instead of QProcess pipes owned by the IDE.
    program_.setCreateProcessArgumentsModifier([](QProcess::CreateProcessArguments* args) {
        args->flags |= CREATE_NEW_CONSOLE;
        args->startupInfo->dwFlags &= ~STARTF_USESTDHANDLES;
        args->startupInfo->hStdInput = nullptr;
        args->startupInfo->hStdOutput = nullptr;
        args->startupInfo->hStdError = nullptr;
    });
#endif
    program_.start(executablePath_, QStringList{});
}

void BuildController::collectBuildOutput()
{
    buildOutput_ += build_.readAllStandardOutput();
}

void BuildController::onBuildFinished(int code, QProcess::ExitStatus status)
{
    collectBuildOutput();
    if (cancelled_) { finishStopped(); return; }
    if (stage_ != Stage::Compiling && stage_ != Stage::Linking) return;
    if (status != QProcess::NormalExit || code != 0)
    {
        fail(buildOutput_.isEmpty() ? "The compiler exited unexpectedly." : QString::fromUtf8(buildOutput_));
        return;
    }
    if (!buildOutput_.isEmpty()) emit textOutput(QString::fromUtf8(buildOutput_));
    if (stage_ == Stage::Compiling)
    {
        compileMs_ = stageTimer_.elapsed();
        link();
    }
    else
    {
        emit buildTiming(compileMs_, stageTimer_.elapsed());
        launch();
    }
}

void BuildController::onProgramFinished(int code, QProcess::ExitStatus status)
{
    if (cancelled_) { finishStopped(); return; }
    setStage(Stage::Idle);

    QFile errorFile(runtimeErrorPath_);
    if (errorFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        const QString message = QString::fromUtf8(errorFile.readAll()).trimmed();
        if (!message.isEmpty()) emit runtimeError("Runtime error: " + message, sourceSnapshot_);
    }

    if (status == QProcess::NormalExit)
    {
        emit phaseChanged(QString("Finished (exit %1)").arg(code));
    }
    else
    {
        emit phaseChanged(QString("The program stopped unexpectedly. Exit code: %1 (0x%2)")
                              .arg(code)
                              .arg(static_cast<quint32>(code), 8, 16, QLatin1Char('0')));
    }
    emit finished(code, false);
}

void BuildController::fail(const QString& error)
{
    setStage(Stage::Idle);
    emit phaseChanged("Build / run failed");
    emit buildError(error, sourceSnapshot_, sourcePath_);
}

void BuildController::stop()
{
    if (!isBusy()) return;
    cancelled_ = true;
    setStage(Stage::Stopping);
    emit phaseChanged("Stopping...");
    if (build_.state() != QProcess::NotRunning) build_.kill();
    if (program_.state() != QProcess::NotRunning) program_.kill();
    if (build_.state() == QProcess::NotRunning && program_.state() == QProcess::NotRunning)
        finishStopped();
}

void BuildController::finishStopped()
{
    if (stage_ == Stage::Idle) return;
    setStage(Stage::Idle);
    emit phaseChanged("Stopped");
    emit finished(-1, true);
}
