#pragma once

#include "CodeEditor.h"

class Highlighter;

// A tab owns its text, undo history and file identity. The tab's position is
// deliberately NOT the document's identity: users may reorder tabs.
class EditorDocument final : public CodeEditor
{
    Q_OBJECT
public:
    EditorDocument(const QString& text, const QString& path,
                   const QString& untitledName, QWidget* parent = nullptr);

    QString displayName() const;
    const QString& filePath() const { return filePath_; }
    void setFilePath(const QString& path) { filePath_ = path; }
    Highlighter* highlighter() const { return highlighter_; }

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
    Highlighter* highlighter_ = nullptr; // Owned by QTextDocument.
};
