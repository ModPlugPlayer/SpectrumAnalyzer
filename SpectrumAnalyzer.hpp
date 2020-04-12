#ifndef SPECTRUMANALYZER_HPP
#define SPECTRUMANALYZER_HPP

#include <QWidget>
#include "Enums.hpp"

struct Point {
    int x;
    int y;
};

struct DiscreteParameters {
    int barLedAmount;
    double barLedGapPercent;
};

struct SpectrumAnalyzerParameters{
    DRAWMODE drawMode;
    int barAmount;
    double peakValue;
    double barGapRatio;
    DiscreteParameters discreteParameters;
};


class SpectrumAnalyzer : public QWidget
{
    Q_OBJECT
public:
    explicit SpectrumAnalyzer(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
    Point startingPoint, endingPoint;
    QLinearGradient gradient;
    QGradientStops stops;
    double * barValues;
    SpectrumAnalyzerParameters spectrumAnalyzerParameters;
    void paintContinuous(QPainter &painter, SpectrumAnalyzerParameters &spectrumAnalyzerParameters, double* barValues);
    void paintDiscrete(QPainter &painter, SpectrumAnalyzerParameters &spectrumAnalyzerParameters, double *barValues);
signals:

};

#endif // SPECTRUMANALYZER_HPP
