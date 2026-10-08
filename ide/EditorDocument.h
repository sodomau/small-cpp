#pragma once

#include <QWidget>
#include <QSet>
#include <KTextEditor/Document>
#include <KTextEditor/View>

// A tab owns its text, undo history and file identity. The tab's position is
// deliberately NOT the document's identity: users may reorder tabs.
class EditorDocument final : public QWidget
{
    Q_OBJECT
public:
    EditorDocument(const QString& text, const QString& path,
                   const QString& untitledName, QWidget* parent = nullptr);

    QString displayName() const;
    const QString& filePath() const { return filePath_; }
    void setFilePath(const QString& path) { filePath_ = path; }
    KTextEditor::Document* document() const { return document_; }
    KTextEditor::View* editorView() const { return view_; }
    QString toPlainText() const { return document_->text(); }
    void setPlainText(const QString& text) { document_->setText(text); }
    void appendPlainText(const QString& text);
    void insertPlainText(const QString& text);
    void selectAll() { view_->setSelection(document_->documentRange()); }
    void undo();
    void paste();
    void cut();
    void setReadOnly(bool readOnly) { document_->setReadWrite(!readOnly); }
    bool isReadOnly() const { return !document_->isReadWrite(); }
    void setDarkTheme(bool dark);
    void setFont(const QFont& font);
    void markErrorLine(int line);
    void clearError();
    void setDebugLine(int line);
    void clearDebugLine();
    QSet<int> breakpoints() const;
signals:
    void modificationChanged(bool modified);
    void textChanged();
    void breakpointsChanged();
public:
    bool isExample() const { return !exampleId_.isEmpty(); }
    const QString& exampleId() const { return exampleId_; }
    const QString& exampleTitle() const { return exampleTitle_; }
    const QString& exampleSourceName() const { return exampleSourceName_; }
    void markAsExample(const QString& id, const QString& title,
                       const QString& sourceName);
private:
    QString filePath_;
    QString untitledName_;
    QString exampleId_;
    QString exampleTitle_;
    QString exampleSourceName_;
    KTextEditor::Document* document_ = nullptr;
    KTextEditor::View* view_ = nullptr;
    void clearMark(uint type);
};
