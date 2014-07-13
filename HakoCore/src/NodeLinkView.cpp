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
                m_signalMapper->removeMappings(outPort()->object());
                QObject::disconnect(outPort()->object(), outPort()->signal(),
                                    inPort()->object(), inPort()->signal());
                QObject::disconnect(outPort()->object(), outPort()->signal(), m_signalMapper, SLOT(map()));
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

void NodeLinkView::connectorsPositionChanged()
{
    update();
}

void NodeLinkView::setPorts( NodePortView* in, NodePortView* out)
{
    m_inPort = in;
    m_outPort = out;
    connectSignals();
}

QPainterPath NodeLinkView::shape() const
{
    QPointF p1, p2;
    QPainterPath path( m_outPort->pos() );

    p1 = m_outPort->pos();
    QVector<int> indexes;
    for(int i= 0; i< m_connectors.size(); i++) indexes.push_back(i);
    qSort(indexes.begin(), indexes.end(), [=](int a, int b) -> bool{
        if(m_connectors[a]->pos().x() == m_connectors[b]->pos().x()){
            return m_connectors[a]->pos().y() < m_connectors[b]->pos().y();
        }else{
            return m_connectors[a]->pos().x() < m_connectors[b]->pos().x();
        }
    });
    foreach(int index, indexes){
        p2 = m_connectors[index]->scenePos();
        connectFromTo(p1, p2, path);
        p1 = m_connectors[index]->scenePos();
    }

    p2 = m_inPort->pos();
    connectFromTo(p1, p2, path);

    return path;
}

void NodeLinkView::connectFromTo(const QPointF &p1, const QPointF &p2, QPainterPath &path) const
{
    QPointF c1, c2;
    if(((m_inPort->portType() & WRITER) == WRITER) &&
            ((m_outPort->portType() & WRITER) == WRITER)){
        c1 = QPointF(p1.x(), (p2.y()+p1.y() )/2.0);
        c2 = QPointF(p2.x(), (p2.y()+p1.y() )/2.0);
    }else if(((m_inPort->portType() & READER) == READER) &&
             ((m_outPort->portType() & READER) == READER)){
        c1 = QPointF((p2.x()+p1.x() )/2.0, p1.y());
        c2 = QPointF((p2.x()+p1.x() )/2.0, p2.y());
    }

    //    path.cubicTo( c1, c2, p2 );
    path.lineTo(c1);
    path.lineTo(c2);
    path.lineTo(p2);
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

void NodeLinkView::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    LinkConnectorView *con = new LinkConnectorView(this);
    con->setPos(event->scenePos());
    connect(con, SIGNAL(positionChanged()),
            this, SLOT(connectorsPositionChanged()));
    m_connectors.push_back(con);
}

NodeLinkView::~NodeLinkView()
{
    disconnectSignals();
    m_inPort->disconnectLink(this);
    m_outPort->disconnectLink(this);
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
