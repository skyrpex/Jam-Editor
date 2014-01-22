#ifndef MIMEDATA_HPP
#define MIMEDATA_HPP

#include <QMimeData>

class QGraphicsPixmapItem;

class MimeData : public QMimeData
{
    Q_OBJECT
public:
    explicit MimeData(QGraphicsPixmapItem *m_item);

    QGraphicsPixmapItem *keyFrameItem() const;

private:
    QGraphicsPixmapItem *m_item;
};

#endif // MIMEDATA_HPP
