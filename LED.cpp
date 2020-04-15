#include "LED.hpp"

LED::LED()
{

}

void LED::draw(QPainter &painter)
{

}


QColor LED::getColor() const
{
    return color;
}

void LED::setColor(const QColor &value)
{
    color = value;
}
