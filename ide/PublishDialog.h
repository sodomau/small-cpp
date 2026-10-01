#pragma once
#include <QDialog>
#include <QStringList>

class QLineEdit;
class QTreeWidget;

class PublishDialog : public QDialog
{
public:
    PublishDialog(const QString& initialFolder, const QString& programName,
                  QWidget* parent = nullptr);
    QString destination() const;
    QStringList resources() const;
    void addFiles(const QStringList& paths);
    void setProjectRoot(const QString& root);
private:
    QLineEdit* destination_;
    QTreeWidget* files_;
    QString projectRoot_;
};

void ShowPublishComplete(const QString& folder, const QString& executable, QWidget* parent);
