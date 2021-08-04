#ifndef PARAMETERS_HPP
#define PARAMETERS_HPP
#include <QGradientStops>

struct DiscreteParameters {
    int barLedAmount;
    double ledGapRatio;
};

struct ContinousParameters {
    double peakHeight;
};

enum class BarType {
    Discrete, Continuous
};

struct SpectrumAnalyzerParameters{
    BarType barType = BarType::Discrete;
    Qt::Orientation barDirection;
    unsigned char dimmingPercentage = 0;
    unsigned char transparencyPercentage = 100;
    double blackCoefficient;
    int barAmount;
    double peakValue;
    double floorValue;
    double barGapRatio;
    DiscreteParameters discreteParameters;
    ContinousParameters continuousParameters;
    QGradientStops gradientStops;
};

#endif // PARAMETERS_HPP
