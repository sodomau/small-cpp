#include "CodeEditor.h"
#include <QEvent>
#include <QKeyEvent>
#include <QPainter>
#include <QTextBlock>
#include <QTextDocument>
#include <QMouseEvent>

class LineArea : public QWidget
{
public:
    explicit LineArea(CodeEditor* editor) : QWidget(editor), editor_(editor) {}
    QSize sizeHint() const override { return QSize(editor_->lineAreaWidth(), 0); }
protected:
    void paintEvent(QPaintEvent* event) override { editor_->paintLineArea(event); }
    void mousePressEvent(QMouseEvent* event) override {
        if (!editor_->debugGutterEnabled_) return;
        QTextBlock block = editor_->firstVisibleBlock();
        int top = qRound(editor_->blockBoundingGeometry(block).translated(editor_->contentOffset()).top());
        while (block.isValid()) { int h=qRound(editor_->blockBoundingRect(block).height()); if(event->position().y()>=top && event->position().y()<top+h){ int line=block.blockNumber()+1; auto& b=editor_->breakpoints_; if(b.contains(line))b.remove(line);else b.insert(line); editor_->area_->update(); emit editor_->breakpointsChanged(); return;} top+=h;block=block.next(); }
    }
private:
    CodeEditor* editor_;
};

CodeEditor::CodeEditor(QWidget* parent) : QPlainTextEdit(parent), area_(new LineArea(this))
{
    QFont font("Consolas");
    font.setStyleHint(QFont::Monospace);
    font.setPointSize(14);
    setFont(font);
    setLineWrapMode(QPlainTextEdit::NoWrap);
    setTabStopDistance(fontMetrics().horizontalAdvance(' ') * 4);
    connect(this, &QPlainTextEdit::blockCountChanged, this, &CodeEditor::updateMargin);
    connect(this, &QPlainTextEdit::updateRequest, this, [this](const QRect& rect, int dy) {
        if (dy) area_->scroll(0, dy);
        else area_->update(0, rect.y(), area_->width(), rect.height());
        if (rect.contains(viewport()->rect())) updateMargin();
    });
    connect(this, &QPlainTextEdit::cursorPositionChanged, this, &CodeEditor::updateMarks);
    updateMargin();
}
int CodeEditor::lineAreaWidth() const
{
    const int digits = QString::number(qMax(1, blockCount())).size();
    const int numberWidth = fontMetrics().horizontalAdvance('9') * digits;
    return debugGutterEnabled_ ? 36 + numberWidth : 12 + numberWidth;
}
void CodeEditor::setDebugGutterEnabled(bool enabled)
{
    if (debugGutterEnabled_ == enabled) return;
    debugGutterEnabled_ = enabled;
    if (!enabled) { breakpoints_.clear(); debugLine_ = -1; }
    updateMargin();
    area_->update();
}
void CodeEditor::setDarkTheme(bool dark)
{
    darkTheme_ = dark;
    updateMarks();
    area_->update();
}

void CodeEditor::updateMargin()
{
    setViewportMargins(lineAreaWidth(), 0, 0, 0);
    const QRect rect = contentsRect();
    area_->setGeometry(rect.left(), rect.top(), lineAreaWidth(), rect.height());
}
void CodeEditor::resizeEvent(QResizeEvent* event)
{
    QPlainTextEdit::resizeEvent(event);
    updateMargin();
}
void CodeEditor::changeEvent(QEvent* event)
{
    QPlainTextEdit::changeEvent(event);
    if (event->type() == QEvent::FontChange || event->type() == QEvent::PaletteChange)
    {
        updateMargin();
        setTabStopDistance(fontMetrics().horizontalAdvance(' ') * 4);
        updateMarks();
        area_->update();
    }
}

void CodeEditor::paintLineArea(QPaintEvent* event)
{
    QPainter painter(area_);
    painter.fillRect(event->rect(), palette().window());
    QTextBlock block = firstVisibleBlock();
    int top = qRound(blockBoundingGeometry(block).translated(contentOffset()).top());
    while (block.isValid() && top <= event->rect().bottom())
    {
        const int height = qRound(blockBoundingRect(block).height());
        if (block.isVisible() && top + height >= event->rect().top())
        {
            const int line = block.blockNumber() + 1;
            const int currentLine = textCursor().blockNumber() + 1;
            QColor numberColor;
            if (line == errorLine_)
                numberColor = darkTheme_ ? QColor("#ff7777") : QColor("#b00020");
            else if (line == currentLine)
                numberColor = darkTheme_ ? QColor("#f0f0f0") : QColor("#303030");
            else
                numberColor = darkTheme_ ? QColor("#a9adb5") : QColor("#686868");
            if (debugGutterEnabled_ && breakpoints_.contains(line)) { painter.setBrush(QColor("#d94b4b")); painter.setPen(Qt::NoPen); painter.drawEllipse(QPoint(10, top + height/2), 5, 5); }
            if (debugGutterEnabled_ && line == debugLine_) { painter.setBrush(QColor("#e6a23c")); painter.setPen(Qt::NoPen); QPolygon tri; tri << QPoint(18,top+3) << QPoint(26,top+height/2) << QPoint(18,top+height-3); painter.drawPolygon(tri); }
            painter.setPen(numberColor);
            const int numberLeft = debugGutterEnabled_ ? 28 : 4;
            painter.drawText(numberLeft, top, qMax(1, area_->width() - numberLeft - 6),
                             fontMetrics().height(), Qt::AlignRight, QString::number(line));
        }
        top += height;
        block = block.next();
    }
}

