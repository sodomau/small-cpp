#include "ApiBrowser.h"
#include <QCheckBox>
#include <QDialogButtonBox>
#include <QGuiApplication>
#include <QHeaderView>
#include <QHash>
#include <QHBoxLayout>
#include <QLabel>
#include <QPlainTextEdit>
#include <QScreen>
#include <QSplitter>
#include <QTableWidget>
#include <QTreeWidget>
#include <QVBoxLayout>
#include <QSettings>
#include "SmallSettings.h"

ApiBrowser::ApiBrowser(QWidget* parent) : QDialog(parent)
{
    setWindowTitle("Small API at a Glance");
    setObjectName("apiBrowser");
    setModal(false);
    setWindowFlags(Qt::Window |
                   Qt::WindowMinimizeButtonHint |
                   Qt::WindowMaximizeButtonHint |
                   Qt::WindowCloseButtonHint);
    setMinimumSize(760, 520);
    const QByteArray savedGeometry =
        SmallSettings().value("api/windowGeometry").toByteArray();
    if (!savedGeometry.isEmpty())
        restoreGeometry(savedGeometry);
    resize(1000, 680);

    entries_ = ApiReference::core();
    entries_ += ApiReference::image();

    tree_ = new QTreeWidget;
    tree_->setHeaderHidden(true);
    QStringList categories;
    for (const auto& e : entries_) if (!categories.contains(e.category)) categories.append(e.category);
    for (const auto& category : categories)
    {
        auto* group = new QTreeWidgetItem(tree_, {category});
        QFont f=group->font(0); f.setBold(true); group->setFont(0,f);
        group->setFlags(group->flags() & ~Qt::ItemIsSelectable);

        // First collect entries that represent a type itself (Window, File,
        // StopWatch...) so that the same tree node can also own its members.
        QHash<QString, int> typeEntries;
        for (int i=0;i<entries_.size();++i)
            if (entries_[i].category==category && !entries_[i].name.contains('.'))
                typeEntries.insert(entries_[i].name, i);

        QHash<QString, QTreeWidgetItem*> typeNodes;
        for (int i=0;i<entries_.size();++i) if(entries_[i].category==category)
        {
            const QString fullName = entries_[i].name;
            const int dot = fullName.indexOf('.');
            if (dot > 0)
            {
                const QString typeName = fullName.left(dot);
                const QString memberName = fullName.mid(dot + 1);
                QTreeWidgetItem* typeNode = typeNodes.value(typeName, nullptr);
                if (!typeNode)
                {
                    typeNode = new QTreeWidgetItem(group, {typeName});
                    QFont typeFont=typeNode->font(0); typeFont.setBold(true); typeNode->setFont(0,typeFont);
                    if (typeEntries.contains(typeName))
                        typeNode->setData(0, Qt::UserRole, typeEntries.value(typeName));
                    else
                        typeNode->setFlags(typeNode->flags() & ~Qt::ItemIsSelectable);
                    typeNode->setExpanded(true);
                    typeNodes.insert(typeName, typeNode);
                }
                auto* item=new QTreeWidgetItem(typeNode,{memberName});
                item->setData(0,Qt::UserRole,i);
            }
            else
            {
                // If this entry is a type with members, its shared parent node
                // is created above/below and remains selectable. Do not add a
                // second duplicate row.
                bool hasMembers=false;
                const QString prefix=fullName + ".";
                for (const auto& candidate : entries_)
                    if (candidate.category==category && candidate.name.startsWith(prefix))
                    { hasMembers=true; break; }

                if (hasMembers)
                {
                    if (!typeNodes.contains(fullName))
                    {
                        auto* typeNode=new QTreeWidgetItem(group,{fullName});
                        QFont typeFont=typeNode->font(0); typeFont.setBold(true); typeNode->setFont(0,typeFont);
                        typeNode->setData(0,Qt::UserRole,i);
                        typeNode->setExpanded(true);
                        typeNodes.insert(fullName,typeNode);
                    }
                }
                else
                {
                    auto* item=new QTreeWidgetItem(group,{fullName});
                    item->setData(0,Qt::UserRole,i);
                }
            }
        }
        group->setExpanded(true);
    }

    title_=new QLabel; QFont tf=title_->font(); tf.setPointSize(tf.pointSize()+4); tf.setBold(true); title_->setFont(tf);
    usage_=new QLabel; QFont uf=usage_->font(); uf.setFamily("Consolas"); uf.setPointSize(uf.pointSize()+1); usage_->setFont(uf);
    summary_=new QLabel; summary_->setWordWrap(true);
    parameters_=new QTableWidget; parameters_->setColumnCount(3);
    parameters_->setHorizontalHeaderLabels({"Parameter","Kind","Meaning"});
    parameters_->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    parameters_->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    parameters_->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    parameters_->verticalHeader()->hide();
    parameters_->setEditTriggers(QAbstractItemView::NoEditTriggers);
    parameters_->setSelectionMode(QAbstractItemView::NoSelection);
    parameters_->setMaximumHeight(190);
    returns_=new QLabel; returns_->setWordWrap(true);
    example_=new QPlainTextEdit; example_->setReadOnly(true); example_->setMaximumHeight(78);
    note_=new QLabel; note_->setWordWrap(true);
    details_=new QCheckBox("Show C++ details");
    cpp_=new QLabel; cpp_->setWordWrap(true); cpp_->setVisible(false);
    connect(details_,&QCheckBox::toggled,cpp_,&QWidget::setVisible);

    auto* right=new QWidget; auto* layout=new QVBoxLayout(right);
    layout->addWidget(title_); layout->addWidget(usage_); layout->addWidget(summary_);
    auto* ph=new QLabel("Parameters"); QFont bf=ph->font();bf.setBold(true);ph->setFont(bf);layout->addWidget(ph);
    layout->addWidget(parameters_);
    layout->addWidget(returns_);
    auto* eh=new QLabel("Example");eh->setFont(bf);layout->addWidget(eh);layout->addWidget(example_);
    layout->addWidget(note_); layout->addStretch(); layout->addWidget(details_); layout->addWidget(cpp_);

    auto* splitter=new QSplitter; splitter->addWidget(tree_);splitter->addWidget(right);
    splitter->setStretchFactor(0,0); splitter->setStretchFactor(1,1);
    splitter->setSizes({280, 720});
    auto* buttons=new QDialogButtonBox(QDialogButtonBox::Close);connect(buttons,&QDialogButtonBox::rejected,this,&QDialog::close);
    auto* outer=new QVBoxLayout(this);outer->addWidget(splitter);outer->addWidget(buttons);

    connect(tree_,&QTreeWidget::currentItemChanged,this,[this]{showSelection();});
    for(int i=0;i<tree_->topLevelItemCount();++i)
        if(tree_->topLevelItem(i)->childCount()){tree_->setCurrentItem(tree_->topLevelItem(i)->child(0));break;}
}

