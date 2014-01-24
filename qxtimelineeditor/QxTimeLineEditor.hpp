#ifndef QXTIMELINEEDITOR_HPP
#define QXTIMELINEEDITOR_HPP

#include <QGraphicsView>
#include <QList>

class QMenu;
class QAction;
class QxTimeLineEditorPrivate;

class QxTimeLineEditor : public QGraphicsView
{
    Q_OBJECT
public:
    enum ActionID {
        CreateKeyFrameAction,
        RemoveKeyFrameAction
    };

    explicit QxTimeLineEditor(QWidget *parent = 0);

    QList<int> keyFrames() const;
    int frameCount() const;
    int currentFrame() const;
    bool isKeyFrame(int frame) const;

public slots:
    void createKeyFrame(int frame);
    void createKeyFrameAndEmit(int frame);
    void removeKeyFrame(int frame);
    void moveKeyFrame(int frameFrom, int frameTo);
    void clearKeyFrames();

    void setKeyFrames(const QList<int> &keyFrames);
    void setFrameCount(int count);
    void setCurrentFrame(int frame);

signals:
    void currentFrameChanged(int frame);
    void keyFrameCreated(int frame);
    void keyFrameRemoved(int frame);
    void keyFrameMoved(int frameFrom, int frameTo);
    void keyFrameReplaced(int frameFrom, int frameTo);
    void keyFramesCleared();

protected:
    QMenu *contextMenu() const;
    QAction *contextMenuAction(ActionID id) const;

    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);

    virtual void contextMenuEvent(QContextMenuEvent *event);

    virtual void dragEnterEvent(QDragEnterEvent *event);
    virtual void dragMoveEvent(QDragMoveEvent *event);
    virtual void dropEvent(QDropEvent *event);

    virtual void drawBackground(QPainter *painter, const QRectF &rect);

private:
    Q_DECLARE_PRIVATE( QxTimeLineEditor )
    QxTimeLineEditorPrivate* d_ptr;
};

#endif // QXTIMELINEEDITOR_HPP
