#pragma once

#include <QString>
#include <QVector>

struct ApiParameter
{
    QString name;
    QString type;
    QString meaning;
};

struct ApiEntry
{
    QString category;
    QString name;
    QString usage;
    QString summary;
    QVector<ApiParameter> parameters;
    QString returns;
    QString example;
    QString note;
    QString cppPrototype;
};

class ApiReference
{
public:
    static QVector<ApiEntry> core();
    static QVector<ApiEntry> image();
};
