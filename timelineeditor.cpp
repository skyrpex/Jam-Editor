#include "timelineeditor.h"

#include <QDebug>

TimelineEditor::TimelineEditor(QWidget *parent) :
    QxTimeLineEditor(parent)
{
    // Connecting our functions to sync the data
    connect(this, SIGNAL(keyFrameCreated(int)), SLOT(onKeyFrameCreated(int)));
    connect(this, SIGNAL(keyFrameRemoved(int)), SLOT(onKeyFrameRemoved(int)));
    connect(this, SIGNAL(keyFrameMoved(int,int)), SLOT(onKeyFrameMoved(int,int)));
    connect(this, SIGNAL(keyFrameReplaced(int,int)), SLOT(onKeyFrameReplaced(int,int)));
    connect(this, SIGNAL(keyFramesCleared()), SLOT(onKeyFramesCleared()));

    // Set a frame count
    setFrameCount( 15 );

    // Set four keyframes: 0, 3, 4, 8
    setKeyFrames( QList<int>() << 0 << 3 << 4 << 8 );
}

void TimelineEditor::onKeyFrameCreated(int frame)
{
    qDebug() << __FUNCTION__ << frame;
}

void TimelineEditor::onKeyFrameRemoved(int frame)
{
    qDebug() << __FUNCTION__ << frame;
}

void TimelineEditor::onKeyFrameMoved(int frameFrom, int frameTo)
{
    qDebug() << __FUNCTION__ << frameFrom << frameTo;
}

void TimelineEditor::onKeyFrameReplaced(int frameFrom, int frameTo)
{
    qDebug() << __FUNCTION__ << frameFrom << frameTo;
}

void TimelineEditor::onKeyFramesCleared()
{
    qDebug() << __FUNCTION__;
}

void TimelineEditor::showKeyFrameProperties()
{
    qDebug() << __FUNCTION__;
}
