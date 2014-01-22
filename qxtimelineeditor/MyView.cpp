#include "MyView.hpp"
#include <QAction>
#include <QDebug>
#include <QMenu>

MyView::MyView(QWidget *parent) :
    QxTimeLineEditor(parent)
{
    // Connecting our functions to sync the data
    connect(this, SIGNAL(keyFrameCreated(int)), SLOT(onKeyFrameCreated(int)));
    connect(this, SIGNAL(keyFrameRemoved(int)), SLOT(onKeyFrameRemoved(int)));
    connect(this, SIGNAL(keyFrameMoved(int,int)), SLOT(onKeyFrameMoved(int,int)));
    connect(this, SIGNAL(keyFrameReplaced(int,int)), SLOT(onKeyFrameReplaced(int,int)));
    connect(this, SIGNAL(keyFramesCleared()), SLOT(onKeyFramesCleared()));

    // Set a frame count
    setFrameCount( 20 );

    // Set four keyframes: 0, 3, 4, 8
    setKeyFrames( QList<int>() << 0 << 3 << 4 << 8 );

    // Customize the context menu
    QMenu *menu = this->contextMenu();
    m_separatorAction = menu->addSeparator();
    m_propertiesAction = menu->addAction( tr( "Properties" ), this, SLOT( showKeyFrameProperties() ) );
}

void MyView::contextMenuEvent(QContextMenuEvent *event)
{
    // Prevent from removing the first keyframe
    contextMenuAction(RemoveKeyFrameAction)->setDisabled( currentFrame() == 0 );

    // Only show properties action if there is a keyframe under the mouse
    bool isKeyFrame = this->isKeyFrame( currentFrame() );
    m_separatorAction->setVisible( isKeyFrame );
    m_propertiesAction->setVisible( isKeyFrame );

    // Call the context menu
    QxTimeLineEditor::contextMenuEvent( event );
}

void MyView::onKeyFrameCreated(int frame)
{
    qDebug() << __FUNCTION__ << frame;
}

void MyView::onKeyFrameRemoved(int frame)
{
    qDebug() << __FUNCTION__ << frame;
}

void MyView::onKeyFrameMoved(int frameFrom, int frameTo)
{
    qDebug() << __FUNCTION__ << frameFrom << frameTo;
}

void MyView::onKeyFrameReplaced(int frameFrom, int frameTo)
{
    qDebug() << __FUNCTION__ << frameFrom << frameTo;
}

void MyView::onKeyFramesCleared()
{
    qDebug() << __FUNCTION__;
}

void MyView::showKeyFrameProperties()
{
    qDebug() << __FUNCTION__;
}
