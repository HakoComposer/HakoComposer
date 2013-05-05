/*
*  Copyright (c) HakoComposer & Mehrez Kristou (kristou.com), distributed
*  as-is and without warranty under the MIT License. See
*  [root]/license.txt for more. This information must remain intact.
*/

#ifndef SAMPLESETTINGSDIALOG_H
#define SAMPLESETTINGSDIALOG_H

#include <QDialog>
#include <QCloseEvent>

#define QT_NAMESPACE Hako

namespace Ui {
class SampleSettingsDialog;
}

namespace Hako {

class SampleSettingsDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit SampleSettingsDialog(QWidget *parent = 0);
    ~SampleSettingsDialog();

    void closeEvent(QCloseEvent *event);
    void changeEvent(QEvent *event);

private:
    Ui::SampleSettingsDialog *ui;
};

}

#endif // SETTINGSDIALOG_H
