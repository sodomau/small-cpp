#include "FileBuildOptions.h"
#include <QDir>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonParseError>

bool FileBuildOptions::parse(const QString& source, const QString& directory, FileBuildOptions* result, QString* error)
{
    *result = {};
    QString text = source;
    if (text.startsWith(QChar(0xfeff))) text.remove(0, 1);
    QString json;
    for (const auto& line : text.split('\n')) {
        if (!line.startsWith("//@")) break;
        json += line.mid(3) + "\n";
        ++result->lines;
    }
    if (!result->lines) return true;
    QJsonParseError parse;
    const auto doc = QJsonDocument::fromJson(json.toUtf8(), &parse);
    if (parse.error != QJsonParseError::NoError || !doc.isObject()) {
        const int line = json.toUtf8().left(parse.offset).count('\n') + 1;
        *error = QString("Build options at line %1 must form a JSON object: %2").arg(line).arg(parse.errorString());
        return false;
    }
    result->settings = doc.object();
    const QStringList keys{"libraries", "include_paths", "library_paths", "compiler_options", "linker_options"};
    for (auto it = result->settings.begin(); it != result->settings.end(); ++it) {
        if (!keys.contains(it.key()) || !it.value().isArray()) {
            *error = "Unknown or invalid build option: " + it.key(); return false;
        }
        for (const auto& item : it.value().toArray())
            if (!item.isString() || item.toString().trimmed().isEmpty()) {
                *error = it.key() + " needs nonempty strings."; return false;
            }
    }
    auto list = [&](const QString& key, QStringList& target, bool paths = false) {
        for (const auto& item : result->settings.value(key).toArray())
            target << (paths ? QDir(directory).absoluteFilePath(item.toString()) : item.toString());
    };
    list("libraries", result->libraries);
    list("include_paths", result->includePaths, true);
    list("library_paths", result->libraryPaths, true);
    list("compiler_options", result->compilerOptions);
    list("linker_options", result->linkerOptions);
    for (const auto& option : result->compilerOptions + result->linkerOptions)
        if (option.startsWith('@') || option == "-c" || option == "-S" || option == "-E" || option.startsWith("-o") || option.startsWith("--output")) {
            *error = "The IDE manages output files; unsupported option: " + option; return false;
        }
    return true;
}

QString FileBuildOptions::withLibraries(const QString& source, const FileBuildOptions& options, const QStringList& libraries)
{
    auto settings = options.settings;
    settings.insert("libraries", QJsonArray::fromStringList(libraries));
    QString json = QString::fromUtf8(QJsonDocument(settings).toJson(QJsonDocument::Indented)).trimmed();
    QStringList prefix;
    for (const auto& line : json.split('\n')) prefix << "//@ " + line;
    QStringList body = source.split('\n');
    for (int i = 0; i < options.lines; ++i) body.removeFirst();
    return prefix.join('\n') + "\n" + body.join('\n');
}
