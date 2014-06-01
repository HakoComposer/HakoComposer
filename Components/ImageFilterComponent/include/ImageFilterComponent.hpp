/*
*  Copyright (c) HakoComposer & Mehrez Kristou (kristou.com), distributed
*  as-is and without warranty under the MIT License. See
*  [root]/license.txt for more. This information must remain intact.
*/

#ifndef IMAGEFILTERCOMPNENT_H
#define IMAGEFILTERCOMPNENT_H

#include <QTimer>
#include "Component.hpp"
#include "ImageFilterSettingsDialog.h"

namespace Hako {

class ImageFilterComponent: public Component
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.kristou.HakoComposer.ImageFilterComponent" FILE "ImageFilterComponent.json")

public:
    ImageFilterComponent(QGraphicsItem *parent = 0);
    // This function is obligatory to load the component properly
    Component* clone(QGraphicsItem *parent = 0) const { return new ImageFilterComponent(parent); }
    ~ImageFilterComponent();

    void settingsActivated();

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
    ImageFilterSettingsDialog *m_settingDialog;

    void setupComponent();

private slots:
    void recieveBeat();
};

}

#endif // SAMPLECOMPNENT_H
