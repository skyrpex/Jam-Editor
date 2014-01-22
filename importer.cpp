#include "importer.h"
#include "ui_importer.h"

#include <QFileDialog>
#include <QGraphicsPixmapItem>
#include <qxmeshdef.h>

Importer::Importer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Importer)
{
    ui->setupUi(this);

    // Create the view and the scene
    ui->graphicsView->setScene(&m_scene);
}

Importer::~Importer()
{
    delete ui;
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

void Importer::on_margin_editingFinished()
{

}

void Importer::loadImage(const QImage &image)
{
//    m_image = image;
    m_scene.clear();

    QGraphicsPixmapItem *pixmapItem = m_scene.addPixmap(QPixmap::fromImage(image));
    pixmapItem->setOpacity(0.25);

    // Trace the image
    foreach(QxMeshDef def, QxMeshDef::fromImage(image))
    {
        // Transform our mesh def
        def.offset(3);
        def.simplifyByTolerance(0.8);
//        def.simplifyByVertexCount(40);

        // Draw the triangles
        QxMesh mesh = def.mesh();
        for(int i = 2; i < mesh.indices.count(); i+=3)
        {
            int index0 = mesh.indices[i-2];
            int index1 = mesh.indices[i-1];
            int index2 = mesh.indices[i];

            QPolygonF triangle;
            triangle << mesh.vertices[index0]
                        << mesh.vertices[index1]
                           << mesh.vertices[index2];

            m_scene.addPolygon(triangle);
        }

        //    scene.addPolygon(def.boundary, QPen(Qt::blue));
        //    foreach(const QPolygonF &hole, def.holes)
        //    {
        //      scene.addPolygon(hole, QPen(Qt::red));
        //    }
    }
}
