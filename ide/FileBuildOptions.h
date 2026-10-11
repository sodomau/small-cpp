#pragma once
#include <QJsonObject>
#include <QStringList>

struct FileBuildOptions
{
    QJsonObject settings;
    QStringList libraries, includePaths, libraryPaths, compilerOptions, linkerOptions;
    int lines = 0;
    static bool parse(const QString& source, const QString& directory, FileBuildOptions* result, QString* error);
    static QString withLibraries(const QString& source, const FileBuildOptions& options, const QStringList& libraries);
};
