/*
*  Copyright (c) HakoComposer & Mehrez Kristou (kristou.com), distributed
*  as-is and without warranty under the MIT License. See
*  [root]/license.txt for more. This information must remain intact.
*  This file is partly a modified version of the one in https://github.com/nical/kiwi
*/

#include "TemporaryPortView.hpp"
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include "NodeLinkView.hpp"
#include <iostream>
#include <QPainter>

namespace Hako {

TemporaryPortView::TemporaryPortView(PortTypeEnum type, const QPointF& position , QGraphicsItem *parent)
    : NodePortView( type, parent ),
      m_snapDistance(100)
{
    isTemporary = true;
    setFlag( QGraphicsItem::ItemIsMovable );
    setPos( position );
}

NodePortView* TemporaryPortView::getNearestPort(double closestDist)
{
    NodePortView* toConnect = 0;
    foreach( QGraphicsItem* qItm, collidingItems() ){
        NodePortView* itm = dynamic_cast<NodePortView*>(qItm);

        bool compatible = false;
        if(itm && itm->object() && itm->signal()){
            int methodIndex = itm->object()->metaObject()->indexOfMethod(QMetaObject::normalizedSignature(itm->signal()+1));
            if(methodIndex >= 0){
                QMetaMethod myMethod = itm->object()->metaObject()->method(methodIndex);
                compatible = isCompatible(myMethod);
            }
        }

        if( compatible && (itm->portType() == this->portType()) ){
            double distance = (pos() - itm->pos()).manhattanLength();
            if( distance < closestDist ){
                closestDist = distance;
                toConnect = itm;
            }
        }
    }

    return toConnect;
}

void TemporaryPortView::mouseReleaseEvent( QGraphicsSceneMouseEvent* event )
{
    QGraphicsItem::mouseReleaseEvent( event );
    this->ungrabMouse();

    NodePortView* toConnect = getNearestPort(m_snapDistance);
    if( toConnect){
        if( portType() & INPUT ){
            NodePortView* out = m_links.front()->outPort();
            if(!toConnect->connectPort( out )){
                std::cerr << "error: could not connect ports\n";
            }
        }else{
            NodePortView* in = m_links.front()->inPort();
            if( !toConnect->connectPort( in ) ){
                std::cerr << "error: could not connect ports\n";
            }
        }
    }

    delete m_links.front();

    delete this;

}

void TemporaryPortView::updatePosition()
{
    // do nothing
}

void TemporaryPortView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    NodePortView* toConnect = getNearestPort(m_snapDistance);
    if(toConnect)
    {
        painter->setPen( QPen(QColor(50,50,255, 100),3) );
        painter->drawLine( QPointF(0,0), toConnect->pos() - pos() );
    }
    //painter->setBrush( Qt::transparent );
    //painter->drawRect( boundingRect() );
}

QRectF TemporaryPortView::boundingRect() const
{
    return QRectF( -30, -30, 60, 60 );
}

double TemporaryPortView::snapDistance() const
{
    return m_snapDistance;
}

void TemporaryPortView::setSnapDistance(double snapDistance)
{
    m_snapDistance = snapDistance;
}

}
