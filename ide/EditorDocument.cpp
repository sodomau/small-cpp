#include "EditorDocument.h"
#include <KTextEditor/Editor>
#include <KTextEditor/Command>
#include <QVBoxLayout>
#include <QPainter>
#include <QAction>
#include <KActionCollection>
#include <QPlainTextEdit>

#include <QFileInfo>

EditorDocument::EditorDocument(const QString& text, const QString& path,
                               const QString& untitledName, QWidget* parent)
    : QWidget(parent), filePath_(path), untitledName_(untitledName)
{
    setObjectName("codeEditor");
    document_ = KTextEditor::Editor::instance()->createDocument(this);
    view_ = document_->createView(this);
    auto* layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(view_);
    setFocusProxy(view_);
    document_->setMode("C++");
    document_->setHighlightingMode("C++");
    document_->setConfigValue("indent-width", 4);
    document_->setConfigValue("tab-width", 4);
    document_->setConfigValue("replace-tabs", true);
    QString message;
    if (auto* command = KTextEditor::Editor::instance()->queryCommand("set-indent-mode"))
        command->exec(view_, "set-indent-mode cstyle", message);
    view_->setConfigValue("line-numbers", true);
    view_->setConfigValue("icon-bar", true);
    view_->setConfigValue("dynamic-word-wrap", false);
    document_->setEditableMarks(KTextEditor::Document::BreakpointActive);
    for (auto type : {KTextEditor::Document::BreakpointActive, KTextEditor::Document::Execution, KTextEditor::Document::Error}) {
        QPixmap image(18, 18); image.fill(Qt::transparent);
        QPainter painter(&image);
        painter.setBrush(type == KTextEditor::Document::Execution ? QColor("#e5ad35") : QColor("#e65050"));
        painter.setPen(Qt::NoPen);
        if (type == KTextEditor::Document::Execution) painter.drawPolygon(QPolygon{{3,3},{15,9},{3,15}});
        else painter.drawEllipse(3, 3, 12, 12);
        document_->setMarkIcon(type, QIcon(image));
    }
    document_->setMarkDescription(KTextEditor::Document::BreakpointActive, "Breakpoint");
    document_->setMarkDescription(KTextEditor::Document::Execution, "Current debug line");
    document_->setMarkDescription(KTextEditor::Document::Error, "Error");
    connect(document_, &KTextEditor::Document::modifiedChanged, this, [this] { emit modificationChanged(document_->isModified()); });
    connect(document_, &KTextEditor::Document::textChanged, this, [this] { emit textChanged(); });
    connect(document_, &KTextEditor::Document::marksChanged, this, [this] { emit breakpointsChanged(); });
    connect(document_, &KTextEditor::Document::markClicked, this,
        [this](KTextEditor::Document*, KTextEditor::Mark mark, bool& handled) {
            if (isReadOnly()) return;
            handled = true;
            if (mark.type & KTextEditor::Document::BreakpointActive)
                document_->removeMark(mark.line, KTextEditor::Document::BreakpointActive);
            else document_->addMark(mark.line, KTextEditor::Document::BreakpointActive);
        });
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
    document()->setModified(false);
}

void EditorDocument::appendPlainText(const QString& text)
{
    document_->insertText(document_->documentEnd(), "\n" + text);
}
void EditorDocument::insertPlainText(const QString& text)
{
    if (isReadOnly()) return;
    if (view_->selection()) {
        document_->replaceText(view_->selectionRange(), text);
        view_->removeSelection();
    } else view_->insertText(text);
}

void EditorDocument::setFont(const QFont& font)
{
    QWidget::setFont(font);
    view_->setConfigValue("font", font);
}

void EditorDocument::undo()
{
    if (auto* action = view_->actionCollection()->action("edit_undo")) action->trigger();
}
void EditorDocument::paste()
{
    if (auto* action = view_->actionCollection()->action("edit_paste")) action->trigger();
}
void EditorDocument::cut()
{
    if (auto* action = view_->actionCollection()->action("edit_cut")) action->trigger();
}

void EditorDocument::setDarkTheme(bool dark)
{
    view_->setConfigValue("theme", dark ? "Breeze Dark" : "Breeze Light");
    // Keep existing QPlainTextEdit QSS color rules usable after the editor swap.
    QPlainTextEdit styleSample(this);
    styleSample.setObjectName("codeEditor");
    styleSample.setPalette(palette());
    styleSample.ensurePolished();
    setPalette(styleSample.palette());
    view_->setConfigValue("background-color", palette().color(QPalette::Base));
    view_->setConfigValue("selection-color", palette().color(QPalette::Highlight));
}

void EditorDocument::clearMark(uint type)
{
    const auto marks = document_->marks();
    for (auto it = marks.begin(); it != marks.end(); ++it)
        if (it.value()->type & type) document_->removeMark(it.key(), type);
}

void EditorDocument::markErrorLine(int line)
{
    clearError();
    if (line < 1 || line > document_->lines()) return;
    document_->addMark(line - 1, KTextEditor::Document::Error);
    view_->setCursorPosition({line - 1, 0});
}
void EditorDocument::clearError() { clearMark(KTextEditor::Document::Error); }
void EditorDocument::setDebugLine(int line)
{
    clearDebugLine();
    if (line < 1 || line > document_->lines()) return;
    document_->addMark(line - 1, KTextEditor::Document::Execution);
    view_->setCursorPosition({line - 1, 0});
}
void EditorDocument::clearDebugLine() { clearMark(KTextEditor::Document::Execution); }
QSet<int> EditorDocument::breakpoints() const
{
    QSet<int> result;
    const auto marks = document_->marks();
    for (auto it = marks.begin(); it != marks.end(); ++it)
        if (it.value()->type & KTextEditor::Document::BreakpointActive) result.insert(it.key() + 1);
    return result;
}
