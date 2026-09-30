#include "TutorialBrowser.h"
#include "TutorialCatalog.h"
#include "CodeEditor.h"
#include "Highlighter.h"

#include <QGuiApplication>
#include <QDir>
#include <QFrame>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QScreen>
#include <QScrollArea>
#include <QScrollBar>
#include <QSettings>
#include "SmallSettings.h"
#include <QSizePolicy>
#include <QSplitter>
#include <QTextDocument>
#include <QUrl>
#include <QTreeWidget>
#include <QTreeWidgetItemIterator>
#include <QVBoxLayout>
#include <algorithm>

namespace
{
const char* ReadKey = "tutorial/curriculumV2/readLessons";
const char* LastKey = "tutorial/curriculumV2/lastLesson";

QPushButton* Button(const QString& text, const QString& name, QWidget* parent)
{
    auto* button = new QPushButton(text, parent);
    button->setObjectName(name);
    button->setAutoDefault(false);
    button->setMinimumHeight(34);
    button->setStyleSheet("QPushButton { font-size: 10.5pt; padding: 4px 10px; }");
    return button;
}
}

TutorialBrowser::TutorialBrowser(const TutorialCatalog& catalog, QWidget* parent)
    : QDialog(parent), catalog_(catalog), codeFont_("Consolas", 14)
{
    setObjectName("tutorialBrowser");
    setWindowTitle("Tutorial — Small C++");
    setModal(false);
    setWindowFlags(Qt::Window |
                   Qt::WindowMinimizeButtonHint |
                   Qt::WindowMaximizeButtonHint |
                   Qt::WindowCloseButtonHint);

    setSizeGripEnabled(true);
    setMinimumSize(680, 460);
    const QByteArray savedGeometry =
        SmallSettings().value("tutorial/windowGeometry").toByteArray();
    if (!savedGeometry.isEmpty())
        restoreGeometry(savedGeometry);
    codeFont_.setStyleHint(QFont::Monospace);
    codePalette_ = palette();
    QFont uiFont = font();
    uiFont.setPointSize(qMax(11, uiFont.pointSize()));
    setFont(uiFont);
    setStyleSheet(
        "QTreeWidget { font-size: 11pt; }"
        "QTreeWidget::item { min-height: 30px; padding: 2px 4px; }"
        "QGroupBox { font-size: 11pt; font-weight: bold; margin-top: 8px; }"
        "QGroupBox::title { subcontrol-origin: margin; left: 8px; padding: 0 4px; }"
        "QPushButton#tutorialPrevious, QPushButton#tutorialNext { min-width: 105px; }"
        "QPushButton[primaryAction=\"true\"] { font-size: 11pt; font-weight: bold; min-height: 38px; padding: 5px 16px; }"
    );

    auto* layout = new QVBoxLayout(this);
    layout->setContentsMargins(16, 16, 16, 12);
    layout->setSpacing(12);
    auto* introduction = new QLabel(QString("%1 lessons are available. Start with any lesson you like.")
        .arg(catalog_.availableIds().size()), this);
    introduction->setObjectName("tutorialIntro");
    introduction->setWordWrap(true);
    layout->addWidget(introduction);

    auto* splitter = new QSplitter(Qt::Horizontal, this);
    splitter->setObjectName("tutorialSplitter");
    splitter->setChildrenCollapsible(false);
    tree_ = new QTreeWidget;
    tree_->setObjectName("tutorialList");
    tree_->setHeaderHidden(true);
    tree_->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tree_->setSelectionMode(QAbstractItemView::SingleSelection);
    tree_->setUniformRowHeights(true);
    tree_->setIndentation(14);
    tree_->setMinimumWidth(180);
    tree_->setAccessibleName("Tutorial curriculum and lesson titles");
    scroll_ = new QScrollArea;
    scroll_->setObjectName("tutorialScroll");
    scroll_->setWidgetResizable(true);
    scroll_->setFrameShape(QFrame::NoFrame);
    splitter->addWidget(tree_);
    splitter->addWidget(scroll_);
    splitter->setStretchFactor(0, 0);
    splitter->setStretchFactor(1, 1);
    splitter->setSizes({260, 750});
    layout->addWidget(splitter, 1);

    auto* footer = new QHBoxLayout;
    previous_ = Button("← Previous", "tutorialPrevious", this);
    next_ = Button("Next →", "tutorialNext", this);
    auto* closeButton = Button("Close", "tutorialClose", this);
    progress_ = new QLabel;
    progress_->setObjectName("tutorialProgress");
    progress_->setWordWrap(true);
    footer->addWidget(previous_);
    footer->addWidget(progress_, 1);
    footer->addWidget(next_);
    footer->addWidget(closeButton);
    layout->addLayout(footer);
    connect(previous_, &QPushButton::clicked, this, &TutorialBrowser::previousLesson);
    connect(next_, &QPushButton::clicked, this, &TutorialBrowser::nextLesson);
    connect(closeButton, &QPushButton::clicked, this, &QDialog::reject);

    const QStringList stored = SmallSettings().value(ReadKey).toStringList();
    for (const QString& id : stored)
        if (const auto* lesson = catalog_.find(id); lesson && lesson->available)
            readLessons_.insert(id);

    for (const auto& part : catalog_.parts())
    {
        auto* category = new QTreeWidgetItem(tree_, QStringList{part.title});
        category->setToolTip(0, part.title);
        QFont bold = tree_->font();
        bold.setBold(true);
        category->setFont(0, bold);
        for (const QString& id : part.lessonIds)
        {
            auto* item = new QTreeWidgetItem(category);
            item->setData(0, Qt::UserRole, id);
            const auto* lesson = catalog_.find(id);
            item->setToolTip(0, lesson && lesson->available ? lesson->title
                : "Not available yet. It is not locked because of previous lessons.");
        }
        category->setExpanded(part.id == "basics");
    }
    connect(tree_, &QTreeWidget::currentItemChanged, this,
            [this](QTreeWidgetItem*, QTreeWidgetItem*) { showSelection(); });
    updateReadLabels();
    const QString last = SmallSettings().value(LastKey).toString();
    if (!selectLesson(last))
    {
        const QStringList available = catalog_.availableIds();
        if (!available.isEmpty()) selectLesson(available.first());
        else showSelection();
    }
    const QScreen* screen = parent ? parent->screen() : QGuiApplication::primaryScreen();
    const QSize space = screen ? screen->availableGeometry().size() : QSize(1200, 850);
    resize(qMin(1120, qMax(680, space.width() - 80)),
           qMin(820, qMax(460, space.height() - 80)));
}

