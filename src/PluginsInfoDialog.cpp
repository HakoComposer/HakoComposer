#include "PluginsInfoDialog.h"
#include "ui_PluginsInfoDialog.h"

PluginsInfoDialog::PluginsInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PluginsInfoDialog)
{
    ui->setupUi(this);

    connect(ui->closeButton, SIGNAL(clicked()),
            this, SLOT(close()));
}

PluginsInfoDialog::~PluginsInfoDialog()
{
    delete ui;
}

void PluginsInfoDialog::setComponentList(const QList<Component *> &components)
{
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(components.size());
    QTableWidgetItem *item;
    for (int i = 0; i < components.size(); i++) {
        Component *component = components[i];

        // Component icon
        item = new QTableWidgetItem(component->componentName());
        item->setIcon(component->componentIcon());
        ui->tableWidget->setItem(i, 0, item);

        item = new QTableWidgetItem(component->componentVersion());
        ui->tableWidget->setItem(i, 1, item);

        item = new QTableWidgetItem(component->componentId());
        ui->tableWidget->setItem(i, 2, item);

        item = new QTableWidgetItem(component->componentAuthor());
        ui->tableWidget->setItem(i, 3, item);
    }

    ui->tableWidget->resizeColumnsToContents();
}
