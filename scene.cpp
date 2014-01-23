#include "scene.h"

#include <QPainter>

const QColor OriginColor{50, 50, 50};
const QColor GridColor{230, 230, 230};

void Scene::drawBackground(QPainter *painter, const QRectF &rect)
{
    const QRectF target = sceneRect().intersected(rect);

    {
        const int gridSize = 25;
        qreal left = int(target.left()) - (int(target.left()) % gridSize);
        qreal top = int(target.top()) - (int(target.top()) % gridSize);

        QVarLengthArray<QLineF, 100> lines;

        for (qreal x = left; x < target.right(); x += gridSize)
            lines.append(QLineF(x, target.top(), x, target.bottom()));
        for (qreal y = top; y < target.bottom(); y += gridSize)
            lines.append(QLineF(target.left(), y, target.right(), y));

        //    qDebug() << lines.size();

        painter->setPen(GridColor);
        painter->drawLines(lines.data(), lines.size());
    }

    painter->setPen(OriginColor);
    painter->drawLine(target.left(), 0, target.right(), 0);
    painter->drawLine(0, target.top(), 0, target.bottom());
}
