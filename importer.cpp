#include "importer.h"
#include "ui_importer.h"

#include <QFileDialog>
#include <QGraphicsPixmapItem>
#include <qxmeshdef.h>
#include <qxclipper.h>

Importer::Importer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Importer)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(&m_scene);
    ui->graphicsView->setDragMode(QGraphicsView::RubberBandDrag);

    on_browse_clicked();
}

Importer::~Importer()
{
    delete ui;
}

QImage Importer::image() const
{
    return QImage(m_fileName);
}

QVector<QRectF> Importer::rects() const
{
    QVector<QRectF> rects;
    foreach(QGraphicsItem *item, m_scene.selectedItems()) {
        rects << item->boundingRect();
    }
    return rects;
}

void Importer::on_browse_clicked()
{
    // Add the image
    QString fileName = QFileDialog::getOpenFileName();
    QImage image(fileName);
    if(image.isNull())
        return;

    m_fileName = fileName;
//    m_image = image;
    ui->imageLabel->setText(fileName);

    loadImage(image);
}

void Importer::on_reload_clicked()
{
//    if(m_image.isNull()) {
//        return;
//    }

    QImage image(m_fileName);
    if(image.isNull())
        return;

    loadImage(image);
}

void Importer::loadImage(const QImage &image)
{
//    m_image = image;
    m_scene.clear();

    QGraphicsPixmapItem *pixmapItem = m_scene.addPixmap(QPixmap::fromImage(image));
    pixmapItem->setOpacity(0.25);

    // Merge boundaries
    QList<QxMeshDef> defs = QxMeshDef::fromImage(image);
    QList<QPolygonF> boundingPolygons;
    boundingPolygons.reserve(defs.count());
    foreach(const QxMeshDef &def, QxMeshDef::fromImage(image)) {
        boundingPolygons << QPolygonF(def.boundary.boundingRect());
    }

    // Create the items
    foreach(const QPolygonF &polygon, QxClipper::merged(boundingPolygons)) {
        QGraphicsRectItem *item = m_scene.addRect(polygon.boundingRect());
        item->setFlags(QGraphicsItem::ItemIsSelectable);
    }
}
