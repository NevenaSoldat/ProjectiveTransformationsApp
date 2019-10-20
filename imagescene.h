#ifndef IMAGESCENE_H
#define IMAGESCENE_H

#include <QPixmap>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QVector>

class ImageScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit ImageScene(QObject *parent = 0);

    void setImageItem(QPixmap* pixmap);

signals:
    void addNewPoint(QGraphicsSceneMouseEvent *mouseEvent);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

private:
    QGraphicsPixmapItem* m_pixmapItem;

};

#endif // IMAGESCENE_H
