#include "DiscreteBar.hpp"

DiscreteBar::DiscreteBar(QWidget *parent):Bar(parent){
}

void DiscreteBar::draw(QPainter &painter) {

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
}

double DiscreteBar::getLedGapRatio() const
{
    return ledGapRatio;
}

void DiscreteBar::setLedGapRatio(double value)
{
    ledGapRatio = value;
}
