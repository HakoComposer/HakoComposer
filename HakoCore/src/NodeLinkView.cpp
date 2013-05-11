/*
*  Copyright (c) HakoComposer & Mehrez Kristou (kristou.com), distributed
*  as-is and without warranty under the MIT License. See
*  [root]/license.txt for more. This information must remain intact.
*  This file is partly a modified version of the one in https://github.com/nical/kiwi
*/

#include "NodeLinkView.hpp"
#include <QPainter>
#include <QGraphicsScene>
#include <QCursor>
#include <QPropertyAnimation>
#include <QDebug>

namespace Hako {

NodeLinkView::NodeLinkView(PortTypeEnum type, NodePortView* p1, NodePortView* p2, QGraphicsItem *parent):
    QGraphicsObject(parent),
    m_color(QColor(Qt::blue)),
    m_signalMapper(new QSignalMapper(this))
{
    setFlag(QGraphicsItem::ItemIsSelectable);
    setCursor(QCursor(Qt::ArrowCursor));
    setAcceptHoverEvents(true);

    QObject::connect(m_signalMapper, SIGNAL(mapped(int)),
                 this, SLOT(signalActivated(int)));

    if(!p1){qWarning() << "NodeLinkView::constructor warning p1 = nil ptr";}
    if(!p2){qWarning() << "NodeLinkView::constructor warning p2 = nil ptr";}

    m_type = type;
    if( p1->portType() & INPUT ){
        m_inPort = p1;
        m_outPort = p2;
    }else{
        m_inPort = p2;
        m_outPort = p1;
    }

    connectSignals();
}

void NodeLinkView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setPen( QPen(m_color, 3) );
    painter->drawPath( shape() );
}

QRectF NodeLinkView::boundingRect() const
{
    return QRectF( m_outPort->pos(), m_inPort->pos());
}

void NodeLinkView::updatePosition( PortTypeEnum type, const QPointF& position )
{
    if(type & OUTPUT){
        setPos( position );
    }
}

void NodeLinkView::connectSignals()
{
    if(inPort()->object() && outPort()->object()){
        if(inPort()->signal() && outPort()->signal()){
            if(!outPort()->isTemporary && !inPort()->isTemporary){
                QObject::connect(outPort()->object(), outPort()->signal(),
                                 inPort()->object(), inPort()->signal());
                QObject::connect(outPort()->object(), outPort()->signal(), m_signalMapper, SLOT(map()));
                m_signalMapper->setMapping(outPort()->object(), 0);
            }
        }
    }
}

void NodeLinkView::disconnectSignals()
{
    if(inPort()->object() && outPort()->object()){
        if(inPort()->signal() && outPort()->signal()){
            if(!outPort()->isTemporary && !inPort()->isTemporary){
                QObject::disconnect(outPort()->object(), outPort()->signal(),
                                    inPort()->object(), inPort()->signal());
                QObject::disconnect(outPort()->object(), outPort()->signal(), m_signalMapper, SLOT(map()));
                m_signalMapper->removeMappings(outPort()->object());
            }
        }
    }
}

void NodeLinkView::signalActivated(int index)
{
    Q_UNUSED(index);
    QPropertyAnimation *animation = new QPropertyAnimation(this, "color");
    animation->setDuration(250);
    animation->setStartValue(QColor(Qt::green));
    animation->setEndValue(m_color);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void NodeLinkView::setPorts( NodePortView* in, NodePortView* out)
{
    m_inPort = in;
    m_outPort = out;
    connectSignals();
}

QPainterPath NodeLinkView::shape() const
{
    QPointF p1, p2, c1, c2;

    p1 = m_outPort->pos();
    p2 = m_inPort->pos();

    if(((m_inPort->portType() & WRITER) == WRITER) &&
            ((m_outPort->portType() & WRITER) == WRITER)){
        c1 = QPointF(m_outPort->pos().x(), (m_inPort->pos().y()+m_outPort->pos().y() )/2.0);
        c2 = QPointF(m_inPort->pos().x(), (m_inPort->pos().y()+m_outPort->pos().y() )/2.0);
    }else if(((m_inPort->portType() & READER) == READER) &&
             ((m_outPort->portType() & READER) == READER)){
        c1 = QPointF((m_inPort->pos().x()+m_outPort->pos().x() )/2.0, m_outPort->pos().y());
        c2 = QPointF((m_inPort->pos().x()+m_outPort->pos().x() )/2.0, m_inPort->pos().y());
    }

    QPainterPath path( m_outPort->pos() );
    path.cubicTo( c1, c2, p2 );
    return path;
}

void NodeLinkView::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
    event->accept();
}

void NodeLinkView::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseMoveEvent(event);
}

void NodeLinkView::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);
    if(event->button() == Qt::RightButton){
        delete this;
    }
}

void NodeLinkView::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    QGraphicsItem::hoverEnterEvent(event);
    setColor(QColor(Qt::red));
}

void NodeLinkView::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    QGraphicsItem::hoverLeaveEvent(event);
    setColor(QColor(Qt::blue));
}

NodeLinkView::~NodeLinkView()
{
    m_inPort->disconnectLink(this);
    m_outPort->disconnectLink(this);
    disconnectSignals();
}

QColor NodeLinkView::color() const
{
    return m_color;
}

void NodeLinkView::setColor(const QColor &color)
{
    m_color = color;
    update();
}

}
