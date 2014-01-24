#include "propertyeditor.h"
#include "ui_propertyeditor.h"
#include "keyframe.h"

#include <QInputDialog>

PropertyEditor::PropertyEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PropertyEditor)
{
    ui->setupUi(this);
    setKeyFrame(nullptr);
}

PropertyEditor::~PropertyEditor()
{
    delete ui;
}

void PropertyEditor::setKeyFrame(KeyFrame *keyFrame)
{
    m_keyFrame = keyFrame;
    setEnabled(m_keyFrame);

    ui->comboBox->clear();
    if (keyFrame) {
        ui->comboBox->addItems(keyFrame->customProperties().keys());
    }
}

void PropertyEditor::on_add_clicked()
{
    QString name = QInputDialog::getText(this, "name", "name");
    if (name.isEmpty()) {
        return;
    }

    m_keyFrame->setCustomProperty(name.toStdString().c_str(), 0.0);
    ui->comboBox->addItem(name);
}

void PropertyEditor::on_remove_clicked()
{
    QString name = ui->comboBox->currentText();
    m_keyFrame->removeCustomProperty(name);
    ui->comboBox->removeItem(ui->comboBox->currentIndex());
}

void PropertyEditor::on_comboBox_currentIndexChanged(const QString &arg1)
{
    if (!m_keyFrame) {
        return;
    }

    qreal value = m_keyFrame->customProperties().value(arg1);
    ui->doubleSpinBox->setValue(value);
}

void PropertyEditor::on_doubleSpinBox_valueChanged(double arg1)
{
    if (!m_keyFrame) {
        return;
    }

    QString name = ui->comboBox->currentText();
    m_keyFrame->setCustomProperty(name, arg1);
}
