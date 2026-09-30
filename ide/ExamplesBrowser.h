#pragma once

#include <QDialog>
#include <QFont>
#include <QPalette>

class CodeEditor;
class ExampleCatalog;
class Highlighter;
class QLabel;
class QPushButton;
class QTreeWidget;

// Created only when requested. A modeless dialog rather than a permanent panel
// or a project tree. The catalog is owned by MainWindow and outlives this dialog.
class ExamplesBrowser final : public QDialog
{
    Q_OBJECT
public:
    explicit ExamplesBrowser(const ExampleCatalog& catalog, QWidget* parent = nullptr);
    ~ExamplesBrowser() override;
    void setAppearance(const QFont& font, const QPalette& palette, bool dark);
    QString selectedId() const;
    bool selectExample(const QString& id);

signals:
    void exampleRequested(const QString& id);

private:
    const ExampleCatalog& catalog_;
    QTreeWidget* tree_ = nullptr;
    QLabel* title_ = nullptr;
    QLabel* description_ = nullptr;
    QLabel* concepts_ = nullptr;
    QLabel* notes_ = nullptr;
    CodeEditor* preview_ = nullptr;
    Highlighter* highlighter_ = nullptr;
    QPushButton* open_ = nullptr;

    void showSelection();
    void openSelected();
};
