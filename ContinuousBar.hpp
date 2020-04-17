#ifndef CONTINUOUSBAR_HPP
#define CONTINUOUSBAR_HPP
#include "Bar.hpp"
#include <QPaintEvent>
#include <QPainter>
#include <QRectF>

class ContinuousBar : public Bar
{
public:
    ContinuousBar(QWidget *parent);
    inline void paintEvent(QPaintEvent *event);
};

inline void ContinuousBar::paintEvent(QPaintEvent *event){

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    if(getOrientation() == ORIENTATION::VERTICAL){
        if(getTransparencyPercentage() != 100)
            painter.fillRect(QRectF(0, 0, size().width(), size().height()), dimmedGradient);
        painter.fillRect(QRectF(0, ((qreal)size().height()) - getVuLength(), size().width(), getVuLength()), gradient);
    }
    else{
        if(getTransparencyPercentage() != 100)
            painter.fillRect(QRectF(0, 0, size().width(), size().height()), dimmedGradient);
        painter.fillRect(QRectF(0, 0, getVuLength(), size().height()), gradient);
    }

}

#endif // CONTINUOUSBAR_HPP
