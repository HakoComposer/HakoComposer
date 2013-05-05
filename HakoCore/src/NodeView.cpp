/*
*  Copyright (c) HakoComposer & Mehrez Kristou (kristou.com), distributed
*  as-is and without warranty under the MIT License. See
*  [root]/license.txt for more. This information must remain intact.
*  This file is partly a modified version of the one in https://github.com/nical/kiwi
*/

#include "NodeView.hpp"
#include <QPainter>
#include <QLinearGradient>

#include "NodePortView.hpp"
#include <QGraphicsScene>
#include <QPropertyAnimation>
#include <QIcon>
#include <QCursor>
#include <QDebug>

namespace Hako {

//#define SHOW_NODE_INDEX

NodeButton::NodeButton(const QPixmap& pixmap, QGraphicsItem *parentItem,  QObject *parentObject):
    QObject(parentObject),
    QGraphicsPixmapItem(pixmap, parentItem)
{
    setFlag(QGraphicsPixmapItem::ItemIsSelectable);
    setCursor(QCursor(Qt::ArrowCursor));
}

void NodeButton::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsPixmapItem::mouseReleaseEvent(event);
    emit clicked(event->screenPos());
}

void NodeButton::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsPixmapItem::mousePressEvent(event);
}

void NodeButton::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawPixmap(offset(), pixmap());
}

NodeView::NodeView(QGraphicsItem *parent):
    QGraphicsObject(parent),
    m_closeButton(NULL),
    m_settingsButton(NULL),
    m_menuButton(NULL),
    m_index(0)
{
    initNode(QPointF(0, 0), 0, 0, 0, 0);
}

NodeView::NodeView(const QPointF& position
                   , unsigned int nbReaderInputs
                   , unsigned int nbReaderOutputs
                   , unsigned int nbWriterInputs
                   , unsigned int nbWriterOutputs
                   , QGraphicsItem *parent):
    QGraphicsObject(parent),
    m_closeButton(NULL),
    m_settingsButton(NULL),
    m_menuButton(NULL),
    m_index(0)
{
    initNode(position, nbReaderInputs, nbReaderOutputs, nbWriterInputs, nbWriterOutputs);
}

NodeView::~NodeView()
{
    removeAllPorts();
}

void NodeView::removeAllPorts()
{
    qDeleteAll(m_readerInputPorts);
    m_readerInputPorts.clear();
    qDeleteAll(m_readerOutputPorts);
    m_readerOutputPorts.clear();
    qDeleteAll(m_writerInputPorts);
    m_writerInputPorts.clear();
    qDeleteAll(m_writerOutputPorts);
    m_writerOutputPorts.clear();
}

void NodeView::initNode( const QPointF& position
                         , unsigned int nbReaderInputs
                         , unsigned int nbReaderOutputs
                         , unsigned int nbWriterInputs
                         , unsigned int nbWriterOutputs )
{
    setFlags(QGraphicsItem::ItemIsMovable /*|QGraphicsItem::ItemIsSelectable*/);
    setAcceptHoverEvents(true);

    setPos( position );
    m_nameMargin = 30.0;
    m_portYOffset = 40.0;

    m_closeButton = new NodeButton(QPixmap(":/HakoCore/close"), this);
    m_closeButton->setToolTip("Delete the component");
    m_closeButton->setOpacity(0.0);

    m_settingsButton = new NodeButton(QPixmap(":/HakoCore/settings"), this);
    m_settingsButton->setToolTip("Open settings");
    m_settingsButton->setOpacity(0.0);

    m_menuButton = new NodeButton(QPixmap(":/HakoCore/menu"), this);
    m_menuButton->setToolTip("Show component menu");
    m_menuButton->setOpacity(0.0);
    m_menuButton->hide();

    QObject::connect(m_closeButton, SIGNAL(clicked(const QPoint &)),
                     this, SIGNAL(closeClicked(const QPoint &)));
    QObject::connect(m_settingsButton, SIGNAL(clicked(const QPoint &)),
                     this, SIGNAL(settingsClicked(const QPoint &)));
    QObject::connect(m_menuButton, SIGNAL(clicked(const QPoint &)),
                     this, SIGNAL(menuClicked(const QPoint &)));

    m_dropShadow.setBlurRadius( 16 );
    m_dropShadow.setXOffset( 0.0 );
    m_dropShadow.setYOffset( 5.0 );

    setGraphicsEffect( &m_dropShadow );

    initPorts(nbReaderInputs, nbReaderOutputs, nbWriterInputs, nbWriterOutputs);

    updateGeometry();
}

