#ifndef CONTINUOUSBAR_HPP
#define CONTINUOUSBAR_HPP
#include "Bar.hpp"

class ContinuousBar : public Bar
{
public:
    ContinuousBar(SpectrumAnalyzer *spectrumAnalyzer);
    void draw(QPainter &painter) override;
};

#endif // CONTINUOUSBAR_HPP
