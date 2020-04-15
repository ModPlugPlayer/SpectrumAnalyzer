#ifndef LED_HPP
#define LED_HPP
#include <QColor>
#include "Drawable.hpp"
#include "Dimmable.hpp"

class LED : public Drawable, public Dimmable
{
public:
    LED();
    inline void draw(QPainter &painter) override;

    inline QColor getColor() const;
    inline void setColor(const QColor &value);

    inline void setDimmingPercentage(unsigned const char &dimmingPercentage);
private:
    QColor color;
    QColor dimmedColor;
};

inline void LED::setDimmingPercentage(unsigned const char &dimmingPercentage) {
    Dimmable::setDimmingPercentage(dimmingPercentage);
    dimmedColor = color.lighter(dimmingPercentage);
}

inline void LED::draw(QPainter &painter)
{

}

inline QColor LED::getColor() const
{
    return color;
}

inline void LED::setColor(const QColor &value)
{
    color = value;
    dimmedColor = value.lighter(getDimmingPercentage());
}

#endif // LED_HPP
