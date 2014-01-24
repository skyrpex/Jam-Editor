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

void AnimationToJson::fromJson(Animation &animation, const QJsonDocument &json)
{
    const QJsonObject object = json.object();
    animation.setFrameCount(object.find("frameCount").value().toInt());
    animation.setFps(object.find("fps").value().toInt());
    animation.setOrigin(pointFromJsonObject(object.find("origin").value().toObject()));
}

QJsonObject AnimationToJson::toJsonObject(const Animation &animation)
{
    QJsonObject animationObject;
    animationObject.insert("frameCount", animation.frameCount());
    animationObject.insert("fps", animation.fps());
    animationObject.insert("origin", toJsonObject(animation.origin()));

    QJsonArray keyFramesArray;
    const auto keyFrames = animation.keyFrames();
    for(auto it = keyFrames.begin(); it != keyFrames.end(); ++it) {
        QJsonObject keyFrameObject;
        keyFrameObject.insert("frame", it.key());
        keyFrameObject.insert("data", toJsonObject(*it.value()));
        keyFramesArray.append(keyFrameObject);
    }
    animationObject.insert("keyFrames", keyFramesArray);

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

QPointF AnimationToJson::pointFromJsonObject(const QJsonObject &object)
{
    return QPointF(object.find("x").value().toDouble(), object.find("y").value().toDouble());
}
