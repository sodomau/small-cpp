#pragma once
#include <QSettings>

// Honor the configured backend. Normal runs use NativeFormat; tests select
// IniFormat and an isolated temporary directory without touching user settings.
inline QSettings SmallSettings()
{
    return QSettings(QSettings::defaultFormat(), QSettings::UserScope,
                     QStringLiteral("SmallCpp"), QStringLiteral("SmallCppIDE"));
}
