#ifndef TIMELINEEDITOR_H
#define TIMELINEEDITOR_H

#include "qxtimelineeditor/QxTimeLineEditor.hpp"

#include "animation.h"

class TimelineEditor : public QxTimeLineEditor
{
    Q_OBJECT
public:
    TimelineEditor(QWidget *parent = 0);

    void setAnimation(Animation *animation);

private slots:
    void onKeyFrameCreated(int frame);
    void onKeyFrameRemoved(int frame);
    void onKeyFrameMoved(int frameFrom, int frameTo);
    void onKeyFrameReplaced(int frameFrom, int frameTo);
    void onKeyFramesCleared();
    void showKeyFrameProperties();

private:
    Animation *m_animation;
};

#endif // TIMELINEEDITOR_H
