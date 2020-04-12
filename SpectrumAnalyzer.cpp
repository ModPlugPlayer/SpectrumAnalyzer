#include "SineItem.hpp"
#include "SpectrumAnalyzer.hpp"
#include <QtGui>
#include <QDebug>
#include <cmath>
SpectrumAnalyzer::SpectrumAnalyzer(QWidget *parent) : QWidget(parent)
{
    gradient = QLinearGradient();
    gradient.setSpread(QGradient::Spread::PadSpread);
    spectrumAnalyzerParameters.gradientStops.append(QPair<double,QColor>(0.0, Qt::red));
    spectrumAnalyzerParameters.gradientStops.append(QPair<double,QColor>(0.5, Qt::yellow));
    spectrumAnalyzerParameters.gradientStops.append(QPair<double,QColor>(1.0, Qt::green));

    gradient.setStops(spectrumAnalyzerParameters.gradientStops);
    barValues = new double[20];
    for(int i=0; i<20; i++)
        barValues[i] = (i+1)*5;

    spectrumAnalyzerParameters.barDirection = ORIENTATION::VERTICAL;
    spectrumAnalyzerParameters.barAmount = 20;
    spectrumAnalyzerParameters.peakValue = 100;
    spectrumAnalyzerParameters.barGapRatio = 0.9;
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
    paintContinuous(painter, spectrumAnalyzerParameters, barValues);
}

