/*
*  Copyright (c) HakoComposer & Mehrez Kristou (kristou.com), distributed
*  as-is and without warranty under the MIT License. See
*  [root]/license.txt for more. This information must remain intact.
*/

#ifndef IMAGELOADERCOMPONENT_H
#define IMAGELOADERCOMPONENT_H

#include "Component.hpp"
#include "ImageLoaderSettingsDialog.h"

namespace Hako {

class ImageLoaderComponent: public Component
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.kristou.HakoComposer.ImageLoaderComponent")
public:
    ImageLoaderComponent(QGraphicsItem *parent = 0);
    // This function is obligatory to load the component properly
    Component* clone(QGraphicsItem *parent = 0) const { return new ImageLoaderComponent(parent); }

    ~ImageLoaderComponent();

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
    void componentGotConnected();

signals:
    void sendImage(const QImage &image);

private:
    ImageLoaderSettingsDialog *m_settingDialog;

    void setupComponent();

private slots:
    void reloadImage();
};

}

#endif // IMAGELOADERCOMPONENT_H
