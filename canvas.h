#ifndef CANVAS_H
#define CANVAS_H

#include "keyframe.h"

#include <QGraphicsScene>
#include <QWidget>

namespace Ui {
class Canvas;
}

class Canvas : public QWidget
{
    Q_OBJECT

public:
    explicit Canvas(QWidget *parent = 0);
    ~Canvas();

    void setKeyFrame(KeyFrame *keyFrame);

private:
    Ui::Canvas *ui;
    QGraphicsScene m_scene;
};

#endif // CANVAS_H
