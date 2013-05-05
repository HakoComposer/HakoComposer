/*
*  Copyright (c) HakoComposer & Mehrez Kristou (kristou.com), distributed
*  as-is and without warranty under the MIT License. See
*  [root]/license.txt for more. This information must remain intact.
*/

#include "ImageLoaderSettingsDialog.h"
#include "ui_ImageLoaderSettingsDialog.h"
#include <QFileDialog>

namespace Hako {

ImageLoaderSettingsDialog::ImageLoaderSettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImageLoaderSettingsDialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowStaysOnTopHint);

    connect(ui->browseButton, SIGNAL(clicked()),
            this, SLOT(browseButtonClicked()));
}

ImageLoaderSettingsDialog::~ImageLoaderSettingsDialog()
{
    delete ui;
}

void ImageLoaderSettingsDialog::closeEvent(QCloseEvent *event)
{
    event->ignore();
    hide();
}

void ImageLoaderSettingsDialog::changeEvent(QEvent *event)
{
    if(event->type() == QEvent::LanguageChange){
        ui->retranslateUi(this);
    }else if(event->type() == QEvent::ActivationChange){
        // Do sothing when showed every time
    }
    QDialog::changeEvent(event);
}

void ImageLoaderSettingsDialog::reloadImage()
{
    if(!m_image.isNull()){
        emit imageAvailable(m_image);
    }
}


void ImageLoaderSettingsDialog::browseButtonClicked()
{
    QString filename = QFileDialog::getOpenFileName(this,
                                                    tr("Open Image"),
                                                    QDir::homePath(),
                                                    tr("Image Files (*.png *.jpg *.bmp)"));
    if(!filename.isEmpty() && m_image.load(filename)){
        ui->pathLabel->setText(filename);
        ui->imageLabel->setPixmap(QPixmap::fromImage(m_image));
        ui->imageLabel->show();
        emit imageAvailable(m_image);
    }
}

}
