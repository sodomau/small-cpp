#include "ExtensionRegistry.h"

#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QRegularExpression>

QVector<SmallExtension> ExtensionRegistry::discover(const QString& extensionsRoot)
{
    QVector<SmallExtension> result;
    QDir root(extensionsRoot);
    for (const QString& folder : root.entryList(QDir::Dirs | QDir::NoDotAndDotDot, QDir::Name))
    {
        const QString base = root.filePath(folder);
        QFile file(QDir(base).filePath("extension.json"));
        if (!file.open(QIODevice::ReadOnly)) continue;

        QJsonParseError error;
        const auto doc = QJsonDocument::fromJson(file.readAll(), &error);
        if (error.error != QJsonParseError::NoError || !doc.isObject()) continue;
        const auto o = doc.object();

        SmallExtension e;
        e.id = o.value("id").toString();
        e.name = o.value("name").toString(e.id);
        e.header = o.value("header").toString();
        const QString include = o.value("include").toString("include");
        const QString lib = o.value("lib").toString("lib");
        const QString library = o.value("library").toString();
        e.includeDirectory = QDir(base).filePath(include);
        e.libraryPath = QDir(QDir(base).filePath(lib)).filePath(library);
        e.tutorialDirectory = QDir(base).filePath(o.value("tutorial").toString("tutorial"));
        e.examplesDirectory = QDir(base).filePath(o.value("examples").toString("examples"));

        if (!e.id.isEmpty() && !e.header.isEmpty() && !library.isEmpty())
            result.append(e);
    }
    return result;
}

QVector<SmallExtension> ExtensionRegistry::detect(
    const QString& source, const QVector<SmallExtension>& installed)
{
    QVector<SmallExtension> result;
    for (const auto& extension : installed)
    {
        const QString escaped = QRegularExpression::escape(extension.header);
        const QRegularExpression include(
            "^\\s*#\\s*include\\s*[<\\\"]" + escaped + "[>\\\"]",
            QRegularExpression::MultilineOption);
        if (include.match(source).hasMatch())
            result.append(extension);
    }
    return result;
}
