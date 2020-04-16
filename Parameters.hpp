#ifndef PARAMETERS_HPP
#define PARAMETERS_HPP
#include "Enums.hpp"
#include <QGradientStops>

struct DiscreteParameters {
    int barLedAmount;
    double ledGapRatio;
};

struct SpectrumAnalyzerParameters{
    ORIENTATION barDirection;
    bool dimmedBackground;
    double blackCoefficient;
    int barAmount;
    double peakValue;
    double barGapRatio;
    DiscreteParameters discreteParameters;
    QGradientStops gradientStops;
};

#endif // PARAMETERS_HPP
