#pragma once
#include "SmallBuildConfig.h"
#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>
#include <QProcessEnvironment>

namespace Toolchain {
inline QString root() { return QCoreApplication::applicationDirPath(); }
inline QString compiler()
{
#ifdef Q_OS_WIN
    const QString bundled = QDir(root()).filePath("env/ucrt64/bin/g++.exe");
    if (QFileInfo::exists(bundled)) return bundled;
#endif
    return QString::fromUtf8(SmallBuildConfig::Compiler);
}
inline QProcessEnvironment environment()
{
    auto env = QProcessEnvironment::systemEnvironment();
    QStringList paths{QFileInfo(compiler()).absolutePath()};
    const QString msysBin = QDir(root()).filePath("env/usr/bin");
    if (QFileInfo(msysBin).isDir()) paths << msysBin;
    paths << root();
    const QString qtBin = QString::fromUtf8(SmallBuildConfig::QtBin);
    if (!QFileInfo(QDir(root()).filePath("env/ucrt64/bin/g++.exe")).isFile()
        && QFileInfo(qtBin).isDir()) paths << qtBin;
    paths << env.value("PATH");
    env.insert("PATH", paths.join(QDir::listSeparator()));
    env.insert("QT_PLUGIN_PATH", root());
    env.insert("QT_QPA_PLATFORM_PLUGIN_PATH", QDir(root()).filePath("platforms"));
    env.insert("LC_ALL", "C");
    return env;
}
}
