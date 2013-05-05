/*
*  Copyright (c) HakoComposer & Mehrez Kristou (kristou.com), distributed
*  as-is and without warranty under the MIT License. See
*  [root]/license.txt for more. This information must remain intact.
*/

#include "ImageViewerSettingsDialog.h"
#include "ui_ImageViewerSettingsDialog.h"
#include <QFileDialog>

namespace Hako {

ImageViewerSettingsDialog::ImageViewerSettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImageViewerSettingsDialog)
{
    ui->setupUi(this);

    setWindowFlags(Qt::WindowStaysOnTopHint);
}

ImageViewerSettingsDialog::~ImageViewerSettingsDialog()
{
    delete ui;
}

void ImageViewerSettingsDialog::closeEvent(QCloseEvent *event)
{
    event->ignore();
    hide();
}

void ImageViewerSettingsDialog::changeEvent(QEvent *event)
{
    if(event->type() == QEvent::LanguageChange){
        ui->retranslateUi(this);
    }else if(event->type() == QEvent::ActivationChange){
        // Do sothing when showed every time
    }
    QDialog::changeEvent(event);
}

void ImageViewerSettingsDialog::showImage(const QImage &image)
{
    ui->imageLabel->setPixmap(QPixmap::fromImage(image));
    ui->imageLabel->show();
}

}
