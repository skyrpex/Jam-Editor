#include "keyframe.h"

#include <QDebug>

KeyFrame::KeyFrame(const QString &fileName, const QRectF &rect)
{
    setSubImage(fileName, rect);
}

void KeyFrame::setSubImage(const QString &fileName, const QRectF &rect)
{
    m_fileName = fileName;
    m_rect = rect;
    reload();
}

void KeyFrame::reload()
{
    m_subImage = QImage(m_fileName).copy(m_rect.toRect());
}

QImage KeyFrame::image() const
{
    return m_subImage;
}

QString KeyFrame::fileName() const
{
    return m_fileName;
}

QRectF KeyFrame::rect() const
{
    return m_rect;
}
