#include "DiscreteBar.hpp"
#include "MathUtil.hpp"
#include <QDebug>

DiscreteBar::DiscreteBar() {
}

void DiscreteBar::draw(QPainter &painter) {
    if(getOrientation() == ORIENTATION::VERTICAL){
        //if(getTransparencyPercentage() != 100)
        //   painter.fillRect(QRectF(getCoordinates().x(), getCoordinates().y(), getSizes().width(), getSizes().height()), dimmedGradient);

        for(LED &led:leds)
            led.draw(painter);

        //painter.fillRect(QRectF(getCoordinates().x(), ((qreal) getCoordinates().y()) + getSizes().height() - ledSize, getSizes().width(), ledSize), gradient.getColor(ledSize/getSizes().height()));
        //painter.fillRect(QRectF(getCoordinates().x(), ((qreal) getCoordinates().y()) + getSizes().height() - getVuLength(), getSizes().width(), getVuLength()), gradient);
    }
    else{
        if(getTransparencyPercentage() != 100)
            painter.fillRect(QRectF(getCoordinates().x(), getCoordinates().y(), getSizes().width(), getSizes().height()), dimmedGradient);
        painter.fillRect(QRectF(getCoordinates().x(), getCoordinates().y(), getVuLength(), getSizes().height()), gradient);
    }
}

int DiscreteBar::getLedAmount() const
{
    return leds.size();
}

void DiscreteBar::setLedAmount(int ledAmount)
{
    leds.clear();
    leds.resize(ledAmount);
    leds.fill(LED(), ledAmount);
    recalculateLeds();
}

double DiscreteBar::getLedGapRatio() const
{
    return ledGapRatio;
}

void DiscreteBar::setLedGapRatio(double value)
{
    ledGapRatio = value;
    recalculateLeds();
}

void DiscreteBar::recalculateLeds()
{
    if(this->getLedAmount() >0 && this->getLedGapRatio() > 0) {
        MathUtil::divideLineIntoSegmentsAndGaps(getSizes().height(), this->getLedAmount(), this->getLedGapRatio(), ledSize, gapSize);
        for(int i=0; i<getLedAmount(); i++) {
            qreal height = i*(ledSize + gapSize);
            qreal centerHeight = height + (ledSize/2);
            leds[i].setCoordinates(QPointF(getCoordinates().x(), height));
            leds[i].setSizes(QSizeF(getSizes().width(), ledSize));
            leds[i].setColor(gradient.getColor(centerHeight/getSizes().height()));
        }
    }
}
