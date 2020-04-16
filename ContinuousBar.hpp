#ifndef CONTINUOUSBAR_HPP
#define CONTINUOUSBAR_HPP
#include "Bar.hpp"

class ContinuousBar : public Bar
{
public:
    ContinuousBar();
    void draw(QPainter &painter) override;
    QGradientStops getGradientStops() const;
    void setGradientStops(const QGradientStops &gradientStops);

private:
    QGradient gradient;
};

#endif // CONTINUOUSBAR_HPP
