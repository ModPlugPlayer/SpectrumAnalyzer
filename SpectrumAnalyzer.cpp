#include "SineItem.hpp"
#include "SpectrumAnalyzer.hpp"
#include <QtGui>
#include <QDebug>
#include <cmath>
SpectrumAnalyzer::SpectrumAnalyzer(QWidget *parent) : QWidget(parent)
{

}

void SpectrumAnalyzer::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    startingPoint.x = event->region().begin()->left();
    startingPoint.y = event->region().begin()->top();
    endingPoint.x = event->region().begin()->right();
    endingPoint.y = event->region().begin()->bottom();
    //qDebug()<<event->region().rectCount();
    qDebug()<<"beginning x:"<<startingPoint.x<<" y:"<<startingPoint.y;
    qDebug()<<"ending x:"<<endingPoint.x<<" y:"<<endingPoint.y;

//    painter.translate(width() / 2, height() / 2);
//    painter.scale(side / 200.0, side / 200.0);
//    painter.drawRect(startingPoint.x, startingPoint.y, endingPoint.x, endingPoint.y);
    //painter.drawRect(QRectF(0,0,10.5,10.5));

    QLinearGradient m_gradient(0,0,0,height());
    m_gradient.setColorAt(0.0, Qt::red);
    m_gradient.setColorAt(0.5, Qt::yellow);
    m_gradient.setColorAt(1.0, Qt::cyan);

    int barAmount = 20;
    int gapAmount = barAmount -1;

    int w = endingPoint.x;
    int h = endingPoint.y;
    double barWidth = (((double)w) / barAmount)*0.9;
    double gapWidth = (((double)w) - (barWidth*barAmount))/(double)gapAmount;
    /*
    qDebug()<<"bar amount: "<<barAmount<<"bar width: "<<barWidth;
    qDebug()<<"gap amount: "<<gapAmount<<"gap width: "<<gapWidth;
    */
//    barWidth = barWidth - gapWidth;


    for(int i=0; i<barAmount+1; i++) {
        painter.fillRect(QRectF((barWidth + gapWidth)*i, 0, barWidth, h), m_gradient);
    }
    /*
    painter.fillRect(QRect(0, 0, barWidth, h), m_gradient);
    painter.fillRect(QRect(barWidth + gapWidth, 0, barWidth, h), m_gradient);
    */
    //SineItem *item = new SineItem();
    //item->paint(&painter,nullptr, this);

}
