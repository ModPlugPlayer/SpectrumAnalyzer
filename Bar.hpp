#ifndef BAR_HPP
#define BAR_HPP
#include <QWidget>
#include "Enums.hpp"
#include "SpectrumAnalyzer.hpp"
#include "Drawable.hpp"
#include "Dimmable.hpp"

class Bar : public Drawable, public Dimmable
{
public:
    Bar(SpectrumAnalyzer *spectrumAnalyzer);
    virtual void draw(QPainter &painter) = 0;

    void setValue(double value);
    double getValue();

protected:
    Bar();
    SpectrumAnalyzer * spectrumAnalyzer;
    QLinearGradient gradient;
    double value;
    double length;
};

#endif // BAR_HPP
