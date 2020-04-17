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
    refreshGradient();
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
    QGradientStops dimmedGradientStops;
    for(QGradientStop gradientStop : gradientStops){
        QColor color = gradientStop.second;
        int alpha = (100-getTransparencyPercentage())*255/100;
        color.setAlpha(alpha);
        color = color.lighter(100-getDimmingPercentage());
        dimmedGradientStops.append(QPair<double,QColor>(gradientStop.first, color));
    }
    dimmedGradient.setStops(dimmedGradientStops);
}

void Bar::refreshGradient()
{
    if(orientation == ORIENTATION::VERTICAL) {
        gradient.setStart(0.0,getSizes().height());
        gradient.setFinalStop(QPointF(0,0));
        dimmedGradient.setStart(0.0,getSizes().height());
        dimmedGradient.setFinalStop(QPointF(0,0));
    }
    else {
        gradient.setStart(getSizes().width(),0.0);
        gradient.setFinalStop(QPointF(0,0));
        dimmedGradient.setStart(getSizes().width(), 0.0);
        dimmedGradient.setFinalStop(QPointF(0,0));
    }
}
