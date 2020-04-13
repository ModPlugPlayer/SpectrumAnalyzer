#include "SineItem.hpp"
#include "SpectrumAnalyzer.hpp"
#include <QtGui>
#include <QDebug>
#include <cmath>
SpectrumAnalyzer::SpectrumAnalyzer(QWidget *parent) : QWidget(parent)
{
    gradient = QLinearGradient();
    gradient.setSpread(QGradient::Spread::PadSpread);
    parameters.gradientStops.append(QPair<double,QColor>(0.0, Qt::red));
    parameters.gradientStops.append(QPair<double,QColor>(0.5, Qt::yellow));
    parameters.gradientStops.append(QPair<double,QColor>(1.0, Qt::green));

    gradient.setStops(parameters.gradientStops);
    barValues = new double[20];
    for(int i=0; i<20; i++)
        barValues[i] = (i+1)*5;

    parameters.barDirection = ORIENTATION::VERTICAL;
    parameters.barAmount = 20;
    parameters.peakValue = 100;
    parameters.barGapRatio = 0.9;
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
    startingPoint.x = event->region().begin()->left();
    startingPoint.y = event->region().begin()->top();
    endingPoint.x = event->region().begin()->right();
    endingPoint.y = event->region().begin()->bottom();
    paintContinuous(painter, parameters, barValues);
}

void SpectrumAnalyzer::refreshCalculatedParameters(int width, int height)
{
    SpectrumAnalyzerParameters &p = parameters;
    if(parameters.barDirection == ORIENTATION::VERTICAL)
        calculatedParameters.peakLength = height;
    else
        calculatedParameters.peakLength = width;

    int gapAmount = p.barAmount -1;
    double totalWidth = p.barDirection==ORIENTATION::VERTICAL?width:height;
    calculatedParameters.peakLength = p.barDirection==ORIENTATION::VERTICAL?height:width;
    calculatedParameters.barWidth = (totalWidth / p.barAmount)*p.barGapRatio;
    calculatedParameters.gapWidth = (totalWidth - (calculatedParameters.barWidth*p.barAmount))/(double)gapAmount;
}

