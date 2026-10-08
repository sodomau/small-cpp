#include "EditorDocument.h"
#include <KTextEditor/Editor>
#include <KTextEditor/Command>
#include <QVBoxLayout>
#include <QPainter>
#include <QAction>
#include <KActionCollection>
#include <QPlainTextEdit>

#include <QFileInfo>
#include "ApiReference.h"
#include <KTextEditor/CodeCompletionModel>
#include <QRegularExpression>

namespace {
// Vocabulary completion, deliberately independent of Qt's C++ syntax word lists.
// This is not a C++ type analyser: names written in this document are also offered.
class LearnerCompletion final : public KTextEditor::CodeCompletionModel
{
public:
    explicit LearnerCompletion(QObject* parent) : CodeCompletionModel(parent) {}
    void completionInvoked(KTextEditor::View* view, const KTextEditor::Range& range,
                           InvocationType) override
    {
        const QString prefix = view->document()->text(range);
        QSet<QString> words;
        const QString keywords = QStringLiteral(
            "alignas alignof auto bool break case catch char char8_t char16_t char32_t class "
            "const consteval constexpr constinit continue co_await co_return co_yield decltype "
            "default delete do double else enum explicit extern false float for friend if inline "
            "int long mutable namespace new noexcept nullptr operator private protected public "
            "requires return short signed sizeof static static_assert struct switch template this "
            "thread_local throw true try typedef typename union unsigned using virtual void "
            "volatile wchar_t while concept small_main initialize_small shutdown_small");
        for (const auto& word : keywords.split(' ')) words.insert(word);
        static const QRegularExpression identifier(R"([A-Za-z_][A-Za-z0-9_]*)");
        for (const auto& entry : ApiReference::core()) {
            auto names = identifier.globalMatch(entry.name);
            while (names.hasNext()) words.insert(names.next().captured());
        }
        // Ignore comments and quoted text when harvesting the learner's names.
        static const QRegularExpression tokens(
            R"re(//[^\n]*|/\*[\s\S]*?\*/|"(?:\\.|[^"\\])*"|'(?:\\.|[^'\\])*'|([A-Za-z_][A-Za-z0-9_]*))re");
        auto matches = tokens.globalMatch(view->document()->text());
        while (matches.hasNext()) {
            const QString name = matches.next().captured(1);
            if (!name.isEmpty()) words.insert(name);
        }
        beginResetModel();
        candidates_.clear();
        for (const auto& word : words)
            if (word.startsWith(prefix) && word != prefix) candidates_.append(word);
        candidates_.sort();
        setRowCount(candidates_.size());
        endResetModel();
    }
    QVariant data(const QModelIndex& index, int role) const override
    {
        if (role == Qt::DisplayRole && index.column() == Name
            && index.row() >= 0 && index.row() < candidates_.size())
            return candidates_[index.row()];
        return {};
    }
private:
    QStringList candidates_;
};
}

EditorDocument::EditorDocument(const QString& text, const QString& path,
                               const QString& untitledName, QWidget* parent)
    : QWidget(parent), filePath_(path), untitledName_(untitledName)
{
    setObjectName("codeEditor");
    document_ = KTextEditor::Editor::instance()->createDocument(this);
    view_ = document_->createView(this);
    // File identity and saving belong to MainWindow, not the embedded view.
    // Duplicate native bindings otherwise make Qt reject Ctrl+S as ambiguous.
    for (const auto* name : {"file_save", "file_save_as"})
        if (auto* action = view_->actionCollection()->action(name))
            action->setShortcuts({});
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
    // Selecting C++ highlighting installs the built-in keyword/word models.
    // Replace them only after the document mode has been initialized.
    const auto defaults = view_->codeCompletionModels();
    for (auto* model : defaults) view_->unregisterCompletionModel(model);
    view_->registerCompletionModel(new LearnerCompletion(document_));
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
    // The code font belongs to the renderer, not status controls and menus.
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
