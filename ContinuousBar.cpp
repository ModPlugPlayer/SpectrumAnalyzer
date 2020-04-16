#include "ContinuousBar.hpp"
#include <QPainter>
#include <QDebug>

ContinuousBar::ContinuousBar(){
}

void ContinuousBar::draw(QPainter &painter) {
    if(getOrientation() == ORIENTATION::VERTICAL){
        if(isDimmable())
            painter.fillRect(QRectF(getCoordinates().x(), getCoordinates().y(), getSizes().width(), getSizes().height()), dimmedGradient);
        painter.fillRect(QRectF(getCoordinates().x(), ((qreal) getCoordinates().y()) + getSizes().height() - getVuLength(), getSizes().width(), getVuLength()), gradient);
    }
    else
        painter.fillRect(QRectF(getCoordinates().x(), getCoordinates().y(), getVuLength(), getSizes().height()), gradient);
}
