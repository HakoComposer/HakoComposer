/*
*  Copyright (c) HakoComposer & Mehrez Kristou (kristou.com), distributed
*  as-is and without warranty under the MIT License. See
*  [root]/license.txt for more. This information must remain intact.
*  This file is partly a modified version of the one in https://github.com/nical/kiwi
*/

#ifndef NODELINKVIEW_HPP
#define NODELINKVIEW_HPP

#include <QGraphicsObject>
#include <QSignalMapper>
#include "NodePortView.hpp"

namespace Hako {

class NodeLinkView : public QGraphicsObject
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor)
public:
    NodeLinkView( PortTypeEnum type, NodePortView* out, NodePortView* in, QGraphicsItem *parent = 0 );
    virtual ~NodeLinkView();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    PortTypeEnum portType() const { return m_type; }
    void updatePosition( PortTypeEnum type, const QPointF& pos );
    NodePortView* inPort() const { return m_inPort; }
    NodePortView* outPort() const { return m_outPort; }
    void setPorts( NodePortView* in, NodePortView* out);

    QColor color() const;
    void setColor(const QColor &color);

protected:
    QPainterPath shape() const;
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

private:
    PortTypeEnum m_type;
    NodePortView* m_outPort;
    NodePortView* m_inPort;
    QColor m_color;
    QSignalMapper *m_signalMapper;

    void connectSignals();
    void disconnectSignals();

private slots:
    void signalActivated(int index);
};

}

#endif // NODELINKVIEW_HPP
