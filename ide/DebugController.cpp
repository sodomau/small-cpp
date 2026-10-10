#include "DebugController.h"
#include "SmallBuildConfig.h"
#include "Toolchain.h"
#include "EntryPoint.h"
#include "BuildController.h"
#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>
#include <QLibraryInfo>
#include <QProcessEnvironment>
#include <QRegularExpression>
#include <QSaveFile>
#include <QTimer>

DebugController::DebugController(QObject* p):QObject(p)
{
    projectBuild_ = new BuildController(this);
    connect(projectBuild_, &BuildController::phaseChanged, this, &DebugController::phaseChanged);
    connect(projectBuild_, &BuildController::buildError, this, [this](const QString& raw, const QString& source, const QString& file) {
        setStage(Stage::Idle); emit buildError(raw, source, file);
    });
    connect(projectBuild_, &BuildController::finished, this, [this](int, bool) {
        if (stage_ == Stage::Stopping) { setStage(Stage::Idle); emit finished(); }
    });
    connect(projectBuild_, &BuildController::projectBuilt, this, [this](const QString& executable) {
        if (stage_ == Stage::Stopping) { setStage(Stage::Idle); emit finished(); return; }
        executablePath_ = executable;
        projectSnapshots_ = projectBuild_->projectSnapshots();
        sourcePath_ = project_.absolute(project_.sources.first());
        sourceSnapshot_ = projectSnapshots_.value(sourcePath_);
        startGdb();
    });
    build_.setProcessChannelMode(QProcess::MergedChannels);
    connect(&build_,&QProcess::readyReadStandardOutput,this,[this]{buildOutput_+=build_.readAllStandardOutput();});
    connect(&build_,qOverload<int,QProcess::ExitStatus>(&QProcess::finished),this,[this](int c,QProcess::ExitStatus s){
        buildOutput_+=build_.readAllStandardOutput();
        if(s!=QProcess::NormalExit||c!=0){ setStage(Stage::Idle); emit buildError(QString::fromUtf8(buildOutput_),sourceSnapshot_,sourcePath_); return; }
        if(stage_==Stage::Compiling) link(); else if(stage_==Stage::Linking) startGdb();
    });
    gdb_.setProcessChannelMode(QProcess::MergedChannels);
    connect(&gdb_,&QProcess::readyReadStandardOutput,this,[this]{miBuffer_+=gdb_.readAllStandardOutput();processMi();});
    connect(&gdb_,qOverload<int,QProcess::ExitStatus>(&QProcess::finished),this,[this](int,QProcess::ExitStatus){ if(stage_!=Stage::Idle){setStage(Stage::Idle);emit finished();} });
}
DebugController::~DebugController(){ if(build_.state()!=QProcess::NotRunning)build_.kill(); if(gdb_.state()!=QProcess::NotRunning)gdb_.kill(); }
void DebugController::setStage(Stage s){bool b=isBusy();stage_=s;if(b!=isBusy())emit busyChanged(isBusy());}
QString DebugController::compiler() const { return Toolchain::compiler(); }
QString DebugController::gdbPath() const { QString p=QDir(QFileInfo(compiler()).absolutePath()).filePath(
#ifdef Q_OS_WIN
"gdb.exe"
#else
"gdb"
#endif
); return p; }
void DebugController::configureEnvironment(QProcess& process)
{
    auto env = Toolchain::environment();
    if (projectActive_)
        env.insert("PATH", project_.libraryPaths.join(QDir::listSeparator()) + QDir::listSeparator() + env.value("PATH"));
    process.setProcessEnvironment(env);
}

