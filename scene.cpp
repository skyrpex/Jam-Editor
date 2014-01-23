#include "scene.h"

#include <QPainter>

const QColor OriginColor{50, 50, 50};
const QColor GridColor{230, 230, 230};

void Scene::drawBackground(QPainter *painter, const QRectF &rect)
{
    // Draw grid
    {
        const int gridSize = 25;
        qreal left = int(rect.left()) - (int(rect.left()) % gridSize);
        qreal top = int(rect.top()) - (int(rect.top()) % gridSize);

        QVarLengthArray<QLineF, 100> lines;

        for (qreal x = left; x < rect.right(); x += gridSize)
            lines.append(QLineF(x, rect.top(), x, rect.bottom()));
        for (qreal y = top; y < rect.bottom(); y += gridSize)
            lines.append(QLineF(rect.left(), y, rect.right(), y));

        //    qDebug() << lines.size();

        painter->setPen(GridColor);
        painter->drawLines(lines.data(), lines.size());
    }

    // Draw origin
    painter->setPen(OriginColor);
    painter->drawLine(rect.left(), 0, rect.right(), 0);
    painter->drawLine(0, rect.top(), 0, rect.bottom());
}
