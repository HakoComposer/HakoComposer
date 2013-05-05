#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

/*
*  Copyright (c) HakoComposer & Mehrez Kristou (kristou.com), distributed
*  as-is and without warranty under the MIT License. See
*  [root]/license.txt for more. This information must remain intact.
*/

#include <QMainWindow>
#include <QGraphicsScene>
#include <QLibrary>
#include "Workspace.hpp"
#include "PluginsInfoDialog.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void registerComponents(const QList<Component *> &components);
    void setupConnections();
    QList<Component *> loadComponents();
    void closeEvent(QCloseEvent *);
private:
    Ui::MainWindow *ui;
    Workspace m_workspace;
    PluginsInfoDialog m_pluginsInfoDialog;

private slots:
    void newActionTriggered();
    void saveActionTriggered();
    void openActionTriggered();

    void aboutPluginTriggered();
};

#endif // MAINWINDOW_HPP
