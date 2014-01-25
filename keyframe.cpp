#include "keyframe.h"
#include "hitbox.h"

#include <QImage>

KeyFrame::KeyFrame() {

}

KeyFrame::KeyFrame(const QString &fileName, const QRectF &rect) {
    setFileName(fileName);
    setRect(rect);
}

KeyFrame::~KeyFrame() {
    qDeleteAll(m_hitBoxes);
}

QImage KeyFrame::image() const
{
    return QImage(m_fileName).copy(m_rect.toRect());
}

QString KeyFrame::fileName() const {
    return m_fileName;
}

QRectF KeyFrame::rect() const {
    return m_rect;
}

QPointF KeyFrame::offset() const
{
    return m_offset;
}

QVector<HitBox *> KeyFrame::hitBoxes() const {
    return m_hitBoxes;
}

QMap<QString, qreal> KeyFrame::customProperties() const
{
    return m_customProperties;
}

void KeyFrame::setFileName(const QString &fileName) {
    if (m_fileName == fileName) {
        return;
    }

    m_fileName = fileName;
    emit fileNameChanged(fileName);
}

void KeyFrame::setOffset(const QPointF &offset)
{
    m_offset = offset;
}

void KeyFrame::setRect(const QRectF &rect) {
    if (m_rect == rect) {
        return;
    }

    m_rect = rect;
    emit rectChanged(rect);
}

void KeyFrame::insertHitBox(int i, HitBox *hitBox) {
    if (m_hitBoxes.value(i) == hitBox) {
        return;
    }

    m_hitBoxes.insert(i, hitBox);
    emit hitBoxInserted(i, hitBox);
}

HitBox *KeyFrame::takeHitBox(int i) {
    HitBox *hitBox = m_hitBoxes.takeAt(i);
    emit hitBoxRemoved(i, hitBox);
    return hitBox;
}

void KeyFrame::removeHitBox(HitBox *hitBox)
{
    m_hitBoxes.remove(m_hitBoxes.indexOf(hitBox));
}

void KeyFrame::setCustomProperty(const QString &name, qreal value)
{
    m_customProperties[name] = value;
}

void KeyFrame::removeCustomProperty(const QString &name)
{
    m_customProperties.remove(name);
}
