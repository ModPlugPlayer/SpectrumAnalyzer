/*
LED class declarations and definitions of Spectrum Analyzer
Copyright (C) 2020 Volkan Orhan

This library is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation; either version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with this library; if not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

#pragma once

#include <QColor>
#include "Drawable.hpp"
#include "Dimmable.hpp"

class LED : public Drawable, public Dimmable
{
public:
    inline LED();
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
    inline void refreshColor();
    inline void refreshDimmedColor();
};


inline LED::LED()
{

}

inline void LED::refreshColor()
{

}

inline void LED::refreshDimmedColor()
{
    int alpha = (100-getTransparencyPercentage())*255/100;
    dimmedColor = color.lighter(100-getDimmingPercentage());
    dimmedColor.setAlpha(alpha);
}


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
