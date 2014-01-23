#include "animationtojson.h"
#include "animation.h"

#include <QJsonObject>
#include <QJsonValue>

AnimationToJson::AnimationToJson()
{
}

QJsonDocument AnimationToJson::toJson(Animation *animation)
{
    QJsonObject object;
    object.insert("name", QJsonValue(QString("test")));
    return QJsonDocument(object);
}
