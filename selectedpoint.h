#ifndef SELECTEDPOINT_H
#define SELECTEDPOINT_H

#include <QGraphicsItem>

// Javno nasledjuje klasu QGraphicsItem
class SelectedPoint : public QGraphicsItem
{
public:
    //konstruktor
    SelectedPoint();
    //destruktor
    ~SelectedPoint();

signals:
    void sgSelectedPointMoved();

protected:
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0);
    QRectF boundingRect() const;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event);

};





#endif // SELECTEDPOINT_H
