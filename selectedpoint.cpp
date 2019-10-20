#include "selectedpoint.h"

SelectedPoint::SelectedPoint()
{

}

SelectedPoint::~SelectedPoint(){

}

void SelectedPoint::paint( QPainter * painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    // Outer area of cross
    /*painter->setRenderHint(QPainter::Antialiasing);
    QPen pen(Qt::green, CROP_MARK_THICKNESS, Qt::SolidLine, Qt::FlatCap);
    QBrush brush(Qt::green);
    painter->setPen(pen);
    painter->setBrush(brush);
    painter->drawEllipse(QPoint(0,0), CROP_MARK_LENGTH, CROP_MARK_LENGTH);*/
}


QRectF SelectedPoint::boundingRect( void ) const
{
   // int width = CROP_MARK_LENGTH * 4;
    //int height = CROP_MARK_LENGTH * 4;
    //return QRectF(-CROP_MARK_LENGTH*2, -CROP_MARK_LENGTH*2, width, height);
    return QRectF();
}

void SelectedPoint::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    /*QGraphicsItem::mouseMoveEvent(event);
    if (_containerScene->contains(event->scenePos()))
    {
        scene()->update();
        update(event->scenePos().x(), event->scenePos().y(), CROP_MARK_LENGTH * 2, CROP_MARK_LENGTH * 2);
    }

    _containerScene->updateGridPoints();*/
}



