#ifndef DISCRETEBAR_HPP
#define DISCRETEBAR_HPP
#include "Bar.hpp"
#include "LED.hpp"
#include "Parameters.hpp"

class DiscreteBar : public Bar
{
public:
    DiscreteBar();
    void draw(QPainter &painter);
    int getLedAmount() const;
    void setLedAmount(int value);

    double getLedGapRatio() const;
    void setLedGapRatio(double value);

private:
    QVector<LED> leds;
    double ledGapRatio;
};

#endif // DISCRETEBAR_HPP
