#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "importer.h"
#include "keyframe.h"

#include <QxMesh>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->timelineWidget->setAnimation(&m_animation);

    connect(ui->timelineWidget, SIGNAL(keyFrameChanged(int)), this, SLOT(onKeyFrameChanged(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onKeyFrameChanged(int keyFrame)
{
    ui->canvas->setKeyFrame(m_animation.keyFrames().value(keyFrame));
}

void MainWindow::on_actionNew_triggered()
{
    m_animation.clear();
    ui->timelineWidget->clear();
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
