/*
*  Copyright (c) HakoComposer & Mehrez Kristou (kristou.com), distributed
*  as-is and without warranty under the MIT License. See
*  [root]/license.txt for more. This information must remain intact.
*/

#ifndef IMAGELOADERSETTINGSDIALOG_H
#define IMAGELOADERSETTINGSDIALOG_H

#include <QDialog>
#include <QCloseEvent>
#include <QImage>

#define QT_NAMESPACE Hako

namespace Ui {
class ImageLoaderSettingsDialog;
}

namespace Hako {

class ImageLoaderSettingsDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit ImageLoaderSettingsDialog(QWidget *parent = 0);
    ~ImageLoaderSettingsDialog();
    
    void closeEvent(QCloseEvent *event);
    void changeEvent(QEvent *event);

    void reloadImage();

signals:
    void imageAvailable(const QImage &image);

private:
    Ui::ImageLoaderSettingsDialog *ui;
    QImage m_image;

private slots:
    void browseButtonClicked();
};

}

#endif // SETTINGSDIALOG_H
