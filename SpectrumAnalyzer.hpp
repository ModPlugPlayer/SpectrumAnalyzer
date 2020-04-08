#ifndef SPECTRUMANALYZER_HPP
#define SPECTRUMANALYZER_HPP

#include <QWidget>
#include "Enums.hpp"

struct Point {
    int x;
    int y;
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
    inline void paintContinuous(QPainter &painter, DRAWMODE drawMode, int barAmount, double peakValue, double* barValues);

signals:

};

#endif // SPECTRUMANALYZER_HPP
