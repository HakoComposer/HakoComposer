/*
*  Copyright (c) HakoComposer & Mehrez Kristou (kristou.com), distributed
*  as-is and without warranty under the MIT License. See
*  [root]/license.txt for more. This information must remain intact.
*  This file is partly a modified version of the one in https://github.com/nical/kiwi
*/

#ifndef TEMPORARYPORTVIEW_HPP
#define TEMPORARYPORTVIEW_HPP

#include "NodePortView.hpp"

namespace Hako {

class TemporaryPortView : public NodePortView
{
    Q_OBJECT
public:
    TemporaryPortView( PortTypeEnum type, const QPointF& position, QGraphicsItem *parent = 0 );
    void updatePosition();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    NodePortView *getNearestPort(double closestDist);
    double snapDistance() const;
    void setSnapDistance(double snapDistance);

protected:
    void mouseReleaseEvent( QGraphicsSceneMouseEvent* event );

private:
    double m_snapDistance;
};

}

#endif // TEMPORARYPORTVIEW_HPP
