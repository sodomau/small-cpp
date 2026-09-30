#include "ExampleCatalog.h"

#include <QFile>
#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QRegularExpression>
#include <QResource>
#include <QSet>
#include <QStringDecoder>
#include <utility>

// Q_INIT_RESOURCE must be outside a namespace. This reference also keeps the
// resource object from being discarded when linking small_ide_components.a.
static void InitializeExampleResources()
{
    Q_INIT_RESOURCE(SmallExamples);
}

ExampleCatalog::ExampleCatalog()
{
    static const bool initialized = [] {
        InitializeExampleResources();
        return true;
    }();
    Q_UNUSED(initialized);
    load();
}

const ExampleEntry* ExampleCatalog::find(const QString& id) const
{
    for (const auto& entry : entries_)
        if (entry.id == id) return &entry;
    return nullptr;
}

void ExampleCatalog::load()
{
    QFile manifest(":/small/examples/catalog.json");
    if (!manifest.open(QIODevice::ReadOnly))
    {
        error_ = "The built-in example catalog is missing. Rebuild SmallCppIDE.";
        return;
    }
    QJsonParseError parse;
    const QJsonDocument json = QJsonDocument::fromJson(manifest.readAll(), &parse);
    if (parse.error != QJsonParseError::NoError || !json.isObject())
    {
        error_ = "Could not read the example catalog: " + parse.errorString();
        return;
    }
    const QJsonObject object = json.object();
    if (object.value("version").toInt() != 1 || !object.value("examples").isArray())
    {
        error_ = "The example catalog has an unsupported format.";
        return;
    }
    QVector<ExampleEntry> pending;
    QSet<QString> ids;
    const QRegularExpression validSource("^(reference|programs)/[a-z0-9_]+\\.cpp$");
    for (const auto& value : object.value("examples").toArray())
    {
        const QJsonObject item = value.toObject();
        ExampleEntry entry;
        entry.id = item.value("id").toString();
        entry.group = item.value("group").toString();
        entry.title = item.value("title").toString();
        entry.description = item.value("description").toString();
        entry.notes = item.value("notes").toString();
        entry.sourceName = item.value("source").toString();
        const QString expectedGroup = entry.sourceName.startsWith("reference/") ? "Reference" : "Programs";
        if (!validSource.match(entry.sourceName).hasMatch() ||
            entry.id != entry.sourceName.chopped(4) || ids.contains(entry.id) ||
            entry.group != expectedGroup || entry.title.trimmed().isEmpty() ||
            entry.description.trimmed().isEmpty() || entry.notes.trimmed().isEmpty() ||
            !item.value("concepts").isArray())
        {
            error_ = "Invalid or duplicate example entry: " + entry.id;
            return;
        }
        for (const auto& conceptValue : item.value("concepts").toArray())
        {
            const QString conceptName = conceptValue.toString();
            if (conceptName.trimmed().isEmpty())
            {
                error_ = "An example has an empty concept label: " + entry.id;
                return;
            }
            entry.concepts.append(conceptName);
        }
        if (entry.concepts.isEmpty())
        {
            error_ = "An example has no concept labels: " + entry.id;
            return;
        }
        QFile source(":/small/examples/" + entry.sourceName);
        if (!source.open(QIODevice::ReadOnly))
        {
            error_ = "The built-in example source is missing: " + entry.sourceName;
            return;
        }
        QStringDecoder decoder(QStringDecoder::Utf8);
        entry.code = decoder.decode(source.readAll());
        if (decoder.hasError() || entry.code.trimmed().isEmpty())
        {
            error_ = "The example is empty or is not UTF-8: " + entry.sourceName;
            return;
        }
        ids.insert(entry.id);
        pending.append(entry);
    }
    if (pending.isEmpty())
    {
        error_ = "The built-in example catalog is empty.";
        return;
    }

    // Installed extensions own their examples. Discover them from the same
    // self-contained folders used by the build system.
    QDir extensions(QDir(QCoreApplication::applicationDirPath()).filePath("extensions"));
    for (const QString& folder : extensions.entryList(QDir::Dirs | QDir::NoDotAndDotDot, QDir::Name))
    {
        const QString base = extensions.filePath(folder);
        QFile manifestFile(QDir(base).filePath("extension.json"));
        if (!manifestFile.open(QIODevice::ReadOnly)) continue;
        const auto manifestDoc = QJsonDocument::fromJson(manifestFile.readAll());
        if (!manifestDoc.isObject()) continue;
        const auto extensionObject = manifestDoc.object();
        const QString extensionName = extensionObject.value("name").toString(folder);
        const QString examplesName = extensionObject.value("examples").toString("examples");
        const QString examplesDir = QDir(base).filePath(examplesName);
        QFile catalogFile(QDir(examplesDir).filePath("catalog.json"));
        if (!catalogFile.open(QIODevice::ReadOnly)) continue;
        QJsonParseError extensionParse;
        const auto extensionDoc = QJsonDocument::fromJson(catalogFile.readAll(), &extensionParse);
        if (extensionParse.error != QJsonParseError::NoError || !extensionDoc.isObject()) continue;
        const auto extensionCatalog = extensionDoc.object();
        if (extensionCatalog.value("version").toInt() != 1 ||
            !extensionCatalog.value("examples").isArray()) continue;

        for (const auto& value : extensionCatalog.value("examples").toArray())
        {
            const auto item = value.toObject();
            ExampleEntry entry;
            entry.id = item.value("id").toString();
            entry.group = "Extensions / " + extensionName;
            entry.title = item.value("title").toString();
            entry.description = item.value("description").toString();
            entry.notes = item.value("notes").toString();
            entry.sourceName = item.value("source").toString();
            for (const auto& conceptValue : item.value("concepts").toArray())
                entry.concepts.append(conceptValue.toString());
            if (entry.id.isEmpty() || ids.contains(entry.id) || entry.title.isEmpty() ||
                entry.sourceName.isEmpty() || entry.concepts.isEmpty()) continue;
            QFile source(QDir(examplesDir).filePath(entry.sourceName));
            if (!source.open(QIODevice::ReadOnly)) continue;
            QStringDecoder decoder(QStringDecoder::Utf8);
            entry.code = decoder.decode(source.readAll());
            if (decoder.hasError() || entry.code.trimmed().isEmpty()) continue;
            ids.insert(entry.id);
            pending.append(entry);
        }
    }

    entries_ = std::move(pending);
}
