#ifndef PLUGINSINFODIALOG_H
#define PLUGINSINFODIALOG_H

#include <QDialog>
#include "Component.hpp"

using namespace Hako;

namespace Ui {
class PluginsInfoDialog;
}

class PluginsInfoDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit PluginsInfoDialog(QWidget *parent = 0);
    ~PluginsInfoDialog();

    void setComponentList(const QList<Component *> &components);
    
private:
    Ui::PluginsInfoDialog *ui;
};

#endif // PLUGINSINFODIALOG_H
