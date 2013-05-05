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
    connect(&m_timer, SIGNAL(timeout()), this, SIGNAL(sendBeat()));
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

QIcon SampleComponent::componentIcon() const
{
    return QIcon(":/Sample/logo");
}

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

QString SampleComponent::componentAuthor() const
{
    return "Mehrez Kristou";
}

QString SampleComponent::componentVersion() const
{
    return "1.0.0";
}

QString SampleComponent::componentAuthorContact() const
{
    return "mehrez@kristou.com";
}

QColor SampleComponent::componentColor() const
{
    return QColor(Qt::yellow);
}

}
