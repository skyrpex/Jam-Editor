#include "canvas.h"
#include "ui_canvas.h"
#include "keyframe.h"
#include "animation.h"
#include "keyframeitem.h"

Canvas::Canvas(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Canvas),
    m_mode(MoveMode)
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
        m_scene.addItem(new KeyFrameItem(keyFrame));
    }
}

void Canvas::setMode(Canvas::Mode mode)
{
    m_mode = mode;
}

void Canvas::on_resetZoom_clicked()
{
    ui->graphicsView->resetMatrix();
}
