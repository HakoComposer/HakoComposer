/*
*  Copyright (c) HakoComposer & Mehrez Kristou (kristou.com), distributed
*  as-is and without warranty under the MIT License. See
*  [root]/license.txt for more. This information must remain intact.
*/

#include "ImageFilterSettingsDialog.h"
#include "ui_ImageFilterSettingsDialog.h"
#include <QDebug>

namespace Hako {

ImageFilterSettingsDialog::ImageFilterSettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImageFilterSettingsDialog)
{
    ui->setupUi(this);

    setWindowFlags(Qt::WindowStaysOnTopHint);

    IplImage *image = cvLoadImage("/Users/anjin/Downloads/1367433920_kthememgr.png");
    cvShowImage("TEST",image);
}

ImageFilterSettingsDialog::~ImageFilterSettingsDialog()
{
    delete ui;
}

void ImageFilterSettingsDialog::closeEvent(QCloseEvent *event)
{
    event->ignore();
    hide();
}

void ImageFilterSettingsDialog::changeEvent(QEvent *event)
{
    if(event->type() == QEvent::LanguageChange){
        ui->retranslateUi(this);
    }else if(event->type() == QEvent::ActivationChange){
        // Do sothing when showed every time
    }
    QDialog::changeEvent(event);
}

}
