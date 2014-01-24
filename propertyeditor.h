#ifndef PROPERTYEDITOR_H
#define PROPERTYEDITOR_H

#include <QWidget>

namespace Ui {
class PropertyEditor;
}

class KeyFrame;

class PropertyEditor : public QWidget
{
    Q_OBJECT

public:
    explicit PropertyEditor(QWidget *parent = 0);
    ~PropertyEditor();

    void setKeyFrame(KeyFrame *keyFrame);

private slots:
    void on_add_clicked();
    void on_remove_clicked();

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_doubleSpinBox_valueChanged(double arg1);

private:
    Ui::PropertyEditor *ui;
    KeyFrame *m_keyFrame;
};

#endif // PROPERTYEDITOR_H
