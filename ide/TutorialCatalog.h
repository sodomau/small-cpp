#pragma once

#include <QString>
#include <QStringList>
#include <QVector>
#include <QPair>

struct TutorialBlock
{
    enum class Kind { Text, Code };
    Kind kind = Kind::Text;
    QString title;
    QString content; // Markdown prose or complete, runnable C++ source.
    QString sourceName;
};

struct TutorialExercise
{
    QString title;
    QString prompt;
    QString hint;
    QString starter;
    QString solution;
};

struct TutorialLesson
{
    QString id;
    int number = 0;
    QString partId;
    QString title;
    QString goal;
    bool available = false; // Unwritten is different from locked.
    QVector<TutorialBlock> blocks;
    QVector<TutorialExercise> exercises;
    QString relatedExample;
    QString sourceDirectory; // Absolute lesson directory; base for Markdown images.
};

struct TutorialPart
{
    QString id;
    QString title;
    QStringList lessonIds;
};

// A filesystem-backed content catalog. Lessons are Markdown + C++ bundles
// loaded from tutorial/ beside the IDE, so content can be added after build.
// Invalid content produces a readable error, never partial data.
class TutorialCatalog
{
public:
    TutorialCatalog(const QString& language = QString());
    static QString defaultLanguage();
    static QVector<QPair<QString, QString>> languages();
    bool isValid() const { return error_.isEmpty(); }
    const QString& errorString() const { return error_; }
    const QVector<TutorialPart>& parts() const { return parts_; }
    const QVector<TutorialLesson>& lessons() const { return lessons_; }
    const TutorialLesson* find(const QString& id) const;
    QStringList availableIds() const;

private:
    QVector<TutorialPart> parts_;
    QVector<TutorialLesson> lessons_;
    QString error_;
    QString language_;
    void load();
};
