/*
*  Copyright (c) HakoComposer & Mehrez Kristou (kristou.com), distributed
*  as-is and without warranty under the MIT License. See
*  [root]/license.txt for more. This information must remain intact.
*/

#ifndef IMAGEFILTERSETTINGSDIALOG_H
#define IMAGEFILTERSETTINGSDIALOG_H

#include <QDialog>
#include <QCloseEvent>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#define QT_NAMESPACE Hako

namespace Ui {
class ImageFilterSettingsDialog;
}

namespace Hako {

class ImageFilterSettingsDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit ImageFilterSettingsDialog(QWidget *parent = 0);
    ~ImageFilterSettingsDialog();

    void closeEvent(QCloseEvent *event);
    void changeEvent(QEvent *event);

private:
    Ui::ImageFilterSettingsDialog *ui;
};

}

#endif // SETTINGSDIALOG_H
