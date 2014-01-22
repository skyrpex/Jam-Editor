#include "mainwindow.h"
//#include "qxtimelineeditor/MyView.hpp"
#include <QApplication>

#include <QxMesh>
#include <QxMeshDef>

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>

#include <QFileDialog>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
