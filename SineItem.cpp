#include "SineItem.hpp"
#include <QtMath>
#include <QPen>
#include <QPainter>

static const float DX = 1;
static const float MAX_X = 50;

SineItem::SineItem()
{

}


QRectF SineItem::boundingRect() const
{
    return QRectF(0, -1, MAX_X, 2);
}

void SineItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen pen;
    pen.setCosmetic(true);
    painter->setPen(pen);
    const int steps = qRound(MAX_X / DX);
    QPointF previousPoint(0, sin(0));
    for(int i = 1; i < steps; ++i) {
        const float x = DX * i;
        QPointF point(x, sin(x));
        painter->drawLine(previousPoint, point);
        previousPoint = point;
    }
    setScale(5.0);
    Q_UNUSED(option)
    Q_UNUSED(widget)
}
