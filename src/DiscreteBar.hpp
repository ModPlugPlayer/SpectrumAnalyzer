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

    inline void setSizes(const QSizeF &sizes);

private:
    QVector<LED> leds;
    double ledGapRatio;
    qreal ledSize, gapSize;
    void recalculateLeds();
};

inline void DiscreteBar::setSizes(const QSizeF &sizes)
{
    Bar::setSizes(sizes);
    recalculateLeds();
}

#endif // DISCRETEBAR_HPP
