#pragma once
#include <QObject>
#include <QProcess>
#include <QTemporaryDir>
#include <QSet>
#include <QHash>
#include <memory>
#include "ExtensionRegistry.h"
#include "ProjectFolder.h"
#include <QMap>
class BuildController;

struct DebugVariable { QString name, value; };
Q_DECLARE_METATYPE(DebugVariable)

class DebugController : public QObject
{
    Q_OBJECT
public:
    enum class Stage { Idle, Compiling, Linking, Starting, Running, Stopped, Stopping };
    explicit DebugController(QObject* parent=nullptr);
    ~DebugController() override;
    bool isBusy() const { return stage_ != Stage::Idle; }
    bool isStopped() const { return stage_ == Stage::Stopped; }
    void start(const QString& source, const QString& originalFilePath, const QString& unsavedName,
               const QSet<int>& breakpoints);
    void stop();
    void continueRun();
    void stepOver();
    void stepInto();
    void stepOut();
    void setBreakpoint(int line, bool enabled);
    void startProject(const ProjectFolder& project, const QMap<QString, QSet<int>>& breakpoints);
    void setProjectBreakpoint(const QString& file, int line, bool enabled);
signals:
    void busyChanged(bool);
    void phaseChanged(const QString&);
    void buildError(const QString& raw, const QString& source, const QString& sourceFile);
    void stoppedAt(int line);
    void stoppedAtFile(const QString& file, int line);
    void variablesChanged(const QList<DebugVariable>& locals, const QList<DebugVariable>& globals);
    void finished();
private:
    QProcess build_, gdb_;
    Stage stage_=Stage::Idle;
    std::unique_ptr<QTemporaryDir> directory_;
    QString sourceSnapshot_, sourcePath_, objectPath_, executablePath_;
    QString originalDirectory_, sdkDirectory_, extensionsDirectory_, runtimePath_, entryPath_, idePausePath_;
    QVector<SmallExtension> extensions_;
    bool usesOwnMain_=false;
    QByteArray buildOutput_, miBuffer_;
    int token_=0;
    enum class Pending { None, StartRun, Continue, Next, Step, Finish, FilterStep, RefreshLocals, RefreshGlobals, EvalGlobal, EvalLocalString };
    Pending pending_=Pending::None;
    QStringList globalNames_;
    QList<DebugVariable> locals_, globals_;
    int globalIndex_=0;
    int localStringIndex_=-1;
    QSet<int> breakpoints_;
    QHash<int, QString> gdbBreakpointIds_;
    QHash<int, int> breakpointRequestLines_;
    QHash<int, bool> breakpointRequestEnabled_;
    BuildController* projectBuild_ = nullptr;
    bool projectActive_ = false;
    ProjectFolder project_;
    QMap<QString, QSet<int>> projectBreakpoints_;
    QMap<QString, QString> projectSnapshots_;
    QHash<QString, QString> projectBreakpointIds_;
    QHash<int, QString> projectBreakpointRequests_;
    void emitStop(const QString& file, int line);
    void setStage(Stage);
    QString compiler() const;
    QString gdbPath() const;
    void configureEnvironment(QProcess&);
    void compile(); void link(); void startGdb();
    void sendMi(const QString&, Pending);
    void processMi(); void handleRecord(const QString&);
    void executionStopped(const QString& record);
    void refreshVariables(); void evalNextLocalString(); void requestGlobals(); void evalNextGlobal();
    bool isUserFile(const QString&) const;
    static QString miField(const QString&, const QString&);
};
