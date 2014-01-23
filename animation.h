#ifndef ANIMATION_H
#define ANIMATION_H

#include <QObject>
#include <QPointF>
#include <QMap>

#include "keyframe.h"

class Animation : public QObject
{
    Q_OBJECT
public:
    explicit Animation(QObject *parent = 0);
    ~Animation();

    int frameCount() const;
    int fps() const;
    QPointF origin() const;
    QMap<int, KeyFrame *> keyFrames() const;

    void insertKeyFrame(int i, KeyFrame *keyFrame);
    KeyFrame *takeKeyFrame(int i);

    void clear();

signals:
    void frameCountChanged(int count);
    void fpsChanged(int fps);
    void originChanged(const QPointF &origin);
    void keyFrameInserted(int i);
    void keyFrameRemoved(int i);

public slots:
    void setFrameCount(int count);
    void setFps(int fps);
    void setOrigin(const QPointF &origin);

private:
    int m_frameCount;
    int m_fps;
    QPointF m_origin;
    QMap<int, KeyFrame *> m_keyFrames;
};

#endif // ANIMATION_H
