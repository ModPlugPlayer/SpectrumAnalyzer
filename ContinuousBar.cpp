#include "ContinuousBar.hpp"
#include <QPainter>
#include <QDebug>

ContinuousBar::ContinuousBar(){
}

void ContinuousBar::draw(QPainter &painter) {
    if(getOrientation() == ORIENTATION::VERTICAL)
        painter.fillRect(QRectF(getCoordinates().x(), getCoordinates().y(), getSizes().width(), getVuLength()), gradient);
    else
        painter.fillRect(QRectF(getCoordinates().x(), getCoordinates().y(), getVuLength(), getSizes().height()), gradient);
}
