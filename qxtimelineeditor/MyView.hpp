#ifndef MYVIEW_HPP
#define MYVIEW_HPP

#include "QxTimeLineEditor.hpp"

class MyView : public QxTimeLineEditor
{
    Q_OBJECT
public:
    explicit MyView(QWidget *parent = 0);

protected:
    void contextMenuEvent(QContextMenuEvent *event);

private slots:
    void onKeyFrameCreated(int frame);
    void onKeyFrameRemoved(int frame);
    void onKeyFrameMoved(int frameFrom, int frameTo);
    void onKeyFrameReplaced(int frameFrom, int frameTo);
    void onKeyFramesCleared();
    void showKeyFrameProperties();

private:
    QAction *m_separatorAction;
    QAction *m_propertiesAction;
};

#endif // MYVIEW_HPP
