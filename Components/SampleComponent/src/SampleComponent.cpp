/*
*  Copyright (c) HakoComposer & Mehrez Kristou (kristou.com), distributed
*  as-is and without warranty under the MIT License. See
*  [root]/license.txt for more. This information must remain intact.
*/

#include "SampleComponent.hpp"
#include <QDebug>

namespace Hako {

SampleComponent::SampleComponent(QGraphicsItem *parent):
    Component(parent)
{
    setupComponent();

    // We create the settings windows
    m_settingDialog = new SampleSettingsDialog();

    // this is a sample behavior of this component, it will send a beat avery second
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(treatBeat()));
    m_timer.start(1000);

    // An example of a component menu with some actions
    QMenu *menu = new QMenu();
    menu->addAction(new QAction("Open", menu));
    setMenu(menu);
}

SampleComponent::~SampleComponent()
{
    delete m_settingDialog;
}

void SampleComponent::setupComponent()
{
    // We register
    registerOutput(COMPONENT_SIGNAL(sendBeat()), "OUT");
    registerInput(COMPONENT_SLOT(recieveBeat()), "IN");

    registerSpecialOutput(COMPONENT_SIGNAL(sendBeat()), "OUT");
    registerSpecialInput(COMPONENT_SLOT(recieveBeat()), "IN");
}

void SampleComponent::recieveBeat()
{
    qDebug() << "Beat";
}

void SampleComponent::treatBeat()
{
    flash(QColor(Qt::red), 500);
    emit sendBeat();
}

// This member function get invoked every time a user
// click on the settings button.
void SampleComponent::settingsActivated()
{
    // We show the settings window
    m_settingDialog->show();
    m_settingDialog->raise();
}

// Next are nessesary information needed by
// the component to be represented correctly
QString SampleComponent::componentName() const
{
    return "Sample";
}

//Here where the component icon is set
QIcon SampleComponent::componentIcon() const
{
    return QIcon(":/Sample/logo");
}

//The component id is important to differentiate components
QString SampleComponent::componentId() const
{
    return "com.kristou.components.Sample";
}

QString SampleComponent::componentDescription() const
{
    return "A Sample Component witch send a beat on its output, and print it if it recieve it";
}

// Here is the path in the component library.
// It must always start with '/'
QString SampleComponent::componentCategory() const
{
    return "/Other";
}

//Somw information about the component creator
QString SampleComponent::componentAuthor() const
{
    return "Mehrez Kristou";
}

// The version of course
QString SampleComponent::componentVersion() const
{
    return "0.1.0";
}

// How to contact the auther
QString SampleComponent::componentAuthorContact() const
{
    return "mehrez@kristou.com";
}

// The component's background color
QColor SampleComponent::componentColor() const
{
    return QColor(Qt::yellow);
}

}
