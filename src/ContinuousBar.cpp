#include "ContinuousBar.hpp"
#include <QPainter>
#include <QDebug>

ContinuousBar::ContinuousBar(){
}

void ContinuousBar::draw(QPainter &painter) {
    if(getOrientation() == ORIENTATION::VERTICAL){
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