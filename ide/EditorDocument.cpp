#include "EditorDocument.h"
#include "Highlighter.h"

#include <QFileInfo>
#include <QTextDocument>

EditorDocument::EditorDocument(const QString& text, const QString& path,
                               const QString& untitledName, QWidget* parent)
    : CodeEditor(parent), filePath_(path), untitledName_(untitledName)
{
    setObjectName("codeEditor");
    highlighter_ = new Highlighter(document());
    setPlainText(text);
    document()->setModified(false);
}

QString EditorDocument::displayName() const
{
    if (isExample()) return exampleTitle_ + " [Example]";
    return filePath_.isEmpty() ? untitledName_ : QFileInfo(filePath_).fileName();
}

void EditorDocument::markAsExample(const QString& id, const QString& title,
                                   const QString& sourceName)
{
    exampleId_ = id;
    exampleTitle_ = title;
    exampleSourceName_ = QFileInfo(sourceName).fileName();
    filePath_.clear(); // Never offer the embedded source as a Save destination.
    setReadOnly(true);
    setAcceptDrops(false);
    setUndoRedoEnabled(false);
    document()->setModified(false);
}
