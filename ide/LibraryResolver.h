#pragma once
#include <QObject>
#include <QProcess>
#include <QJsonObject>
#include <functional>

// Uses the environment's own package databases; never records an installed flag.
class LibraryResolver : public QObject
{
    Q_OBJECT
public:
    explicit LibraryResolver(QObject* parent = nullptr);
    ~LibraryResolver() override;
    std::function<QString(const QString&, const QStringList&)> chooseProvider;
    std::function<bool(const QStringList&)> confirmInstall;
    void resolve(const QStringList& modules);
    void cancel();
    bool isRunning() const { return process_.state() != QProcess::NotRunning; }
    static QString pkgConfig();
    static QString pacman();
    static QJsonObject catalog();
    static QString catalogPath();
    static QJsonObject scanCatalog(const QByteArray& listing);
    static QStringList splitFlags(const QString& text);
signals:
    void output(const QString& text);
    void ready(const QStringList& cflags, const QStringList& libs);
    void failed(const QString& message);
    void cancelled();
private:
    QProcess process_;
    QStringList modules_, missing_, packages_;
    QByteArray bytes_;
    int index_ = 0, step_ = 0;
    QStringList cflags_;
    bool cancelled_ = false, bootstrap_ = false;
    void run(const QString& program, const QStringList& args);
    void checkNext();
    void installMissing();
    void installPackages();
    void finished(int code, QProcess::ExitStatus status);
};
