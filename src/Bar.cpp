#include "Bar.hpp"

Bar::Bar() {
    gradient.setSpread(QGradient::Spread::PadSpread);
    gradient.setInterpolationMode(QLinearGradient::InterpolationMode::ColorInterpolation);
    value = 0;
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

void Bar::setFloorValue(const double &floorValue) {
    this->floorValue = floorValue;
    refresh();
}

double Bar::getFloorValue(){
    return this->floorValue;
}

Qt::Orientation Bar::getOrientation() const
{
    return orientation;
}

void Bar::setOrientation(const Qt::Orientation &value)
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
    double peakLength = orientation == Qt::Orientation::Vertical ? getSizes().height() : getSizes().width();
    if(peakValue != 0)
        this->vuLength = peakLength * value / (peakValue - floorValue);
}

void Bar::refreshDimmedGradient()
{
    QGradientStops gradientStops = getGradientStops();
    QGradientStops dimmedGradientStops;
    for(QGradientStop &gradientStop : gradientStops){
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
    if(orientation == Qt::Orientation::Vertical) {
        gradient.setStart(0.0, getSizes().height());
        gradient.setFinalStop(QPointF(0.0, 0.0));
        dimmedGradient.setStart(0.0, getSizes().height());
        dimmedGradient.setFinalStop(QPointF(0.0, 0.0));
    }
    else {
        gradient.setStart(0.0, 0.0);
        gradient.setFinalStop(QPointF(getSizes().width(), 0.0));
        dimmedGradient.setStart(0.0, 0.0);
        dimmedGradient.setFinalStop(QPointF(getSizes().width(), 0.0));
    }
}
