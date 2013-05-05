/*
*  Copyright (c) HakoComposer & Mehrez Kristou (kristou.com), distributed
*  as-is and without warranty under the MIT License. See
*  [root]/license.txt for more. This information must remain intact.
*/

#ifndef SERIALSETTINGSDIALOG_H
#define SERIALSETTINGSDIALOG_H

#include <QDialog>
#include <QCloseEvent>
#include "qextserialport.h"

#define QT_NAMESPACE Hako

namespace Ui {
class SerialSettingsDialog;
}

namespace Hako {

class SerialSettingsDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit SerialSettingsDialog(QWidget *parent = 0);
    ~SerialSettingsDialog();

    void closeEvent(QCloseEvent *event);
    void changeEvent(QEvent *event);
    
    QextSerialPort *connection() const;
    void setConnection(QextSerialPort *connection);

private:
    Ui::SerialSettingsDialog *ui;
    QextSerialPort *m_connection;
    long m_baudrate;

    QStringList getPortNames();
    QStringList getPortFrendlyNames();
    bool open(const QString &device, long baudrate);
    BaudRateType decodeBaudrate(long baudrate);
    void close();
    bool setBaudrate(long baudrate);
    long baudrate() const;
    bool isConnected() const;

private slots:
    void rescanClicked();
    void connectButtonClicked();
};

}

#endif // SETTINGSDIALOG_H
