#include "importer.h"
#include "timelineeditor.h"

#include <QDebug>

TimelineEditor::TimelineEditor(QWidget *parent) :
    QxTimeLineEditor(parent),
    m_animation(0)
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
//    setKeyFrames( QList<int>() << 0 << 3 << 4 << 8 );
}

void TimelineEditor::setAnimation(Animation *animation)
{
//    if(m_animation) {
//        m_animation->disconnect(this);
//    }

    m_animation = animation;


    if(m_animation) {
        setKeyFrames(m_animation->keyFrames().keys());
//        connect(m_animation, SIGNAL(keyFrameInserted(int)), this, SLOT(createKeyFrame(int)));
//        connect(m_animation, SIGNAL(keyFrameRemoved(int)), this, SLOT(removeKeyFrame(int)));
    }
}

void TimelineEditor::onKeyFrameCreated(int frame)
{
//    qDebug() << __FUNCTION__ << frame;
    if(!m_animation) {
        return;
    }
    Importer importer(this);
    if(importer.exec()) {
        QString fileName = importer.fileName();
        QRectF rect = importer.mergedRects();
        KeyFrame *keyFrame = new KeyFrame(fileName, rect);

        m_animation->insertKeyFrame(currentFrame(), keyFrame);
        emit currentFrameChanged(currentFrame());
    }
}

void TimelineEditor::onKeyFrameRemoved(int frame)
{
//    qDebug() << __FUNCTION__ << frame;
    if(!m_animation) {
        return;
    }
    delete m_animation->takeKeyFrame(frame);
}

void TimelineEditor::onKeyFrameMoved(int frameFrom, int frameTo)
{
//    qDebug() << __FUNCTION__ << frameFrom << frameTo;
    if(!m_animation) {
        return;
    }
    KeyFrame *keyFrame = m_animation->takeKeyFrame(frameFrom);
    m_animation->insertKeyFrame(frameTo, keyFrame);
}

void TimelineEditor::onKeyFrameReplaced(int frameFrom, int frameTo)
{
//    qDebug() << __FUNCTION__ << frameFrom << frameTo;
    if(!m_animation) {
        return;
    }
    delete m_animation->takeKeyFrame(frameTo);
    KeyFrame *keyFrame = m_animation->takeKeyFrame(frameFrom);
    m_animation->insertKeyFrame(frameTo, keyFrame);
}

void TimelineEditor::onKeyFramesCleared()
{
//    qDebug() << __FUNCTION__;
}

void TimelineEditor::showKeyFrameProperties()
{
//    qDebug() << __FUNCTION__;
}
