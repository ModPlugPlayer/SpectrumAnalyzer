#include "SineItem.hpp"
#include "SpectrumAnalyzer.hpp"
#include <QtGui>
#include <QDebug>
#include <cmath>

void SpectrumAnalyzer::paintDiscrete(QPainter &painter, SpectrumAnalyzerParameters &spectrumAnalyzerParameters, double* barValues)
{
    SpectrumAnalyzerParameters &p = spectrumAnalyzerParameters;
    painter.setRenderHint(QPainter::Antialiasing);
    //qDebug()<<event->region().rectCount();
    qDebug()<<"beginning x:"<<startingPoint.x<<" y:"<<startingPoint.y;
    qDebug()<<"ending x:"<<endingPoint.x<<" y:"<<endingPoint.y;
   // gradient = QLinearGradient(0,0,0,height());

//    gradient.setStops(stops);
    if(p.drawMode == DRAWMODE::VERTICAL)
        gradient.setFinalStop(0.0, height());
    else
        gradient.setFinalStop(width(), 0.0);
//    gradient.setColorAt(0.0, Qt::red);
//    gradient.setColorAt(0.5, Qt::yellow);
//    gradient.setColorAt(1.0, Qt::green);

//    painter.translate(width() / 2, height() / 2);
//    painter.scale(side / 200.0, side / 200.0);
//    painter.drawRect(startingPoint.x, startingPoint.y, endingPoint.x, endingPoint.y);
    //painter.drawRect(QRectF(0,0,10.5,10.5));


    int gapAmount = p.barAmount -1;

    int w = endingPoint.x;
    int h = endingPoint.y;
    double totalWidth = p.drawMode==DRAWMODE::VERTICAL?w:h;
    double barWidth = (totalWidth / p.barAmount)*p.barGapRatio;
    double peakHeight = p.drawMode==DRAWMODE::VERTICAL?h:w;
    double gapWidth = (totalWidth - (barWidth*p.barAmount))/(double)gapAmount;
    qDebug()<<"gap width:"<<gapWidth<<" bar width: "<<barWidth << " total width: " << totalWidth;

    /*
    qDebug()<<"bar amount: "<<barAmount<<"bar width: "<<barWidth;
    qDebug()<<"gap amount: "<<gapAmount<<"gap width: "<<gapWidth;
    */
//    barWidth = barWidth - gapWidth;

    //gradient.setFinalStop(height());

    double currentBarHeight = 0;

    for(int i=0; i<p.barAmount+1; i++) {
        currentBarHeight = (barValues[i]*peakHeight)/p.peakValue;
        if(p.drawMode == DRAWMODE::VERTICAL)
            painter.fillRect(QRectF((barWidth + gapWidth)*i, peakHeight-currentBarHeight, barWidth, currentBarHeight), gradient);
        else
            painter.fillRect(QRectF(0, (barWidth + gapWidth)*i, currentBarHeight, barWidth), gradient);
    }

    /*
    for(int i=0; i<barAmount+1; i++) {
        if(drawMode == DRAWMODE::VERTICAL)
            painter.fillRect(QRectF((barWidth + gapWidth)*i, 0, barWidth, (barValues[i]*h)/peakValue), gradient);
        else
            painter.fillRect(QRectF(0, (barWidth + gapWidth)*i, (barValues[i]*w)/peakValue, barWidth), gradient);
    }
    */

    //painter.eraseRect(0, 100, width(), 5);
    /*
    painter.fillRect(QRect(0, 0, barWidth, h), m_gradient);
    painter.fillRect(QRect(barWidth + gapWidth, 0, barWidth, h), m_gradient);
    */
    //SineItem *item = new SineItem();
    //item->paint(&painter,nullptr, this);

}
