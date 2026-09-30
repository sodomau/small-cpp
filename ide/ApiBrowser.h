#pragma once
#include "ApiReference.h"
#include <QDialog>
#include <QFont>
#include <QPalette>

class QLabel;
class QTreeWidget;
class QTableWidget;
class QPlainTextEdit;
class QCheckBox;

class ApiBrowser final : public QDialog
{
    Q_OBJECT
public:
    explicit ApiBrowser(QWidget* parent = nullptr);
    ~ApiBrowser() override;
    void setAppearance(const QFont& font, const QPalette& palette, bool dark);

private:
    QVector<ApiEntry> entries_;
    QTreeWidget* tree_ = nullptr;
    QLabel* title_ = nullptr;
    QLabel* usage_ = nullptr;
    QLabel* summary_ = nullptr;
    QTableWidget* parameters_ = nullptr;
    QLabel* returns_ = nullptr;
    QPlainTextEdit* example_ = nullptr;
    QLabel* note_ = nullptr;
    QLabel* cpp_ = nullptr;
    QCheckBox* details_ = nullptr;

    void showSelection();
};
