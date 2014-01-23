#pragma once

#include <QObject>
#include <QString>
#include <QRectF>

class HitBox : public QObject {
    Q_OBJECT
public:
    HitBox();
    HitBox(const QString &group, const QRectF &rect);

    QString group() const;
    QRectF rect() const;

public slots:
    void setGroup(const QString &group);
    void setRect(const QRectF &rect);

signals:
    void groupChanged(const QString &group);
    void rectChanged(const QRectF &rect);

private:
    QString m_group;
    QRectF m_rect;
};
