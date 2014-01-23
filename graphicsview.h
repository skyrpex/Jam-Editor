#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>

class GraphicsView : public QGraphicsView
{
public:
    GraphicsView(QWidget *parent = nullptr);

protected:
    //Take over the interaction
    virtual void wheelEvent(QWheelEvent* event);
};

#endif // GRAPHICSVIEW_H
