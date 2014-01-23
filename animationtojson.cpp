#include "animationtojson.h"
#include "animation.h"
#include "keyframe.h"

#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QVariant>
#include <QDebug>

AnimationToJson::AnimationToJson()
{
}

QJsonDocument AnimationToJson::toJson(const Animation &animation)
{
    return QJsonDocument(toJsonObject(animation));
}

QJsonObject AnimationToJson::toJsonObject(const Animation &animation)
{
    QJsonObject animationObject;
    animationObject.insert("frameCount", animation.frameCount());
    animationObject.insert("fps", animation.fps());
    animationObject.insert("origin", toJsonObject(animation.origin()));

    QJsonObject keyFramesObject;
    const auto keyFrames = animation.keyFrames();
    for(auto it = keyFrames.begin(); it != keyFrames.end(); ++it) {
        keyFramesObject.insert(QString::number(it.key()), toJsonObject(*it.value()));
    }
    animationObject.insert("keyFrames", keyFramesObject);

    return animationObject;
}

QJsonObject AnimationToJson::toJsonObject(const KeyFrame &keyFrame)
{
    QJsonObject object;
    object.insert("fileName", keyFrame.fileName());
    object.insert("rect", toJsonObject(keyFrame.rect()));
    object.insert("offset", toJsonObject(keyFrame.offset()));
    return object;
}

QJsonObject AnimationToJson::toJsonObject(const QPointF &point)
{
    QJsonObject object;
    object.insert("x", point.x());
    object.insert("y", point.y());
    return object;
}

QJsonObject AnimationToJson::toJsonObject(const QRectF &rect)
{
    QJsonObject object;
    object.insert("topLeft", toJsonObject(rect.topLeft()));
    object.insert("bottomRight", toJsonObject(rect.bottomRight()));
    return object;
}
