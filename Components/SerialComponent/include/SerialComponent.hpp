/*
*  Copyright (c) HakoComposer & Mehrez Kristou (kristou.com), distributed
*  as-is and without warranty under the MIT License. See
*  [root]/license.txt for more. This information must remain intact.
*/

#ifndef SERIALCOMPNENT_H
#define SERIALCOMPNENT_H

#include "Component.hpp"
#include <QByteArray>
#include "qextserialport.h"
#include "SerialSettingsDialog.h"
#include <QMutex>

namespace Hako {

class SerialComponent: public Component
{
    Q_OBJECT

public:
    SerialComponent(QGraphicsItem *parent = 0);
    Component* clone(QGraphicsItem *parent = 0) const {return(new SerialComponent(parent));}
    ~SerialComponent();

    void settingsActivated();

    QString componentName() const;
    QIcon componentIcon() const;
    QString componentId() const;
    QString componentDescription() const;
    QString componentCategory() const;
    QString componentAuthor() const;
    QString componentVersion() const;
    QString componentAuthorContact() const;
    QColor componentColor() const;

signals:
    void dataAvailable(const QByteArray &data);

private:
    QextSerialPort m_connection;
    long m_baudrate;
    SerialSettingsDialog *m_settingDialog;

    void setupComponent();

    bool isConnected() const;
    void flush();

private slots:
    void sendData(const QByteArray &data);
    void onReadyRead();
};

}

#endif // SERIALCOMPNENT_H
