/*
*  Copyright (c) HakoComposer & Mehrez Kristou (kristou.com), distributed
*  as-is and without warranty under the MIT License. See
*  [root]/license.txt for more. This information must remain intact.
*/

#ifndef IMAGEVIEWERCOMPONENT_H
#define IMAGEVIEWERCOMPONENT_H

#include "Component.hpp"
#include "ImageViewerSettingsDialog.h"

namespace Hako {

class ImageViewerComponent: public Component
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.kristou.HakoComposer.ImageViewerComponent" FILE "ImageViewerComponent.json")

public:
    ImageViewerComponent(QGraphicsItem *parent = 0);
    // This function is obligatory to load the component properly
    Component* clone(QGraphicsItem *parent = 0) const { return new ImageViewerComponent(parent); }

    ~ImageViewerComponent();

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
    void reloadImage();

private:
    ImageViewerSettingsDialog *m_settingDialog;

    void setupComponent();

private slots:
    void recieveImage(const QImage &image);
};

}

#endif // IMAGEVIEWERCOMPONENT_H
