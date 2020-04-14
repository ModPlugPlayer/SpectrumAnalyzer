#ifndef SPECTRUMANALYZER_HPP
#define SPECTRUMANALYZER_HPP

#include <QWidget>
#include "Enums.hpp"

struct Point {
    int x;
    int y;
};

struct CalculatedParameters {
    double barWidth;
    double gapWidth;
    double peakLength;
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

class SpectrumAnalyzer : public QWidget
{
    Q_OBJECT
public:
    explicit SpectrumAnalyzer(QWidget *parent = nullptr);
    void refreshCalculatedParameters(int width, int height);
    CalculatedParameters calculatedParameters;
    SpectrumAnalyzerParameters parameters;

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    QSize size;
    QLinearGradient gradient;
    double * barValues;
    void paintContinuous(QPainter &painter, SpectrumAnalyzerParameters &spectrumAnalyzerParameters, double* barValues);
    void paintDiscrete(QPainter &painter, SpectrumAnalyzerParameters &spectrumAnalyzerParameters, double *barValues);
private:
signals:

};

#endif // SPECTRUMANALYZER_HPP
