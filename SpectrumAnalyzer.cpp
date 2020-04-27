#include "SineItem.hpp"
#include "SpectrumAnalyzer.hpp"
#include <QtGui>
#include <QDebug>
#include <cmath>
#include "MathUtil.hpp"

SpectrumAnalyzer::SpectrumAnalyzer(QWidget *parent) : QWidget(parent)
{
    gradientStops.append(QPair<double,QColor>(0.0, Qt::green));
    gradientStops.append(QPair<double,QColor>(0.5, Qt::yellow));
    gradientStops.append(QPair<double,QColor>(1.0, Qt::red));

    /*
    barValues = new double[20];
    for(int i=0; i<20; i++) {
        barValues[i] = (i+1)*5;
    }
    for(int i=0; i<20; i++){
        bars.push_back(DiscreteBar());
    }*/




    parameters.barDirection = ORIENTATION::HORIZONTAL;
    parameters.barAmount = 2;
    /*
    parameters.barDirection = ORIENTATION::HORIZONTAL;
    parameters.barAmount = 2;
    parameters.dimmingPercentage = 30;
    parameters.transparencyPercentage = 55;
    */
    parameters.peakValue = 100;
    parameters.barGapRatio = 0.95;
    parameters.dimmingPercentage = 20;
    parameters.transparencyPercentage = 65;
    parameters.discreteParameters.ledGapRatio = 0.7;
    parameters.discreteParameters.barLedAmount = 100;

    init();
    //gradient = QGradient::Preset::JuicyCake;

/*
    gradient.setColorAt(0.0, Qt::red);
    gradient.setColorAt(0.5, Qt::yellow);
    gradient.setColorAt(1.0, Qt::green);
    //gradient = QGradient::Seashore;
*/
}

void SpectrumAnalyzer::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    //paintContinuous(painter, parameters, barValues);
    for(Bar &bar:bars) {
        bar.draw(painter);
    }
}

void SpectrumAnalyzer::resizeEvent(QResizeEvent *event)
{
    qreal barWidth, gapWidth;
    if(parameters.barDirection == ORIENTATION::VERTICAL)
        MathUtil::divideLineIntoSegmentsAndGaps<qreal>(size().width(), parameters.barAmount, parameters.barGapRatio, barWidth, gapWidth);
    else
        MathUtil::divideLineIntoSegmentsAndGaps<qreal>(size().height(), parameters.barAmount, parameters.barGapRatio, barWidth, gapWidth);

    int i=0;
    for(DiscreteBar &bar:bars) {
        bar.setOrientation(parameters.barDirection);
        bar.setPeakValue(parameters.peakValue);
        if(parameters.barDirection == ORIENTATION::VERTICAL){
            bar.setSizes(QSizeF(barWidth, size().height()));
            bar.setCoordinates(QPointF((barWidth + gapWidth)*i, 0));
        }
        else {
            bar.setSizes(QSizeF(size().width(), barWidth));
            bar.setCoordinates(QPointF(0, (barWidth + gapWidth)*i));
        }
        bar.setValue(barValues[i]);
        bar.setGradientStops(gradientStops);
        bar.setDimmingPercentage(parameters.dimmingPercentage);
        bar.setTransparencyPercentage(parameters.transparencyPercentage);
        bar.setLedAmount(parameters.discreteParameters.barLedAmount);
        bar.setLedGapRatio(parameters.discreteParameters.ledGapRatio);

        i++;
    }
}

void SpectrumAnalyzer::init()
{
    barValues = new double[parameters.barAmount];

    barValues[0] = 45;
    barValues[1] = 90;
    for(int i=0; i<parameters.barAmount; i++){
        bars.push_back(DiscreteBar());
    }
}
