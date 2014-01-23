#pragma once

#include <QObject>
#include <QString>
#include <QRectF>
#include <QVector>

class HitBox;

class KeyFrame : public QObject {
    Q_OBJECT
public:
    KeyFrame();
    KeyFrame(const QString &fileName, const QRectF &rect);
    ~KeyFrame();

    QImage image() const;
    QString fileName() const;
    QRectF rect() const;
    QPointF offset() const;
    QVector<HitBox *> hitBoxes() const;

public slots:
    void setFileName(const QString &fileName);
    void setRect(const QRectF &rect);
    void setOffset(const QPointF &offset);
    void insertHitBox(int i, HitBox *hitBox);
    HitBox *takeHitBox(int i);

signals:
    void fileNameChanged(const QString &fileName);
    void rectChanged(const QRectF &rect);
    void offsetChanged(const QPointF &offset);
    void hitBoxInserted(int i, HitBox *hitBox);
    void hitBoxRemoved(int i, HitBox *hitBox);

private:
    QString m_fileName;
    QRectF m_rect;
    QPointF m_offset;
    QVector<HitBox *> m_hitBoxes;
};
