#pragma once
#include <QString>

struct SmallDiagnostic
{
    QString text;
    int line = 0;
    int column = 0;
};

SmallDiagnostic ExplainDiagnostic(const QString& raw, const QString& source,
                                 const QString& sourceFile);
