#include "animationtojson.h"
#include "animation.h"
#include "keyframe.h"
#include "hitbox.h"

#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QVariant>
#include <QDebug>
#include <QDir>
#include <QFileInfo>

AnimationToJson::AnimationToJson()
{
}

QJsonDocument AnimationToJson::toJson(const Animation &animation)
{
    return QJsonDocument(toJsonObject(animation));
}

void AnimationToJson::fromJson(Animation &animation, const QJsonDocument &json, const QString &fileName)
{
    fromJsonObject(animation, json.object(), fileName);
}

QJsonObject AnimationToJson::toJsonObject(const Animation &animation)
{
    QJsonObject animationObject;
    animationObject.insert("frameCount", animation.frameCount());
    animationObject.insert("fps", animation.fps());
//    animationObject.insert("origin", toJsonObject(animation.origin()));

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
    object.insert("fileName", QFileInfo(keyFrame.fileName()).fileName());
    object.insert("rect", toJsonObject(keyFrame.rect()));
//    qDebug() << keyFrame.rect() << toJsonObject(keyFrame.rect());
    object.insert("offset", toJsonObject(keyFrame.offset()));

    QJsonObject customPropertiesObject;
    const auto customProperties = keyFrame.customProperties();
    for(auto it = customProperties.begin(); it != customProperties.end(); ++it) {
        customPropertiesObject.insert(it.key(), it.value());
    }
    object.insert("customProperties", customPropertiesObject);

    QJsonArray hitBoxes;
    for (HitBox *hitBox : keyFrame.hitBoxes()) {
        hitBoxes.append(toJsonObject(*hitBox));
    }
    object.insert("hitBoxes", hitBoxes);
    return object;
}

QJsonObject AnimationToJson::toJsonObject(const HitBox &hitBox)
{
    QJsonObject object;
    object.insert("group", hitBox.group());
    object.insert("rect", toJsonObject(hitBox.rect()));
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

void AnimationToJson::fromJsonObject(Animation &animation, const QJsonObject &object, const QString &fileName)
{
    animation.setFrameCount(object.find("frameCount").value().toInt());
    animation.setFps(object.find("fps").value().toInt());
    animation.setOrigin(pointFromJsonObject(object.find("origin").value().toObject()));

    QJsonArray keyFramesArray = object.find("keyFrames").value().toArray();
    for(auto keyFrameValue : keyFramesArray) {
        QJsonObject keyFrameObject = keyFrameValue.toObject();
        int frame = keyFrameObject.find("frame").value().toInt();

        auto keyFrame = new KeyFrame;
        fromJsonObject(*keyFrame, keyFrameObject.find("data").value().toObject(), fileName);
        animation.insertKeyFrame(frame, keyFrame);
    }
}

void AnimationToJson::fromJsonObject(KeyFrame &keyFrame, const QJsonObject &object, const QString &fileName)
{
    keyFrame.setFileName(QFileInfo(fileName).dir().absolutePath() + "/" + object.find("fileName").value().toString());
    keyFrame.setOffset(pointFromJsonObject(object.find("offset").value().toObject()));
    keyFrame.setRect(rectFromJsonObject(object.find("rect").value().toObject()));

    QJsonObject customPropertiesObject = object.find("customProperties").value().toObject();
//    qDebug() << customPropertiesObject;
    for (auto it = customPropertiesObject.begin(); it != customPropertiesObject.end(); ++it) {
        keyFrame.setCustomProperty(it.key(), it.value().toDouble());
    }
//    for (const auto &value : customPropertiesObject) {
//        value.
//        qDebug() << value;
//        for (auto it = value.begin(); it != value.end(); ++it) {
//            keyFrame.setCustomProperty(it.key(), it.value().toDouble());
//        }
//    }

    for (const QJsonValue &value : object.find("hitBoxes").value().toArray()) {
        auto hitBox = new HitBox();
        fromJsonObject(*hitBox, value.toObject());
        keyFrame.insertHitBox(keyFrame.hitBoxes().count(), hitBox);
    }
}

void AnimationToJson::fromJsonObject(HitBox &hitBox, const QJsonObject &object)
{
    hitBox.setGroup(object.find("group").value().toString());
    hitBox.setRect(rectFromJsonObject(object.find("rect").value().toObject()));
}

QPointF AnimationToJson::pointFromJsonObject(const QJsonObject &object)
{
    return QPointF(object.find("x").value().toDouble(), object.find("y").value().toDouble());
}

QRectF AnimationToJson::rectFromJsonObject(const QJsonObject &object)
{
    return QRectF(pointFromJsonObject(object.find("topLeft").value().toObject()),
                  pointFromJsonObject(object.find("bottomRight").value().toObject()));
}
