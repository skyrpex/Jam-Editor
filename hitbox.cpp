#include "hitbox.h"

HitBox::HitBox() {

}

HitBox::HitBox(const QString &group, const QRectF &rect) :
    m_group(group),
    m_rect(rect) {

}

QString HitBox::group() const {
    return m_group;
}

QRectF HitBox::rect() const {
    return m_rect;
}

void HitBox::setGroup(const QString &group) {
    if (m_group == group) {
        return;
    }

    m_group = group;
    emit groupChanged(group);
}

void HitBox::setRect(const QRectF &rect) {
    if (m_rect == rect) {
        return;
    }

    m_rect = rect;
    emit rectChanged(rect);
}
