#ifndef KEYFRAME_H
#define KEYFRAME_H

#include <QImage>
#include <QString>
#include <QRectF>

class KeyFrame
{
public:
    KeyFrame(const QString &fileName, const QRectF &rect);

    void setSubImage(const QString &fileName, const QRectF &rect);
    void reload();

    QImage image() const;
    QString fileName() const;
    QRectF rect() const;

private:
    QString m_fileName;
    QRectF m_rect;
    QImage m_subImage;
};

#endif // KEYFRAME_H
