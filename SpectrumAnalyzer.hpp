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
    void paintContinuous(QPainter &painter, DRAWMODE drawMode, int barAmount);

signals:

};

#endif // SPECTRUMANALYZER_HPP
