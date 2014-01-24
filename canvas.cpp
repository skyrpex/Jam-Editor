#include "canvas.h"
#include "ui_canvas.h"
#include "keyframe.h"
#include "animation.h"
#include "keyframeitem.h"

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
    ui->graphicsView->setKeyFrame(keyFrame);
}

void Canvas::setMode(Canvas::Mode mode)
{
    ui->graphicsView->setMode(mode);
}

void Canvas::on_resetZoom_clicked()
{
    ui->graphicsView->resetMatrix();
}
