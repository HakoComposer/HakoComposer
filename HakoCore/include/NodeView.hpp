/*
*  Copyright (c) HakoComposer & Mehrez Kristou (kristou.com), distributed
*  as-is and without warranty under the MIT License. See
*  [root]/license.txt for more. This information must remain intact.
*  This file is partly a modified version of the one in https://github.com/nical/kiwi
*/

#ifndef NODEVIEW_HPP
#define NODEVIEW_HPP

#include <QGraphicsObject>
#include <QRectF>
#include <QGraphicsDropShadowEffect>
#include <QGraphicsPixmapItem>
#include <QList>
#include "NodePortView.hpp"

namespace Hako {

class NodeButton: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity)
public:
    explicit NodeButton(const QPixmap &pixmap, QGraphicsItem *parentItem = 0, QObject *parentObject = 0);

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

signals:
    void clicked(const QPoint &pos);
};

class NodeView : public QGraphicsObject
{
    Q_OBJECT
    Q_PROPERTY(QColor baseColor READ baseColor WRITE setBaseColor NOTIFY baseColorChanged)
public:

    explicit NodeView(QGraphicsItem *parent = 0);
    explicit NodeView( const QPointF& position
            , unsigned int nbReaderInputs = 0
            , unsigned int nbReaderOutputs = 0
            , unsigned int nbWriterInputs = 0
            , unsigned int nbWriterOutputs = 0.
            , QGraphicsItem *parent = 0);
    virtual ~NodeView();

    QPointF PortPosition( PortTypeEnum type, unsigned int index );
    void removeAllPorts();
    void initPorts(  unsigned int nbReaderInputs = 0
            , unsigned int nbReaderOutputs = 0
            , unsigned int nbWriterInputs = 0
            , unsigned int nbWriterOutputs = 0 );

    void addToWorkspace( QGraphicsScene* scene );

    NodePortView* port(PortTypeEnum type, unsigned int index);
    int addPort(PortTypeEnum type, QObject *sender, char *signal, const QString &name = "");
    int portCount(PortTypeEnum type);
    QRectF boundingRect() const;

    double portYOffset() const;
    void setPortYOffset(double portYOffset);

    virtual QString componentName() const;

    virtual QIcon componentIcon() const;

    virtual QString componentId() const;

    virtual QColor componentColor() const;

    virtual void componentGotConnected();

    void setCloseButtonVisible(bool state);
    void setSettingsButtonVisible(bool state);
    void setMenuButtonVisible(bool state);

    unsigned int index() const;
    void setIndex(unsigned int index);

    QList<NodeLinkView *> getLinks();

    QColor baseColor() const;

public slots:
    void setBaseColor(QColor arg);
    void flash(QColor color, int duration);

signals:
    void closeClicked(const QPoint &pos);
    void settingsClicked(const QPoint &pos);
    void menuClicked(const QPoint &pos);
    void baseColorChanged(QColor arg);

protected:
    void mouseMoveEvent( QGraphicsSceneMouseEvent * event );
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

private:
    void initNode( const QPointF& position
                   , unsigned int nbReaderInputs = 0
            , unsigned int nbReaderOutputs = 0
            , unsigned int nbWriterInputs = 0
            , unsigned int nbWriterOutputs = 0 );


    QRectF m_rect;
    QGraphicsDropShadowEffect m_dropShadow;
    QList<NodePortView*> m_readerInputPorts;
    QList<NodePortView*> m_readerOutputPorts;
    QList<NodePortView*> m_writerInputPorts;
    QList<NodePortView*> m_writerOutputPorts;
    double m_portYOffset;
    double m_nameMargin;
    NodeButton *m_closeButton;
    NodeButton *m_settingsButton;
    NodeButton *m_menuButton;
    unsigned int m_index;
    QColor m_baseColor;

    void updateGeometry();
    void updatePortsPosition();
    void showButton(NodeButton *button);
    void hideButton(NodeButton *button);
};

}

#endif // NODEVIEW_HPP
