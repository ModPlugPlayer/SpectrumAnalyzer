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
    for(int i=0; i<20; i++) {
        barValues[i] = (i+1)*5;
    }
    for(int i=0; i<20; i++){
        ContinuousBar * bar = new ContinuousBar(parent);
        bar->setOrientation(ORIENTATION::HORIZONTAL);
        bar->setGradientStops(gradientStops);
        bars.push_back(bar);
    }





    parameters.barDirection = ORIENTATION::VERTICAL;
    parameters.barAmount = 20;
    parameters.peakValue = 100;
    parameters.barGapRatio = 0.8;
    parameters.dimmingPercentage = 30;
    parameters.transparencyPercentage = 55;
    initUI(this);

    //gradient = QGradient::Preset::JuicyCake;

/*
    gradient.setColorAt(0.0, Qt::red);
    gradient.setColorAt(0.5, Qt::yellow);
    gradient.setColorAt(1.0, Qt::green);
    //gradient = QGradient::Seashore;
*/
}

void SpectrumAnalyzer::initUI(QWidget *parent)
{
    layout = new QGridLayout(parent);
    layout->setSpacing(QWidget::height()/100);
    setLayout(layout);
    for(ContinuousBar *bar:bars){
        layout->addWidget(bar);
    }
}

void SpectrumAnalyzer::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    //paintContinuous(painter, parameters, barValues);
    qDebug()<<"paint";
}

void SpectrumAnalyzer::resizeEvent(QResizeEvent *event)
{
    layout->setSpacing(size().height()/100);

    updateBars();

    //paintContinuous(painter, parameters, barValues);


    qDebug()<<"resize x"<<size().width();
    qDebug()<<"resize y"<<size().height();

}

void SpectrumAnalyzer::updateBars()
{
    qreal barWidth, gapWidth;
    if(parameters.barDirection == ORIENTATION::VERTICAL)
        MathUtil::divideLineIntoSegmentsAndGaps(size().width(), parameters.barAmount, parameters.barGapRatio, barWidth, gapWidth);
    else
        MathUtil::divideLineIntoSegmentsAndGaps(size().height(), parameters.barAmount, parameters.barGapRatio, barWidth, gapWidth);

    int i=0;
    /*
    for(Bar &bar:bars) {
        bar.setOrientation(parameters.barDirection);
        bar.setPeakValue(parameters.peakValue);
        layout->addWidget(&bar, 0, i);
        bar.setValue(barValues[i]);
        bar.setGradientStops(gradientStops);
        bar.setDimmingPercentage(parameters.dimmingPercentage);
        bar.setTransparencyPercentage(parameters.transparencyPercentage);
        i++;
    }*/
}
