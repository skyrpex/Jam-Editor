#ifndef CANVAS_H
#define CANVAS_H

#include <QGraphicsScene>
#include <QWidget>

namespace Ui {
class Canvas;
}

class Animation;
class KeyFrame;

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
    Animation *m_animation;
};

#endif // CANVAS_H
