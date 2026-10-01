#pragma once

#include <QStringList>
#include <QVector>
#include "ExtensionRegistry.h"

struct PackageFile { QString source, relativePath; };

// Plans an export from a prepared portable installation, never the user's
// entire source directory. The caller copies into a temporary sibling folder.
class ProgramPackage
{
public:
    static bool plan(const QString& installation, const QStringList& resources,
                     const QVector<SmallExtension>& extensions,
                     QVector<PackageFile>* files, QString* error);
};
