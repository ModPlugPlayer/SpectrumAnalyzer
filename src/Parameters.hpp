#ifndef PARAMETERS_HPP
#define PARAMETERS_HPP
#include <QGradientStops>

struct DiscreteParameters {
    int barLedAmount;
    double ledGapRatio;
};

struct SpectrumAnalyzerParameters{
    Qt::Orientation barDirection;
    unsigned char dimmingPercentage = 0;
    unsigned char transparencyPercentage = 100;
    double blackCoefficient;
    int barAmount;
    double peakValue;
    double floorValue;
    double barGapRatio;
    DiscreteParameters discreteParameters;
    QGradientStops gradientStops;
};

#endif // PARAMETERS_HPP
