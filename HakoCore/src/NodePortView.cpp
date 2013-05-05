/*
*  Copyright (c) HakoComposer & Mehrez Kristou (kristou.com), distributed
*  as-is and without warranty under the MIT License. See
*  [root]/license.txt for more. This information must remain intact.
*  This file is partly a modified version of the one in https://github.com/nical/kiwi
*/

#include "NodePortView.hpp"

#include "NodeView.hpp"
#include "NodeLinkView.hpp"
#include "TemporaryPortView.hpp"

#include <QPainter>
#include <QLinearGradient>
#include <QGraphicsScene>
#include <QCursor>
#include <QDebug>

namespace Hako {

NodePortView::NodePortView(NodeView* node, PortTypeEnum type, unsigned int index , QGraphicsItem *parent):
    QGraphicsObject(parent),
    isTemporary(false),
    m_node(node),
    m_normalColor(Qt::white),
    m_connectedColor(Qt::gray),
    m_compatibleColor(Qt::green),
    m_uncompatibleColor(Qt::red),
    m_signal(NULL),
    m_object(NULL),
    m_name(""),
    m_componentId("")
{
    m_type = type;
    m_index = index;
    m_dragging = false;
    m_compatible = false;
    updatePosition();
    setCursor(QCursor(QPixmap(":/HakoCore/link"), 8, 8));
    //    setFlags( QGraphicsItem::ItemIsSelectable );
}

NodePortView::NodePortView(PortTypeEnum type, QGraphicsItem *parent):
    QGraphicsObject(parent),
    isTemporary(false),
    m_node(NULL),
    m_normalColor(Qt::white),
    m_connectedColor(Qt::gray),
    m_compatibleColor(Qt::green),
    m_uncompatibleColor(Qt::red),
    m_signal(NULL),
    m_object(NULL),
    m_name(""),
    m_componentId("")
{
    m_type = type;
}

NodePortView::~NodePortView()
{
    deleteLink();
}

QString NodePortView::printNodeType(PortTypeEnum type)
{
    QString result;
    if( type & READER ) result += QString("reader ");
    if( type & WRITER ) result += QString("writer ");
    if( type & INPUT ) result += QString("input");
    if( type & OUTPUT ) result += QString("output");

    return result;
}

void NodePortView::deleteLink( NodeLinkView* link )
{
    if(link == 0){
        qDeleteAll(m_links);
        m_links.clear();
    }else{
        foreach(NodeLinkView* it, m_links){
            if( it == link ) delete link;
        }
    }
}

bool NodePortView::isConnected(NodePortView* p) const
{
    if(p){
        foreach(NodeLinkView* it, m_links){
            if(it->inPort() == p || it->outPort() == p){
                return true;
            }
        }
        return false;
    }else{
        return !m_links.isEmpty();
    }
}

void NodePortView::disconnectLink(NodeLinkView *link)
{
    if(link == 0){
        m_links.clear();
    }else{
        m_links.removeAll(link);
    }
}

void NodePortView::addLink(NodeLinkView *link)
{
    m_links.append( link );
    if(!isTemporary && portType() == READER_OUTPUT){
        m_node->componentGotConnected();
    }
}

bool NodePortView::isCompatible( NodePortView* port ) const
{
    if(!port){
        return false;
    }

    if(!isCompatible( port->portType() )){
        return false;
    }

    if(port->isTemporary){
        return true;
    }

    if(port->object() && port->signal()){
        int methodIndex = port->object()->metaObject()->indexOfMethod(QMetaObject::normalizedSignature(port->signal()+1));
        if(methodIndex >= 0){
            QMetaMethod myMethod = port->object()->metaObject()->method(methodIndex);
            return isCompatible(myMethod);
        }
    }

    return true;
}

bool NodePortView::isCompatible( QMetaMethod method ) const{
    if(object() && signal()){
        int methodIndex = object()->metaObject()->indexOfMethod(QMetaObject::normalizedSignature(signal()+1));
        if(methodIndex >= 0){
            QMetaMethod myMethod = object()->metaObject()->method(methodIndex);
            if(method.parameterTypes().size() == myMethod.parameterTypes().size()){
                for(int i = 0; i < method.parameterTypes().size(); i++){
                    QByteArray param1 = method.parameterTypes()[i];
                    QByteArray param2 = myMethod.parameterTypes()[i];
                    if(param1 != param2){
                        return false;
                    }
                }
                return true;
            }
        }
    }

    return false;
}

bool NodePortView::isCompatible( PortTypeEnum pType ) const{
    if( (m_type & INPUT_OUTPUT_MASK) == (pType & INPUT_OUTPUT_MASK) ){
        qDebug() << "// input -> input or output -> output";
        return false;
    }

    if( (m_type & READER_WRITER_MASK) != (pType & READER_WRITER_MASK) ){
        qDebug() << "reader -> writer or writer -> reader";
        return false;
    }

    return true;
}

void NodePortView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->save();

    if( isSelected() ){
        painter->setPen( QPen(QColor(50,50,100),2) );
    }else{
        painter->setPen( QPen(QColor(100,100,100),2) );
    }

    painter->setBrush(getPortColor());

    painter->drawEllipse( -5, -5, 10, 10 );

