#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QActionGroup>

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

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void onKeyFrameChanged(int keyFrame);
    void on_actionNew_triggered();
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionExit_triggered();

    void on_actionMove_mode_triggered();

    void on_actionDraw_damage_hitbox_triggered();

    void on_actionDraw_body_hitbox_triggered();

private:
    bool newFile();
    bool save();
    bool saveAs();
    bool saveFile(const QString &fileName);
    bool open();
    bool openFile(const QString &fileName);
    bool maybeSave();
    Ui::MainWindow *ui;
    Animation m_animation;
    QActionGroup m_actionGroup;
};

#endif // MAINWINDOW_H
