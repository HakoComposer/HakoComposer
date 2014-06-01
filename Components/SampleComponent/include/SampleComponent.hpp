/*
*  Copyright (c) HakoComposer & Mehrez Kristou (kristou.com), distributed
*  as-is and without warranty under the MIT License. See
*  [root]/license.txt for more. This information must remain intact.
*/

#ifndef SAMPLECOMPNENT_H
#define SAMPLECOMPNENT_H

#include <QTimer>

#include "Component.hpp"
#include "SampleSettingsDialog.h"

namespace Hako {

class SampleComponent: public Component
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.kristou.HakoComposer.SampleComponent")

public:
    SampleComponent(QGraphicsItem *parent = 0);
    // This function is obligatory to load the component properly
    Component* clone(QGraphicsItem *parent = 0) const { return new SampleComponent(parent); }
    ~SampleComponent();

    void settingsActivated();

    // This set of methods is needed to identify the coponent
    QString componentName() const;
    QIcon componentIcon() const;
    QString componentId() const;
    QString componentDescription() const;
    QString componentCategory() const;
    QString componentAuthor() const;
    QString componentVersion() const;
    QString componentAuthorContact() const;
    QColor componentColor() const;

signals:
    void sendBeat();

private:
    QTimer m_timer;
    SampleSettingsDialog *m_settingDialog;

    void setupComponent();

private slots:
    void recieveBeat();
};

}

#endif // SAMPLECOMPNENT_H
