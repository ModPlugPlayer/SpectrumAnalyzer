#ifndef SINEITEM_HPP
#define SINEITEM_HPP

#include <QGraphicsItem>



class SineItem : public QGraphicsItem
{
public:
    SineItem();

    // QGraphicsItem interface
public:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // SINEITEM_HPP
