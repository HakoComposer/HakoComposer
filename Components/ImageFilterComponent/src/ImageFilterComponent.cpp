/*
*  Copyright (c) HakoComposer & Mehrez Kristou (kristou.com), distributed
*  as-is and without warranty under the MIT License. See
*  [root]/license.txt for more. This information must remain intact.
*/

#include "ImageFilterComponent.hpp"
#include <QDebug>

namespace Hako {

ImageFilterComponent::ImageFilterComponent(QGraphicsItem *parent):
    Component(parent)
{
    setupComponent();

    // We create the settings windows
    m_settingDialog = new ImageFilterSettingsDialog();

    // this is a sample behavior of this component, it will send a beat avery second
    connect(&m_timer, SIGNAL(timeout()), this, SIGNAL(sendBeat()));
    m_timer.start(1000);

    // An example of a component menu with some actions
    QMenu *menu = new QMenu();
    menu->addAction(new QAction("Open", menu));
    setMenu(menu);
}

ImageFilterComponent::~ImageFilterComponent()
{
    delete m_settingDialog;
}

void ImageFilterComponent::setupComponent()
{
    // We register
    registerOutput(COMPONENT_SIGNAL(sendBeat()), "OUT");
    registerInput(COMPONENT_SLOT(recieveBeat()), "IN");

    registerSpecialOutput(COMPONENT_SIGNAL(sendBeat()), "OUT");
    registerSpecialInput(COMPONENT_SLOT(recieveBeat()), "IN");
}

void ImageFilterComponent::recieveBeat()
{
    qDebug() << "Beat";
}

// This member function get invoked every time a user
// click on the settings button.
void ImageFilterComponent::settingsActivated()
{
    // We show the settings window
    m_settingDialog->show();
    m_settingDialog->raise();
}


// Next are nessesary information needed by
// the component to be represented correctly
QString ImageFilterComponent::componentName() const
{
    return "Image Filter";
}

QIcon ImageFilterComponent::componentIcon() const
{
    return QIcon(":/Sample/logo");
}

QString ImageFilterComponent::componentId() const
{
    return "com.kristou.components.ImageFilter";
}

QString ImageFilterComponent::componentDescription() const
{
    return "A Sample Component witch send a beat on its output, and print it if it recieve it";
}

// Here is the path in the component library.
// It must always start with '/'
QString ImageFilterComponent::componentCategory() const
{
    return "/Other";
}

QString ImageFilterComponent::componentAuthor() const
{
    return "Mehrez Kristou";
}

QString ImageFilterComponent::componentVersion() const
{
    return "1.0.0";
}

QString ImageFilterComponent::componentAuthorContact() const
{
    return "mehrez@kristou.com";
}

QColor ImageFilterComponent::componentColor() const
{
    return QColor(Qt::gray);
}

}
