#ifndef SPECTRUMANALYZER_HPP
#define SPECTRUMANALYZER_HPP

#include <QWidget>
#include "Parameters.hpp"
#include "ContinuousBar.hpp"
#include "DiscreteBar.hpp"

class SpectrumAnalyzer : public QWidget
{
    Q_OBJECT
public:
    explicit SpectrumAnalyzer(QWidget *parent = nullptr);
    SpectrumAnalyzerParameters parameters;

private:
    QVector<DiscreteBar> bars;
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    QGradientStops gradientStops;
    double * barValues;
   // void paintContinuous(QPainter &painter, SpectrumAnalyzerParameters &spectrumAnalyzerParameters, double* barValues);
    //void paintDiscrete(QPainter &painter, SpectrumAnalyzerParameters &spectrumAnalyzerParameters, double *barValues);
signals:

};

#endif // SPECTRUMANALYZER_HPP
