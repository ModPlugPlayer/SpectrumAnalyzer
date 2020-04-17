#include "Bar.hpp"

Bar::Bar() {
    gradient.setSpread(QGradient::Spread::PadSpread);
    gradient.setInterpolationMode(QLinearGradient::InterpolationMode::ColorInterpolation);
}

void Bar::setValue(const double &value) {
    this->value = value;
    refresh();
}

double Bar::getValue(){
    return this->value;
}

void Bar::setPeakValue(const double &peakValue) {
    this->peakValue = peakValue;
    refresh();
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
    refresh();
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

void Bar::refresh()
{
    refreshVuLength();
    refreshDimmedGradient();
}

void Bar::refreshVuLength()
{
    double peakLength = orientation == ORIENTATION::VERTICAL ? getSizes().height() : getSizes().width();
    if(peakValue != 0)
        this->vuLength = peakLength * value / peakValue;
}

void Bar::refreshDimmedGradient()
{
    QGradientStops gradientStops = getGradientStops();
    for(QGradientStop gradientStop : gradientStops){
        QColor color = gradientStop.second;
        color.setAlpha((100-getDimmingPercentage())*255/100);
        dimmedGradient.setColorAt(gradientStop.first, color);
    }
}
