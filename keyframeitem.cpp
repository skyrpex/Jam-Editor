#include "keyframeitem.h"
#include "keyframe.h"

KeyFrameItem::KeyFrameItem(KeyFrame *keyFrame) :
    m_keyFrame(keyFrame)
{
    setFlags(ItemIsMovable | ItemIsSelectable | ItemSendsScenePositionChanges);
    setShapeMode(BoundingRectShape);

    Q_ASSERT(keyFrame);
    setPixmap(QPixmap::fromImage(keyFrame->image()));
    setPos(keyFrame->offset());
}

QVariant KeyFrameItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemPositionHasChanged) {
        m_keyFrame->setOffset(pos());
    }

    return QGraphicsPixmapItem::itemChange(change, value);
}