void CodeEditor::indentSelection(bool remove)
{
    QTextCursor cursor = textCursor();
    int start = document()->findBlock(cursor.selectionStart()).blockNumber();
    int end = document()->findBlock(cursor.selectionEnd()).blockNumber();
    if (cursor.hasSelection() && cursor.selectionEnd() == document()->findBlock(cursor.selectionEnd()).position())
        --end;
    cursor.beginEditBlock();
    for (int line = start; line <= end; ++line)
    {
        QTextBlock block = document()->findBlockByNumber(line);
        QTextCursor edit(block);
        if (!remove) edit.insertText("    ");
        else
        {
            int count = 0;
            const QString text = block.text();
            if (text.startsWith('\t')) count = 1;
            else while (count < 4 && count < text.size() && text[count] == ' ') ++count;
            edit.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor, count);
            edit.removeSelectedText();
        }
    }
    cursor.endEditBlock();
}
void CodeEditor::keyPressEvent(QKeyEvent* event)
{
    if (isReadOnly() || (event->modifiers() & (Qt::ControlModifier | Qt::AltModifier | Qt::MetaModifier)))
    {
        QPlainTextEdit::keyPressEvent(event);
        return;
    }
    if (event->key() == Qt::Key_Tab || event->key() == Qt::Key_Backtab)
    {
        if (textCursor().hasSelection() || event->key() == Qt::Key_Backtab)
            indentSelection(event->key() == Qt::Key_Backtab);
        else
        {
            const int column = textCursor().positionInBlock();
            insertPlainText(QString(4 - column % 4, ' '));
        }
        return;
    }
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)
    {
        QTextCursor cursor = textCursor();
        const QString before = cursor.block().text().left(cursor.positionInBlock());
        QString indent;
        for (QChar c : before)
        {
            if (c != ' ' && c != '\t') break;
            indent += c;
        }
        if (before.trimmed().endsWith('{')) indent += "    ";
        cursor.beginEditBlock();
        cursor.insertText("\n" + indent);
        cursor.endEditBlock();
        setTextCursor(cursor);
        return;
    }
    if (event->text() == "}" && !textCursor().hasSelection())
    {
        QTextCursor cursor = textCursor();
        const QString before = cursor.block().text().left(cursor.positionInBlock());
        if (before.trimmed().isEmpty() && before.endsWith("    "))
        {
            cursor.beginEditBlock();
            cursor.movePosition(QTextCursor::PreviousCharacter, QTextCursor::KeepAnchor, 4);
            cursor.insertText("}");
            cursor.endEditBlock();
            setTextCursor(cursor);
            return;
        }
    }
    QPlainTextEdit::keyPressEvent(event);
}
void CodeEditor::markErrorLine(int line) { errorLine_ = line; updateMarks(); area_->update(); }
void CodeEditor::clearError() { if (errorLine_ != -1) { errorLine_ = -1; updateMarks(); area_->update(); } }
void CodeEditor::updateMarks()
{
    QList<QTextEdit::ExtraSelection> selections;
    QTextEdit::ExtraSelection current;
    current.cursor = textCursor();
    current.cursor.clearSelection();
    current.format.setProperty(QTextFormat::FullWidthSelection, true);
    current.format.setBackground(palette().alternateBase());
    selections.append(current);
    if (errorLine_ > 0)
    {
        QTextBlock block = document()->findBlockByNumber(errorLine_ - 1);
        if (block.isValid())
        {
            QTextEdit::ExtraSelection error;
            error.cursor = QTextCursor(block);
            error.format.setProperty(QTextFormat::FullWidthSelection, true);
            error.format.setBackground(darkTheme_ ? QColor("#522b34") : QColor("#ffe1e1"));
            error.format.setForeground(darkTheme_ ? QColor("#ffd9df") : QColor("#781414"));
            selections.append(error);
        }
    }
    setExtraSelections(selections);
    area_->update();
}

void CodeEditor::setDebugLine(int line) { debugLine_=line; updateMarks(); area_->update(); }
void CodeEditor::clearDebugLine() { if(debugLine_!=-1){debugLine_=-1;updateMarks();area_->update();} }
