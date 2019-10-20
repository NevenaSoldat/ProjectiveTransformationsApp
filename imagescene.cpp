#include "imagescene.h"
#include <QGraphicsSceneMouseEvent>

ImageScene::ImageScene(QObject *parent)
    : QGraphicsScene(parent)
{
}

void ImageScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() != Qt::LeftButton)
        return;

    emit addNewPoint(mouseEvent);
}

void ImageScene::setImageItem(QPixmap* pixmap)
{

    m_pixmapItem = new QGraphicsPixmapItem();

    m_pixmapItem->setPixmap(*pixmap);
}
