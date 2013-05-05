/*
*  Copyright (c) HakoComposer & Mehrez Kristou (kristou.com), distributed
*  as-is and without warranty under the MIT License. See
*  [root]/license.txt for more. This information must remain intact.
*/

#include "Component.hpp"
#include <QGraphicsScene>
#include <QDebug>

namespace Hako {

Component::Component(QGraphicsItem *parent):
    NodeView(parent)
{
    QObject::connect(this, SIGNAL(closeClicked(const QPoint &)),
                     this, SLOT(closeButtonClicked(const QPoint &)));
    QObject::connect(this, SIGNAL(settingsClicked(const QPoint &)),
                     this, SLOT(settingsButtonClicked(const QPoint &)));
    QObject::connect(this, SIGNAL(menuClicked(const QPoint &)),
                     this, SLOT(menuButtonClicked(const QPoint &)));
}

Component::~Component()
{
    removeFromWorkspace();
}

void Component::removeFromWorkspace()
{
    removeAllPorts();
    if(scene()) scene()->removeItem(this);
}

int Component::registerOutput(char *signal, const QString &name)
{
    return addPort(READER_OUTPUT, this, signal, name);
}

int Component::registerInput(char *slot, const QString &name)
{
    return addPort(READER_INPUT, this, slot, name);
}

int Component::registerSpecialOutput(char *signal, const QString &name)
{
    return addPort(WRITER_OUTPUT, this, signal, name);
}

int Component::registerSpecialInput(char *slot, const QString &name)
{
    return addPort(WRITER_INPUT, this, slot, name);
}

bool Component::connectInput(int in, Component *component, int out)
{
    if(in < portCount(READER_INPUT) && out < component->portCount(READER_OUTPUT)){
        return port(READER_INPUT, in)->connectPort( component->port(READER_OUTPUT, out) );
    }else{
        return false;
    }
}

bool Component::connectOutput(int out, Component *component, int in)
{
    if(out < portCount(READER_OUTPUT) && in < component->portCount(READER_INPUT)){
        return port(READER_OUTPUT, out)->connectPort( component->port(READER_INPUT, in) );
    }else{
        return false;
    }
}

bool Component::connectSpecialInput(int in, Component *component, int out)
{
    if(in < portCount(WRITER_INPUT) && out < component->portCount(WRITER_OUTPUT)){
        return port(WRITER_INPUT, in)->connectPort( component->port(WRITER_OUTPUT, out) );
    }else{
        return false;
    }
}

bool Component::connectSpecialOutput(int out, Component *component, int in)
{
    if(out < portCount(WRITER_OUTPUT) && in < component->portCount(WRITER_INPUT)){
        return port(WRITER_OUTPUT, out)->connectPort( component->port(WRITER_INPUT, in) );
    }else{
        return false;
    }
}

void Component::settingsActivated()
{
}

bool Component::closeComponent()
{
    return true;
}

void Component::setMenu(QMenu *menu)
{
    m_menu = menu;
    setMenuButtonVisible(m_menu ? true : false);
}

void Component::closeButtonClicked(const QPoint &pos)
{
    Q_UNUSED(pos);
    if(closeComponent()){
        removeFromWorkspace();
        delete this;
    }
}

void Component::settingsButtonClicked(const QPoint &pos)
{
    Q_UNUSED(pos);
    settingsActivated();
}

void Component::menuButtonClicked(const QPoint &pos)
{
    if(m_menu){
        m_menu->exec(pos);
    }
}

}
