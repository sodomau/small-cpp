#include "PeDependencies.h"
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QSet>
#include <QtEndian>
#include <QCryptographicHash>
#include <algorithm>

QStringList PeDependencies::imports(const QString& binary, QString* error)
{
    QFile file(binary);
    if (!file.open(QIODevice::ReadOnly)) { *error = "Cannot inspect DLL imports: " + binary; return {}; }
    const QByteArray bytes = file.readAll();
    auto u16 = [&](qsizetype offset) -> quint16 { return offset >= 0 && offset + 2 <= bytes.size() ? qFromLittleEndian<quint16>(bytes.constData() + offset) : 0; };
    auto u32 = [&](qsizetype offset) -> quint32 { return offset >= 0 && offset + 4 <= bytes.size() ? qFromLittleEndian<quint32>(bytes.constData() + offset) : 0; };
    const qsizetype pe = u32(0x3c), optional = pe + 24;
    if (bytes.size() < 64 || bytes.left(2) != "MZ" || pe + 24 >= bytes.size() || bytes.mid(pe, 4) != QByteArray("PE\0\0", 4)) { *error = "Invalid Windows binary: " + binary; return {}; }
    const bool x64 = u16(optional) == 0x20b;
    if (!x64 && u16(optional) != 0x10b) { *error = "Unsupported Windows binary: " + binary; return {}; }
    const qsizetype sections = optional + u16(pe + 20);
    const int count = u16(pe + 6);
    auto offset = [&](quint32 rva) -> qsizetype {
        if (rva < u32(optional + 60)) return rva < bytes.size() ? rva : -1;
        for (int i = 0; i < count; ++i) {
            const qsizetype section = sections + i * 40;
            if (section + 40 > bytes.size()) break;
            const quint32 address = u32(section + 12), size = u32(section + 16);
            if (rva >= address && quint64(rva) < quint64(address) + size) {
                const quint64 position = quint64(u32(section + 20)) + rva - address;
                if (position < quint64(bytes.size())) return qsizetype(position);
            }
        }
        return -1;
    };
    QStringList result;
    const qsizetype data = optional + (x64 ? 112 : 96);
    const int number = u32(optional + (x64 ? 108 : 92));
    for (const int directory : {1, 13}) {
        if (number <= directory || data + directory * 8 + 8 > sections) continue;
        const quint32 rva = u32(data + directory * 8);
        if (!rva) continue;
        const qsizetype start = offset(rva);
        const int stride = directory == 1 ? 20 : 32;
        if (start < 0) { *error = "Invalid DLL import table: " + binary; return {}; }
        bool ended = false;
        for (int i = 0; i < 4096; ++i) {
            const qsizetype entry = start + i * stride;
            if (entry + stride > bytes.size()) break;
            const quint32 nameRva = u32(entry + (directory == 1 ? 12 : 4));
            if (!nameRva) { ended = true; break; }
            if (directory == 13 && !(u32(entry) & 1)) { *error = "Unsupported delay-load import: " + binary; return {}; }
            const qsizetype name = offset(nameRva);
            const qsizetype end = name < 0 ? -1 : bytes.indexOf('\0', name);
            if (name < 0 || end < name || end - name > 260) break;
            const QString dll = QString::fromLatin1(bytes.mid(name, end - name));
            if (dll.isEmpty() || dll.contains('/') || dll.contains('\\') || dll.contains(':') || dll == "." || dll == "..") break;
            result << dll;
        }
        if (!ended) { *error = "Malformed DLL imports: " + binary; return {}; }
    }
    result.removeDuplicates(); return result;
}
bool PeDependencies::collect(const QString& executable, const QStringList& directories, QVector<PackageFile>* files, QString* error)
{
    QMap<QString, QString> chosen;
    QStringList queue{executable};
    for (const auto& file : *files) if (file.source.endsWith(".dll", Qt::CaseInsensitive)) {
        if (!file.relativePath.contains('/')) chosen.insert(QFileInfo(file.source).fileName().toLower(), file.source);
        queue << file.source;
    }
    QSet<QString> seen;
    auto hash = [](const QString& path) { QFile file(path); if (!file.open(QIODevice::ReadOnly)) return QByteArray(); QCryptographicHash sha(QCryptographicHash::Sha256); sha.addData(&file); return sha.result(); };
    const QDir system(qEnvironmentVariable("SystemRoot", "C:/Windows") + "/System32");
    while (!queue.isEmpty()) {
        const QString binary = queue.takeLast(); if (seen.contains(binary)) continue; seen.insert(binary);
        const auto names = imports(binary, error); if (!error->isEmpty()) return false;
        for (const auto& name : names) {
            const QString key = name.toLower();
            if (key.startsWith("api-ms-") || key.startsWith("ext-ms-")) continue;
            QString found;
            for (const auto& directory : directories) {
                const auto candidate = QDir(directory).filePath(name);
                if (QFileInfo(candidate).isFile()) { found = candidate; break; }
            }
            if (chosen.contains(key)) {
                if (!found.isEmpty() && QFileInfo(found).canonicalFilePath() != QFileInfo(chosen[key]).canonicalFilePath() && hash(found) != hash(chosen[key])) {
                    *error = "Conflicting DLL versions: " + name + ". Use libraries compatible with this Small C++ environment."; return false;
                }
                continue;
            }
            if (found.isEmpty()) {
                if (QFileInfo(system.filePath(name)).isFile()) continue;
                *error = "Missing runtime DLL: " + name + " (required by " + QFileInfo(binary).fileName() + ")"; return false;
            }
            chosen.insert(key, found); files->append({found, name}); queue << found;
        }
    }
    return true;
}
