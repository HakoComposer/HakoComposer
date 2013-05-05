/*
*  Copyright (c) HakoComposer & Mehrez Kristou (kristou.com), distributed
*  as-is and without warranty under the MIT License. See
*  [root]/license.txt for more. This information must remain intact.
*/

#ifndef IMAGEVIEWERSETTINGSDIALOG_H
#define IMAGEVIEWERSETTINGSDIALOG_H

#include <QDialog>
#include <QCloseEvent>
#include <QImage>

#define QT_NAMESPACE Hako

namespace Ui {
class ImageViewerSettingsDialog;
}

namespace Hako {

class ImageViewerSettingsDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit ImageViewerSettingsDialog(QWidget *parent = 0);
    ~ImageViewerSettingsDialog();
    
    void closeEvent(QCloseEvent *event);
    void changeEvent(QEvent *event);

    void showImage(const QImage &image);

signals:
    void reloadImage();

private:
    Ui::ImageViewerSettingsDialog *ui;
    QImage m_image;
};

}

#endif // SETTINGSDIALOG_H
