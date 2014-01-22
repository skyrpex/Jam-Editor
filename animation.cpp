#include "animation.h"

Animation::Animation(QObject *parent) :
    QObject(parent),
    m_frameCount(15)
{
}

Animation::~Animation()
{
    qDeleteAll(m_keyFrames);
}

int Animation::frameCount() const
{
    return m_frameCount;
}

int Animation::fps() const
{
    return m_fps;
}

QPointF Animation::origin() const
{
    return m_origin;
}

QMap<int, KeyFrame *> Animation::keyFrames() const
{
    return m_keyFrames;
}

void Animation::insertKeyFrame(int i, KeyFrame *keyFrame)
{
    if(m_keyFrames.contains(i)) {
        delete m_keyFrames.value(i);
    }

    m_keyFrames.insert(i, keyFrame);
    emit keyFrameInserted(i);
}

KeyFrame *Animation::takeKeyFrame(int i)
{
    KeyFrame *k = m_keyFrames.take(i);
    emit keyFrameRemoved(i);
    return k;
}

void Animation::setFrameCount(int count)
{
    if (m_frameCount == count) {
        return;
    }

    m_frameCount = count;
    emit frameCountChanged(count);
}

void Animation::setFps(int fps)
{
    if (m_fps == fps) {
        return;
    }

    m_fps = fps;
    emit fpsChanged(fps);
}

void Animation::setOrigin(const QPointF &origin)
{
    if (m_origin == origin) {
        return;
    }

    m_origin = origin;
    emit originChanged(origin);
}
