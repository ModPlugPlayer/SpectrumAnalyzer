#ifndef SPECTRUMANALYZER_HPP
#define SPECTRUMANALYZER_HPP

#include <QWidget>
#include "Parameters.hpp"
#include "ContinuousBar.hpp"

class SpectrumAnalyzer : public QWidget
{
    Q_OBJECT
public:
    explicit SpectrumAnalyzer(QWidget *parent = nullptr);
    void refreshCalculatedParameters(int width, int height);
    CalculatedParameters calculatedParameters;
    SpectrumAnalyzerParameters parameters;

private:
    QVector<ContinuousBar> bars;
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    QSize size;
    QGradientStops gradientStops;
    double * barValues;
    void updateBars();
   // void paintContinuous(QPainter &painter, SpectrumAnalyzerParameters &spectrumAnalyzerParameters, double* barValues);
    //void paintDiscrete(QPainter &painter, SpectrumAnalyzerParameters &spectrumAnalyzerParameters, double *barValues);
signals:

};

#endif // SPECTRUMANALYZER_HPP
