#include "hitboxitem.h"
#include "hitbox.h"

#include <QColor>
#include <QPen>
#include <QBrush>

const QPen BodyPen{QColor{0, 255, 0}};
const QBrush BodyBrush{QColor{0, 255, 0, 30}};
const QPen DamagePen{QColor{255, 0, 0}};
const QBrush DamageBrush{QColor{255, 0, 0, 30}};

HitBoxItem::HitBoxItem(HitBox *hitBox)
    : m_hitBox(hitBox)
{
    setFlags(ItemIsMovable | ItemIsSelectable | ItemSendsScenePositionChanges);
    setRect(hitBox->rect());
    setPen(hitBox->group() == "body"? BodyPen : DamagePen);
    setBrush(hitBox->group() == "body"? BodyBrush : DamageBrush);
}

HitBox *HitBoxItem::hitBox() const
{
    return m_hitBox;
}
