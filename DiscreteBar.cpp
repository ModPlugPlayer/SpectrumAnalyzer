#include "DiscreteBar.hpp"
#include "MathUtil.hpp"
#include <QDebug>

DiscreteBar::DiscreteBar() {
}

void DiscreteBar::draw(QPainter &painter) {
    if(getOrientation() == ORIENTATION::VERTICAL){
        for(LED &led:leds){
            if(getVuLength()>=getSizes().height() - led.getCoordinates().y())
                led.setLight(true);
            else
                led.setLight(false);
            led.draw(painter);
        }
    }
    else{
        for(LED &led:leds){
            if(getVuLength()>=led.getCoordinates().x())
                led.setLight(true);
            else
                led.setLight(false);
            led.draw(painter);
        }
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
        if(getOrientation() == ORIENTATION::VERTICAL) {
            MathUtil::divideLineIntoSegmentsAndGaps(getSizes().height(), this->getLedAmount(), this->getLedGapRatio(), ledSize, gapSize);
            for(int i=0; i<getLedAmount(); i++) {
                qreal length = i*(ledSize + gapSize);
                qreal centerLength = length + (ledSize/2);
                leds[i].setCoordinates(QPointF(getCoordinates().x(), length));
                leds[i].setSizes(QSizeF(getSizes().width(), ledSize));
                leds[i].setColor(gradient.getColor((getSizes().height() - centerLength)/getSizes().height()));
                leds[i].setDimmingPercentage(getDimmingPercentage());
                leds[i].setTransparencyPercentage(getTransparencyPercentage());
            }
        }
        else {
            MathUtil::divideLineIntoSegmentsAndGaps(getSizes().width(), this->getLedAmount(), this->getLedGapRatio(), ledSize, gapSize);
            for(int i=0; i<getLedAmount(); i++) {
                qreal length = i*(ledSize + gapSize);
                qreal centerLength = length + (ledSize/2);
                leds[i].setCoordinates(QPointF(length, getCoordinates().y()));
                leds[i].setSizes(QSizeF(ledSize, getSizes().height()));
                leds[i].setColor(gradient.getColor((getSizes().width() - centerLength)/getSizes().width()));
                leds[i].setDimmingPercentage(getDimmingPercentage());
                leds[i].setTransparencyPercentage(getTransparencyPercentage());
            }
        }
    }
}
