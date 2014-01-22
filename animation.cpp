#include "animation.h"

Animation::Animation(QObject *parent) :
    QObject(parent),
    m_frameCount(15)
{
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
