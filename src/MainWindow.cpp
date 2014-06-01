/*
*  Copyright (c) HakoComposer & Mehrez Kristou (kristou.com), distributed
*  as-is and without warranty under the MIT License. See
*  [root]/license.txt for more. This information must remain intact.
*/

#include "MainWindow.hpp"
#include "ui_MainWindow.h"
#include "NodeView.hpp"
#include "NodePortView.hpp"

#include <QPluginLoader>
#include <QFileDialog>
#include <QMessageBox>
#include <QDirIterator>
#include <QDebug>

#include "ComponentInterface.h"

//#include "SampleComponent.hpp"
//#include "SerialComponent.hpp"
//#include "ImageLoaderComponent.h"
//#include "ImageViewerComponent.h"
//#include "ImageFilterComponent.hpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle(QApplication::applicationName() + QString(" V") + QString(QApplication::applicationVersion()) +
                   QString(" By ") + QString(QApplication::organizationName()));

    ui->graphicsView->setScene( &m_workspace );

    setupConnections();
    registerComponents(loadComponents());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupConnections()
{
    connect(ui->action_New, SIGNAL(triggered()),
            this, SLOT(newActionTriggered()));
    connect(ui->action_Save, SIGNAL(triggered()),
            this, SLOT(saveActionTriggered()));
    connect(ui->action_Open, SIGNAL(triggered()),
            this, SLOT(openActionTriggered()));
    connect(ui->actionQuit, SIGNAL(triggered()),
            this, SLOT(close()));

    connect(ui->actionAbout_plugins, SIGNAL(triggered()),
            this, SLOT(aboutPluginTriggered()));
}

void MainWindow::newActionTriggered()
{
    m_workspace.clearWorkspace();
}

void MainWindow::saveActionTriggered()
{
    QString filename = QFileDialog::getSaveFileName( this,
                                                     "Save Block Project dialog",
                                                     QDir::homePath(),
                                                     "Block Project (*hpf)");
    if(!filename.isEmpty()){
        if(m_workspace.saveWorkspace(filename)){
            QMessageBox::information( this, "Saving Project",
                                      "The project is saved successefully");
        }
    }
}

void MainWindow::openActionTriggered()
{
    QString filename = QFileDialog::getOpenFileName( this,
                                                     "Open Block Project dialog",
                                                     QDir::homePath(),
                                                     "Block Project (*hpf)");
    if(!filename.isEmpty()){
        m_workspace.loadWorkspace(filename);
    }
}

void MainWindow::aboutPluginTriggered()
{
    m_pluginsInfoDialog.setComponentList(m_workspace.getRegisteredComponents());
    m_pluginsInfoDialog.show();
    m_pluginsInfoDialog.raise();
}

void MainWindow::registerComponents(const QList<Component *> &components)
{
    foreach(Component *component, components){
        if(component){
            component->setParent(this);
            ui->treeWidget->addComponent(component);
            m_workspace.registerComponent(component);
        }
    }
}

QList<Component *> MainWindow::loadComponents()
{
    QList<Component *> result;

    QDir pluginsDir(qApp->applicationDirPath());
#if defined(Q_OS_WIN)
    if (pluginsDir.dirName().toLower() == "debug" || pluginsDir.dirName().toLower() == "release")
        pluginsDir.cdUp();
#elif defined(Q_OS_MAC)
    if (pluginsDir.dirName() == "MacOS") {
        pluginsDir.cdUp();
        pluginsDir.cdUp();
        pluginsDir.cdUp();
    }
#endif
    pluginsDir.cd("plugins");

    foreach (QString fileName, pluginsDir.entryList(QDir::Files)) {
        QString absFileName = pluginsDir.absoluteFilePath(fileName);
        QPluginLoader loader(absFileName);
        QObject *plugin = loader.instance();
        if (plugin) {
            ComponentInterface *interface =  qobject_cast<ComponentInterface *>(plugin);
            if(interface){
                result.push_back(interface->getComponent());
            }
        }
    }
    return result;
}

void MainWindow::closeEvent(QCloseEvent *)
{
    m_workspace.clearWorkspace();
}
