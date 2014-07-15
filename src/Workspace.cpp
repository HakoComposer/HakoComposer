/*
*  Copyright (c) HakoComposer & Mehrez Kristou (kristou.com), distributed
*  as-is and without warranty under the MIT License. See
*  [root]/license.txt for more. This information must remain intact.
*/

#include "Workspace.hpp"
#include <QMimeData>
#include <QGraphicsItem>
#include <QFile>
#include "NodeLinkView.hpp"
#include <QDebug>

Workspace::Workspace(QObject *parent):
    QGraphicsScene(parent),
    m_componentCount(0)
{
}

void Workspace::registerComponent(Component *component)
{
    m_registeredComponents.push_back(component);
}

Component *Workspace::getComponent(const QString &id)
{
    foreach (Component *item, m_registeredComponents) {
        if(item->componentId() == id){
            return item;
        }
    }
    return NULL;
}

void Workspace::addComponent(Component *component, QPointF position)
{
    if(component){
        component->setIndex(m_componentCount++);
        component->setPos(position
                          //- QPointF(component->boundingRect().width() /2, component->boundingRect().height() /2)
                          );
        component->addToWorkspace(this);
        update();
    }
}

Component *Workspace::addComponent(const QString &id, QPointF position)
{
    Component *component = getComponent(id)->clone();
    if(component){
        addComponent(component, position);
        return component;
    }
    return NULL;
}

Component *Workspace::addCopyComponent(Component *original, QPointF position)
{
    if(original){
        Component *component = original->clone();
        if(component){
            addComponent(component, position);
            return component;
        }
    }
    return NULL;
}

void Workspace::clearWorkspace()
{
        // Delete all links to disconnect components
        foreach (QGraphicsItem* item, items()) {
            NodeLinkView *link = dynamic_cast<NodeLinkView *>(item);
            if(link){
                delete link;
            }
        }

        // Delete all components
        foreach (QGraphicsItem* item, items()) {
            Component *component = dynamic_cast<Component *>(item);
            if(component){
                component->removeFromWorkspace();
                delete component;
            }
        }


    // Delete what is left!
    clear();
    m_componentCount = 0;
}

void Workspace::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    if (event->mimeData()->hasText() && isComponentRegistered(event->mimeData()->text())) {
        event->acceptProposedAction();
    }
}

void Workspace::dragLeaveEvent(QGraphicsSceneDragDropEvent *event)
{
    Q_UNUSED(event);
    update();
}

QStringList Workspace::getRegisteredComponentIds()
{
    QStringList result;
    foreach(Component *c, m_registeredComponents){
        result << c->componentId();
    }
    return result;
}

QStringList Workspace::getComponentsRecords()
{
    QStringList result;
    foreach (QGraphicsItem *item, items()) {
        Component *component = dynamic_cast<Component *>(item);
        if(component){
            result << component->componentId() +
                      "#" + QString::number(component->index()) +
                      "$" + QString::number(component->pos().x()) +
                      "," + QString::number(component->pos().y());
        }
    }
    return result;
}

void Workspace::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    if (event->mimeData()->hasText() && isComponentRegistered(event->mimeData()->text())) {
        QString id = event->mimeData()->text();
        addComponent(id, event->scenePos());
    }
}

void Workspace::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    Q_UNUSED(event);
}

bool Workspace::isComponentRegistered(const QString &id)
{
    foreach (Component *item, m_registeredComponents) {
        if(item->componentId() == id){
            return true;
        }
    }
    return false;
}

bool Workspace::saveWorkspace(const QString &filename)
{
    QFile file(filename);
    if(file.open(QIODevice::WriteOnly | QIODevice::Text)){
        QTextStream ts(&file);

        ts << "[Components]" << endl;
        QStringList componentList = getComponentsRecords();
        foreach(QString c, componentList){
            ts << c << endl;
        }
        ts << "]Components[" << endl;

        ts << "[Links]" << endl;
        QMap<QString, QString> linkList = getLinksRecords();
        for (QMap<QString, QString>::iterator item = linkList.begin(); item != linkList.end(); item++)
            ts << item.key() << " => " << item.value() << endl;
        ts << "]Links[" << endl;

        file.close();
        return true;
    }
    return false;
}

bool Workspace::loadWorkspace(const QString &filename)
{
    clearWorkspace();
    QFile file(filename);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream ts(&file);
        loadLinks(&ts, loadComponents(&ts));
        file.close();
        return true;
    }

    return false;
}

QList<Component *> Workspace::getRegisteredComponents()
{
    return m_registeredComponents;
}

