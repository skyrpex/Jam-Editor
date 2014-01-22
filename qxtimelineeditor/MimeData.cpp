#include "MimeData.hpp"

MimeData::MimeData(QGraphicsPixmapItem *item)
    : m_item(item)
{
}

QGraphicsPixmapItem *MimeData::keyFrameItem() const
{
    return m_item;
}
