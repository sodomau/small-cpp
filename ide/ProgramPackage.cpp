#include "ProgramPackage.h"
#include <QDir>
#include <QDirIterator>
#include <QFileInfo>
#include <QSet>
#include <QRegularExpression>

QString ProgramPackage::executableName(const QString& sourceName)
{
    QString base = QFileInfo(sourceName).completeBaseName();
    base.replace(QRegularExpression("[^A-Za-z0-9_-]+"), "_");
    base.remove(QRegularExpression("^_+|_+$"));
    if (base.isEmpty()) base = "Program";
    base = base.left(80);
    if (QRegularExpression("^(CON|PRN|AUX|NUL|COM[1-9]|LPT[1-9])$",
                           QRegularExpression::CaseInsensitiveOption).match(base).hasMatch())
        base.prepend("Program-");
    return base + ".exe";
}

bool ProgramPackage::plan(const QString& installation, const QStringList& resources,
                          const QVector<SmallExtension>& extensions,
                          QVector<PackageFile>* files, QString* error, const QString& executable, const QString& resourceRoot)
{
    files->clear();
    error->clear();
    const QDir root(installation);
    QSet<QString> names{executable.toLower(), "readme.txt", "source", "relink", ".smallcpp-package"};
    auto add = [&](const QString& source, const QString& relative) {
        const QFileInfo info(source);
        if (!info.isFile() || info.isSymLink() || names.contains(relative.toLower())) {
            *error = "Missing, unsupported or conflicting package file: " + source;
            return false;
        }
        names.insert(relative.toLower());
        files->append({source, relative});
        return true;
    };
    auto tree = [&](const QString& source, const QString& destination) {
        QDirIterator it(source, QDir::Files | QDir::Hidden | QDir::NoDotAndDotDot,
                        QDirIterator::Subdirectories);
        while (it.hasNext()) {
            const QString path = it.next();
            if (!add(path, destination + "/" + QDir(source).relativeFilePath(path))) return false;
        }
        return true;
    };
    for (const QString& required : {QString("Qt6Core.dll"), QString("Qt6Gui.dll"),
                                   QString("Qt6Widgets.dll"), QString("Qt6Multimedia.dll"),
                                   QString("platforms/qwindows.dll"), QString("LICENSE"),
                                   QString("licenses/SOURCE_ACCESS.md"), QString("libwinpthread-1.dll"),
                                   QString("libgcc_s_seh-1.dll"), QString("libstdc++-6.dll"),
                                   QString("qt/lib/libQt6Core.a"), QString("qt/lib/libQt6Gui.a"),
                                   QString("qt/lib/libQt6Widgets.a"), QString("qt/lib/libQt6Multimedia.a")}) {
        if (!QFileInfo::exists(root.filePath(required))) {
            *error = "Publish needs a prepared Windows portable installation. Missing: " + required;
            return false;
        }
    }
    for (const auto& info : root.entryInfoList({"*.dll"}, QDir::Files))
        if (!add(info.absoluteFilePath(), info.fileName())) return false;
    for (const QString folder : {"platforms", "imageformats", "multimedia", "styles",
                                  "generic", "iconengines", "networkinformation", "tls", "licenses"}) {
        if (!tree(root.filePath(folder), folder)) return false;
        names.insert(folder.toLower());
    }
    if (!add(root.filePath("LICENSE"), "LICENSE")) return false;
    // Preserve the matching libraries for relinking; no compiler or IDE is shipped.
    if (!tree(root.filePath("runtime"), "relink/runtime") ||
        !tree(root.filePath("qt/lib"), "relink/qt/lib")) return false;
    for (const auto& extension : extensions) {
        if (!QRegularExpression("^[A-Za-z0-9_-]+$").match(extension.id).hasMatch() ||
            !QRegularExpression("^[A-Za-z0-9_.+-]+$").match(QFileInfo(extension.libraryPath).fileName()).hasMatch()) {
            *error = "Unsupported extension package name: " + extension.id;
            return false;
        }
        if (!add(extension.libraryPath, "relink/extensions/" + extension.id + "/" +
                 QFileInfo(extension.libraryPath).fileName())) return false;
        if (!tree(extension.includeDirectory, "relink/extensions/" + extension.id + "/include")) return false;
    }
    for (const QString& resource : resources) {
        const QString name = resourceRoot.isEmpty() ? QFileInfo(resource).fileName()
            : QDir(resourceRoot).relativeFilePath(QFileInfo(resource).absoluteFilePath());
        if (QDir::isAbsolutePath(name) || name.startsWith("../") || names.contains(name.section('/', 0, 0).toLower())) {
            *error = "Unsupported or conflicting resource path: " + name; return false;
        }
        if (!add(resource, name)) return false;
    }
    return true;
}
