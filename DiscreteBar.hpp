#ifndef DISCRETEBAR_HPP
#define DISCRETEBAR_HPP
#include "Bar.hpp"

class DiscreteBar : public Bar
{
public:
    DiscreteBar(SpectrumAnalyzerParameters &spectrumAnalyzerParameters);
    void draw(QPainter &painter);
};

#endif // DISCRETEBAR_HPP
