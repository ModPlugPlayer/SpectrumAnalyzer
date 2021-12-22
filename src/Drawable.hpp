/*
Drawable class declarations and definitions of Spectrum Analyzer
Copyright (C) 2020 Volkan Orhan

This library is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation; either version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with this library; if not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/
#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

#include <QPointF>
#include <QSizeF>
#include <QPainter>

class Drawable
{
public:
    inline Drawable();

    virtual void draw(QPainter &painter) = 0;

    inline QPointF getCoordinates() const;
    inline void setCoordinates(const QPointF &value);

    inline QSizeF getSizes() const;
    inline void setSizes(const QSizeF &value);

private:
    QPointF coordinates;
    QSizeF sizes;
};

inline Drawable::Drawable()
{

}

inline QPointF Drawable::getCoordinates() const
{
    return coordinates;
}

inline void Drawable::setCoordinates(const QPointF &value)
{
    coordinates = value;
}

inline QSizeF Drawable::getSizes() const
{
    return sizes;
}

inline void Drawable::setSizes(const QSizeF &value)
{
    sizes = value;
}

#endif // DRAWABLE_HPP
