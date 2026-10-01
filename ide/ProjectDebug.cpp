#include "DebugController.h"
#include "BuildController.h"
#include <QDir>
#include <QFileInfo>

void DebugController::startProject(const ProjectFolder& project, const QMap<QString, QSet<int>>& breakpoints)
{
    if (isBusy()) return;
    project_ = project;
    projectActive_ = true;
    projectBreakpoints_ = breakpoints;
    projectBreakpointIds_.clear(); projectBreakpointRequests_.clear();
    breakpoints_.clear(); gdbBreakpointIds_.clear();
    breakpointRequestLines_.clear(); breakpointRequestEnabled_.clear();
    originalDirectory_ = project.root;
    setStage(Stage::Compiling);
    projectBuild_->startProject(project, true);
}

void DebugController::emitStop(const QString& file, int line)
{
    if (projectActive_) {
        const QString path = QDir::cleanPath(file);
        sourceSnapshot_ = projectSnapshots_.value(path);
        emit stoppedAtFile(path, line);
    } else emit stoppedAt(line);
}

void DebugController::setProjectBreakpoint(const QString& file, int line, bool enabled)
{
    if (line <= 0 || !project_.contains(file)) return;
    if (enabled) projectBreakpoints_[file].insert(line);
    else projectBreakpoints_[file].remove(line);
    if (gdb_.state() != QProcess::Running || stage_ == Stage::Compiling || stage_ == Stage::Idle) return;
    const QString key = file + ":" + QString::number(line);
    if (enabled) {
        if (projectBreakpointIds_.contains(key) || projectBreakpointRequests_.values().contains(key)) return;
        projectBreakpointRequests_[token_ + 1] = key;
        QString path = QDir::fromNativeSeparators(file);
        path.replace('"', "\\\"");
        sendMi(QString("-break-insert \"%1:%2\"").arg(path).arg(line), Pending::None);
    } else {
        const QString id = projectBreakpointIds_.take(key);
        if (!id.isEmpty()) sendMi("-break-delete " + id, Pending::None);
    }
}
