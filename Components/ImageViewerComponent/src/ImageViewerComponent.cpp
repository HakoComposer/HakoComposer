/*
*  Copyright (c) HakoComposer & Mehrez Kristou (kristou.com), distributed
*  as-is and without warranty under the MIT License. See
*  [root]/license.txt for more. This information must remain intact.
*/

#include "ImageViewerComponent.h"

namespace Hako {

ImageViewerComponent::ImageViewerComponent(QGraphicsItem *parent):
    Component(parent)
{
    setupComponent();

    // We create the settings windows
    m_settingDialog = new ImageViewerSettingsDialog();
    connect(m_settingDialog, SIGNAL(reloadImage()),
            this, SIGNAL(reloadImage()));
}

ImageViewerComponent::~ImageViewerComponent()
{
    delete m_settingDialog;
}

void ImageViewerComponent::settingsActivated()
{
    // We show the settings window
    m_settingDialog->show();
    m_settingDialog->raise();
}

QString ImageViewerComponent::componentName() const
{
    return "Image Viewer";
}

QIcon ImageViewerComponent::componentIcon() const
{
    return QIcon(":/ImageViewer/logo");
}

QString ImageViewerComponent::componentId() const
{
    return "com.kristou.components.ImageViewer";
}

QString ImageViewerComponent::componentDescription() const
{
    return "Show an image.";
}

QString ImageViewerComponent::componentCategory() const
{
    return "/Image";
}

QString ImageViewerComponent::componentAuthor() const
{
    return "Mehrez Kristou";
}

QString ImageViewerComponent::componentVersion() const
{
    return "0.1.0";
}

QString ImageViewerComponent::componentAuthorContact() const
{
    return "mehrez@kristou.com";
}

QColor ImageViewerComponent::componentColor() const
{
    return QColor(Qt::magenta);
}

void ImageViewerComponent::setupComponent()
{
    registerInput(COMPONENT_SLOT(recieveImage(const QImage &)), "Image");
    registerSpecialOutput(COMPONENT_SIGNAL(reloadImage()), "Reload");
}

void ImageViewerComponent::recieveImage(const QImage &image)
{
    m_settingDialog->showImage(image);
}

}
