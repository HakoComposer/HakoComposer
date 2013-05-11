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
    ui(new Ui::ImageFilterSettingsDialog),
    m_image(NULL)
{
    ui->setupUi(this);

    setWindowFlags(Qt::WindowStaysOnTopHint);

    //    IplImage *image = cvLoadImage("/Users/anjin/Downloads/1367433920_kthememgr.png");
    //    cvShowImage("TEST",image);
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

QImage ImageFilterSettingsDialog::iplImageToQImage(const IplImage *iplImage)
{
    // Local variables
    int height = iplImage->height;
    int width = iplImage->width;
    // PIXEL DEPTH=8-bits unsigned, NO. OF CHANNELS=1
    if(iplImage->depth == IPL_DEPTH_8U && iplImage->nChannels == 1)
    {
        // Set the color table (used to translate colour indexes to qRgb values)
        QVector<QRgb> colorTable;
        for (int i=0; i<256; i++)
            colorTable.push_back(qRgb(i,i,i));
        // Copy input IplImage
        const uchar *qImageBuffer = (const uchar*)iplImage->imageData;
        // Create QImage with same dimensions as input IplImage
        QImage img(qImageBuffer, width, height, QImage::Format_Indexed8);
        img.setColorTable(colorTable);
        return img;
    }
    // PIXEL DEPTH=8-bits unsigned, NO. OF CHANNELS=3
    else if(iplImage->depth == IPL_DEPTH_8U && iplImage->nChannels == 3)
    {
        // Copy input IplImage
        const uchar *qImageBuffer = (const uchar*)iplImage->imageData;
        // Create QImage with same dimensions as input IplImage
        QImage img(qImageBuffer, width, height, QImage::Format_RGB888);
        return img.rgbSwapped();
    }
    else
    {
        qDebug() << "ERROR: IplImage could not be converted to QImage.";
        return QImage();
    }
}

IplImage* ImageFilterSettingsDialog::qImageToIplImage(const QImage& qImage)
{
    int width = qImage.width();
    int height = qImage.height();

    // Creates a iplImage with 3 channels
    IplImage *img = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 3);
    char * imgBuffer = img->imageData;

    //Remove alpha channel
    int jump = (qImage.hasAlphaChannel()) ? 4 : 3;

    for (int y=0;y<img->height;y++){
        QByteArray a((const char*)qImage.scanLine(y), qImage.bytesPerLine());
        for (int i=0; i<a.size(); i+=jump){
            //Swap from RGB to BGR
            imgBuffer[2] = a[i];
            imgBuffer[1] = a[i+1];
            imgBuffer[0] = a[i+2];
            imgBuffer+=3;
        }
    }

    return img;
}

void ImageFilterSettingsDialog::imageGot(const QImage &image)
{
    if(m_image){
        delete m_image;
        m_image = NULL;
    }
    m_image = new QImage(image);
}

}
