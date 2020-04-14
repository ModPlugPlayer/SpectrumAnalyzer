#ifndef PARAMETERS_HPP
#define PARAMETERS_HPP
#include "Enums.hpp"
#include <QGradientStops>

struct CalculatedParameters {
    double barWidth;
    double gapWidth;
    double totalWidth;
    double peakLength;
    double gapAmount;
};

struct DiscreteParameters {
    int barLedAmount;
    double ledGapRatio;
};

struct SpectrumAnalyzerParameters{
    ORIENTATION barDirection;
    int barAmount;
    double peakValue;
    double barGapRatio;
    DiscreteParameters discreteParameters;
    QGradientStops gradientStops;
};

#endif // PARAMETERS_HPP