TutorialBrowser::~TutorialBrowser()
{
    SmallSettings().setValue("tutorial/windowGeometry", saveGeometry());
}


QString TutorialBrowser::selectedId() const
{
    const auto* item = tree_->currentItem();
    return item ? item->data(0, Qt::UserRole).toString() : QString{};
}

bool TutorialBrowser::selectLesson(const QString& id)
{
    if (!catalog_.find(id)) return false;
    for (QTreeWidgetItemIterator it(tree_); *it; ++it)
        if ((*it)->data(0, Qt::UserRole).toString() == id)
        {
            if ((*it)->parent()) (*it)->parent()->setExpanded(true);
            tree_->setCurrentItem(*it);
            tree_->scrollToItem(*it);
            return true;
        }
    return false;
}

QLabel* TutorialBrowser::prose(const QString& markdown, const QString& baseDirectory, QWidget* parent)
{
    // QTextDocument parses a small, local Markdown subset. Raw HTML is disabled;
    // there is no WebEngine and no external URL/image loading in this view.
    QFont bodyFont = font();
    bodyFont.setPointSize(qMax(12, bodyFont.pointSize()));
    QTextDocument text;
    text.setDefaultFont(bodyFont);
    if (!baseDirectory.isEmpty())
        text.setBaseUrl(QUrl::fromLocalFile(QDir(baseDirectory).absolutePath() + "/"));
    text.setMarkdown(markdown, QTextDocument::MarkdownNoHTML);
    auto* label = new QLabel(text.toHtml(), parent);
    label->setTextFormat(Qt::RichText);
    label->setWordWrap(true);
    label->setTextInteractionFlags(Qt::TextSelectableByMouse | Qt::TextSelectableByKeyboard);
    label->setOpenExternalLinks(false);
    label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    label->setMinimumWidth(0);
    label->setFont(bodyFont);
    return label;
}

CodeEditor* TutorialBrowser::codePreview(const QString& code, const QString& name, QWidget* parent)
{
    auto* editor = new CodeEditor(parent);
    editor->setObjectName(name);
    editor->setReadOnly(true);
    editor->setDebugGutterEnabled(false);
    editor->setAcceptDrops(false);
    editor->setUndoRedoEnabled(false);
    editor->setLineWrapMode(QPlainTextEdit::NoWrap);
    editor->setPlainText(code);
    editor->document()->setModified(false);
    editor->setAccessibleName("Read-only tutorial code");
    auto* highlighter = new Highlighter(editor->document());
    previews_.append({editor, highlighter});
    stylePreview(editor);
    return editor;
}

void TutorialBrowser::stylePreview(CodeEditor* editor)
{
    editor->setFont(codeFont_);
    editor->setTabStopDistance(editor->fontMetrics().horizontalAdvance(' ') * 4);
    editor->setPalette(codePalette_);
    editor->setDarkTheme(dark_);
    for (const auto& preview : previews_)
        if (preview.editor == editor) preview.highlighter->setDark(dark_);
    // Avoid tiny scroll boxes for the short snippets; longer solutions can scroll.
    const int lines = qBound(3, editor->document()->blockCount(), 18);
    editor->setFixedHeight(lines * editor->fontMetrics().lineSpacing() + 26);
}

