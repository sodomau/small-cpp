#include "ExamplesBrowser.h"
#include "ExampleCatalog.h"
#include "CodeEditor.h"
#include "Highlighter.h"

#include <QDialogButtonBox>
#include <QGuiApplication>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QScreen>
#include <QSplitter>
#include <QTextCursor>
#include <QTextDocument>
#include <QTreeWidget>
#include <QTreeWidgetItemIterator>
#include <QVBoxLayout>
#include <QSettings>
#include "SmallSettings.h"

ExamplesBrowser::ExamplesBrowser(const ExampleCatalog& catalog, QWidget* parent)
    : QDialog(parent), catalog_(catalog)
{
    setObjectName("examplesBrowser");
    setWindowTitle("Examples — Small C++");
    setModal(false);
    setWindowFlags(Qt::Window |
                   Qt::WindowMinimizeButtonHint |
                   Qt::WindowMaximizeButtonHint |
                   Qt::WindowCloseButtonHint);

    setSizeGripEnabled(true);
    setMinimumSize(640, 460);
    const QByteArray savedGeometry =
        SmallSettings().value("examples/windowGeometry").toByteArray();
    if (!savedGeometry.isEmpty())
        restoreGeometry(savedGeometry);
    QFont uiFont = font();
    uiFont.setPointSize(qMax(11, uiFont.pointSize()));
    setFont(uiFont);
    setStyleSheet(
        "QTreeWidget { font-size: 11pt; }"
        "QTreeWidget::item { min-height: 30px; padding: 2px 4px; }"
        "QPushButton { min-height: 34px; font-size: 10.5pt; padding: 4px 12px; }"
    );

    auto* layout = new QVBoxLayout(this);
    layout->setContentsMargins(16, 16, 16, 12);
    layout->setSpacing(12);
    auto* splitter = new QSplitter(Qt::Horizontal, this);
    splitter->setObjectName("exampleSplitter");
    splitter->setChildrenCollapsible(false);

    tree_ = new QTreeWidget;
    tree_->setObjectName("exampleList");
    tree_->setHeaderHidden(true);
    tree_->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tree_->setSelectionMode(QAbstractItemView::SingleSelection);
    tree_->setUniformRowHeights(true);
    tree_->setIndentation(16);
    tree_->setMinimumWidth(190);
    tree_->setAccessibleName("Example categories and names");

    auto* details = new QWidget;
    auto* detailLayout = new QVBoxLayout(details);
    detailLayout->setContentsMargins(14, 0, 0, 0);
    detailLayout->setSpacing(8);
    title_ = new QLabel;
    title_->setObjectName("exampleTitle");
    QFont titleFont = font();
    titleFont.setPointSize(qMax(16, titleFont.pointSize() + 4));
    titleFont.setBold(true);
    title_->setFont(titleFont);
    title_->setTextFormat(Qt::PlainText);
    title_->setWordWrap(true);
    description_ = new QLabel;
    description_->setObjectName("exampleDescription");
    concepts_ = new QLabel;
    concepts_->setObjectName("exampleConcepts");
    notes_ = new QLabel;
    notes_->setObjectName("exampleNotes");
    for (QLabel* label : {description_, concepts_, notes_})
    {
        label->setTextFormat(Qt::PlainText);
        label->setWordWrap(true);
        label->setTextInteractionFlags(Qt::TextSelectableByMouse);
    }
    preview_ = new CodeEditor;
    preview_->setObjectName("examplePreview");
    preview_->setReadOnly(true);
    preview_->setAcceptDrops(false);
    preview_->setUndoRedoEnabled(false);
    preview_->setAccessibleName("Read-only example code preview");
    highlighter_ = new Highlighter(preview_->document());
    detailLayout->addWidget(title_);
    detailLayout->addWidget(description_);
    detailLayout->addWidget(concepts_);
    detailLayout->addWidget(notes_);
    detailLayout->addSpacing(4);
    detailLayout->addWidget(preview_, 1);
    splitter->addWidget(tree_);
    splitter->addWidget(details);
    splitter->setStretchFactor(0, 0);
    splitter->setStretchFactor(1, 1);
    splitter->setSizes({230, 700});
    layout->addWidget(splitter, 1);

    auto* footer = new QHBoxLayout;
    auto* hint = new QLabel("Open a read-only tab, then choose Try to edit your own copy.");
    hint->setObjectName("exampleBrowserHint");
    hint->setWordWrap(true);
    footer->addWidget(hint, 1);
    auto* buttons = new QDialogButtonBox(QDialogButtonBox::Open | QDialogButtonBox::Close);
    open_ = buttons->button(QDialogButtonBox::Open);
    open_->setObjectName("openExampleButton");
    open_->setDefault(true);
    open_->setEnabled(false);
    buttons->button(QDialogButtonBox::Close)->setObjectName("closeExamplesButton");
    footer->addWidget(buttons);
    layout->addLayout(footer);
    connect(buttons, &QDialogButtonBox::accepted, this, &ExamplesBrowser::openSelected);
    connect(buttons, &QDialogButtonBox::rejected, this, &QDialog::reject);

    QStringList groups;
    for (const auto& entry : catalog_.entries())
        if (!groups.contains(entry.group)) groups.append(entry.group);

    for (const QString& group : groups)
    {
        auto* category = new QTreeWidgetItem(tree_, QStringList{group});
        QFont categoryFont = tree_->font();
        categoryFont.setBold(true);
        category->setFont(0, categoryFont);
        for (const auto& entry : catalog_.entries())
        {
            if (entry.group != group) continue;
            auto* item = new QTreeWidgetItem(category, QStringList{entry.title});
            item->setData(0, Qt::UserRole, entry.id);
            item->setToolTip(0, entry.description);
        }
        category->setExpanded(true);
    }
    connect(tree_, &QTreeWidget::currentItemChanged, this,
            [this](QTreeWidgetItem*, QTreeWidgetItem*) { showSelection(); });
    connect(tree_, &QTreeWidget::itemActivated, this,
            [this](QTreeWidgetItem*, int) { openSelected(); });

    if (!catalog_.isValid())
    {
        title_->setText("Examples unavailable");
        description_->setText(catalog_.errorString());
        tree_->setEnabled(false);
    }
    else if (!catalog_.entries().isEmpty()) selectExample(catalog_.entries().first().id);

    const QScreen* screen = parent ? parent->screen() : QGuiApplication::primaryScreen();
    const QSize available = screen ? screen->availableGeometry().size() : QSize(1100, 800);
    resize(qMin(1000, qMax(640, available.width() - 80)),
           qMin(740, qMax(460, available.height() - 80)));
}

