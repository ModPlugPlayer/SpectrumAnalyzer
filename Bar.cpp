#include "Bar.hpp"

Bar::Bar() {
    gradient.setSpread(QGradient::Spread::PadSpread);
}

void Bar::setValue(const double &value) {
    this->value = value;
    refreshVuLength();
}

double Bar::getValue(){
    return this->value;
}

void Bar::setPeakValue(const double &peakValue) {
    this->peakValue = peakValue;
    refreshVuLength();
}

double Bar::getPeakValue(){
    return this->peakValue;
}

ORIENTATION Bar::getOrientation() const
{
    return orientation;
}

void Bar::setOrientation(const ORIENTATION &value)
{
    orientation = value;
    refreshVuLength();
}

QGradientStops Bar::getGradientStops() const
{
    return gradient.stops();
}

void Bar::setGradientStops(const QGradientStops &gradientStops)
{
    gradient.setStops(gradientStops);
}

double Bar::getVuLength() const
{
    return vuLength;
}

void Bar::refreshVuLength()
{
    double peakLength = orientation == ORIENTATION::VERTICAL ? getSizes().height() : getSizes().width();
    if(peakValue != 0)
        this->vuLength = peakLength * value / peakValue;
}
