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

    barValues = new double[20];
    for(int i=0; i<20; i++){
        bars.push_back(ContinuousBar());
    }





    parameters.barDirection = ORIENTATION::HORIZONTAL;
    parameters.barAmount = 20;
    parameters.peakValue = 100;
    parameters.barGapRatio = 0.8;
    parameters.dimmingPercentage = 30;
    parameters.transparencyPercentage = 55;

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
    qDebug()<<"paint";
}

void SpectrumAnalyzer::resizeEvent(QResizeEvent *event)
{
    size = event->size();

    updateBars();

    //paintContinuous(painter, parameters, barValues);


    qDebug()<<"resize x"<<size.width();
    qDebug()<<"resize y"<<size.height();
}

void SpectrumAnalyzer::updateBars()
{
    qreal barWidth, gapWidth;
    if(parameters.barDirection == ORIENTATION::VERTICAL)
        MathUtil::divideLineIntoSegmentsAndGaps(size.width(), parameters.barAmount, parameters.barGapRatio, barWidth, gapWidth);
    else
        MathUtil::divideLineIntoSegmentsAndGaps(size.height(), parameters.barAmount, parameters.barGapRatio, barWidth, gapWidth);

    int i=0;
    for(Bar &bar:bars) {
        bar.setOrientation(parameters.barDirection);
        bar.setPeakValue(parameters.peakValue);
        if(parameters.barDirection == ORIENTATION::VERTICAL){
            bar.setSizes(QSizeF(barWidth, size.height()));
            bar.setCoordinates(QPointF((barWidth + gapWidth)*i, 0));
        }
        else {
            bar.setSizes(QSizeF(size.width(), barWidth));
            bar.setCoordinates(QPointF(0, (barWidth + gapWidth)*i));
        }
        bar.setValue((i+1)*5);
        bar.setGradientStops(gradientStops);
        bar.setDimmingPercentage(parameters.dimmingPercentage);
        bar.setTransparencyPercentage(parameters.transparencyPercentage);
        i++;
    }
}
