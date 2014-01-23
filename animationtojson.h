#ifndef ANIMATIONTOJSON_H
#define ANIMATIONTOJSON_H

#include <QJsonDocument>

class Animation;

class AnimationToJson
{
public:
    AnimationToJson();

    QJsonDocument toJson(Animation *animation);
};

#endif // ANIMATIONTOJSON_H