QMap<QString, QString> Workspace::getLinksRecords()
{
    QMap<QString, QString> result;
    int index = 0;
    foreach (QGraphicsItem *item, items()) {
        NodeLinkView* link = dynamic_cast<NodeLinkView *>(item);
        if(link){
            result.insertMulti(QString::number(index) + ":" +
                        link->outPort()->componentId() +
                        "#" + QString::number(link->outPort()->getNodeIndex()) +
                        "$" + QString::number((int)link->outPort()->portType()) +
                        "-" + QString::number(link->outPort()->index()) ,
                        link->inPort()->componentId() +
                        "#" + QString::number(link->inPort()->getNodeIndex()) +
                        "$" + QString::number((int)link->inPort()->portType()) +
                        "-" + QString::number(link->inPort()->index())
                        );
            index++;
        }
    }
    return result;
}

QMap<QString, Component *> Workspace::loadComponents(QTextStream *ts)
{
    QMap<QString, Component *> result;

    bool componentsRecordsFound = false;

    ts->seek(0);

    while(!ts->atEnd()){
        QString line = ts->readLine();
        if(line.startsWith("[Components]")){
            componentsRecordsFound = true;
            continue;
        }
        if(line.startsWith("]Components[")){
            componentsRecordsFound = false;
            break;
        }
        if(componentsRecordsFound){
            QStringList parts = line.split('$', QString::SkipEmptyParts);
            if(parts.size() != 2){
                continue;
            }
            QString idAndIndex = parts[0];
            QString position = parts[1];

            QStringList idParts = idAndIndex.split('#', QString::SkipEmptyParts);
            if(idParts.size() != 2){
                continue;
            }
            QString id = idParts[0];
            if(!isComponentRegistered(id)){
                continue;
            }

            QStringList positionParts = position.split(',', QString::SkipEmptyParts);
            if(positionParts.size() != 2){
                continue;
            }
            QPointF pos(positionParts[0].toInt(), positionParts[1].toInt());

            result.insertMulti(idAndIndex, addComponent(id, pos));
        }
    }

    return result;
}

void Workspace::loadLinks(QTextStream *ts, const QMap<QString, Component *> &components)
{
    bool linksRecordsFound = false;

    ts->seek(0);

    while(!ts->atEnd()){
        QString line = ts->readLine();
        if(line.startsWith("[Links]")){
            linksRecordsFound = true;
            continue;
        }
        if(line.startsWith("]Links[")){
            linksRecordsFound = false;
            break;
        }
        if(linksRecordsFound){
            QStringList sections = line.split(":", QString::SkipEmptyParts);
            if(sections.size() != 2){
                continue;
            }

            QStringList parts = sections[1].split(" => ", QString::SkipEmptyParts);
            if(parts.size() != 2){
                continue;
            }

            QString link0 = parts[0];
            QString link1 = parts[1];

            PortTypeEnum link0PortType = UNKNOWN;
            unsigned int link0PortIndex = -1;
            Component *link0Component = getLinkInfo(link0, link0PortType, link0PortIndex, components);
            if(!link0Component){
                continue;
            }

            PortTypeEnum link1PortType = UNKNOWN;
            unsigned int link1PortIndex = -1;
            Component *link1Component = getLinkInfo(link1, link1PortType, link1PortIndex, components);
            if(!link1Component){
                continue;
            }

            switch(link0PortType){
            case READER_OUTPUT:{
                link0Component->connectOutput(link0PortIndex, link1Component, link1PortIndex);
            }break;
            case READER_INPUT:{
                link0Component->connectInput(link0PortIndex, link1Component, link1PortIndex);
            }break;
            case WRITER_OUTPUT:{
                link0Component->connectSpecialOutput(link0PortIndex, link1Component, link1PortIndex);
            }break;
            case WRITER_INPUT:{
                link0Component->connectSpecialInput(link0PortIndex, link1Component, link1PortIndex);
            }break;
            default:{
                ;
            }break;
            }
        }
    }
}

Component *Workspace::getLinkInfo(const QString &st,
                                  PortTypeEnum &type, unsigned int & index,
                                  const QMap<QString, Component *> &components)
{
    // Link1

    Component *component = NULL;

    QStringList parts = st.split('$', QString::SkipEmptyParts);
    if(parts.size() != 2){
        return component;
    }
    QString idAndIndex = parts[0];
    QString typeAndInput = parts[1];

    if(!components.contains(idAndIndex)){
        return component;
    }

    component = (Component *)components.value(idAndIndex, NULL);
    if(!component){
        return component;
    }

    QStringList typeparts = typeAndInput.split('-', QString::SkipEmptyParts);
    if(typeparts.size() != 2){
        return component;
    }

    type = (PortTypeEnum)typeparts[0].toInt();
    index = (unsigned int)typeparts[1].toInt();

    return component;
}
