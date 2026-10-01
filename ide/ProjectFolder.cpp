#include "ProjectFolder.h"
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QSaveFile>
#include <functional>

QString ProjectFolder::absolute(const QString& relative) const { return QDir(root).filePath(relative); }
bool ProjectFolder::isSource(const QString& path) { return QFileInfo(path).suffix().compare("cpp", Qt::CaseInsensitive) == 0; }
bool ProjectFolder::isHeader(const QString& path)
{
    return QStringList{"h", "hpp", "hh", "hxx", "inl"}.contains(QFileInfo(path).suffix().toLower());
}
bool ProjectFolder::contains(const QString& path) const
{
    if (root.isEmpty() || path.isEmpty()) return false;
    const QFileInfo info(path);
    const QString canonical = info.canonicalFilePath();
    const QString parent = QFileInfo(info.absolutePath()).canonicalFilePath();
    const QString resolved = canonical.isEmpty() ? (parent.isEmpty() ? info.absoluteFilePath() : QDir(parent).filePath(info.fileName())) : canonical;
    return QDir::cleanPath(resolved).startsWith(root + "/", Qt::CaseInsensitive);
}
bool ProjectFolder::excludes(const QString& relative) const
{
    for (const auto& path : excluded)
        if (relative.compare(path, Qt::CaseInsensitive) == 0 || relative.startsWith(path + "/", Qt::CaseInsensitive)) return true;
    return false;
}
bool ProjectFolder::load(const QString& folder, QString* error)
{
    const QString requested = folder;
    *this = ProjectFolder{};
    root = QFileInfo(requested).canonicalFilePath();
    if (root.isEmpty() || !QFileInfo(root).isDir()) { *error = "Choose an existing project folder."; return false; }
    name = QDir(root).dirName();
    QFile config(absolute("small.project"));
    if (config.exists()) {
        if (!config.open(QIODevice::ReadOnly)) { *error = "Cannot read small.project: " + config.errorString(); return false; }
        QJsonParseError parse;
        auto document = QJsonDocument::fromJson(config.readAll(), &parse);
        if (parse.error != QJsonParseError::NoError || !document.isObject()) {
            *error = "small.project must be a JSON object. " + parse.errorString(); return false;
        }
        settings = document.object();
        const QStringList allowed{"version", "name", "exclude", "include_paths", "library_paths", "libraries", "compiler_options", "linker_options"};
        for (auto it = settings.begin(); it != settings.end(); ++it)
            if (!allowed.contains(it.key())) { *error = "Unknown small.project setting: " + it.key(); return false; }
        if (settings.contains("version") && settings.value("version").toInt(-1) != 1) { *error = "Unsupported small.project version."; return false; }
        if (settings.contains("name")) {
            if (!settings.value("name").isString() || settings.value("name").toString().trimmed().isEmpty()) { *error = "Project name must be text."; return false; }
            name = settings.value("name").toString().trimmed();
        }
        auto list = [&](const QString& key, QStringList& target, bool paths = false) {
            if (!settings.contains(key)) return true;
            if (!settings.value(key).isArray()) { *error = key + " must be an array of strings."; return false; }
            for (const auto& item : settings.value(key).toArray()) {
                if (!item.isString() || item.toString().trimmed().isEmpty()) { *error = key + " needs nonempty strings."; return false; }
                target << (paths ? QDir::cleanPath(QDir(root).absoluteFilePath(item.toString())) : item.toString());
            }
            return true;
        };
        if (!list("exclude", excluded) || !list("include_paths", includePaths, true) || !list("library_paths", libraryPaths, true) ||
            !list("libraries", libraries) || !list("compiler_options", compilerOptions) || !list("linker_options", linkerOptions)) return false;
        for (auto& path : excluded) {
            path = QDir::cleanPath(QDir::fromNativeSeparators(path));
            if (QDir::isAbsolutePath(path) || path == "." || path == ".." || path.startsWith("../")) {
                *error = "Exclude paths must be inside the project folder."; return false;
            }
        }
        // Keep output paths and compilation stages under IDE control.
        for (const auto& option : compilerOptions + linkerOptions)
            if (option.startsWith("@") || option == "-c" || option == "-S" || option == "-E" || option.startsWith("-o") || option.startsWith("--output")) {
                *error = "The IDE manages output files; unsupported option: " + option; return false;
            }
    }
    return scan(error);
}
bool ProjectFolder::scan(QString* error)
{
    files.clear(); sources.clear(); headers.clear(); resources.clear();
    if (!QFileInfo(root).isDir()) { *error = "The project folder is no longer available."; return false; }
    std::function<void(const QString&)> visit = [&](const QString& relative) {
        QDir directory(absolute(relative));
        for (const auto& info : directory.entryInfoList(QDir::AllEntries | QDir::Hidden | QDir::NoDotAndDotDot, QDir::DirsFirst | QDir::Name)) {
            if (info.isSymLink()) continue;
            const QString path = relative.isEmpty() ? info.fileName() : relative + "/" + info.fileName();
            if (info.isDir()) {
                const QString n = info.fileName().toLower();
                if (QStringList{".git", ".svn", ".hg", ".smallcpp", "build", "cmakefiles"}.contains(n) ||
                    n.startsWith(".smallcpp-publish-") || QFileInfo(QDir(info.absoluteFilePath()).filePath(".smallcpp-package")).exists()) continue;
                visit(path);
            } else if (info.isFile() && info.fileName() != "small.project" && info.fileName() != ".smallcpp-package") {
                files << path;
                if (excludes(path)) continue;
                if (isSource(path)) sources << path;
                else if (isHeader(path)) headers << path;
                else resources << path;
            }
        }
    };
    visit("");
    return true;
}
bool ProjectFolder::setExcluded(const QString& relative, bool exclude, QString* error)
{
    const QString path = QDir::cleanPath(QDir::fromNativeSeparators(relative));
    if (path.isEmpty() || path == "." || path == ".." || path.startsWith("../") || QDir::isAbsolutePath(path)) { *error = "Choose a file or folder inside this project."; return false; }
    QStringList next = excluded;
    if (exclude) { if (!next.contains(path)) next << path; }
    else next.removeAll(path);
    QJsonObject config = settings;
    config.insert("version", 1);
    config.insert("exclude", QJsonArray::fromStringList(next));
    QSaveFile file(absolute("small.project"));
    const auto bytes = QJsonDocument(config).toJson();
    if (!file.open(QIODevice::WriteOnly) || file.write(bytes) != bytes.size() || !file.commit()) { *error = "Could not save project settings: " + file.errorString(); return false; }
    return load(root, error);
}
