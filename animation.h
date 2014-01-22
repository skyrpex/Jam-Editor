#ifndef ANIMATION_H
#define ANIMATION_H

#include <QObject>
#include <QPointF>

class Animation : public QObject
{
    Q_OBJECT
public:
    explicit Animation(QObject *parent = 0);

    int frameCount() const;
    int fps() const;
    QPointF origin() const;

signals:
    void frameCountChanged(int count);
    void fpsChanged(int fps);
    void originChanged(const QPointF &origin);

public slots:
    void setFrameCount(int count);
    void setFps(int fps);
    void setOrigin(const QPointF &origin);

private:
    int m_frameCount;
    int m_fps;
    QPointF m_origin;
};

#endif // ANIMATION_H
