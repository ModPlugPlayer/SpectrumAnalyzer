#include "SineItem.hpp"
#include "SpectrumAnalyzer.hpp"
#include <QtGui>
#include <QDebug>
#include <cmath>
SpectrumAnalyzer::SpectrumAnalyzer(QWidget *parent) : QWidget(parent)
{
    gradient = QLinearGradient();
    gradient.setSpread(QGradient::Spread::PadSpread);
    stops.append(QPair<double,QColor>(0.0, Qt::red));
    stops.append(QPair<double,QColor>(0.5, Qt::yellow));
    stops.append(QPair<double,QColor>(1.0, Qt::green));

    gradient.setStops(stops);
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
    paintContinuous(painter, DRAWMODE::VERTICAL, 20);

}

void SpectrumAnalyzer::paintContinuous(QPainter &painter, DRAWMODE drawMode, int barAmount)
{
    painter.setRenderHint(QPainter::Antialiasing);
    //qDebug()<<event->region().rectCount();
    qDebug()<<"beginning x:"<<startingPoint.x<<" y:"<<startingPoint.y;
    qDebug()<<"ending x:"<<endingPoint.x<<" y:"<<endingPoint.y;
   // gradient = QLinearGradient(0,0,0,height());

//    gradient.setStops(stops);
    if(drawMode == DRAWMODE::VERTICAL)
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


    int gapAmount = barAmount -1;

    int w = endingPoint.x;
    int h = endingPoint.y;
    double totalWidth = drawMode==DRAWMODE::VERTICAL?w:h;
    double barWidth = (totalWidth / barAmount)*0.9;
    double gapWidth = (totalWidth - (barWidth*barAmount))/(double)gapAmount;
    qDebug()<<"gap width:"<<gapWidth<<" bar width: "<<barWidth << " total width: " << totalWidth;

    /*
    qDebug()<<"bar amount: "<<barAmount<<"bar width: "<<barWidth;
    qDebug()<<"gap amount: "<<gapAmount<<"gap width: "<<gapWidth;
    */
//    barWidth = barWidth - gapWidth;

    //gradient.setFinalStop(height());


    for(int i=0; i<barAmount+1; i++) {
        if(drawMode == DRAWMODE::VERTICAL)
            painter.fillRect(QRectF((barWidth + gapWidth)*i, 0, barWidth, h), gradient);
        else
            painter.fillRect(QRectF(0, (barWidth + gapWidth)*i, w, barWidth), gradient);
    }

    //painter.eraseRect(0, 100, width(), 5);
    /*
    painter.fillRect(QRect(0, 0, barWidth, h), m_gradient);
    painter.fillRect(QRect(barWidth + gapWidth, 0, barWidth, h), m_gradient);
    */
    //SineItem *item = new SineItem();
    //item->paint(&painter,nullptr, this);

}
