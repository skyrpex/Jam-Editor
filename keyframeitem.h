#ifndef KEYFRAMEITEM_H
#define KEYFRAMEITEM_H

#include <QGraphicsPixmapItem>

class KeyFrame;

class KeyFrameItem : public QGraphicsPixmapItem
{
public:
    KeyFrameItem(KeyFrame *keyFrame);

    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

private:
    KeyFrame *m_keyFrame;
};

#endif // KEYFRAMEITEM_H
