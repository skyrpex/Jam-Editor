#include "timelinewidget.h"
#include "ui_timelinewidget.h"

#include <QScrollBar>

TimelineWidget::TimelineWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TimelineWidget),
    m_animation(0),
    m_lastKeyFrame(-1)
{
    ui->setupUi(this);
    QScrollBar *scrollBar = ui->timelineEditor->horizontalScrollBar();
    ui->verticalLayout->addWidget( scrollBar );
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(advanceFrame()));


    connect(ui->timelineEditor, SIGNAL(currentFrameChanged(int)), this, SLOT(onEditorFrameChanged(int)));
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
    ui->timelineEditor->setAnimation(animation);
    m_timer.stop();

    if(m_animation) {
        setFrameCount(m_animation->frameCount());

        connect(m_animation, SIGNAL(frameCountChanged(int)), this, SLOT(setFrameCount(int)));
        connect(m_animation, SIGNAL(fpsChanged(int)), this, SLOT(setFps(int)));
    }
}

int TimelineWidget::currentFrame() const
{
    return ui->timelineEditor->currentFrame();
}

void TimelineWidget::createKeyFrame()
{
    ui->timelineEditor->createKeyFrame(ui->timelineEditor->currentFrame());
}

void TimelineWidget::play()
{
    m_timer.start(intervalFromFps());
}

void TimelineWidget::pause()
{
    m_timer.stop();
}

void TimelineWidget::stop()
{
    ui->timelineEditor->setCurrentFrame(0);
    m_timer.stop();
}

void TimelineWidget::onEditorFrameChanged(int frame)
{
    int keyFrame = keyframeForFrame(frame);
    if (keyFrame == -1) {
        return;
    }

    if (m_lastKeyFrame == keyFrame) {
        return;
    }

    m_lastKeyFrame = keyFrame;
    emit keyFrameChanged(keyFrame);
}

void TimelineWidget::setFrameCount(int count)
{
    ui->timelineEditor->setFrameCount(count);
    ui->frameCount->setValue(count);
}

void TimelineWidget::setFps(int fps)
{
    ui->fps->setValue(fps);
    m_timer.setInterval(intervalFromFps());
}

void TimelineWidget::advanceFrame()
{
    int frame = ui->timelineEditor->currentFrame() + 1;
    frame %= ui->frameCount->value();
    ui->timelineEditor->setCurrentFrame( frame );
}

void TimelineWidget::on_fps_editingFinished()
{
    m_animation->setFps(ui->fps->value());
}

void TimelineWidget::on_frameCount_editingFinished()
{
    m_animation->setFrameCount(ui->frameCount->value());
}

void TimelineWidget::on_toolButton_clicked()
{
    if(m_timer.isActive()) {
        pause();
    }
    else {
        play();
    }
}

void TimelineWidget::on_toolButton_2_clicked()
{
    stop();
}

int TimelineWidget::intervalFromFps()
{
    return 1000 / ui->fps->value();
}

int TimelineWidget::keyframeForFrame(int frame)
{
    const auto keyframes = m_animation->keyFrames();
    if (keyframes.isEmpty()) {
        return -1;
    }

    if (keyframes.contains(frame)) {
        return frame;
    }

    auto it = keyframes.lowerBound(frame);
    if (it == keyframes.begin()) {
        return -1;
    }

    --it;
    return it.key();
}
