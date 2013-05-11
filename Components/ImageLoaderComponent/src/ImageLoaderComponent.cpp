/*
*  Copyright (c) HakoComposer & Mehrez Kristou (kristou.com), distributed
*  as-is and without warranty under the MIT License. See
*  [root]/license.txt for more. This information must remain intact.
*/

#include "ImageLoaderComponent.h"

namespace Hako {

ImageLoaderComponent::ImageLoaderComponent(QGraphicsItem *parent):
    Component(parent)
{
    setupComponent();

    // We create the settings windows
    m_settingDialog = new ImageLoaderSettingsDialog();
    connect(m_settingDialog, SIGNAL(imageAvailable(const QImage &)),
            this, SIGNAL(sendImage(const QImage &)));
}

ImageLoaderComponent::~ImageLoaderComponent()
{
    delete m_settingDialog;
}

void ImageLoaderComponent::settingsActivated()
{
    // We show the settings window
    m_settingDialog->show();
    m_settingDialog->raise();
}

QString ImageLoaderComponent::componentName() const
{
    return "Image Loader";
}

QIcon ImageLoaderComponent::componentIcon() const
{
    return QIcon(":/ImageLoader/logo");
}

QString ImageLoaderComponent::componentId() const
{
    return "com.kristou.components.ImageLoader";
}

QString ImageLoaderComponent::componentDescription() const
{
    return "Load an image from file.";
}

QString ImageLoaderComponent::componentCategory() const
{
    return "/Image";
}

QString ImageLoaderComponent::componentAuthor() const
{
    return "Mehrez Kristou";
}

QString ImageLoaderComponent::componentVersion() const
{
    return "0.1.0";
}

QString ImageLoaderComponent::componentAuthorContact() const
{
    return "mehrez@kristou.com";
}

QColor ImageLoaderComponent::componentColor() const
{
    return QColor(Qt::green);
}

void ImageLoaderComponent::componentGotConnected()
{
    reloadImage();
}

void ImageLoaderComponent::setupComponent()
{
    registerOutput(COMPONENT_SIGNAL(sendImage(const QImage &)), "Image");
    registerSpecialInput(COMPONENT_SLOT(reloadImage()), "Reload");
}

void ImageLoaderComponent::reloadImage()
{
    m_settingDialog->reloadImage();
}

}
