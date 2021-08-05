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
