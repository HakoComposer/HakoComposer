#ifndef LINKCONNECTORVIEW_H
#define LINKCONNECTORVIEW_H

#include <QGraphicsObject>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QWidget>
#include <QRectF>

class LinkConnectorView : public QGraphicsObject
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor)
    Q_PROPERTY(QRectF rect READ rect WRITE setRect)
public:
    LinkConnectorView(QGraphicsItem * parent = 0);
    virtual ~LinkConnectorView();

    QRectF rect() const;
    void setRect(const QRectF &rect);

    QColor color() const;
    void setColor(const QColor &color);

signals:
    void positionChanged();

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);


private:
    QRectF m_rect;
    QColor m_color;
};

#endif // LINKCONNECTORVIEW_H
