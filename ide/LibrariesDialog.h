#pragma once
#include <QDialog>
#include <QProcess>
#include <QJsonObject>
class QTreeWidget;
class QLineEdit;
class QPushButton;
class QLabel;
class QProgressBar;
class LibrariesDialog : public QDialog
{
public:
    explicit LibrariesDialog(const QStringList& selected, QWidget* parent = nullptr, const QString& catalogDestination = {});
    ~LibrariesDialog() override;
    QStringList libraries() const { return selected_; }
private:
    QStringList selected_, installed_;
    QString catalogDestination_;
    QJsonObject catalog_;
    QTreeWidget* list_;
    QLineEdit* search_;
    QPushButton* update_;
    QLabel* hint_;
    QProgressBar* progress_;
    QProcess process_;
    QByteArray bytes_;
    int step_ = 0;
    void populate();
    void run(const QString& program, const QStringList& args);
};
