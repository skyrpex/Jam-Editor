#include "QxTimeLineEditor.hpp"
#include "QxTimeLineEditor_p.hpp"
#include "MimeData.hpp"
#include "Constants.hpp"
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QDrag>
#include <QMimeData>
#include <QDebug>
#include <QGraphicsPixmapItem>
#include <cmath>
#include <QMenu>
#include <QScrollBar>

QxTimeLineEditor::QxTimeLineEditor(QWidget *parent) :
    QGraphicsView(new QGraphicsScene, parent)
  , d_ptr( new QxTimeLineEditorPrivate( this ) )
{
//    resize(800, 600);

    Q_D( QxTimeLineEditor );

    setAlignment( Qt::AlignLeft | Qt::AlignTop );
    setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    setBackgroundBrush( QPixmap( BackgroundFileName ) );
//    setFrameStyle( NoFrame );
    setAcceptDrops( true );

    int height = QPixmap( KeyFrameFileName ).height();
    setMinimumHeight( height );
    setMaximumHeight( height );

    d->dragItem.setPixmap( QPixmap( KeyFrameDragFileName ) );
    d->dragItem.setZValue( 1 );
    d->dragItem.setVisible( false );
    scene()->addItem( &d->dragItem );

    d->currentFrameItem.setPen( QPen( Qt::red ) );
    d->currentFrameItem.setZValue( 2 );
    qreal x = QPixmap( KeyFrameFileName ).width() / 2.0 - 1;
    d->currentFrameItem.setLine( x, 0, x, height - 1 );
    scene()->addItem( &d->currentFrameItem );
}

void QxTimeLineEditor::setKeyFrames(const QList<int> &keyFrames)
{
    Q_D( QxTimeLineEditor );
    clearKeyFrames();

    foreach( int frame, keyFrames ) {
        createKeyFrame( frame );
        if( frame > d->frameCount ) {
            setFrameCount( frame );
        }
    }
}

QList<int> QxTimeLineEditor::keyFrames() const
{
    Q_D( const QxTimeLineEditor );
    return d->keyFrames.keys();
}

void QxTimeLineEditor::setFrameCount(int count)
{
    Q_D( QxTimeLineEditor );
    d->frameCount = count;

    QRectF rect = sceneRect();
    rect.setWidth( count * QPixmap( KeyFrameFileName ).width() );
    setSceneRect( rect );

    viewport()->update();
}

int QxTimeLineEditor::frameCount() const
{
    Q_D( const QxTimeLineEditor );
    return d->frameCount;
}

void QxTimeLineEditor::setCurrentFrame(int frame)
{
    Q_D( QxTimeLineEditor );

    qreal x = d->framePos( frame );
    if( d->currentFrameItem.x() == x ) {
        return;
    }

    d->currentFrameItem.setX( x );
    emit currentFrameChanged( frame );
}

QMenu *QxTimeLineEditor::contextMenu() const
{
    Q_D( const QxTimeLineEditor );

    return d->menu;
}

QAction *QxTimeLineEditor::contextMenuAction(QxTimeLineEditor::ActionID id) const
{
    Q_D( const QxTimeLineEditor );

    switch(id) {
    case CreateKeyFrameAction:
        return d->createKeyFrameAction;

    case RemoveKeyFrameAction:
        return d->removeKeyFrameAction;

    default:
        return 0;
    }
}

int QxTimeLineEditor::currentFrame() const
{
    Q_D( const QxTimeLineEditor );
    return d->currentFrameItem.x() / QPixmap( KeyFrameFileName ).width();
}

bool QxTimeLineEditor::isKeyFrame(int frame) const
{
    Q_D( const QxTimeLineEditor );
    return d->keyFrames.contains( frame );
}

