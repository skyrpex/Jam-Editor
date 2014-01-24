#ifndef HITBOXITEM_H
#define HITBOXITEM_H

#include <QGraphicsRectItem>

class HitBox;

class HitBoxItem : public QGraphicsRectItem
{
public:
    HitBoxItem(HitBox *hitBox);

    HitBox *hitBox() const;

private:
    HitBox *m_hitBox;
};

#endif // HITBOXITEM_H
