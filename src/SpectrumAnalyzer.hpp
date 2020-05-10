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

    SpectrumAnalyzerParameters getParameters() const;
    void setParameters(const SpectrumAnalyzerParameters &value);

    void setBarValue(size_t barIndex, double value);
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
private:
    SpectrumAnalyzerParameters parameters;
    QVector<DiscreteBar> bars;
    QGradientStops gradientStops;
   // void paintContinuous(QPainter &painter, SpectrumAnalyzerParameters &spectrumAnalyzerParameters, double* barValues);
    //void paintDiscrete(QPainter &painter, SpectrumAnalyzerParameters &spectrumAnalyzerParameters, double *barValues);
signals:

};

#endif // SPECTRUMANALYZER_HPP
