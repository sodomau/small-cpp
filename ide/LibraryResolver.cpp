#include "LibraryResolver.h"
#include "Toolchain.h"
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QRegularExpression>
#include <QStandardPaths>
#include <QTimer>

QString LibraryResolver::pkgConfig() { return QDir(QFileInfo(Toolchain::compiler()).absolutePath()).filePath("pkg-config.exe"); }
QString LibraryResolver::pacman()
{
    const QDir prefix(QFileInfo(Toolchain::compiler()).absolutePath());
    return prefix.absoluteFilePath("../../usr/bin/pacman.exe");
}
QString LibraryResolver::catalogPath()
{
    return QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation) + "/msys2_pkgconfig_map.json";
}
QJsonObject LibraryResolver::catalog()
{
    static const bool initialized = [] { Q_INIT_RESOURCE(Libraries); return true; }();
    Q_UNUSED(initialized);
    for (const auto& path : {catalogPath(), Toolchain::root() + "/msys2_pkgconfig_map.json", QString(":/libraries/msys2_pkgconfig_map.json")}) {
        QFile file(path);
        if (!file.open(QIODevice::ReadOnly)) continue;
        const auto document = QJsonDocument::fromJson(file.readAll());
        if (document.isObject() && !document.object().isEmpty()) return document.object();
    }
    return {};
}
QJsonObject LibraryResolver::scanCatalog(const QByteArray& listing)
{
    QMap<QString, QStringList> modules;
    const QRegularExpression pattern("^(mingw-w64-ucrt-x86_64-\\S+)\\s+ucrt64/(?:lib|share)/pkgconfig/([^/]+)\\.pc$");
    for (const auto& line : QString::fromUtf8(listing).split('\n')) {
        const auto match = pattern.match(line.trimmed());
        if (match.hasMatch()) modules[match.captured(2)] << match.captured(1);
    }
    QJsonObject result;
    for (auto it = modules.begin(); it != modules.end(); ++it) {
        it.value().removeDuplicates(); it.value().sort();
        result.insert(it.key(), it.value().size() == 1 ? QJsonValue(it.value().first()) : QJsonValue(QJsonArray::fromStringList(it.value())));
    }
    return result;
}
QStringList LibraryResolver::splitFlags(const QString& text)
{
    // pkg-config emits shell quoting (including escaped spaces), not Windows command quoting.
    QStringList result; QString word; QChar quote; bool escaped = false, active = false;
    for (const auto character : text) {
        if (escaped) { word += character; escaped = false; active = true; continue; }
        if (character == '\\' && quote != '\'') { escaped = true; active = true; continue; }
        if (!quote.isNull()) { if (character == quote) quote = {}; else word += character; active = true; continue; }
        if (character == '\'' || character == '"') { quote = character; active = true; continue; }
        if (character.isSpace()) { if (active) result << word; word.clear(); active = false; }
        else { word += character; active = true; }
    }
    if (escaped) word += '\\';
    if (active) result << word;
    return result;
}
LibraryResolver::LibraryResolver(QObject* parent) : QObject(parent)
{
    connect(&process_, &QProcess::readyReadStandardOutput, this, [this] {
        const auto data = process_.readAllStandardOutput(); bytes_ += data;
        if (step_ == 2 || step_ == 5) emit output(QString::fromUtf8(data));
    });
    connect(&process_, &QProcess::readyReadStandardError, this, [this] { emit output(QString::fromUtf8(process_.readAllStandardError())); });
    connect(&process_, &QProcess::finished, this, &LibraryResolver::finished);
    connect(&process_, &QProcess::errorOccurred, this, [this](QProcess::ProcessError error) {
        if (!cancelled_ && error == QProcess::FailedToStart) emit failed("Could not start library tools: " + process_.errorString());
    });
}
void LibraryResolver::run(const QString& program, const QStringList& args)
{
    bytes_.clear();
    auto env = Toolchain::environment();
    const QDir bin(QFileInfo(Toolchain::compiler()).absolutePath());
    env.insert("PKG_CONFIG_LIBDIR", bin.absoluteFilePath("../lib/pkgconfig") + QDir::listSeparator() + bin.absoluteFilePath("../share/pkgconfig"));
    env.remove("PKG_CONFIG_PATH"); env.remove("PKG_CONFIG_SYSROOT_DIR");
    env.insert("MSYSTEM", "UCRT64"); env.insert("CHERE_INVOKING", "1"); env.insert("MSYS2_PATH_TYPE", "minimal");
    process_.setProcessEnvironment(env);
    process_.start(program, args);
}
void LibraryResolver::resolve(const QStringList& modules)
{
    if (isRunning()) { emit failed("A library operation is still finishing. Try again when it completes."); return; }
    cancelled_ = false; bootstrap_ = false; modules_ = modules; modules_.removeDuplicates();
    missing_.clear(); packages_.clear(); cflags_.clear(); index_ = 0; step_ = 0;
    if (modules_.isEmpty()) { QTimer::singleShot(0, this, [this] { if (!cancelled_) emit ready({}, {}); }); return; }
    for (const auto& module : modules_)
        if (!QRegularExpression("^[A-Za-z0-9_+.-]+$").match(module).hasMatch() || module.startsWith('-')) {
            emit failed("Invalid pkg-config module name: " + module); return;
        }
    if (!QFileInfo::exists(pkgConfig())) {
        const QString package = "mingw-w64-ucrt-x86_64-pkgconf";
        if (!confirmInstall || !confirmInstall({package})) { emit failed("Library setup cancelled. pkg-config is required."); return; }
        if (cancelled_) return;
        packages_ << package; step_ = 2; bootstrap_ = true;
        installPackages(); return;
    }
    checkNext();
}
void LibraryResolver::checkNext()
{
    if (cancelled_) return;
    if (index_ < modules_.size()) { step_ = 0; run(pkgConfig(), {"--exists", modules_[index_]}); return; }
    if (!missing_.isEmpty()) { installMissing(); return; }
    step_ = 3; run(pkgConfig(), QStringList{"--cflags"} + modules_);
}
void LibraryResolver::installMissing()
{
    const auto mapping = catalog();
    packages_.clear();
    for (const auto& module : missing_) {
        const auto value = mapping.value(module);
        QStringList providers;
        if (value.isString()) providers << value.toString();
        else for (const auto& item : value.toArray()) providers << item.toString();
        if (providers.isEmpty()) { emit failed("No package found for " + module + ". Try Libraries > Update List or install it in MSYS2 Terminal."); return; }
        const QString provider = providers.size() == 1 ? providers.first() : (chooseProvider ? chooseProvider(module, providers) : QString());
        if (provider.isEmpty()) { emit failed("Library selection cancelled."); return; }
        if (!providers.contains(provider) || !QRegularExpression("^mingw-w64-ucrt-x86_64-[A-Za-z0-9_+.-]+$").match(provider).hasMatch()) {
            emit failed("Invalid library provider: " + provider); return;
        }
        packages_ << provider;
    }
    packages_.removeDuplicates();
    if (!confirmInstall || !confirmInstall(packages_)) { emit failed("Library installation cancelled. Your library declarations were kept."); return; }
    if (cancelled_) return;
    step_ = 2;
    emit output("Installing libraries:\n" + packages_.join('\n') + "\n");
    installPackages();
}
void LibraryResolver::installPackages()
{
    const QDir bin(QFileInfo(pacman()).absolutePath());
    if (!QFileInfo(bin.absoluteFilePath("../../etc/pacman.d/gnupg/pubring.kbx")).isFile()
        && !QFileInfo(bin.absoluteFilePath("../../etc/pacman.d/gnupg/pubring.gpg")).isFile()) {
        step_ = 5; emit output("Preparing the MSYS2 environment for its first installation...\n");
        run(bin.filePath("bash.exe"), {"--login", "-c", "true"}); return;
    }
    step_ = 2; run(pacman(), QStringList{"-S", "--needed", "--noconfirm"} + packages_);
}
void LibraryResolver::finished(int code, QProcess::ExitStatus status)
{
    bytes_ += process_.readAllStandardOutput();
    if (cancelled_) { emit cancelled(); return; }
    if (step_ == 0) { if (code != 0) missing_ << modules_[index_]; ++index_; checkNext(); return; }
    if (status != QProcess::NormalExit || code != 0) {
        emit failed("Library tool failed:\n" + QString::fromUtf8(bytes_) + "\nSee Console. You may need to update the MSYS2 environment in its terminal."); return;
    }
    if (step_ == 5) { step_ = 2; run(pacman(), QStringList{"-S", "--needed", "--noconfirm"} + packages_); return; }
    if (step_ == 2 && bootstrap_) { bootstrap_ = false; index_ = 0; missing_.clear(); checkNext(); return; }
    if (step_ == 2) {
        // Recheck every module after pacman rather than trusting package names.
        step_ = 1; index_ = 0; missing_.clear();
        run(pkgConfig(), QStringList{"--exists"} + modules_); return;
    }
    if (step_ == 1) { step_ = 3; run(pkgConfig(), QStringList{"--cflags"} + modules_); return; }
    if (step_ == 3) { cflags_ = splitFlags(QString::fromUtf8(bytes_).trimmed()); step_ = 4; run(pkgConfig(), QStringList{"--libs"} + modules_); return; }
    emit ready(cflags_, splitFlags(QString::fromUtf8(bytes_).trimmed()));
}
void LibraryResolver::cancel()
{
    cancelled_ = true;
    // Never interrupt a pacman transaction mid-write. Stop waits for it to finish;
    // the requested compile/run will then be cancelled.
    if (isRunning() && step_ != 2 && step_ != 5) process_.terminate();
}

LibraryResolver::~LibraryResolver() { if (process_.state() != QProcess::NotRunning) { process_.terminate(); process_.waitForFinished(3000); } }
