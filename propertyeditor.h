#ifndef PROPERTYEDITOR_H
#define PROPERTYEDITOR_H

#include <QWidget>

namespace Ui {
class PropertyEditor;
}

class PropertyEditor : public QWidget
{
    Q_OBJECT

public:
    explicit PropertyEditor(QWidget *parent = 0);
    ~PropertyEditor();

private slots:
    void on_add_clicked();

    void on_remove_clicked();

private:
    Ui::PropertyEditor *ui;
};

#endif // PROPERTYEDITOR_H
