/*
Bar class declarations and definitions of Spectrum Analyzer
Copyright (C) 2020 Volkan Orhan

This library is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation; either version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with this library; if not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

#pragma once
#include <QWidget>
#include "Drawable.hpp"
#include "Dimmable.hpp"
#include "Gradient.hpp"
#include "Parameters.hpp"

class Bar : public Drawable, public Dimmable
{
public:
    inline virtual void draw(QPainter &painter) = 0;
    inline virtual BarType getBarType() = 0;

    inline double getValue();
    inline void setValue(const double &value);

    inline double getPeakValue();
    inline void setPeakValue(const double &peakValue);

    inline double getFloorValue();
    inline void setFloorValue(const double &floorValue);

    inline Qt::Orientation getOrientation() const;
    inline void setOrientation(const Qt::Orientation &value);

    inline QGradientStops getGradientStops() const;
    inline void setGradientStops(const QGradientStops &gradientStops);

    inline void setSizes(const QSizeF &sizes);

    inline double getVuLength() const;

    inline void setDimmingPercentage(const int &dimmingPercentage);

    inline void setTransparencyPercentage(const unsigned char &transparencyPercentage);

private:
    double value = 0;
    double peakValue;
    double floorValue = 0;
    double vuLength;
    Qt::Orientation orientation;
    inline void refresh();
    inline void refreshVuLength();
    inline void refreshGradient();
    inline void refreshDimmedGradient();
protected:
    Gradient gradient;
    Gradient dimmedGradient;
    inline QColor getGradientColor(qreal key);
    inline QColor getDimmedGradientColor(qreal key);
    inline void init();
};

inline QColor Bar::getGradientColor(qreal key) {
    return gradient.getColor(key);
}

inline QColor Bar::getDimmedGradientColor(qreal key) {
    return dimmedGradient.getColor(key);
}

inline void Bar::setSizes(const QSizeF &sizes)
{
    Drawable::setSizes(sizes);
    refresh();
}

inline void Bar::setDimmingPercentage(const int &dimmingPercentage)
{
    Dimmable::setDimmingPercentage(dimmingPercentage);
    refresh();
}

inline void Bar::setTransparencyPercentage(const unsigned char &transparencyPercentage)
{
    Dimmable::setTransparencyPercentage(transparencyPercentage);
    refresh();
}

inline void Bar::init() {
    gradient.setSpread(QGradient::Spread::PadSpread);
    gradient.setInterpolationMode(QLinearGradient::InterpolationMode::ColorInterpolation);
    value = 0;
}

inline void Bar::setValue(const double &value) {
    this->value = value;
    refresh();
}

inline double Bar::getValue(){
    return this->value;
}

inline void Bar::setPeakValue(const double &peakValue) {
    double oldValue = value;
    double oldPeakValue = this->peakValue;
    double newPeakValue = peakValue;
    this->peakValue = peakValue;
    value = (newPeakValue - floorValue)*(oldValue-floorValue)/(oldPeakValue-floorValue);
    refresh();
}

inline double Bar::getPeakValue(){
    return this->peakValue;
}

inline void Bar::setFloorValue(const double &floorValue) {
    double oldValue = value;
    double oldFloorValue = this->floorValue;
    double newFloorValue = floorValue;
    this->floorValue = floorValue;
    value = (peakValue - newFloorValue)*(oldValue-floorValue)/(peakValue-oldFloorValue);
    refresh();
}

inline double Bar::getFloorValue(){
    return this->floorValue;
}

inline Qt::Orientation Bar::getOrientation() const
{
    return orientation;
}

inline void Bar::setOrientation(const Qt::Orientation &value)
{
    orientation = value;
    refresh();
}

inline QGradientStops Bar::getGradientStops() const
{
    return gradient.stops();
}

inline void Bar::setGradientStops(const QGradientStops &gradientStops)
{
    gradient.setStops(gradientStops);
}

inline double Bar::getVuLength() const
{
    return vuLength;
}

inline void Bar::refresh()
{
    refreshVuLength();
    refreshGradient();
    refreshDimmedGradient();
}

inline void Bar::refreshVuLength()
{
    double peakLength = orientation == Qt::Orientation::Vertical ? getSizes().height() : getSizes().width();
    if(peakValue-floorValue != 0)
        this->vuLength = peakLength * (value-floorValue) / (peakValue - floorValue);
    else
        this->vuLength = peakLength;
}

inline void Bar::refreshDimmedGradient()
{
    QGradientStops gradientStops = getGradientStops();
    QGradientStops dimmedGradientStops;
    for(QGradientStop &gradientStop : gradientStops){
        QColor color = gradientStop.second;
        //darker if dimmingPercentage is between -99 and -1
        //lighter if dimmingPercentage is between 1 and 99
        //black if dimmingPercentage is -100
        //white if dimmingPercentage is 100
        int dimmingPercentage = getDimmingPercentage();
        if(dimmingPercentage == 100)
            color = QColorConstants::White;
        else if(dimmingPercentage == -100)
            color = QColorConstants::Black;
        else if(dimmingPercentage > 0)
            color = color.lighter(100 + dimmingPercentage);
        else if(dimmingPercentage < 0)
            color = color.lighter(100 + dimmingPercentage);
        int alpha = (100-getTransparencyPercentage())*255/100;
        color.setAlpha(alpha);
        dimmedGradientStops.append(QPair<double,QColor>(gradientStop.first, color));
    }
    dimmedGradient.setStops(dimmedGradientStops);
}

inline void Bar::refreshGradient()
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
