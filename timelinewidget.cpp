#include "timelinewidget.h"
#include "ui_timelinewidget.h"

#include <QScrollBar>

TimelineWidget::TimelineWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TimelineWidget),
    m_animation(0)
{
    ui->setupUi(this);
    QScrollBar *scrollBar = ui->timelineEditor->horizontalScrollBar();
    ui->verticalLayout->addWidget( scrollBar );
}

TimelineWidget::~TimelineWidget()
{
    delete ui;
}

void TimelineWidget::setAnimation(Animation *animation)
{
    if(m_animation) {
        m_animation->disconnect(this);
    }

    m_animation = animation;

    if(m_animation) {
        setFrameCount(m_animation->frameCount());

        animation->connect(m_animation, SIGNAL(frameCountChanged(int)), this, SLOT(setFrameCount(int)));
        animation->connect(m_animation, SIGNAL(fpsChanged(int)), this, SLOT(setFps(int)));
    }
}

void TimelineWidget::setFrameCount(int count)
{
    ui->timelineEditor->setFrameCount(count);
    ui->frameCount->setValue(count);
}

void TimelineWidget::setFps(int fps)
{
    ui->fps->setValue(fps);
}

void TimelineWidget::on_fps_editingFinished()
{
    m_animation->setFps(ui->fps->value());
}

void TimelineWidget::on_frameCount_editingFinished()
{
    m_animation->setFrameCount(ui->frameCount->value());
}
