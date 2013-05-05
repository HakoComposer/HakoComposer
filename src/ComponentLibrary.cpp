/*
*  Copyright (c) HakoComposer & Mehrez Kristou (kristou.com), distributed
*  as-is and without warranty under the MIT License. See
*  [root]/license.txt for more. This information must remain intact.
*/

#include "ComponentLibrary.hpp"
#include <QHeaderView>
#include <QMimeData>
#include <QDrag>
#include <QDebug>

ComponentLibrary::ComponentLibrary(QWidget *parent) :
    QTreeWidget(parent)
{
    setColumnCount(1);
    header()->close();
    setAnimated(true);
    setSelectionMode(QAbstractItemView::SingleSelection);
}

QTreeWidgetItem *ComponentLibrary::addCategory(const QString &name, QTreeWidgetItem *parent)
{
    if(parent){
        for(int i = 0; i < parent->childCount(); i++){
            if(parent->child(i)->text(0) == name){
                return parent->child(i);
            }
        }
        QTreeWidgetItem *item = new QTreeWidgetItem();
        item->setText(0, name);
        item->setIcon(0, QIcon(":/icons/folder"));
        parent->addChild(item);
        return item;
    }else{
        for(int i = 0; i < m_categories.size(); i++){
            if(m_categories.at(i)->text(0) == name){
                return m_categories.at(i);
            }
        }
        QTreeWidgetItem *item = new QTreeWidgetItem();
        item->setText(0, name);
        item->setIcon(0, QIcon(":/icons/folder"));
        m_categories.push_back(item);
        addTopLevelItem(item);
        return item;
    }
}

void ComponentLibrary::addComponent(Component *component)
{
    QString path = component->componentCategory();
    QStringList parts = path.split('/', QString::SkipEmptyParts);
    if(path.startsWith('/') && parts.size() > 0){
        QTreeWidgetItem *item = NULL;
        for(int i = 0; i < parts.size(); i++){
            item = addCategory(parts[i], item);
        }
        if(item){
            QTreeWidgetItem *entry = new QTreeWidgetItem();
            entry->setText(0, component->componentName());
            entry->setIcon(0, component->componentIcon());
            entry->setToolTip(0, component->componentDescription());
            entry->setData(0, Qt::UserRole +1, component->componentId());
            item->addChild(entry);
        }
    }else{
        qDebug() << path << " does not start with /";
    }
}

bool ComponentLibrary::categoryExists(const QString &category)
{
    foreach(QTreeWidgetItem * item, m_categories){
        if(item->text(0) == category){
            return true;
        }
    }
    return false;
}

QTreeWidgetItem *ComponentLibrary::findEntry(const QString &name, QTreeWidgetItem *parent){
    if(parent){
        if(parent->text(0) == name){
            return parent;
        }
        for(int i = 0; i < parent->childCount(); i++){
            QTreeWidgetItem *item = findEntry(name, parent->child(i));
            if(item) return item;
        }
    }
    return NULL;
}

QTreeWidgetItem *ComponentLibrary::findEntry(const QString &name)
{
    for(int i = 0; i < m_categories.size(); i++){
        QTreeWidgetItem *item = findEntry(name, m_categories.at(i));
        if(item) return item;
    }
    return NULL;
}

void ComponentLibrary::mouseMoveEvent(QMouseEvent *event)
{
    QTreeWidget::mouseMoveEvent(event);

    // if not left button - return
    if (!(event->buttons() & Qt::LeftButton)) return;

    // if no item selected, return (else it would crash)
    if (currentItem() == NULL) return;

    QTreeWidgetItem *item = currentItem();

    if(item && !item->data(0, Qt::UserRole +1).toString().isEmpty()){
        QMimeData *mimeData = new QMimeData;
        mimeData->setText(item->data(0, Qt::UserRole +1).toString());

        // Create drag
        QDrag *drag = new QDrag(this);
        drag->setMimeData(mimeData);
        drag->setPixmap(item->icon(0).pixmap(QSize(32, 32)));
        drag->start(Qt::CopyAction);
    }
}