void DebugController::start(const QString&s,const QString&orig,const QString&name,const QSet<int>&bps){if(isBusy())return;projectActive_=false;breakpoints_=bps;gdbBreakpointIds_.clear();breakpointRequestLines_.clear();breakpointRequestEnabled_.clear();sourceSnapshot_=s;sdkDirectory_=QDir(QCoreApplication::applicationDirPath()).filePath("runtime");extensionsDirectory_=QDir(QCoreApplication::applicationDirPath()).filePath("extensions");runtimePath_=QDir(sdkDirectory_).filePath(QString::fromUtf8(SmallBuildConfig::RuntimeFile));entryPath_=QDir(sdkDirectory_).filePath(QString::fromUtf8(SmallBuildConfig::EntryFile));idePausePath_=QDir(sdkDirectory_).filePath(QString::fromUtf8(SmallBuildConfig::IdePauseFile));usesOwnMain_=DetectEntryPoint(s)==SmallEntryPoint::Main;extensions_=ExtensionRegistry::detect(s,ExtensionRegistry::discover(extensionsDirectory_));directory_=std::make_unique<QTemporaryDir>(QDir::tempPath()+"/SmallCpp-debug-XXXXXX");if(!directory_->isValid()){emit buildError("Cannot create debug folder.",s,{});return;}QString n=orig.isEmpty()?QFileInfo(name).fileName():QFileInfo(orig).fileName();if(!n.endsWith(".cpp",Qt::CaseInsensitive))n+=".cpp";sourcePath_=directory_->filePath(n);objectPath_=directory_->filePath("program.o");executablePath_=directory_->filePath(
#ifdef Q_OS_WIN
"program.exe"
#else
"program"
#endif
);originalDirectory_=orig.isEmpty()?directory_->path():QFileInfo(orig).absolutePath();QSaveFile f(sourcePath_);auto bytes=s.toUtf8();if(!f.open(QIODevice::WriteOnly)||f.write(bytes)!=bytes.size()||!f.commit()){emit buildError("Cannot write temporary debug source.",s,sourcePath_);return;}compile();}
void DebugController::compile(){setStage(Stage::Compiling);emit phaseChanged("Compiling for debugging...");buildOutput_.clear();QStringList a={"-std=c++20","-O0","-g","-fno-omit-frame-pointer","-fdiagnostics-color=never","-I",sdkDirectory_,"-iquote",originalDirectory_,"-c",sourcePath_,"-o",objectPath_};if(!usesOwnMain_){a.prepend(QDir(sdkDirectory_).filePath("small.h"));a.prepend("-include");a.prepend("-DSMALL_BEGINNER_MODE");}for(auto&e:extensions_)a<<"-I"<<e.includeDirectory;configureEnvironment(build_);build_.setWorkingDirectory(directory_->path());build_.start(compiler(),a);}
void DebugController::link(){setStage(Stage::Linking);emit phaseChanged("Linking debugger program...");buildOutput_.clear();QStringList a={objectPath_};if(!usesOwnMain_)a<<entryPath_;a<<idePausePath_;for(auto&e:extensions_)a<<e.libraryPath;a<<runtimePath_;QString portableQtLib=QDir(QCoreApplication::applicationDirPath()).filePath("qt/lib");for(const char*l:SmallBuildConfig::QtLibraries){QString recorded=QString::fromUtf8(l);QString bundled=QDir(portableQtLib).filePath(QFileInfo(recorded).fileName());a<<(QFileInfo::exists(bundled)?bundled:recorded);}a<<"-o"<<executablePath_;build_.start(compiler(),a);}
void DebugController::startGdb()
{
    if(!QFileInfo::exists(gdbPath())){
        setStage(Stage::Idle);
        emit buildError("GDB was not found next to the compiler:\n"+gdbPath(),sourceSnapshot_,sourcePath_);
        return;
    }

    setStage(Stage::Starting);
    emit phaseChanged("Starting debugger...");
    miBuffer_.clear();
    configureEnvironment(gdb_);
    gdb_.setWorkingDirectory(originalDirectory_);

#ifdef Q_OS_WIN
    // GDB itself must keep its stdin/stdout connected to QProcess for MI.
    // But the inferior (the learner's program) should get the same separate
    // Windows console that normal Run uses.
    //
    // GDB on Windows supports this directly: when the inferior is created,
    // request a new console for it.  This does not detach GDB's MI channel.
#endif

    // Connect BEFORE start().  On a fast local process QProcess::started can be
    // delivered immediately; connecting afterwards creates a race that leaves
    // GDB alive but with no MI commands ever sent.
    connect(&gdb_, &QProcess::started, this, [this]{
        emit phaseChanged("Loading debug program...");
#ifdef Q_OS_WIN
        // Match normal Run behavior: create a console for the inferior while
        // leaving GDB itself hidden and controlled through MI.
        sendMi("-gdb-set new-console on", Pending::None);
#endif
        sendMi("-file-exec-and-symbols \""+QDir::fromNativeSeparators(executablePath_)+"\"",Pending::None);

        // Register only breakpoints explicitly created by the user.
        // Debug means "run under GDB", not "stop automatically at main/small_main".
        // Register the initial snapshot through the same live-breakpoint path
        // used by gutter clicks, so GDB breakpoint IDs are tracked consistently.
        const auto initialBreakpoints = breakpoints_;
        breakpoints_.clear();
        gdbBreakpointIds_.clear();
        for(int line : initialBreakpoints)
            setBreakpoint(line, true);
        if (projectActive_) {
            const auto initial = projectBreakpoints_;
            projectBreakpointIds_.clear();
            for (auto it = initial.begin(); it != initial.end(); ++it)
                for (int line : it.value()) setProjectBreakpoint(it.key(), line, true);
        }

        emit phaseChanged(breakpoints_.isEmpty()
                              ? "Running under debugger..."
                              : "Running to breakpoint...");
        sendMi("-exec-run",Pending::StartRun);
    }, Qt::SingleShotConnection);

    gdb_.start(gdbPath(),{"--quiet","--interpreter=mi2"});

    // Never leave the IDE apparently frozen if GDB cannot launch.
    QTimer::singleShot(5000, this, [this]{
        if(stage_==Stage::Starting && gdb_.state()!=QProcess::Running){
            const QString message = "GDB did not start.\n\n" + gdb_.errorString()
                                  + "\n\nExpected debugger:\n" + gdbPath();
            if(gdb_.state()!=QProcess::NotRunning) gdb_.kill();
            setStage(Stage::Idle);
            emit buildError(message,sourceSnapshot_,sourcePath_);
        }
    });
}
void DebugController::sendMi(const QString& c,Pending p){pending_=p;gdb_.write((QString::number(++token_)+c+"\n").toUtf8());}
void DebugController::processMi(){int pos;while((pos=miBuffer_.indexOf('\n'))>=0){QString r=QString::fromUtf8(miBuffer_.left(pos)).trimmed();miBuffer_.remove(0,pos+1);if(!r.isEmpty())handleRecord(r);}}
QString DebugController::miField(const QString&r,const QString&k){QRegularExpression re(k+"=\"((?:\\\\.|[^\"])*)\"");auto m=re.match(r);if(!m.hasMatch())return{};QString v=m.captured(1);v.replace("\\\\","\\");v.replace("\\\"","\"");return v;}
bool DebugController::isUserFile(const QString& f)const{if(projectActive_)return projectSnapshots_.contains(QDir::cleanPath(f));return QFileInfo(f).fileName().compare(QFileInfo(sourcePath_).fileName(),Qt::CaseInsensitive)==0;}
void DebugController::handleRecord(const QString&r){
    // Track the GDB breakpoint number returned for each live gutter request.
    QRegularExpression tokenResultRe(R"(^(\d+)\^(done|error)(.*)$)");
    auto tokenMatch = tokenResultRe.match(r);
    if (tokenMatch.hasMatch()) {
        const int responseToken = tokenMatch.captured(1).toInt();
        if (projectBreakpointRequests_.contains(responseToken)) {
            const QString key = projectBreakpointRequests_.take(responseToken);
            const QString id = miField(tokenMatch.captured(3), "number");
            if (tokenMatch.captured(2) == "done" && !id.isEmpty()) projectBreakpointIds_[key] = id;
            else if (tokenMatch.captured(2) == "error") emit phaseChanged("Could not set project breakpoint");
        }
        if (breakpointRequestLines_.contains(responseToken)) {
            const int line = breakpointRequestLines_.take(responseToken);
            const bool enabled = breakpointRequestEnabled_.take(responseToken);
            if (tokenMatch.captured(2) == "done" && enabled) {
                QRegularExpression numberRe(QStringLiteral("number=\\\"([^\\\"]+)\\\""));
                auto numberMatch = numberRe.match(tokenMatch.captured(3));
                if (numberMatch.hasMatch())
                    gdbBreakpointIds_[line] = numberMatch.captured(1);
            } else if (tokenMatch.captured(2) == "error") {
                // Keep the IDE's visual state authoritative, but surface the
                // debugger failure instead of silently ignoring the click.
                emit phaseChanged(enabled ? "Could not set breakpoint"
                                          : "Could not remove breakpoint");
            }
        }
    }
    if(r.startsWith("*stopped")){executionStopped(r);return;}if(r.contains("^error")){
        if(pending_==Pending::EvalLocalString){
            locals_[localStringIndex_].value="<unavailable>";
            evalNextLocalString();
        }else emit phaseChanged("Debugger error");
        return;
    }if(pending_==Pending::RefreshLocals&&r.contains("^done,variables=[")){locals_.clear();QRegularExpression re(R"re(\{name="([^"]+)"(?:,arg="[^"]+")?,type="([^"]*)"(?:,value="([^"]*)")?\})re");auto it=re.globalMatch(r);while(it.hasNext()){auto m=it.next();DebugVariable v{m.captured(1),m.captured(3)};if(v.value.isEmpty()&&(m.captured(2)=="String"||m.captured(2)=="Small::String"))v.value="<String>";locals_<<v;}localStringIndex_=-1;evalNextLocalString();}
else if(pending_==Pending::RefreshGlobals&&r.startsWith("~\"")){/* console chunks handled below */}
else if(pending_==Pending::EvalLocalString&&r.contains("^done,value=")){QString val=miField(r,"value");const int quote=val.indexOf(QLatin1Char('"'));locals_[localStringIndex_].value=quote>=0?val.mid(quote):val;evalNextLocalString();}
else if(pending_==Pending::EvalGlobal&&r.contains("^done,value=")){QString val=miField(r,"value");globals_[globalIndex_].value=val;if(++globalIndex_<globals_.size())evalNextGlobal();else{pending_=Pending::None;emit variablesChanged(locals_,globals_);}}

}
void DebugController::executionStopped(const QString& r)
{
    const QString reason = miField(r, "reason");

    if (reason == "signal-received") {
        const QString signalName = miField(r, "signal-name");
        const QString signalMeaning = miField(r, "signal-meaning");
        emit phaseChanged(signalMeaning.isEmpty()
                              ? "Runtime error"
                              : "Runtime error: " + signalMeaning);
        setStage(Stage::Stopped);
        emitStop(miField(r, "fullname"), miField(r, "line").toInt());
        return;
    }

    // When the learner closes a Small Window, the program exits normally.
    // GDB itself stays alive after reporting this MI event, so treating every
    // *stopped record as a breakpoint leaves the IDE stuck in debug mode.
    if (reason.startsWith("exited")) {
        emit phaseChanged("Program finished");
        emit stoppedAt(0);
        locals_.clear();
        globals_.clear();
        emit variablesChanged(locals_, globals_);

        setStage(Stage::Stopping);
        if (gdb_.state() != QProcess::NotRunning) {
            sendMi("-gdb-exit", Pending::None);
            QTimer::singleShot(500, &gdb_, [this] {
                if (gdb_.state() != QProcess::NotRunning)
                    gdb_.kill();
            });
        } else {
            setStage(Stage::Idle);
            emit finished();
        }
        return;
    }

    QString file = miField(r, "fullname");
    if(file.isEmpty()) file = miField(r, "file");

    if(pending_==Pending::FilterStep && !isUserFile(file)){
        sendMi("-exec-step",Pending::FilterStep);
        return;
    }

    setStage(Stage::Stopped);
    int line=miField(r,"line").toInt();
    emit phaseChanged("Paused");
    emitStop(file, line);
    refreshVariables();
}
void DebugController::refreshVariables(){sendMi("-stack-list-variables --simple-values",Pending::RefreshLocals);}
// Read the bundled libstdc++ string buffer without calling an inline c_str() in the inferior.
void DebugController::evalNextLocalString(){ for(int i=localStringIndex_+1;i<locals_.size();++i){if(locals_[i].value=="<String>"){localStringIndex_=i;sendMi("-data-evaluate-expression \""+locals_[i].name+".data_._M_dataplus._M_p\"",Pending::EvalLocalString);return;}}requestGlobals();}
void DebugController::requestGlobals(){globals_.clear();globalNames_.clear(); // inexpensive source scan: top-level simple declarations; GDB evaluates values.
 int depth=0;QRegularExpression re("^\\s*(?:static\\s+)?(?:bool|int|double|float|char|String)\\s+([A-Za-z_]\\w*)\\s*(?:=|;)");for(const QString&line:sourceSnapshot_.split('\n')){auto m=re.match(line);if(depth==0&&m.hasMatch())globalNames_<<m.captured(1);for(QChar c:line){if(c=='{')++depth;else if(c=='}')--depth;}}for(auto&n:globalNames_)globals_<<DebugVariable{n,{}};globalIndex_=0;if(globals_.isEmpty()){emit variablesChanged(locals_,globals_);pending_=Pending::None;}else evalNextGlobal();}
void DebugController::evalNextGlobal(){sendMi("-data-evaluate-expression \""+globals_[globalIndex_].name+"\"",Pending::EvalGlobal);}
void DebugController::setBreakpoint(int line, bool enabled)
{
    if (line <= 0) return;

    if (enabled) breakpoints_.insert(line);
    else breakpoints_.remove(line);

    // Before GDB is running this is just the snapshot used at startup.
    if (gdb_.state() != QProcess::Running ||
        stage_ == Stage::Idle || stage_ == Stage::Compiling ||
        stage_ == Stage::Linking)
        return;

    if (enabled) {
        if (gdbBreakpointIds_.contains(line)) return;
        const int requestToken = token_ + 1;
        breakpointRequestLines_.insert(requestToken, line);
        breakpointRequestEnabled_.insert(requestToken, true);
        sendMi(QString("-break-insert \"%1:%2\"")
                   .arg(QDir::fromNativeSeparators(sourcePath_))
                   .arg(line), Pending::None);
    } else {
        const QString id = gdbBreakpointIds_.take(line);
        if (!id.isEmpty()) {
            const int requestToken = token_ + 1;
            breakpointRequestLines_.insert(requestToken, line);
            breakpointRequestEnabled_.insert(requestToken, false);
            sendMi("-break-delete " + id, Pending::None);
        }
    }
}

void DebugController::continueRun(){if(isStopped()){setStage(Stage::Running);sendMi("-exec-continue",Pending::Continue);}}
void DebugController::stepOver(){if(isStopped()){setStage(Stage::Running);sendMi("-exec-next",Pending::Next);}}
void DebugController::stepInto(){if(isStopped()){setStage(Stage::Running);sendMi("-exec-step",Pending::FilterStep);}}
void DebugController::stepOut(){if(isStopped()){setStage(Stage::Running);sendMi("-exec-finish",Pending::Finish);}}
void DebugController::stop(){if(!isBusy())return;setStage(Stage::Stopping);if(projectBuild_->isBusy()){projectBuild_->stop();return;}if(build_.state()!=QProcess::NotRunning)build_.kill();if(gdb_.state()!=QProcess::NotRunning){gdb_.write("-gdb-exit\n");QTimer::singleShot(300,&gdb_,[this]{if(gdb_.state()!=QProcess::NotRunning)gdb_.kill();});}else{setStage(Stage::Idle);emit finished();}}
