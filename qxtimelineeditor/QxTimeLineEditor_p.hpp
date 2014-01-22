#ifndef QXTIMELINEEDITOR_P_HPP
#define QXTIMELINEEDITOR_P_HPP

#include <QObject>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QGraphicsLineItem>
#include <QSet>
#include <QMenu>

class QxTimeLineEditor;

class QxTimeLineEditorPrivate : public QObject
{
    Q_OBJECT
public:
    QxTimeLineEditorPrivate( QxTimeLineEditor *widget );

    qreal snapToScene(int x) const;
    QPointF snapToScene(const QPoint &pos) const;
    int frameAt(const QPoint &pos) const;
    qreal framePos(int frame) const;

public slots:
    void createKeyFrame();
    void removeKeyFrame();

private:
    Q_DECLARE_PUBLIC( QxTimeLineEditor )
    QxTimeLineEditor* q_ptr;

public:
    QGraphicsPixmapItem dragItem;
    int frameCount;
    QHash<int, QGraphicsPixmapItem *> keyFrames;
    QGraphicsLineItem currentFrameItem;
    QMenu *menu;
    QAction *createKeyFrameAction;
    QAction *removeKeyFrameAction;
};

#endif // QXTIMELINEEDITOR_P_HPP
