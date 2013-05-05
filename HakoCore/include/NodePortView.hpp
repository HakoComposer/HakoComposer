/*
*  Copyright (c) HakoComposer & Mehrez Kristou (kristou.com), distributed
*  as-is and without warranty under the MIT License. See
*  [root]/license.txt for more. This information must remain intact.
*  This file is partly a modified version of the one in https://github.com/nical/kiwi
*/

#ifndef NODEPORTVIEW_HPP
#define NODEPORTVIEW_HPP

#include <QGraphicsObject>
#include <QPointF>
#include <QGraphicsSceneMouseEvent>
#include <QObject>
#include <QMetaMethod>

namespace Hako {

class NodeView;
class NodeLinkView;

enum PortTypeEnum{
       UNKNOWN = 0x0
     , READER = 0x1
     , WRITER = 0x2
     , INPUT = 0x4
     , OUTPUT = 0x8
     , READER_INPUT = READER | INPUT
     , READER_OUTPUT = READER | OUTPUT
     , WRITER_INPUT = WRITER | INPUT
     , WRITER_OUTPUT = WRITER | OUTPUT
     , INPUT_OUTPUT_MASK = INPUT | OUTPUT
     , READER_WRITER_MASK = READER | WRITER
};

inline PortTypeEnum operator&(PortTypeEnum lhs, PortTypeEnum rhs){
    return static_cast<PortTypeEnum>(static_cast<int>(lhs) & static_cast<int>(rhs) );
}
inline PortTypeEnum operator|(PortTypeEnum lhs, PortTypeEnum rhs){
    return static_cast<PortTypeEnum>(static_cast<int>(lhs) | static_cast<int>(rhs) );
}

class NodePortView : public QGraphicsObject
{
    Q_OBJECT
public:
    NodePortView( NodeView* node, PortTypeEnum type, unsigned int index, QGraphicsItem *parent = 0 );
    virtual ~NodePortView();

    static QString printNodeType( PortTypeEnum type);

    void deleteLink( NodeLinkView* link = 0 );

    PortTypeEnum portType() const { return m_type; }
    unsigned int index() const { return m_index; }
    virtual void updatePosition();
    bool connectPort( NodePortView* p );
    bool isCompatible( PortTypeEnum pType ) const;
    bool isCompatible(NodePortView *port) const;
    bool isConnected(NodePortView *p = NULL) const;
    bool isCompatible(QMetaMethod method) const;
    void disconnectLink(NodeLinkView *link);
    void addLink(NodeLinkView *link);

    QColor normalColor() const;
    void setNormalColor(const QColor &normalColor);

    QColor connectedColor() const;
    void setConnectedColor(const QColor &connectedColor);

    QColor compatibleColor() const;
    void setCompatibleColor(const QColor &compatibleColor);

    QColor uncompatibleColor() const;
    void setUncompatibleColor(const QColor &uncompatibleColor);

    char *signal() const;
    void setSignal(char *signal);

    QObject *object() const;
    void setObject(QObject *object);

    bool isTemporary;

    QString name() const;
    void setName(const QString &name);

    QString componentId() const;
    void setComponentId(const QString &componentId);

    unsigned int getNodeIndex() const;
    QList<NodeLinkView*> getLinks() const;

protected:
    NodePortView(PortTypeEnum type, QGraphicsItem *parent = 0 );
    void mousePressEvent( QGraphicsSceneMouseEvent * event );
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    QList<NodeLinkView*> m_links;

private:
    QPointF m_pos;
    NodeView* m_node;
    PortTypeEnum m_type;
    unsigned int m_index;
    QColor m_normalColor;
    QColor m_connectedColor;
    QColor m_compatibleColor;
    QColor m_uncompatibleColor;
    bool m_dragging;
    bool m_compatible;
    char *m_signal;
    QObject *m_object;
    QString m_name;
    QString m_componentId;

    QColor getPortColor();
};

}
#endif // NODEPORTVIEW_HPP
