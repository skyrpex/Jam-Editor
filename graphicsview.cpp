#include "graphicsview.h"

#include <QWheelEvent>

GraphicsView::GraphicsView(QWidget *parent)
    : QGraphicsView(parent)
{
}

void GraphicsView::wheelEvent(QWheelEvent* event) {

    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

    // Scale the view / do the zoom
    double scaleFactor = 1.15;
    if(event->delta() > 0) {
        // Zoom in
        scale(scaleFactor, scaleFactor);
    } else {
        // Zooming out
        scale(1.0 / scaleFactor, 1.0 / scaleFactor);
    }

    viewport()->update();

    // Don't call superclass handler here
    // as wheel is normally used for moving scrollbars
}
