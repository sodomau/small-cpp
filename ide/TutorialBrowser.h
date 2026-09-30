#pragma once

#include <QDialog>
#include <QFont>
#include <QPalette>
#include <QSet>
#include <QString>
#include <QVector>

class CodeEditor;
class Highlighter;
class QLabel;
class QPushButton;
class QScrollArea;
class QTreeWidget;
class QVBoxLayout;
class TutorialCatalog;
struct TutorialLesson;

// A modeless textbook window. Try emits complete source; MainWindow owns the
// editable copy. There is deliberately no editor/project state in the lesson.
class TutorialBrowser final : public QDialog
{
    Q_OBJECT
public:
    explicit TutorialBrowser(const TutorialCatalog& catalog, QWidget* parent = nullptr);
    ~TutorialBrowser() override;
    void setAppearance(const QFont& codeFont, const QPalette& palette, bool dark);
    QString selectedId() const;
    bool selectLesson(const QString& id);
    bool isRead(const QString& id) const { return readLessons_.contains(id); }

signals:
    void tryRequested(const QString& code, const QString& description);
    void exampleRequested(const QString& id);

private:
    const TutorialCatalog& catalog_;
    QTreeWidget* tree_ = nullptr;
    QScrollArea* scroll_ = nullptr;
    QPushButton* previous_ = nullptr;
    QPushButton* next_ = nullptr;
    QLabel* progress_ = nullptr;
    QFont codeFont_;
    QPalette codePalette_;
    bool dark_ = false;
    QSet<QString> readLessons_;
    struct Preview { CodeEditor* editor; Highlighter* highlighter; };
    QVector<Preview> previews_; // Owned by the current page/document.

    void showSelection();
    void showLesson(const TutorialLesson& lesson, QWidget* page, QVBoxLayout* layout);
    void showExercises(const TutorialLesson& lesson, QWidget* page, QVBoxLayout* layout);
    QLabel* prose(const QString& markdown, const QString& baseDirectory, QWidget* parent);
    CodeEditor* codePreview(const QString& code, const QString& name, QWidget* parent);
    void stylePreview(CodeEditor* editor);
    void updateReadLabels();
    void updateNavigation();
    void previousLesson();
    void nextLesson();
};
