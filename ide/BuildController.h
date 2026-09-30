#pragma once

#include <QElapsedTimer>
#include <QObject>
#include <QProcess>
#include <QTemporaryDir>
#include <memory>
#include "ExtensionRegistry.h"

// Owns compile -> link -> run. No blocking process waits on the GUI thread.
class BuildController : public QObject
{
    Q_OBJECT
public:
    enum class Stage { Idle, Compiling, Linking, Starting, Running, Stopping };
    explicit BuildController(QObject* parent = nullptr);
    ~BuildController() override;

    bool isBusy() const { return stage_ != Stage::Idle; }
    Stage stage() const { return stage_; }
    const QString& sourceSnapshot() const { return sourceSnapshot_; }
    void start(const QString& source, const QString& originalFilePath,
               const QString& unsavedName = "Untitled.cpp");
    void stop();

signals:
    void busyChanged(bool busy);
    void phaseChanged(const QString& text);
    void programStarted();
    void textOutput(const QString& text);
    void buildError(const QString& raw, const QString& source, const QString& sourceFile);
    void runtimeError(const QString& raw, const QString& source);
    void buildTiming(qint64 compileMs, qint64 linkMs);
    void finished(int exitCode, bool stopped);

private:
    QProcess build_;
    QProcess program_;
    Stage stage_ = Stage::Idle;
    std::unique_ptr<QTemporaryDir> directory_;
    QString sourceSnapshot_, sourcePath_, objectPath_, executablePath_, runtimeErrorPath_;
    QString originalDirectory_, sdkDirectory_, extensionsDirectory_, runtimePath_, entryPath_, idePausePath_;
    bool usesOwnMain_ = false;
    QVector<SmallExtension> installedExtensions_, extensions_;
    QByteArray buildOutput_;
    QElapsedTimer stageTimer_;
    qint64 compileMs_ = 0;
    bool cancelled_ = false;

    void setStage(Stage stage);
    void compile();
    void link();
    void launch();
    void onBuildFinished(int code, QProcess::ExitStatus status);
    void onProgramFinished(int code, QProcess::ExitStatus status);
    void fail(const QString& error);
    void finishStopped();
    void collectBuildOutput();
    void configureEnvironment(QProcess& process);
    QString compiler() const;
};
