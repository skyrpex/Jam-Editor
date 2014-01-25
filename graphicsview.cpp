#include "graphicsview.h"
#include "keyframe.h"
#include "hitboxitem.h"
#include "hitbox.h"
#include "keyframeitem.h"

#include <QGraphicsLineItem>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QKeyEvent>
#include <QDebug>

GraphicsView::GraphicsView(QWidget *parent)
    : QGraphicsView(parent),
      m_keyFrame(nullptr)
{
    setMode(Canvas::MoveMode);
}

void GraphicsView::setMode(Canvas::Mode mode)
{
    m_mode = mode;

    switch (mode) {
    case Canvas::MoveMode:
        setDragMode(ScrollHandDrag);
        break;

    case Canvas::DrawDamageHitBoxMode:
        setDragMode(RubberBandDrag);
        break;

    case Canvas::DrawBodyHitBoxMode:
        setDragMode(RubberBandDrag);
        break;
    }
}

void GraphicsView::setKeyFrame(KeyFrame *keyFrame)
{
    if (m_keyFrame) {
        m_keyFrame->disconnect(this);
    }

    m_hitBoxes.clear();
    scene()->clear();
    m_keyFrame = keyFrame;

    if (m_keyFrame) {
        scene()->addItem(new KeyFrameItem(keyFrame));
        for(HitBox *hitBox : keyFrame->hitBoxes()) {
            insertHitBox(m_hitBoxes.count(), hitBox);
        }
        connect(keyFrame, &KeyFrame::hitBoxInserted, this, &GraphicsView::insertHitBox);
        connect(keyFrame, &KeyFrame::hitBoxRemoved, this, &GraphicsView::removeHitBox);
    }
}

void GraphicsView::keyPressEvent(QKeyEvent *event)
{
    if (scene() && event->key() == Qt::Key_Delete) {
        for (QGraphicsItem *item : scene()->selectedItems()) {
            auto hitBoxItem = dynamic_cast<HitBoxItem *>(item);
            if (hitBoxItem) {
                m_keyFrame->removeHitBox(hitBoxItem->hitBox());
                delete hitBoxItem->hitBox();
                delete item;
            }
        }
    }
}

void GraphicsView::mousePressEvent(QMouseEvent *event)
{
    if (scene() && m_mode != Canvas::MoveMode) {
        for(QGraphicsItem *item : scene()->items()) {
            item->setFlag(QGraphicsItem::ItemIsSelectable, false);
            item->setFlag(QGraphicsItem::ItemIsMovable, false);
        }
    }
    QGraphicsView::mousePressEvent(event);
}

void GraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    if (scene()) {
        if (m_mode != Canvas::MoveMode) {
            for(QGraphicsItem *item : scene()->items()) {
                item->setFlag(QGraphicsItem::ItemIsSelectable, true);
                item->setFlag(QGraphicsItem::ItemIsMovable, true);
            }
        }
        if (m_keyFrame && (m_mode == Canvas::DrawDamageHitBoxMode
                || m_mode == Canvas::DrawBodyHitBoxMode)) {
            QRect rect = mapToScene(rubberBandRect()).boundingRect().toRect();
            if (rect.isValid()) {
                QString group = (m_mode == Canvas::DrawDamageHitBoxMode)? "damage" : "body";
                m_keyFrame->insertHitBox(m_keyFrame->hitBoxes().count(), new HitBox(group, rect));
            }
        }
    }
    QGraphicsView::mouseReleaseEvent(event);
}

void GraphicsView::wheelEvent(QWheelEvent* event) {

    setTransformationAnchor(AnchorUnderMouse);

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

void GraphicsView::insertHitBox(int i, HitBox *hitBox)
{
    auto item = new HitBoxItem(hitBox);
    m_hitBoxes.insert(i, item);
    scene()->addItem(item);
}

void GraphicsView::removeHitBox(int i, HitBox *hitBox)
{
    HitBoxItem *item = m_hitBoxes.takeAt(i);
    delete item;
}
