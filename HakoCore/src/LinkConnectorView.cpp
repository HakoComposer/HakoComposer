#include "linkconnectorview.h"

LinkConnectorView::LinkConnectorView(QGraphicsItem *parent):
    QGraphicsObject(parent),
    m_rect(-5, -5, 10, 10),
    m_color(Qt::black)
{
    setFlags(QGraphicsItem::ItemIsMovable);
    setCursor(Qt::CrossCursor);
}

LinkConnectorView::~LinkConnectorView()
{

}

QRectF LinkConnectorView::boundingRect() const
{
    return m_rect;
}
QColor LinkConnectorView::color() const
{
    return m_color;
}

void LinkConnectorView::setColor(const QColor &color)
{
    if(m_color != color){
        m_color = color;
        update();
        emit colorChanged(color);
    }
}


QRectF LinkConnectorView::rect() const
{
    return m_rect;
}

void LinkConnectorView::setRect(const QRectF &rect)
{
    if(m_rect != rect){
        m_rect = rect;
        update();
        emit rectChanged(rect);
    }
}

void LinkConnectorView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->setBrush(QBrush(m_color));
    painter->drawEllipse(m_rect);
}

QVariant LinkConnectorView::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemPositionHasChanged) {
        emit positionChanged();
    }
    return QGraphicsObject::itemChange(change, value);
}