    if(portType() == READER_INPUT){
        painter->drawText(10, 5, m_name);
    }
    if(portType() == READER_OUTPUT){
        QFontMetrics fm(painter->font());
        int nameWidth = fm.width(m_name);
        painter->drawText(-10 - nameWidth, 5, m_name);
    }

    painter->restore();
}

QRectF NodePortView::boundingRect() const
{
    return QRectF( -5, -5, 10, 10 );
}

QColor NodePortView::getPortColor()
{
    QColor response = m_normalColor;
    TemporaryPortView* grabber = dynamic_cast<TemporaryPortView*>( scene()->mouseGrabberItem() );
    if(grabber){
        bool compatible = false;
        if(grabber->object() && grabber->signal()){
            int methodIndex = grabber->object()->metaObject()->indexOfMethod(QMetaObject::normalizedSignature(grabber->signal()+1));
            if(methodIndex >= 0){
                QMetaMethod myMethod = grabber->object()->metaObject()->method(methodIndex);
                compatible = isCompatible(myMethod);
            }
        }
        if(compatible && grabber->portType() == portType()){
            response = m_compatibleColor;
        }else{
            response = m_uncompatibleColor;
        }
    }else{
        if(isConnected()){
            response = m_connectedColor;
        }else{
            response = m_normalColor;
        }
    }

    return response;
}

void NodePortView::updatePosition(){
    switch(m_type){
    case READER_OUTPUT: {
        setPos(    m_node->pos().x() + m_node->boundingRect().right()
                   ,m_node->pos().y() + m_node->boundingRect().top() + 40 + 20*m_index );
        break;
    }
    case READER_INPUT: {
        setPos(    m_node->pos().x() + m_node->boundingRect().left()
                   ,m_node->pos().y() + m_node->boundingRect().top() + 40 + 20*m_index );
        break;
    }
    case WRITER_INPUT: {
        setPos(    m_node->pos().x() + 35 + 20*m_index
                   ,m_node->pos().y() + m_node->boundingRect().top() );
        break;
    }
    case WRITER_OUTPUT: {
        setPos(    m_node->pos().x() + 35 + 20*m_index
                   ,m_node->pos().y() + m_node->boundingRect().bottom() );
        break;
    }
    default: {
        foreach(NodeLinkView* link, m_links){
            link->updatePosition(m_type , pos() );
        }
    }
    }
}

bool NodePortView::connectPort( NodePortView* p)
{
    if(p == 0){
        // TODO disconnect;
        return true;
    }


    if( isConnected(p) ){
        return false;
    }

    if(!isCompatible(p)){
        return false;
    }

    NodeLinkView* nlink = new NodeLinkView( m_type & READER_WRITER_MASK, this, p );
    addLink( nlink );
    p->addLink( nlink );
    scene()->addItem( nlink );
    nlink->setZValue( -100 );

    return true;
}

void NodePortView::mousePressEvent( QGraphicsSceneMouseEvent * event )
{
    //TODO if ctrl not pressed...

    if(event->buttons().testFlag(Qt::LeftButton)){
        PortTypeEnum ntype;
        switch( m_type )
        {
        case READER_INPUT: {ntype = READER_OUTPUT; break;}
        case READER_OUTPUT:{ntype = READER_INPUT; break;}
        case WRITER_INPUT: {ntype = WRITER_OUTPUT; break;}
        case WRITER_OUTPUT: {ntype = WRITER_INPUT; break;}
        default: {ntype = UNKNOWN;}
        }

        TemporaryPortView* tpv = new TemporaryPortView( ntype, pos() );
        tpv->setObject(object());
        tpv->setSignal(signal());

        scene()->addItem( tpv );
        tpv->grabMouse();
        setSelected(true);
        connectPort( tpv );
    } else if(event->buttons().testFlag(Qt::RightButton)){
        deleteLink(0);
    }

}

QColor NodePortView::normalColor() const
{
    return m_normalColor;
}

void NodePortView::setNormalColor(const QColor &normalColor)
{
    m_normalColor = normalColor;
}


QColor NodePortView::connectedColor() const
{
    return m_connectedColor;
}

void NodePortView::setConnectedColor(const QColor &connectedColor)
{
    m_connectedColor = connectedColor;
}


QColor NodePortView::compatibleColor() const
{
    return m_compatibleColor;
}

void NodePortView::setCompatibleColor(const QColor &compatibleColor)
{
    m_compatibleColor = compatibleColor;
}

QColor NodePortView::uncompatibleColor() const
{
    return m_uncompatibleColor;
}

void NodePortView::setUncompatibleColor(const QColor &uncompatibleColor)
{
    m_uncompatibleColor = uncompatibleColor;
}

char *NodePortView::signal() const
{
    return m_signal;
}

void NodePortView::setSignal(char *signal)
{
    m_signal = signal;
}

QObject *NodePortView::object() const
{
    return m_object;
}

void NodePortView::setObject(QObject *object)
{
    m_object = object;
}

QString NodePortView::name() const
{
    return m_name;
}

void NodePortView::setName(const QString &name)
{
    m_name = name;
    setToolTip(m_name);
}

QString NodePortView::componentId() const
{
    return m_componentId;
}

void NodePortView::setComponentId(const QString &componentId)
{
    m_componentId = componentId;
}

unsigned int NodePortView::getNodeIndex() const
{
    return m_node->index();
}

QList<NodeLinkView *> NodePortView::getLinks() const
{
    return m_links;
}

}
