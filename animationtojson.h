#ifndef ANIMATIONTOJSON_H
#define ANIMATIONTOJSON_H

#include <QJsonDocument>

class Animation;
class KeyFrame;
class QPointF;
class QRectF;

class AnimationToJson
{
public:
    AnimationToJson();

    QJsonDocument toJson(const Animation &animation);

private:
    QJsonObject toJsonObject(const Animation &animation);
    QJsonObject toJsonObject(const KeyFrame &keyFrame);
    QJsonObject toJsonObject(const QPointF &point);
    QJsonObject toJsonObject(const QRectF &rect);
};

#endif // ANIMATIONTOJSON_H
