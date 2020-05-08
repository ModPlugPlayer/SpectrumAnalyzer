#include "Gradient.hpp"
#include <QPropertyAnimation>
//#include <algorithm>

Gradient::Gradient()
{

}

void Gradient::setStops(const QGradientStops &stops)
{
    QLinearGradient::setStops(stops);
    stopsMap.clear();
    for(QGradientStop stop:stops){
        stopsMap.insert(stop.first, stop.second);
    }
}

void Gradient::setColorAt(qreal pos, const QColor &color)
{
    QLinearGradient::setColorAt(pos, color);
    stopsMap.insert(pos, color);
}

QColor Gradient::getColor(qreal key) const {
    qreal rkey = 1.0-key;
    return getInterpolatedColor(rkey);
}


QColor Gradient::getInterpolatedColor(qreal key) const
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
QColor Gradient::getColor(double value)
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
QColor Gradient::interpolate(QColor start,QColor end,double ratio)
{
    int r = (int)(ratio*start.red() + (1-ratio)*end.red());
    int g = (int)(ratio*start.green() + (1-ratio)*end.green());
    int b = (int)(ratio*start.blue() + (1-ratio)*end.blue());
    return QColor::fromRgb(r,g,b);
}
*/
