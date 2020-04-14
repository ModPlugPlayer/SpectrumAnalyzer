#include "SineItem.hpp"
#include "SpectrumAnalyzer.hpp"
#include <QtGui>
#include <QDebug>
#include <cmath>

void pointDiscreteBar(QPainter painter, SpectrumAnalyzerParameters &spectrumAnalyzerParameters, CalculatedParameters &calculatedParameters, QRectF &barCoordinates) {
    double ledGapLength = calculatedParameters.peakLength * (1.0f - spectrumAnalyzerParameters.discreteParameters.ledGapRatio)/((double)spectrumAnalyzerParameters.discreteParameters.barLedAmount-1);
    double ledLength = calculatedParameters.peakLength * (spectrumAnalyzerParameters.discreteParameters.ledGapRatio)/((double)spectrumAnalyzerParameters.discreteParameters.barLedAmount);
    for(int i=0; i<spectrumAnalyzerParameters.discreteParameters.barLedAmount; i++) {
        QColor color;
        painter.fillRect(QRectF(barCoordinates.left(), barCoordinates.top(), 0, 0), color);
    }
}

void SpectrumAnalyzer::paintDiscrete(QPainter &painter, SpectrumAnalyzerParameters &spectrumAnalyzerParameters, double* barValues)
{
    SpectrumAnalyzerParameters &p = spectrumAnalyzerParameters;
    painter.setRenderHint(QPainter::Antialiasing);
    //qDebug()<<event->region().rectCount();
   // gradient = QLinearGradient(0,0,0,height());

//    gradient.setStops(stops);
    if(p.barDirection == ORIENTATION::VERTICAL)
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

    /*
    qDebug()<<"bar amount: "<<barAmount<<"bar width: "<<barWidth;
    qDebug()<<"gap amount: "<<gapAmount<<"gap width: "<<gapWidth;
    */
//    barWidth = barWidth - gapWidth;

    //gradient.setFinalStop(height());

    double currentBarHeight = 0;
    double currentBarStartingPoint;

    for(int i=0; i<p.barAmount+1; i++) {
        currentBarHeight = (barValues[i]*calculatedParameters.peakLength)/p.peakValue;
        currentBarStartingPoint = (calculatedParameters.barWidth + calculatedParameters.gapWidth)*i;

        if(p.barDirection == ORIENTATION::VERTICAL) {
            painter.fillRect(QRectF(currentBarStartingPoint, calculatedParameters.peakLength-currentBarHeight, calculatedParameters.barWidth, currentBarHeight), gradient);
        }
        else {
            painter.fillRect(QRectF(0, currentBarStartingPoint, currentBarHeight, calculatedParameters.barWidth), gradient);
        }
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
