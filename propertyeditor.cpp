#include "propertyeditor.h"
#include "ui_propertyeditor.h"

#include <QInputDialog>

PropertyEditor::PropertyEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PropertyEditor)
{
    ui->setupUi(this);
}

PropertyEditor::~PropertyEditor()
{
    delete ui;
}

void PropertyEditor::on_add_clicked()
{
    int row = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(row);
    ui->tableWidget->setItem(row, 0, new QTableWidgetItem);
    ui->tableWidget->setItem(row, 1, new QTableWidgetItem);
}

void PropertyEditor::on_remove_clicked()
{
    ui->tableWidget->removeColumn(ui->tableWidget->currentColumn());
}