ExamplesBrowser::~ExamplesBrowser()
{
    SmallSettings().setValue("examples/windowGeometry", saveGeometry());
}


QString ExamplesBrowser::selectedId() const
{
    const auto* item = tree_->currentItem();
    return item ? item->data(0, Qt::UserRole).toString() : QString{};
}

bool ExamplesBrowser::selectExample(const QString& id)
{
    for (QTreeWidgetItemIterator it(tree_); *it; ++it)
    {
        if ((*it)->data(0, Qt::UserRole).toString() == id && !id.isEmpty())
        {
            tree_->setCurrentItem(*it);
            tree_->scrollToItem(*it);
            return true;
        }
    }
    return false;
}

void ExamplesBrowser::showSelection()
{
    const auto* entry = catalog_.find(selectedId());
    open_->setEnabled(entry != nullptr);
    if (!entry)
    {
        const auto* item = tree_->currentItem();
        title_->setText(item ? item->text(0) : QString("Examples"));
        description_->setText("Choose an example to see its description and code.");
        concepts_->clear();
        notes_->clear();
        preview_->clear();
        return;
    }
    title_->setText(entry->title);
    description_->setText(entry->description);
    concepts_->setText("Uses: " + entry->concepts.join(", "));
    notes_->setText(entry->notes);
    preview_->setPlainText(entry->code);
    preview_->moveCursor(QTextCursor::Start);
    preview_->document()->setModified(false);
}

void ExamplesBrowser::openSelected()
{
    const QString id = selectedId();
    if (!catalog_.find(id)) return;
    emit exampleRequested(id);
    accept(); // Hide; retain selection/size for the next visit.
}

void ExamplesBrowser::setAppearance(const QFont& font, const QPalette& palette, bool dark)
{
    // Match code appearance without changing the native menu/dialog style of
    // the rest of the IDE. Dialog labels must also remain readable in Dark.
    QPalette dialogPalette = palette;
    dialogPalette.setColor(QPalette::WindowText, palette.color(QPalette::Text));
    dialogPalette.setColor(QPalette::ButtonText, palette.color(QPalette::Text));
    dialogPalette.setColor(QPalette::Button, palette.color(QPalette::Window));
    setPalette(dialogPalette);
    tree_->setPalette(dialogPalette);
    preview_->setFont(font);
    preview_->setPalette(palette);
    preview_->setDarkTheme(dark);
    highlighter_->setDark(dark);
}
