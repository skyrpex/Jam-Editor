#ifndef TIMELINEWIDGET_H
#define TIMELINEWIDGET_H

#include <QWidget>

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

private slots:
    void setFrameCount(int count);
    void setFps(int fps);
    void on_fps_editingFinished();
    void on_frameCount_editingFinished();

private:
    Ui::TimelineWidget *ui;
    Animation *m_animation;
};

#endif // TIMELINEWIDGET_H
