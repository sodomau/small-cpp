#pragma once
#include <QString>

struct SmallRuntimeDiagnostic
{
    QString text;
    int line = 0;
};

SmallRuntimeDiagnostic ExplainRuntimeError(const QString& raw, const QString& source);
