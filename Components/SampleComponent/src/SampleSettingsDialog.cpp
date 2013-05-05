/*
*  Copyright (c) HakoComposer & Mehrez Kristou (kristou.com), distributed
*  as-is and without warranty under the MIT License. See
*  [root]/license.txt for more. This information must remain intact.
*/

#include "SampleSettingsDialog.h"
#include "ui_SampleSettingsDialog.h"
#include <QDebug>

namespace Hako {

SampleSettingsDialog::SampleSettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SampleSettingsDialog)
{
    ui->setupUi(this);

    setWindowFlags(Qt::WindowStaysOnTopHint);
}

SampleSettingsDialog::~SampleSettingsDialog()
{
    delete ui;
}

void SampleSettingsDialog::closeEvent(QCloseEvent *event)
{
    event->ignore();
    hide();
}

void SampleSettingsDialog::changeEvent(QEvent *event)
{
    if(event->type() == QEvent::LanguageChange){
        ui->retranslateUi(this);
    }else if(event->type() == QEvent::ActivationChange){
        // Do sothing when showed every time
    }
    QDialog::changeEvent(event);
}

}
