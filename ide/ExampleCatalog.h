#pragma once

#include <QString>
#include <QStringList>
#include <QVector>

// Data for the browser, not a runtime/plugin API. Sources are embedded resources;
// an example never has a writable file path inside the user's project.
struct ExampleEntry
{
    QString id;
    QString group;
    QString title;
    QString description;
    QStringList concepts;
    QString notes;
    QString sourceName;
    QString code;
};

class ExampleCatalog
{
public:
    ExampleCatalog();
    bool isValid() const { return error_.isEmpty(); }
    const QString& errorString() const { return error_; }
    const QVector<ExampleEntry>& entries() const { return entries_; }
    const ExampleEntry* find(const QString& id) const;

private:
    QVector<ExampleEntry> entries_;
    QString error_;
    void load();
};
