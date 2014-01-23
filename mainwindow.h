#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "animation.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void onKeyFrameChanged(int keyFrame);
    void on_actionNew_triggered();
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionExit_triggered();

private:
    Ui::MainWindow *ui;
    Animation m_animation;
};

#endif // MAINWINDOW_H
