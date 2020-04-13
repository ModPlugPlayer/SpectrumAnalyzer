#ifndef BAR_HPP
#define BAR_HPP
#include <QWidget>
#include "Enums.hpp"
#include "SpectrumAnalyzer.hpp"
class Bar
{
public:
    Bar(SpectrumAnalyzer *spectrumAnalyzer);
    virtual void draw(QPainter &painter) = 0;
    void setValue(double value);
    double getValue();
    double getLength();

protected:
    SpectrumAnalyzer * spectrumAnalyzer;
    QLinearGradient gradient;
    double value;
    double length;
    QPointF coordinates;
    Bar();
};

#endif // BAR_HPP