void QxTimeLineEditor::createKeyFrame(int frame)
{
    Q_D( QxTimeLineEditor );

    if( d->keyFrames.contains( frame ) ) {
        qWarning() << tr( "Keyframe already exists at %1" ).arg( frame );
        return;
    }

    QGraphicsPixmapItem *keyFrame = new QGraphicsPixmapItem( QPixmap( KeyFrameFileName )  );
    keyFrame->setX( d->framePos( frame ) );
    scene()->addItem( keyFrame );
    d->keyFrames.insert( frame, keyFrame );

    //    emit keyFrameCreated( frame );
}

void QxTimeLineEditor::createKeyFrameAndEmit(int frame)
{
    createKeyFrame( frame );
    emit keyFrameCreated( frame );
}

void QxTimeLineEditor::removeKeyFrame(int frame)
{
    Q_D( QxTimeLineEditor );

    if( !d->keyFrames.contains( frame ) ) {
        qWarning() << tr( "Keyframe do not exists at %1" ).arg( frame );
        return;
    }

    delete d->keyFrames.take( frame );
    emit keyFrameRemoved( frame );
}

void QxTimeLineEditor::moveKeyFrame(int frameFrom, int frameTo)
{
    Q_D( QxTimeLineEditor );

    // Skip if source equals destination
    if( frameFrom == frameTo ) {
        return;
    }

    // Check if replacing or moving was succesful on the inherited class
    bool isReplacing = d->keyFrames.contains( frameTo );

    // Remove any previous keyframe
    if( isReplacing ) {
        delete d->keyFrames.take( frameTo );
    }

    // Move the keyframe
    QGraphicsPixmapItem *keyFrame = d->keyFrames.take( frameFrom );
    keyFrame->setX( d->framePos( frameTo ) );
    d->keyFrames.insert( frameTo, keyFrame );

    if( isReplacing ) {
        emit keyFrameReplaced( frameFrom, frameTo );
    }
    else {
        emit keyFrameMoved( frameFrom, frameTo );
    }
}

void QxTimeLineEditor::clearKeyFrames()
{
    Q_D( QxTimeLineEditor );

    qDeleteAll( d->keyFrames.values() );
    d->keyFrames.clear();

    emit keyFramesCleared();
}

void QxTimeLineEditor::mousePressEvent(QMouseEvent *event)
{
    Q_D( QxTimeLineEditor );

    QGraphicsView::mousePressEvent( event );

    // Update current frame
    int frame = d->frameAt( event->pos() );
    setCurrentFrame( frame );

    // Start drag
    if( event->buttons() & Qt::LeftButton ) {
        QGraphicsPixmapItem *item = d->keyFrames.value( frame );
        if( item ) {
            QDrag *drag = new QDrag( this );
            drag->setMimeData( new MimeData( item ) );
            drag->exec();
        }
    }
}

void QxTimeLineEditor::mouseMoveEvent(QMouseEvent *event)
{
    Q_D( QxTimeLineEditor );

    QGraphicsView::mouseMoveEvent( event );

    // Update current frame
    setCurrentFrame( d->frameAt( event->pos() ) );
}

void QxTimeLineEditor::contextMenuEvent(QContextMenuEvent *event)
{
    Q_D( QxTimeLineEditor );

    int frame = d->frameAt( event->pos() );
    bool frameInRange = ( frame >= 0 && frame < d->frameCount );
    bool hasKeyFrame = d->keyFrames.contains(frame);

    d->createKeyFrameAction->setVisible( frameInRange && !hasKeyFrame );
    d->removeKeyFrameAction->setVisible( frameInRange && hasKeyFrame );

    d->menu->exec( event->globalPos() );
}

void QxTimeLineEditor::dragEnterEvent(QDragEnterEvent *event)
{
    // Ignore if drag event is external
    if( event->source() != this ) {
        event->ignore();
        return;
    }

    const MimeData *mime = qobject_cast<const MimeData *>( event->mimeData() );
    event->setAccepted( mime );
    if( mime ) {
        Q_D( QxTimeLineEditor );
        d->dragItem.setPos( d->snapToScene( event->pos() ) );
        d->dragItem.setVisible( true );
    }
}

