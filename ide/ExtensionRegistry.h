#pragma once
#include <QString>
#include <QVector>

struct SmallExtension
{
    QString id;
    QString name;
    QString header;
    QString includeDirectory;
    QString libraryPath;
    QString tutorialDirectory;
    QString examplesDirectory;
};

class ExtensionRegistry
{
public:
    static QVector<SmallExtension> discover(const QString& extensionsRoot);
    static QVector<SmallExtension> detect(const QString& source,
                                          const QVector<SmallExtension>& installed);
};
