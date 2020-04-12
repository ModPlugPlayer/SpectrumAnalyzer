#ifndef BAR_HPP
#define BAR_HPP
#include <QWidget>
#include "Enums.hpp"
#include "SpectrumAnalyzer.hpp"
class Bar
{
public:
    Bar(SpectrumAnalyzerParameters &spectrumAnalyzerParameters);
    virtual void draw(QPainter &painter) = 0;
    void refreshCalculatedParameters(int width, int height);
    void setValue(double value);
    double getValue();
    double getLength();

protected:
    SpectrumAnalyzerParameters spectrumAnalyzerParameters;
    CalculatedParameters calculatedParameters;
    QLinearGradient gradient;
    double value;
    double length;
    QPointF coordinates;
    Bar();
};

#endif // BAR_HPP
