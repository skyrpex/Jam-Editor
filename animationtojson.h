#ifndef ANIMATIONTOJSON_H
#define ANIMATIONTOJSON_H

#include <QJsonDocument>

class Animation;
class KeyFrame;
class HitBox;
class QPointF;
class QRectF;

class AnimationToJson
{
public:
    AnimationToJson();

    QJsonDocument toJson(const Animation &animation);

    void fromJson(Animation &animation, const QJsonDocument &json, const QString &fileName);

private:
    QJsonObject toJsonObject(const Animation &animation);
    QJsonObject toJsonObject(const KeyFrame &keyFrame);
    QJsonObject toJsonObject(const HitBox &hitBox);
    QJsonObject toJsonObject(const QPointF &point);
    QJsonObject toJsonObject(const QRectF &rect);

    void fromJsonObject(Animation &animation, const QJsonObject &object, const QString &fileName);
    void fromJsonObject(KeyFrame &keyFrame, const QJsonObject &object, const QString &fileName);
    void fromJsonObject(HitBox &hitBox, const QJsonObject &object);
    QPointF pointFromJsonObject(const QJsonObject &object);
    QRectF rectFromJsonObject(const QJsonObject &object);
};

#endif // ANIMATIONTOJSON_H