void TutorialBrowser::showSelection()
{
    previews_.clear();
    delete scroll_->takeWidget();
    auto* page = new QWidget;
    page->setObjectName("tutorialPage");
    page->setAutoFillBackground(true);
    auto* layout = new QVBoxLayout(page);
    layout->setContentsMargins(20, 12, 20, 24);
    layout->setSpacing(16);
    const auto* lesson = catalog_.find(selectedId());
    auto* title = new QLabel(page);
    title->setObjectName("tutorialTitle");
    title->setTextFormat(Qt::PlainText);
    title->setWordWrap(true);
    QFont heading = font();
    heading.setPointSize(20);
    heading.setBold(true);
    title->setFont(heading);
    layout->addWidget(title);
    if (!catalog_.isValid())
    {
        title->setText("Tutorial unavailable");
        layout->addWidget(prose(catalog_.errorString(), QString(), page));
    }
    else if (!lesson)
    {
        title->setText("Small C++ Tutorial");
        layout->addWidget(prose("Select a lesson on the left. You can start with any available lesson.", QString(), page));
    }
    else
    {
        title->setText(QString("%1. %2").arg(lesson->number).arg(lesson->title));
        if (lesson->available) showLesson(*lesson, page, layout);
        else
        {
            auto* message = prose("**This lesson is not available yet.**\n\nIts content has not been written yet. "
                "Its place in the curriculum is shown, but it is not locked by learning order. "
                "Select an available lesson on the left to start reading.", QString(), page);
            message->setObjectName("tutorialNotAvailable");
            layout->addWidget(message);
        }
        SmallSettings().setValue(LastKey, lesson->id);
    }
    layout->addStretch();
    scroll_->setWidget(page);
    scroll_->verticalScrollBar()->setValue(0);
    updateNavigation();
}

void TutorialBrowser::showLesson(const TutorialLesson& lesson, QWidget* page, QVBoxLayout* layout)
{
    auto* goal = prose(lesson.goal, lesson.sourceDirectory, page);
    goal->setObjectName("tutorialGoal");
    layout->addWidget(goal);
    int codeIndex = 0;
    for (const auto& block : lesson.blocks)
    {
        if (block.kind == TutorialBlock::Kind::Text)
        {
            layout->addWidget(prose(block.content, lesson.sourceDirectory, page));
            continue;
        }
        ++codeIndex;
        auto* group = new QGroupBox(block.title, page);
        auto* codeLayout = new QVBoxLayout(group);
        codeLayout->addWidget(codePreview(block.content, QString("tutorialExample%1").arg(codeIndex), group));
        auto* tryButton = Button("Try This Code", QString("tryTutorialExample%1").arg(codeIndex), group);
        tryButton->setProperty("primaryAction", true);
        tryButton->setMinimumWidth(150);
        codeLayout->addWidget(tryButton, 0, Qt::AlignRight);
        // Capture by value: changing the selected lesson must not invalidate code.
        const QString code = block.content;
        const QString context = QString("Lesson %1 — Example %2").arg(lesson.number).arg(codeIndex);
        connect(tryButton, &QPushButton::clicked, this, [this, code, context] { emit tryRequested(code, context); });
        layout->addWidget(group);
    }
    showExercises(lesson, page, layout);
    if (!lesson.relatedExample.isEmpty())
    {
        auto* related = Button("Open Related Example", "tutorialRelatedExample", page);
        const QString id = lesson.relatedExample;
        connect(related, &QPushButton::clicked, this, [this, id] { emit exampleRequested(id); });
        layout->addWidget(related, 0, Qt::AlignLeft);
    }
}

