#ifndef LED_HPP
#define LED_HPP
#include <QColor>
#include "Drawable.hpp"

class LED : public Drawable
{
public:
    LED();
    void draw(QPainter &painter) override;

    QColor getColor() const;
    void setColor(const QColor &value);

private:
    QColor color;
};

#endif // LED_HPP
