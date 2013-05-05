/*
*  Copyright (c) HakoComposer & Mehrez Kristou (kristou.com), distributed
*  as-is and without warranty under the MIT License. See
*  [root]/license.txt for more. This information must remain intact.
*/

#ifndef COMPONENTLIBRARY_H
#define COMPONENTLIBRARY_H

#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QMouseEvent>
#include "Component.hpp"

using namespace Hako ;

class ComponentLibrary : public QTreeWidget
{
    Q_OBJECT
public:
    explicit ComponentLibrary(QWidget *parent = 0);
    QTreeWidgetItem *addCategory(const QString &name, QTreeWidgetItem *parent);
    void addComponent(Component *component);
    
    QTreeWidgetItem *findEntry(const QString &name, QTreeWidgetItem *parent);
    QTreeWidgetItem *findEntry(const QString &name);

    void mouseMoveEvent(QMouseEvent *event);
signals:
    
public slots:

private:
    QList<QTreeWidgetItem *> m_categories;
    
    bool categoryExists(const QString &category);
};

#endif // COMPONENTLIBRARY_H
