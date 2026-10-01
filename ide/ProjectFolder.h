#pragma once
#include <QStringList>
#include <QJsonObject>

// A folder is the project. The optional JSON file adds exceptions and build options.
class ProjectFolder
{
public:
    QString root, name;
    QStringList excluded, directories, files, sources, headers, resources;
    QStringList includePaths, libraryPaths, libraries, compilerOptions, linkerOptions;
    QJsonObject settings;
    bool load(const QString& folder, QString* error);
    bool scan(QString* error);
    bool excludes(const QString& relative) const;
    bool contains(const QString& path) const;
    bool setExcluded(const QString& relative, bool exclude, QString* error);
    QString absolute(const QString& relative) const;
    static bool isSource(const QString& path);
    static bool isHeader(const QString& path);
    static bool isIgnoredDirectory(const QString& name);
};
