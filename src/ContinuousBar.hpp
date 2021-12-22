/*
ContinuousBar class declarations and definitions of Spectrum Analyzer
Copyright (C) 2020 Volkan Orhan

This library is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation; either version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with this library; if not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

#pragma once
#include "Bar.hpp"

class ContinuousBar : public Bar
{
public:
    inline ContinuousBar();
    inline void draw(QPainter &painter) override;
};

inline ContinuousBar::ContinuousBar()
    :Bar(BarType::Continuous)
{
}

inline void ContinuousBar::draw(QPainter &painter) {
    if(getOrientation() == Qt::Orientation::Vertical){
        if(getTransparencyPercentage() != 100)
            painter.fillRect(QRectF(getCoordinates().x(), getCoordinates().y(), getSizes().width(), getSizes().height()), dimmedGradient);
        painter.fillRect(QRectF(getCoordinates().x(), ((qreal) getCoordinates().y()) + getSizes().height() - getVuLength(), getSizes().width(), getVuLength()), gradient);
    }
    else{
        if(getTransparencyPercentage() != 100)
            painter.fillRect(QRectF(getCoordinates().x(), getCoordinates().y(), getSizes().width(), getSizes().height()), dimmedGradient);
        painter.fillRect(QRectF(getCoordinates().x(), getCoordinates().y(), getVuLength(), getSizes().height()), gradient);
    }
}