void QxTimeLineEditor::dragMoveEvent(QDragMoveEvent *event)
{
    // Ignore if drag event is external
    if( event->source() != this ) {
        event->ignore();
        return;
    }

    const MimeData *mime = qobject_cast<const MimeData *>( event->mimeData() );
    event->setAccepted( mime );

    if( mime ) {
        Q_D( QxTimeLineEditor );
        d->dragItem.setPos( d->snapToScene( event->pos() ) );
    }
}

void QxTimeLineEditor::dropEvent(QDropEvent *event)
{
    Q_D( QxTimeLineEditor );

    // Ignore if drag event is external
    if( event->source() != this ) {
        event->ignore();
        return;
    }

    const MimeData *mime = qobject_cast<const MimeData *>( event->mimeData() );
    event->setAccepted( mime );
    if( mime ) {
        int frameFrom = d->frameAt( mime->keyFrameItem()->pos().toPoint() );
        int frameTo = d->frameAt( event->pos() );
        moveKeyFrame( frameFrom, frameTo );
    }

    // Update current frame
    setCurrentFrame( d->frameAt( event->pos() ) );

    d->dragItem.setVisible( false );

}

void QxTimeLineEditor::drawBackground(QPainter *painter, const QRectF &rect)
{
    Q_D( QxTimeLineEditor );

    // Draw the background
    QGraphicsView::drawBackground( painter, rect );

    // Ofsetted frames are darkened
    painter->setCompositionMode( QPainter::CompositionMode_Multiply );
    painter->resetMatrix();
    int left = d->frameCount * QPixmap( KeyFrameFileName ).width();
    QRectF r( QPointF( left, 0 ), QPointF( viewport()->width(), viewport()->height() ) );
    painter->fillRect( r.intersected(rect), palette().base().color().darker( 120 ) );

    // Gray out if disabled
//    painter->setCompositionMode( QPainter::CompositionMode_Multiply );
//    painter->fillRect( sceneRect()/*.intersected(rect)*/, palette().base() );

    // Restore composition mode
    painter->setCompositionMode( QPainter::CompositionMode_SourceOver );
}

QxTimeLineEditorPrivate::QxTimeLineEditorPrivate(QxTimeLineEditor *widget)
    : q_ptr( widget )
    , menu( new QMenu( widget ) )
{
    createKeyFrameAction = menu->addAction( tr( "Create keyframe" ), this, SLOT( createKeyFrameAndEmit() ) );
    removeKeyFrameAction = menu->addAction( tr( "Remove keyframe" ), this, SLOT( removeKeyFrame() ) );
}

qreal QxTimeLineEditorPrivate::snapToScene(int x) const
{
    Q_Q( const QxTimeLineEditor );
    QPointF scenePos = q->mapToScene( QPoint( x, 0 ) );
    qreal sceneX = scenePos.x();
    qreal width = static_cast<qreal>( QPixmap( KeyFrameFileName ).width() );
    return sceneX - std::fmod( sceneX, width );
}

QPointF QxTimeLineEditorPrivate::snapToScene(const QPoint &pos) const
{
    return QPointF( snapToScene( pos.x() ), 0.0 );
}

int QxTimeLineEditorPrivate::frameAt(const QPoint &pos) const
{
    int x = static_cast<int>( snapToScene( pos ).x() );
    int width = QPixmap( KeyFrameFileName ).width();
    return x / width;
}

qreal QxTimeLineEditorPrivate::framePos(int frame) const
{
    return frame * QPixmap( KeyFrameFileName ).width();
}

void QxTimeLineEditorPrivate::createKeyFrame()
{
    Q_Q( QxTimeLineEditor );
    q->createKeyFrame( q->currentFrame() );
}

void QxTimeLineEditorPrivate::createKeyFrameAndEmit()
{
    Q_Q( QxTimeLineEditor );
    q->createKeyFrameAndEmit( q->currentFrame() );
}

void QxTimeLineEditorPrivate::removeKeyFrame()
{
    Q_Q( QxTimeLineEditor );
    q->removeKeyFrame( q->currentFrame() );
}
