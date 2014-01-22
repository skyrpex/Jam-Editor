#ifndef TIMELINEEDITOR_H
#define TIMELINEEDITOR_H

#include "qxtimelineeditor/QxTimeLineEditor.hpp"

class TimelineEditor : public QxTimeLineEditor
{
    Q_OBJECT
public:
    TimelineEditor(QWidget *parent = 0);

private slots:
    void onKeyFrameCreated(int frame);
    void onKeyFrameRemoved(int frame);
    void onKeyFrameMoved(int frameFrom, int frameTo);
    void onKeyFrameReplaced(int frameFrom, int frameTo);
    void onKeyFramesCleared();
    void showKeyFrameProperties();
};

#endif // TIMELINEEDITOR_H
