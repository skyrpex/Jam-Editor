#include "canvas.h"
#include "ui_canvas.h"

Canvas::Canvas(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Canvas)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(&m_scene);
}

Canvas::~Canvas()
{
    delete ui;
}

void Canvas::setKeyFrame(KeyFrame *keyFrame)
{
    m_scene.clear();
    if(keyFrame) {
        m_scene.addPixmap(QPixmap::fromImage(keyFrame->image()));
    }
}
