#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "importer.h"
#include "keyframe.h"

#include <QxMesh>

#include <QDebug>
#include <QMessageBox>
#include <QMouseEvent>
#include <QCloseEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->timelineWidget->setAnimation(&m_animation);

    connect(ui->timelineWidget, SIGNAL(keyFrameChanged(int)), this, SLOT(onKeyFrameChanged(int)));

    setWindowModified(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (maybeSave()) {
//        writeSettings();
        event->accept();
    } else {
        event->ignore();
    }
}

void MainWindow::onKeyFrameChanged(int keyFrame)
{
    ui->canvas->setKeyFrame(m_animation.keyFrames().value(keyFrame));
}

void MainWindow::on_actionNew_triggered()
{
    if(!maybeSave()) {
        return;
    }

    m_animation.clear();
    ui->timelineWidget->clear();
}

void MainWindow::on_actionOpen_triggered()
{
    if(!maybeSave()) {
        return;
    }

}

void MainWindow::on_actionSave_triggered()
{
    save();
}

void MainWindow::on_actionExit_triggered()
{
    close();
}

bool MainWindow::save()
{
//    setWindowModified(false);
    return true;
}

bool MainWindow::maybeSave()
{
    if( isWindowModified() ){
        QMessageBox::StandardButton ret =
            QMessageBox::warning(
                this,
                "Jam Editor",
                tr( "The Document has been Modified\n"
                    "Do you want to save your changes?"
                 ),
                QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel
            );
        if( ret == QMessageBox::Yes ){
           return save();
        }else if( ret == QMessageBox::Cancel )
           return false;
    }
    return true;
}