void NodeView::updateGeometry()
{
    QFont font;
    QFontMetrics fm(font);
    int nameWidth = fm.width(componentName()
                         #ifdef SHOW_NODE_INDEX
                             + " #" + QString::number(m_index)
                         #endif
                             );

    // to finish

    double nodeWidth = qMax(nameWidth + m_nameMargin *2, 100.0);
    nodeWidth = qMax(nodeWidth, 35.0 + (20.0 * m_writerInputPorts.size()));
    nodeWidth = qMax(nodeWidth, 35.0 + (20.0 * m_writerOutputPorts.size()));

    double nodeHeight = qMax(m_portYOffset + (m_readerInputPorts.size() * 20.0), 120.0);
    nodeHeight = qMax(nodeHeight, m_portYOffset + (m_readerOutputPorts.size() * 20.0));

    prepareGeometryChange();

    m_rect = QRectF( 0, 0, nodeWidth, nodeHeight );

    if(m_closeButton){
        m_closeButton->setPos(m_rect.width() -m_closeButton->boundingRect().width() - 5, 5);
    }
    if(m_settingsButton){
        m_settingsButton->setPos(5, m_rect.height() -m_settingsButton->boundingRect().height() -5);
    }
    if(m_menuButton){
        m_menuButton->setPos(5, 5);
    }

    update();

    updatePortsPosition();
}

void NodeView::updatePortsPosition()
{
    foreach(NodePortView* item, m_readerInputPorts){
        item->updatePosition();
    }

    foreach(NodePortView* item, m_readerOutputPorts){
        item->updatePosition();
    }

    foreach(NodePortView* item, m_writerInputPorts){
        item->updatePosition();
    }

    foreach(NodePortView* item, m_writerOutputPorts){
        item->updatePosition();
    }
}

void NodeView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QLinearGradient gradient( 0.0, 0.0, 0.0, m_rect.bottom() );
    gradient.setColorAt( 1, componentColor() );
    gradient.setColorAt( 0, Qt::white );
    painter->setBrush( gradient );
//    painter->setPen( QPen( Qt::transparent ) );
    painter->setPen( QPen( componentColor() ) );
    painter->drawRoundedRect( m_rect, 10, 10 );
    painter->setPen( QPen( QColor(Qt::black) ) );
    painter->drawText( QPointF(m_nameMargin, 20), componentName()
                   #ifdef SHOW_NODE_INDEX
                       + " #" + QString::number(m_index)
                   #endif
                       );

    QPointF picturePos;
    picturePos.setX((m_rect.width() /2) - (componentIcon().pixmap(32, 32).width() /2));
    picturePos.setY(m_rect.height() - 20 - componentIcon().pixmap(32, 32).height());
    painter->drawPixmap(picturePos, componentIcon().pixmap(32, 32));
}

QVariant NodeView::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    updateGeometry();
    return QGraphicsItem::itemChange(change, value);
}

void NodeView::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    QGraphicsObject::hoverEnterEvent(event);
    showButton(m_closeButton);
    showButton(m_settingsButton);
    showButton(m_menuButton);
}

void NodeView::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    QGraphicsObject::hoverMoveEvent(event);
}

void NodeView::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    QGraphicsObject::hoverLeaveEvent(event);
    hideButton(m_closeButton);
    hideButton(m_settingsButton);
    hideButton(m_menuButton);
}

