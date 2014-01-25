#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>
#include "canvas.h"

class KeyFrame;
class HitBox;
class HitBoxItem;

class GraphicsView : public QGraphicsView
{
public:
    GraphicsView(QWidget *parent = nullptr);

    void setMode(Canvas::Mode mode);
    void setKeyFrame(KeyFrame *keyFrame);

protected:
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void wheelEvent(QWheelEvent* event);

private slots:
    void insertHitBox(int i, HitBox *hitBox);
    void removeHitBox(int i, HitBox *hitBox);

private:
    Canvas::Mode m_mode;
    KeyFrame *m_keyFrame;
    QVector<HitBoxItem *> m_hitBoxes;
};

#endif // GRAPHICSVIEW_H