void TutorialBrowser::showExercises(const TutorialLesson& lesson, QWidget* page, QVBoxLayout* layout)
{
    for (int index = 0; index < lesson.exercises.size(); ++index)
    {
        const auto& exercise = lesson.exercises[index];
        const int number = index + 1;
        const QString suffix = QString::number(number);
        auto* group = new QGroupBox(QString("Exercise %1 — %2").arg(number).arg(exercise.title), page);
        group->setObjectName("tutorialExercise" + suffix);
        auto* exerciseLayout = new QVBoxLayout(group);
        exerciseLayout->setSpacing(12);
        exerciseLayout->addWidget(prose(exercise.prompt, lesson.sourceDirectory, group));
        auto* row = new QHBoxLayout;
        auto* tryButton = Button("Try", "tryTutorialExercise" + suffix, group);
        tryButton->setProperty("primaryAction", true);
        tryButton->setMinimumWidth(80);
        auto* hintButton = Button("Hint", "tutorialHintButton" + suffix, group);
        auto* solutionButton = Button("Show Solution", "tutorialSolutionButton" + suffix, group);
        hintButton->setCheckable(true);
        solutionButton->setCheckable(true);
        row->addWidget(tryButton);
        row->addWidget(hintButton);
        row->addWidget(solutionButton);
        row->addStretch();
        exerciseLayout->addLayout(row);
        auto* hint = prose(exercise.hint, lesson.sourceDirectory, group);
        hint->setObjectName("tutorialHint" + suffix);
        hint->hide();
        exerciseLayout->addWidget(hint);
        auto* solution = new QWidget(group);
        solution->setObjectName("tutorialSolution" + suffix);
        auto* solutionLayout = new QVBoxLayout(solution);
        solutionLayout->setContentsMargins(0, 0, 0, 0);
        solutionLayout->addWidget(prose("This is one example solution. Other solutions may also be correct.", QString(), solution));
        solutionLayout->addWidget(codePreview(exercise.solution, "tutorialSolutionCode" + suffix, solution));
        auto* trySolution = Button("Try Solution", "tryTutorialSolution" + suffix, solution);
        solutionLayout->addWidget(trySolution, 0, Qt::AlignRight);
        solution->hide();
        exerciseLayout->addWidget(solution);
        const QString starter = exercise.starter;
        const QString answer = exercise.solution;
        const QString context = QString("Lesson %1 — Exercise %2").arg(lesson.number).arg(number);
        connect(tryButton, &QPushButton::clicked, this, [this, starter, context] { emit tryRequested(starter, context); });
        connect(trySolution, &QPushButton::clicked, this, [this, answer, context] {
            emit tryRequested(answer, context + " — Solution");
        });
        connect(hintButton, &QPushButton::toggled, this, [hint, hintButton](bool visible) {
            hint->setVisible(visible);
            hintButton->setText(visible ? "Hide Hint" : "Hint");
        });
        connect(solutionButton, &QPushButton::toggled, this, [solution, solutionButton](bool visible) {
            solution->setVisible(visible);
            solutionButton->setText(visible ? "Hide Solution" : "Show Solution");
        });
        layout->addWidget(group);
    }
}

void TutorialBrowser::updateReadLabels()
{
    for (QTreeWidgetItemIterator it(tree_); *it; ++it)
    {
        const QString id = (*it)->data(0, Qt::UserRole).toString();
        const auto* lesson = catalog_.find(id);
        if (!lesson) continue;
        QString label = QString("%1. %2").arg(lesson->number).arg(lesson->title);
        if (readLessons_.contains(id)) label.prepend("✓ ");
        if (!lesson->available) label += " (not available yet)";
        (*it)->setText(0, label);
        (*it)->setForeground(0, codePalette_.color(lesson->available ? QPalette::Text : QPalette::PlaceholderText));
    }
}

void TutorialBrowser::updateNavigation()
{
    const QStringList available = catalog_.availableIds();
    const qsizetype index = available.indexOf(selectedId());
    previous_->setEnabled(index > 0);
    next_->setEnabled(index >= 0);
    next_->setText(index >= 0 && index == available.size() - 1 ? "Finish" : "Next →");
    progress_->setText("✓ marks a lesson as read. Next / Finish updates this mark; it does not grade your answer.");
}

void TutorialBrowser::previousLesson()
{
    const QStringList available = catalog_.availableIds();
    const qsizetype index = available.indexOf(selectedId());
    if (index > 0) selectLesson(available[index - 1]);
}

void TutorialBrowser::nextLesson()
{
    const QStringList available = catalog_.availableIds();
    const QString id = selectedId();
    const qsizetype index = available.indexOf(id);
    if (index < 0) return;
    readLessons_.insert(id);
    QStringList stored = readLessons_.values();
    stored.sort();
    SmallSettings().setValue(ReadKey, stored);
    updateReadLabels();
    if (index + 1 < available.size()) selectLesson(available[index + 1]);
    else progress_->setText("This is the last lesson in this version. You can revisit earlier lessons at any time.");
}

void TutorialBrowser::setAppearance(const QFont& codeFont, const QPalette& palette, bool dark)
{
    codeFont_ = codeFont;
    codePalette_ = palette;
    dark_ = dark;
    QPalette dialogPalette = palette;
    dialogPalette.setColor(QPalette::WindowText, palette.color(QPalette::Text));
    dialogPalette.setColor(QPalette::ButtonText, palette.color(QPalette::Text));
    dialogPalette.setColor(QPalette::Button, palette.color(QPalette::Window));
    setPalette(dialogPalette);
    tree_->setPalette(dialogPalette);
    scroll_->setPalette(dialogPalette);
    for (const auto& preview : previews_) stylePreview(preview.editor);
    updateReadLabels();
}
