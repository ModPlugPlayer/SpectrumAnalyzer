#ifndef GRADIENT_HPP
#define GRADIENT_HPP
#include <QLinearGradient>
#include <QMap>
#include <QColor>

class Gradient : public QLinearGradient
{
public:
    Gradient();
    void setStops(const QGradientStops &stops);
    void setColorAt(qreal pos, const QColor &color);
    QColor getColor(qreal key) const;
private:
    QMap<qreal,QColor> stopsMap;/*
    QColor getColor(double value);
    QColor interpolate(QColor start,QColor end,double ratio);
*/
};

#endif // GRADIENT_HPP
