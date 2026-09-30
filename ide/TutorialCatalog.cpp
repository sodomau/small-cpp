#include "TutorialCatalog.h"

#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QJsonDocument>
#include <QJsonObject>
#include <QRegularExpression>
#include <QSet>
#include <QStringDecoder>
#include <algorithm>
#include <stdexcept>
#include <utility>

namespace
{
void Require(bool condition, const QString& message)
{
    if (!condition) throw std::runtime_error(message.toStdString());
}

QString ReadText(const QString& path)
{
    QFile file(path);
    Require(file.open(QIODevice::ReadOnly), "Missing tutorial content: " + path);
    QStringDecoder decoder(QStringDecoder::Utf8);
    const QString text = decoder.decode(file.readAll());
    Require(!decoder.hasError() && !text.trimmed().isEmpty(),
            "Empty or invalid UTF-8 tutorial content: " + path);
    return text;
}

QString Value(const QMap<QString,QString>& meta, const QString& key)
{
    const QString value = meta.value(key).trimmed();
    Require(!value.isEmpty(), "Missing tutorial field: " + key);
    return value;
}

struct ParsedMarkdown
{
    QMap<QString,QString> meta;
    QString body;
};

ParsedMarkdown ParseFrontMatter(const QString& text, const QString& path)
{
    const QString normalized = QString(text).replace("\r\n","\n");
    Require(normalized.startsWith("---\n"), "Missing tutorial front matter: " + path);
    const int end = normalized.indexOf("\n---\n", 4);
    Require(end >= 0, "Unterminated tutorial front matter: " + path);

    ParsedMarkdown result;
    const QStringList lines = normalized.mid(4, end-4).split('\n');
    for (const QString& line : lines)
    {
        const int colon = line.indexOf(':');
        Require(colon > 0, "Invalid tutorial metadata: " + path);
        result.meta.insert(line.left(colon).trimmed(), line.mid(colon+1).trimmed());
    }
    result.body = normalized.mid(end+5).trimmed();
    return result;
}

QString ReadLocalCpp(const QString& directory, const QString& name)
{
    static const QRegularExpression valid("^[A-Za-z0-9_-]+\\.cpp$");
    Require(valid.match(name).hasMatch(), "Invalid tutorial C++ filename: " + name);
    return ReadText(QDir(directory).filePath(name));
}

void ParseBody(TutorialLesson& lesson, const QString& directory, const QString& body)
{
    const QStringList lines = body.split('\n');
    QString prose;
    TutorialExercise* currentExercise = nullptr;

    auto flushProse = [&] {
        const QString text = prose.trimmed();
        if (!text.isEmpty())
        {
            TutorialBlock block;
            block.kind = TutorialBlock::Kind::Text;
            block.content = text;
            lesson.blocks.append(block);
        }
        prose.clear();
    };

    for (int i=0; i<lines.size(); ++i)
    {
        const QString trimmed = lines[i].trimmed();
        const QRegularExpression tagRe("^@(code|exercise|solution)\\s+(.+\\.cpp)$");
        const auto tag = tagRe.match(trimmed);
        if (tag.hasMatch())
        {
            flushProse();
            const QString kind = tag.captured(1);
            const QString source = tag.captured(2).trimmed();
            if (kind == "code")
            {
                TutorialBlock block;
                block.kind = TutorialBlock::Kind::Code;
                block.sourceName = source;
                block.content = ReadLocalCpp(directory, source);
                // A preceding Markdown heading already labels the block.
                lesson.blocks.append(block);
                currentExercise = nullptr;
            }
            else if (kind == "exercise")
            {
                TutorialExercise exercise;
                exercise.title = "Exercise";
                // Move the immediately preceding text block into the prompt.
                if (!lesson.blocks.isEmpty() &&
                    lesson.blocks.last().kind == TutorialBlock::Kind::Text)
                {
                    exercise.prompt = lesson.blocks.takeLast().content;
                    const QRegularExpression heading("^##\\s+Exercise\\s*[—-]?\\s*(.*)\\n?");
                    auto hm = heading.match(exercise.prompt);
                    if (hm.hasMatch() && !hm.captured(1).trimmed().isEmpty())
                        exercise.title = hm.captured(1).trimmed();
                }
                exercise.starter = ReadLocalCpp(directory, source);
                lesson.exercises.append(exercise);
                currentExercise = &lesson.exercises.last();
            }
            else
            {
                Require(currentExercise != nullptr, "@solution must follow @exercise: " + directory);
                currentExercise->solution = ReadLocalCpp(directory, source);
            }
            continue;
        }

        // Hint is ordinary Markdown between exercise and solution. Keep it in
        // the exercise model because TutorialBrowser already has a Hint UI.
        if (currentExercise && trimmed == "### Hint")
        {
            QString hint;
            ++i;
            while (i < lines.size() && !lines[i].trimmed().startsWith("@solution"))
            {
                hint += lines[i] + "\n";
                ++i;
            }
            currentExercise->hint = hint.trimmed();
            --i; // let @solution be handled normally
            continue;
        }

        prose += lines[i] + "\n";
    }
    flushProse();

    Require(!lesson.blocks.isEmpty(), "Lesson has no content: " + directory);
    for (const auto& exercise : lesson.exercises)
        Require(!exercise.starter.isEmpty() && !exercise.solution.isEmpty(),
                "Exercise needs @exercise and @solution: " + directory);
}


struct FolderIdentity
{
    int order = 0;
    QString id;
};

FolderIdentity ParseLessonFolder(const QString& folder)
{
    static const QRegularExpression pattern("^(\\d{2})_([a-z][a-z0-9_]*)$");
    const auto match = pattern.match(folder);
    Require(match.hasMatch(), "Tutorial lesson folder must be NN_id: " + folder);
    FolderIdentity result;
    result.order = match.captured(1).toInt();
    result.id = match.captured(2);
    Require(result.order > 0, "Tutorial lesson order must be positive: " + folder);
    return result;
}

QJsonObject LanguageManifest()
{
    QFile file(QDir(QCoreApplication::applicationDirPath()).filePath("tutorial/languages.json"));
    if (!file.open(QIODevice::ReadOnly)) return {};
    const QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    return doc.isObject() ? doc.object() : QJsonObject{};
}

QString ResolveLessonMarkdown(const QString& directory, const QString& language)
{
    QString path = QDir(directory).filePath(language + ".md");
    if (QFile::exists(path)) return path;
    path = QDir(directory).filePath(TutorialCatalog::defaultLanguage() + ".md");
    return QFile::exists(path) ? path : QString();
}

QString TutorialRoot()
{
    return QDir(QCoreApplication::applicationDirPath()).filePath("tutorial");
}
}

