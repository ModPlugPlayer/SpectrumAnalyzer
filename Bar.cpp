#include "Bar.hpp"

Bar::Bar(QWidget *parent) : QFrame(parent) {
    gradient.setSpread(QGradient::Spread::PadSpread);
    gradient.setInterpolationMode(QLinearGradient::InterpolationMode::ColorInterpolation);
}

void Bar::setValue(const double value) {
    this->value = value;
    refreshVuLength();
    repaint();
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
    double peakLength = orientation == ORIENTATION::VERTICAL ? size().height() : size().width();
    if(peakValue != 0)
        this->vuLength = peakLength * value / peakValue;
}

void Bar::refreshDimmedGradient()
{
    QGradientStops gradientStops = getGradientStops();
    for(QGradientStop gradientStop : gradientStops){
        QColor color = gradientStop.second;
        int alpha = (100-getTransparencyPercentage())*255/100;
        color.setAlpha(alpha);
        color = color.lighter(100-getDimmingPercentage());
        dimmedGradient.setColorAt(gradientStop.first, color);
    }
}

void Bar::initUI()
{
    //layout = new QGridLayout(this);
    //setLayout(layout);
}

void Bar::refreshGradient()
{
    if(orientation == ORIENTATION::VERTICAL) {
        gradient.setStart(0.0,size().height());
        gradient.setFinalStop(QPointF(0,0));
        dimmedGradient.setStart(0.0,size().height());
        dimmedGradient.setFinalStop(QPointF(0,0));
    }
    else {
        gradient.setStart(size().width(),0.0);
        gradient.setFinalStop(QPointF(0,0));
        dimmedGradient.setStart(size().width(), 0.0);
        dimmedGradient.setFinalStop(QPointF(0,0));
    }
}
