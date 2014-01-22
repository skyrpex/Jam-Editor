#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "importer.h"

#include <QxMesh>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->timelineWidget->setAnimation(&m_animation);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{

}

void MainWindow::on_actionOpen_triggered()
{

}

void MainWindow::on_actionSave_triggered()
{

}

void MainWindow::on_actionExit_triggered()
{
    close();
}

void MainWindow::on_actionImport_triggered()
{
    Importer importer(this);
    importer.exec();
}
