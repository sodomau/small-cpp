#pragma once
#include "ProgramPackage.h"
namespace PeDependencies {
bool collect(const QString& executable, const QStringList& directories, QVector<PackageFile>* files, QString* error);
QStringList imports(const QString& binary, QString* error);
}