TutorialCatalog::TutorialCatalog(const QString& language)
    : language_(language.isEmpty() ? defaultLanguage() : language) { load(); }

QString TutorialCatalog::defaultLanguage()
{
    const QString code = LanguageManifest().value("default").toString();
    return code.isEmpty() ? QStringLiteral("ko") : code;
}

QVector<QPair<QString, QString>> TutorialCatalog::languages()
{
    QVector<QPair<QString, QString>> result;
    const QJsonObject langs = LanguageManifest().value("languages").toObject();
    for (auto it=langs.begin(); it!=langs.end(); ++it)
        result.append({it.key(), it.value().toString(it.key())});
    if (result.isEmpty()) result.append({"ko", QString::fromUtf8("한국어")});
    return result;
}

const TutorialLesson* TutorialCatalog::find(const QString& id) const
{
    for (const auto& lesson : lessons_) if (lesson.id == id) return &lesson;
    return nullptr;
}

QStringList TutorialCatalog::availableIds() const
{
    QStringList ids;
    for (const auto& lesson : lessons_) if (lesson.available) ids.append(lesson.id);
    return ids;
}

void TutorialCatalog::load()
{
    try
    {
        QVector<TutorialLesson> lessons;
        QMap<QString,TutorialPart> partsById;
        QStringList partOrder;
        QSet<QString> ids;

        QDir root(TutorialRoot());
        Require(root.exists(), "Tutorial folder is missing: " + root.path());

        const QStringList folders = root.entryList(QDir::Dirs | QDir::NoDotAndDotDot, QDir::Name);
        for (const QString& folder : folders)
        {
            const QString directory = root.filePath(folder);
            const QString lessonPath = ResolveLessonMarkdown(directory, language_);
            if (lessonPath.isEmpty()) continue;

            const ParsedMarkdown parsed = ParseFrontMatter(ReadText(lessonPath), lessonPath);
            const FolderIdentity identity = ParseLessonFolder(folder);
            TutorialLesson lesson;
            lesson.id = identity.id;
            lesson.title = Value(parsed.meta,"title");
            lesson.partId = Value(parsed.meta,"part");
            lesson.number = identity.order;
            lesson.goal = Value(parsed.meta,"goal");
            lesson.relatedExample = parsed.meta.value("related-example");
            Require(!ids.contains(lesson.id),
                    "Invalid or duplicate tutorial lesson: " + lesson.id);
            ids.insert(lesson.id);
            lesson.sourceDirectory = directory;
            ParseBody(lesson,directory,parsed.body);
            lesson.available = true;

            if (!partsById.contains(lesson.partId))
            {
                TutorialPart part;
                part.id = lesson.partId;
                part.title = Value(parsed.meta,"part-title");
                partsById.insert(part.id,part);
                partOrder.append(part.id);
            }
            partsById[lesson.partId].lessonIds.append(lesson.id);
            lessons.append(lesson);
        }

        std::sort(lessons.begin(),lessons.end(),
                  [](const TutorialLesson&a,const TutorialLesson&b){return a.number<b.number;});
        Require(!lessons.isEmpty(), "No tutorial lessons were found.");

        QVector<TutorialPart> parts;
        for (const QString& id : partOrder) parts.append(partsById.value(id));

        // Extensions keep extension.json as an explicit package manifest.
        // If its tutorial directory exists, NN_id lesson folders are discovered
        // automatically. Extensions themselves have no curriculum ordering;
        // directory-name sorting is only a stable UI presentation choice.
        QDir extensions(QDir(QCoreApplication::applicationDirPath()).filePath("extensions"));
        int displayNumber = lessons.size();
        for (const QString& extensionFolder :
             extensions.entryList(QDir::Dirs | QDir::NoDotAndDotDot, QDir::Name))
        {
            const QString base = extensions.filePath(extensionFolder);
            QFile manifestFile(QDir(base).filePath("extension.json"));
            if (!manifestFile.open(QIODevice::ReadOnly)) continue;
            const QJsonDocument manifestDoc = QJsonDocument::fromJson(manifestFile.readAll());
            if (!manifestDoc.isObject()) continue;
            const QJsonObject manifest = manifestDoc.object();
            const QString extensionId = manifest.value("id").toString(extensionFolder);
            const QString extensionName = manifest.value("name").toString(extensionId);
            const QString tutorialName = manifest.value("tutorial").toString();
            if (tutorialName.isEmpty()) continue;

            QDir tutorialDir(QDir(base).filePath(tutorialName));
            if (!tutorialDir.exists()) continue;

            TutorialPart part;
            part.id = "extension_" + extensionId;
            part.title = "Extension — " + extensionName;

            const QStringList lessonFolders =
                tutorialDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot, QDir::Name);
            QVector<QPair<int,TutorialLesson>> extensionLessons;
            QSet<int> extensionOrders;
            for (const QString& lessonFolder : lessonFolders)
            {
                const QString directory = tutorialDir.filePath(lessonFolder);
                const QString lessonPath = ResolveLessonMarkdown(directory, language_);
                if (lessonPath.isEmpty()) continue;

                const FolderIdentity identity = ParseLessonFolder(lessonFolder);
                Require(!extensionOrders.contains(identity.order),
                        "Duplicate extension tutorial order: " + lessonFolder);
                extensionOrders.insert(identity.order);

                const ParsedMarkdown parsed =
                    ParseFrontMatter(ReadText(lessonPath), lessonPath);
                TutorialLesson lesson;
                lesson.id = "extension_" + extensionId + "_" + identity.id;
                lesson.partId = part.id;
                lesson.title = Value(parsed.meta,"title");
                lesson.goal = Value(parsed.meta,"goal");
                lesson.relatedExample = parsed.meta.value("related-example");
                lesson.sourceDirectory = directory;
                ParseBody(lesson,directory,parsed.body);
                lesson.available = true;
                extensionLessons.append({identity.order,std::move(lesson)});
            }

            std::sort(extensionLessons.begin(),extensionLessons.end(),
                      [](const auto&a,const auto&b){return a.first<b.first;});
            for (auto& ordered : extensionLessons)
            {
                ordered.second.number = ++displayNumber;
                part.lessonIds.append(ordered.second.id);
                lessons.append(std::move(ordered.second));
            }
            if (!part.lessonIds.isEmpty()) parts.append(std::move(part));
        }

        parts_=std::move(parts);
        lessons_=std::move(lessons);
    }
    catch(const std::exception& error)
    {
        error_=QString::fromUtf8(error.what());
        parts_.clear(); lessons_.clear();
    }
}
