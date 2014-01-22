#ifndef TIMELINEWIDGET_H
#define TIMELINEWIDGET_H

#include <QWidget>
#include <QTimer>

#include "animation.h"

namespace Ui {
class TimelineWidget;
}

class TimelineWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TimelineWidget(QWidget *parent = 0);
    ~TimelineWidget();

    void setAnimation(Animation *animation);
    int currentFrame() const;

    void play();
    void pause();
    void stop();

signals:
    void keyFrameChanged(int keyFrame);

private slots:
    void onEditorFrameChanged(int frame);
    void setFrameCount(int count);
    void setFps(int fps);
    void advanceFrame();
    void on_fps_editingFinished();
    void on_frameCount_editingFinished();

    void on_toolButton_clicked();

    void on_toolButton_2_clicked();

private:
    int intervalFromFps();
    Ui::TimelineWidget *ui;
    Animation *m_animation;
    QTimer m_timer;
};

#endif // TIMELINEWIDGET_H
