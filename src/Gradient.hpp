/*
Gradient class declarations and definitions of Spectrum Analyzer
Copyright (C) 2020 Volkan Orhan

This library is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation; either version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with this library; if not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

#pragma once

#include <QLinearGradient>
#include <QMap>
#include <QColor>

#include "Gradient.hpp"
#include <QPropertyAnimation>

//#include <algorithm>

class Gradient : public QLinearGradient
{
public:
    inline Gradient();
    inline void setStops(const QGradientStops &stops);
    inline void setColorAt(qreal pos, const QColor &color);
    inline QColor getColor(qreal key) const;
private:
    QMap<qreal,QColor> stopsMap;
    inline QColor getInterpolatedColor(qreal key) const;
    /*
    inline QColor getColor(double value);
    inline QColor interpolate(QColor start,QColor end,double ratio);
    */
};


inline Gradient::Gradient()
{

}

inline void Gradient::setStops(const QGradientStops &stops)
{
    QLinearGradient::setStops(stops);
    stopsMap.clear();
    for(QGradientStop stop:stops){
        stopsMap.insert(stop.first, stop.second);
    }
}

inline void Gradient::setColorAt(qreal pos, const QColor &color)
{
    QLinearGradient::setColorAt(pos, color);
    stopsMap.insert(pos, color);
}

inline QColor Gradient::getColor(qreal key) const {
    qreal rkey = 1.0-key;
    return getInterpolatedColor(rkey);
}


inline QColor Gradient::getInterpolatedColor(qreal key) const
{
    // key must belong to [0,1]
    key = qBound(0.0, key, 1.0);
    //key = std::clamp<qreal>(key, 0.0, 1.0);

    // directly get color if known
    if(stopsMap.contains(key))
    {
        return stopsMap.value(key);
    }

    // else, emulate a linear gradient
    QPropertyAnimation interpolator ;
    const qreal granularite = 100.0 ;
    interpolator.setEasingCurve(QEasingCurve::Linear) ;
    interpolator.setDuration(granularite) ;
    foreach( qreal key, stopsMap.keys() )
    {
        interpolator.setKeyValueAt(key, stopsMap.value(key)) ;
    }
    interpolator.setCurrentTime(key*granularite) ;
    return interpolator.currentValue().value<QColor>() ;
}
/*
inline QColor Gradient::getColor(double value)
{
    //Asume mGradientColors.count()>1 and value=[0,1]
    double stepbase = 1.0/(mGradientColors.count()-1);
    int interval=mGradientColors.count()-1; //to fix 1<=0.99999999;

      for (int i=1; i<mGradientColors.count();i++)//remove begin and end
        {
            if(value<=i*stepbase ){interval=i;break;}
        }
       double percentage = (value-stepbase*(interval-1))/stepbase;
       QColor color(interpolate(mGradientColors[interval],mGradientColors[interval-1],percentage));
       return color;
}
inline QColor Gradient::interpolate(QColor start,QColor end,double ratio)
{
    int r = (int)(ratio*start.red() + (1-ratio)*end.red());
    int g = (int)(ratio*start.green() + (1-ratio)*end.green());
    int b = (int)(ratio*start.blue() + (1-ratio)*end.blue());
    return QColor::fromRgb(r,g,b);
}
*/
