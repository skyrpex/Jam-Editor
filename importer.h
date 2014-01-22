#ifndef IMPORTER_H
#define IMPORTER_H

#include <QDialog>
#include <QGraphicsScene>
#include <QImage>
#include <QString>

namespace Ui {
class Importer;
}

class Importer : public QDialog
{
    Q_OBJECT

public:
    explicit Importer(QWidget *parent = 0);
    ~Importer();

private slots:
    void on_browse_clicked();
    void on_reload_clicked();

private:
    void loadImage(const QImage &image);
    Ui::Importer *ui;
    QGraphicsScene m_scene;
    QString m_fileName;
//    QImage m_image;
};

#endif // IMPORTER_H
