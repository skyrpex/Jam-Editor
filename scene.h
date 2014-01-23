#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>

class Scene : public QGraphicsScene
{
public:

protected:
    void drawBackground(QPainter *painter, const QRectF &rect);
};

#endif // SCENE_H
