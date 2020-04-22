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
    inline void setTransparencyPercentage(unsigned const char &transparencyPercentage);
    inline bool getLight() const;
    inline void setLight(bool value);

private:
    bool light;
    QColor color;
    QColor dimmedColor;
    void refreshColor();
    void refreshDimmedColor();
};

inline void LED::setDimmingPercentage(unsigned const char &dimmingPercentage) {
    Dimmable::setDimmingPercentage(dimmingPercentage);
    refreshDimmedColor();
}

inline void LED::setTransparencyPercentage(unsigned const char &transparencyPercentage) {
    Dimmable::setTransparencyPercentage(transparencyPercentage);
    refreshDimmedColor();
}

inline void LED::draw(QPainter &painter)
{
    painter.fillRect(QRectF(getCoordinates().x(), getCoordinates().y(), getSizes().width(), getSizes().height()), light?color:dimmedColor);
}

inline QColor LED::getColor() const
{
    return color;
}

inline void LED::setColor(const QColor &value)
{
    color = value;
    refreshDimmedColor();
}

inline bool LED::getLight() const
{
    return light;
}

inline void LED::setLight(bool value)
{
    light = value;
}


#endif // LED_HPP