ApiBrowser::~ApiBrowser()
{
    SmallSettings().setValue("api/windowGeometry", saveGeometry());
}


void ApiBrowser::showSelection()
{
    auto* item=tree_->currentItem(); if(!item)return;
    bool ok=false; int index=item->data(0,Qt::UserRole).toInt(&ok); if(!ok||index<0||index>=entries_.size())return;
    const auto& e=entries_[index];
    title_->setText(e.name);usage_->setText(e.usage);summary_->setText(e.summary);
    parameters_->setRowCount(e.parameters.size());
    for(int row=0;row<e.parameters.size();++row){
        const auto& p=e.parameters[row];
        parameters_->setItem(row,0,new QTableWidgetItem(p.name));
        parameters_->setItem(row,1,new QTableWidgetItem(p.type));
        parameters_->setItem(row,2,new QTableWidgetItem(p.meaning));
    }
    parameters_->setVisible(!e.parameters.isEmpty());
    returns_->setText("<b>Returns:</b> "+e.returns);
    example_->setPlainText(e.example);
    note_->setText(e.note.isEmpty()?QString{}:"Note: "+e.note);
    cpp_->setText(e.cppPrototype.isEmpty()?"C++ details are intentionally hidden in this learner view.":e.cppPrototype);
}

void ApiBrowser::setAppearance(const QFont& font,const QPalette& palette,bool)
{
    setFont(font); setPalette(palette); tree_->setPalette(palette); parameters_->setPalette(palette); example_->setPalette(palette);
}