void NodeView::showButton(NodeButton *button)
{
    QPropertyAnimation *animation = new QPropertyAnimation(button, "opacity");
    animation->setDuration(250);
    animation->setStartValue(0.0);
    animation->setEndValue(1.0);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void NodeView::hideButton(NodeButton *button)
{
    QPropertyAnimation *animation = new QPropertyAnimation(button, "opacity");
    animation->setDuration(250);
    animation->setStartValue(1.0);
    animation->setEndValue(0.0);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

QRectF NodeView::boundingRect() const
{
    return m_rect;
}

QPointF NodeView::PortPosition( PortTypeEnum type, unsigned int index)
{
    Q_UNUSED(type);

    QPointF result( pos() );
    result += QPointF( m_rect.left(), m_portYOffset + index * 15 );
    return result;
}

void NodeView::initPorts( unsigned int nbReaderInputs
                          , unsigned int nbReaderOutputs
                          , unsigned int nbWriterInputs
                          , unsigned int nbWriterOutputs )
{

    removeAllPorts();

    for( unsigned int i = 0; i < nbReaderInputs; ++i){
        NodePortView *port = new NodePortView( this, READER_INPUT, i );
        port->setComponentId(componentId());
        m_readerInputPorts.append(port);
    }

    for( unsigned int i = 0; i < nbReaderOutputs; ++i){
        NodePortView *port = new NodePortView( this, READER_OUTPUT, i );
        port->setComponentId(componentId());
        m_readerOutputPorts.append(port);
    }

    for( unsigned int i = 0; i < nbWriterInputs; ++i){
        NodePortView *port = new NodePortView( this, WRITER_INPUT, i );
        port->setComponentId(componentId());
        m_writerInputPorts.append(port);
    }

    for( unsigned int i = 0; i < nbWriterOutputs; ++i){
        NodePortView *port = new NodePortView( this, WRITER_OUTPUT, i );
        port->setComponentId(componentId());
        m_writerOutputPorts.append(port);
    }
}

void NodeView::mouseMoveEvent( QGraphicsSceneMouseEvent* event )
{
    // call the parent implementation to keep the frag behavior
    QGraphicsItem::mouseMoveEvent( event );

    //update each port's position
    updatePortsPosition();
}

void NodeView::addToWorkspace( QGraphicsScene* scene )
{
    scene->addItem(this);
    for( int i = 0; i < m_readerInputPorts.size(); ++i){
        scene->addItem( m_readerInputPorts[i] );
    }

    for( int i = 0; i < m_readerOutputPorts.size(); ++i){
        scene->addItem( m_readerOutputPorts[i] );
    }

    for( int i = 0; i < m_writerInputPorts.size(); ++i){
        scene->addItem( m_writerInputPorts[i] );
    }

    for( int i = 0; i < m_writerOutputPorts.size(); ++i){
        scene->addItem( m_writerOutputPorts[i] );
    }
}

NodePortView* NodeView::port(PortTypeEnum type, unsigned int index)
{
    switch(type){
    case READER_INPUT: return m_readerInputPorts[index];
    case READER_OUTPUT: return m_readerOutputPorts[index];
    case WRITER_INPUT: return m_writerInputPorts[index];
    case WRITER_OUTPUT: return m_writerOutputPorts[index];
    default: return 0;
    }
}

int NodeView::addPort(PortTypeEnum type, QObject *sender, char *signal, const QString &name)
{
    int portIndex = -1;
    NodePortView* port = NULL;
    switch(type){
    case READER_INPUT:{
        port = new NodePortView( this, READER_INPUT, m_readerInputPorts.size() );
        portIndex = m_readerInputPorts.size();
        m_readerInputPorts.append( port );
        if(scene()) scene()->addItem(port);
    } break;
    case READER_OUTPUT:{
        port = new NodePortView( this, READER_OUTPUT, m_readerOutputPorts.size() );
        portIndex = m_readerOutputPorts.size();
        m_readerOutputPorts.append( port );
        if(scene()) scene()->addItem(port);
    } break;
    case WRITER_INPUT:{
        port = new NodePortView( this, WRITER_INPUT, m_writerInputPorts.size() );
        portIndex = m_writerInputPorts.size();
        m_writerInputPorts.append( port );
        if(scene()) scene()->addItem(port);
    } break;
    case WRITER_OUTPUT:{
        port = new NodePortView( this, WRITER_OUTPUT, m_writerOutputPorts.size() );
        portIndex = m_writerOutputPorts.size();
        m_writerOutputPorts.append( port );
        if(scene()) scene()->addItem(port);
    } break;
    default:{
        ;
    }break;
    }

    if(port){
        port->setObject(sender);
        port->setSignal(signal);
        port->setName(name);
        port->setComponentId(componentId());
    }

    updateGeometry();

    return portIndex;
}

int NodeView::portCount(PortTypeEnum type)
{
    switch(type){
    case READER_INPUT:{ return m_readerInputPorts.size(); }
    case READER_OUTPUT:{ return m_readerOutputPorts.size(); }
    case WRITER_INPUT:{ return m_writerInputPorts.size(); }
    case WRITER_OUTPUT:{ return m_writerOutputPorts.size(); }
    default:{ return 0; }
    }

}

double NodeView::portYOffset() const
{
    return m_portYOffset;
}

void NodeView::setPortYOffset(double portYOffset)
{
    m_portYOffset = portYOffset;
}

QString NodeView::componentName() const
{
    return "";
}

QIcon NodeView::componentIcon() const
{
    return QIcon(":/HakoCore/unknown");
}

QString NodeView::componentId() const
{
    return "";
}

QColor NodeView::componentColor() const
{
    return QColor(Qt::gray);
}

void NodeView::componentGotConnected()
{

}

void NodeView::setCloseButtonVisible(bool state)
{
    if(m_closeButton){
        m_closeButton->setVisible(state);
    }
}

void NodeView::setSettingsButtonVisible(bool state)
{
    if(m_settingsButton){
        m_settingsButton->setVisible(state);
    }
}

void NodeView::setMenuButtonVisible(bool state)
{
    if(m_menuButton){
        m_menuButton->setVisible(state);
    }
}

unsigned int NodeView::index() const
{
    return m_index;
}

void NodeView::setIndex(unsigned int index)
{
    m_index = index;
    update();
}

QList<NodeLinkView *> NodeView::getLinks()
{
    QList<NodeLinkView *> links;
    for( int i = 0; i < m_readerInputPorts.size(); ++i){
        links.append(m_readerInputPorts[i]->getLinks());
    }

    for( int i = 0; i < m_readerOutputPorts.size(); ++i){
        links.append( m_readerOutputPorts[i]->getLinks());
    }

    for( int i = 0; i < m_writerInputPorts.size(); ++i){
        links.append( m_writerInputPorts[i]->getLinks());
    }

    for( int i = 0; i < m_writerOutputPorts.size(); ++i){
        links.append( m_writerOutputPorts[i]->getLinks());
    }

    return links;
}

}
