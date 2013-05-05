/*
*  Copyright (c) HakoComposer & Mehrez Kristou (kristou.com), distributed
*  as-is and without warranty under the MIT License. See
*  [root]/license.txt for more. This information must remain intact.
*/

#include "SerialSettingsDialog.h"
#include "ui_SerialSettingsDialog.h"
#include "qextserialenumerator.h"
#include <QDebug>

#define CONNECTED_STATE "connected"

namespace Hako {

SerialSettingsDialog::SerialSettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SerialSettingsDialog),
    m_connection(NULL)
{
    ui->setupUi(this);

    setWindowFlags(Qt::WindowStaysOnTopHint);

    connect(ui->rescanButton, SIGNAL(clicked()),
            this, SLOT(rescanClicked()));
    connect(ui->connectButton, SIGNAL(clicked()),
            this, SLOT(connectButtonClicked()));
    ui->connectButton->setProperty(CONNECTED_STATE, false);

    ui->baurateBox->addItem("9600");
    ui->baurateBox->addItem("19200");
    ui->baurateBox->addItem("38400");
    ui->baurateBox->addItem("57600");
    ui->baurateBox->addItem("115200");
    ui->baurateBox->setCurrentIndex(ui->baurateBox->count() -1);

    m_baudrate = 115200;
}

SerialSettingsDialog::~SerialSettingsDialog()
{
    delete ui;
}

void SerialSettingsDialog::closeEvent(QCloseEvent *event)
{
    event->ignore();
    hide();
}

void SerialSettingsDialog::changeEvent(QEvent *event)
{
    if(event->type() == QEvent::LanguageChange){
        ui->retranslateUi(this);
    }else if(event->type() == QEvent::ActivationChange){
        rescanClicked();
    }
    QDialog::changeEvent(event);
}

void SerialSettingsDialog::rescanClicked()
{
    ui->portBox->clear();
    QStringList portNames = getPortNames();
    for(int i = 0; i < portNames.size(); i++){
        ui->portBox->addItem(portNames[i]);
    }

    ui->connectButton->setEnabled(ui->portBox->count() > 0);
}

void SerialSettingsDialog::connectButtonClicked()
{
    if(ui->connectButton->property(CONNECTED_STATE).toBool()){
        close();
        ui->connectButton->setProperty(CONNECTED_STATE, false);
        ui->connectButton->setIcon(QIcon(":/icons/connect"));
    }else{
        QString port = ui->portBox->currentText();
        m_baudrate = ui->baurateBox->currentText().toInt();
        if(open(port, m_baudrate)){
            ui->connectButton->setProperty(CONNECTED_STATE, true);
            ui->connectButton->setIcon(QIcon(":/icons/disconnect"));
        }
    }
}

QStringList SerialSettingsDialog::getPortNames()
{
    QList<QextPortInfo> ports = QextSerialEnumerator::getPorts();

    QStringList list;
    foreach (QextPortInfo info, ports) {
        if(info.portName.trimmed().size() > 0 && !list.contains(info.portName)){
            list.push_back(info.portName);
        }
    }

    return list;
}

QStringList SerialSettingsDialog::getPortFrendlyNames()
{
    QList<QextPortInfo> ports = QextSerialEnumerator::getPorts();
    QStringList list;
    foreach (QextPortInfo info, ports) {
        if(info.portName.trimmed().size() > 0 && !list.contains(info.friendName)){
            list.push_back(info.friendName);
        }
    }

    return list;
}

QextSerialPort *SerialSettingsDialog::connection() const
{
    return m_connection;
}

void SerialSettingsDialog::setConnection(QextSerialPort *connection)
{
    m_connection = connection;
}

bool SerialSettingsDialog::open(const QString &device, long baudrate)
{
    if(m_connection){
        m_connection->close();
        m_connection->setPortName(device);
        if (m_connection->open(QIODevice::ReadWrite)) {
            m_connection->setBaudRate(decodeBaudrate(baudrate));
            return true;
        }
    }
    return false;
}

BaudRateType SerialSettingsDialog::decodeBaudrate(long baudrate){
    switch (baudrate) {
    case 115200:
        return BAUD115200;
        break;
    default:
        return BAUD115200;
        break;
    }
}

void SerialSettingsDialog::close()
{
    if(m_connection){
        m_connection->close();
    }
}


bool SerialSettingsDialog::setBaudrate(long baudrate)
{
    if(m_connection){
        m_connection->setBaudRate(decodeBaudrate(baudrate));
        m_baudrate = baudrate;
        return true;
    }
    return false;
}


long SerialSettingsDialog::baudrate() const
{
    return m_baudrate;
}

bool SerialSettingsDialog::isConnected() const
{
    if(m_connection){
        return m_connection->isOpen();
    }
    return false;
}

}
