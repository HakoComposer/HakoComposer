/*
*  Copyright (c) HakoComposer & Mehrez Kristou (kristou.com), distributed
*  as-is and without warranty under the MIT License. See
*  [root]/license.txt for more. This information must remain intact.
*/

#ifndef WORKSPACE_H
#define WORKSPACE_H

#include <QGraphicsScene>
#include <QGraphicsSceneEvent>
#include "Component.hpp"
#include <QTextStream>

using namespace Hako;

class Workspace : public QGraphicsScene
{
    Q_OBJECT
public:
    Workspace(QObject * parent = 0);

    void registerComponent(Component *component);
    Component *getComponent(const QString &id);
    void addComponent(Component *component, QPointF position = QPointF(0, 0));
    Component *addComponent(const QString &id, QPointF position);
    Component *addCopyComponent(Component *original, QPointF position = QPointF(0, 0));
    bool isComponentRegistered(const QString &id);
    void clearWorkspace();

    bool saveWorkspace(const QString &filename);
    bool loadWorkspace(const QString &filename);

    QList<Component *> getRegisteredComponents();
protected:
    void dropEvent(QGraphicsSceneDragDropEvent *event);
    void dragMoveEvent(QGraphicsSceneDragDropEvent *event);
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event);

private:
    QList<Component *> m_registeredComponents;
    unsigned int m_componentCount;

    QStringList getRegisteredComponentIds();
    QStringList getComponentsRecords();
    QMap<QString, QString> getLinksRecords();
    QMap<QString, Component *> loadComponents(QTextStream *ts);
    void loadLinks(QTextStream *ts, const QMap<QString, Component *> &components);
    Component *getLinkInfo(const QString &st, PortTypeEnum &type, unsigned int &index, const QMap<QString, Component *> &components);

};

#endif // WORKSPACE_H
