/*
*  Copyright (c) HakoComposer & Mehrez Kristou (kristou.com), distributed
*  as-is and without warranty under the MIT License. See
*  [root]/license.txt for more. This information must remain intact.
*/

#include "SerialComponent.hpp"
#include <QDebug>

namespace Hako {

SerialComponent::SerialComponent(QGraphicsItem *parent):
    Component(parent)
{
    setupComponent();

    m_settingDialog = new SerialSettingsDialog();
    m_settingDialog->setConnection(&m_connection);

    connect(&m_connection, SIGNAL(readyRead()), this, SLOT(onReadyRead()));

    //    QMenu *menu = new QMenu();
    //    menu->addAction(new QAction("Open", menu));
    //    setMenu(menu);
}

SerialComponent::~SerialComponent()
{
    delete m_settingDialog;
}

void SerialComponent::setupComponent()
{
    registerOutput(COMPONENT_SIGNAL(dataAvailable(const QByteArray &)), "RX");
    registerInput(COMPONENT_SLOT(sendData(const QByteArray &)), "TX");
}

void SerialComponent::settingsActivated()
{
    m_settingDialog->show();
    m_settingDialog->raise();
}

QString SerialComponent::componentName() const
{
    return "Serial";
}

QIcon SerialComponent::componentIcon() const
{
    return QIcon(":/Serial/logo");
}

QString SerialComponent::componentId() const
{
    return "com.kristou.components.Serial";
}

QString SerialComponent::componentDescription() const
{
    return "A Component to communication with the serial port.";
}

QString SerialComponent::componentCategory() const
{
    return "/Communication";
}

QString SerialComponent::componentAuthor() const
{
    return "Mehrez Kristou";
}

QString SerialComponent::componentVersion() const
{
    return "1.0.0";
}

QString SerialComponent::componentAuthorContact() const
{
    return "mehrez@kristou.com";
}

QColor SerialComponent::componentColor() const
{
    return QColor(Qt::blue);
}

void SerialComponent::sendData(const QByteArray &data)
{
    m_connection.write(data);
}

void SerialComponent::onReadyRead()
{
    emit dataAvailable(m_connection.readAll());
}

bool SerialComponent::isConnected() const
{
    return m_connection.isOpen();
}

void SerialComponent::flush()
{
    m_connection.flush();
}

}
