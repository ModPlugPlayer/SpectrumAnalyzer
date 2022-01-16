/*
DiscreteBar class declarations and definitions of Spectrum Analyzer
Copyright (C) 2020 Volkan Orhan

This library is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation; either version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with this library; if not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

#ifndef DISCRETEBAR_HPP
#define DISCRETEBAR_HPP
#include "Bar.hpp"
#include "LED.hpp"
#include "Parameters.hpp"
#include <MathUtil.hpp>
#include <QDebug>

class DiscreteBar : public Bar
{
public:
    inline DiscreteBar();
    inline void draw(QPainter &painter);
    inline int getLedAmount() const;
    inline void setLedAmount(int value);

    inline double getLedGapRatio() const;
    inline void setLedGapRatio(double value);

    inline void setSizes(const QSizeF &sizes);

private:
    QVector<LED> leds;
    double ledGapRatio;
    qreal ledSize, gapSize;
    inline void recalculateLeds();
};


inline DiscreteBar::DiscreteBar():
    Bar(BarType::Discrete)
{
}

inline void DiscreteBar::draw(QPainter &painter) {
    if(getOrientation() == Qt::Orientation::Vertical){
        for(LED &led:leds){
            if(getVuLength()>=getSizes().height() - led.getCoordinates().y())
                led.setLight(true);
            else
                led.setLight(false);
            led.draw(painter);
        }
    }
    else{
        for(LED &led:leds){
            if(getVuLength()>=led.getCoordinates().x())
                led.setLight(true);
            else
                led.setLight(false);
            led.draw(painter);
        }
    }
}

inline int DiscreteBar::getLedAmount() const
{
    return leds.size();
}

inline void DiscreteBar::setLedAmount(int ledAmount)
{
    leds.clear();
    leds.resize(ledAmount);
    leds.fill(LED(), ledAmount);
    recalculateLeds();
}

inline double DiscreteBar::getLedGapRatio() const
{
    return ledGapRatio;
}

inline void DiscreteBar::setLedGapRatio(double value)
{
    ledGapRatio = value;
    recalculateLeds();
}

inline void DiscreteBar::recalculateLeds()
{
    if(this->getLedAmount() >0 && this->getLedGapRatio() > 0) {
        if(getOrientation() == Qt::Orientation::Vertical) {
            DSP::MathUtil::divideLineIntoSegmentsAndGaps(getSizes().height(), this->getLedAmount(), this->getLedGapRatio(), ledSize, gapSize);
            for(int i=0; i<getLedAmount(); i++) {
                qreal length = i*(ledSize + gapSize);
                qreal centerLength = length + (ledSize/2);
                leds[i].setCoordinates(QPointF(getCoordinates().x(), length));
                leds[i].setSizes(QSizeF(getSizes().width(), ledSize));
                leds[i].setColor(gradient.getColor((getSizes().height() - centerLength)/getSizes().height()));
                leds[i].setDimmingPercentage(getDimmingPercentage());
                leds[i].setTransparencyPercentage(getTransparencyPercentage());
            }
        }
        else {
            DSP::MathUtil::divideLineIntoSegmentsAndGaps(getSizes().width(), this->getLedAmount(), this->getLedGapRatio(), ledSize, gapSize);
            for(int i=0; i<getLedAmount(); i++) {
                qreal length = i*(ledSize + gapSize);
                qreal centerLength = length + (ledSize/2);
                leds[i].setCoordinates(QPointF(length, getCoordinates().y()));
                leds[i].setSizes(QSizeF(ledSize, getSizes().height()));
                leds[i].setColor(gradient.getColor((getSizes().width() - centerLength)/getSizes().width()));
                leds[i].setDimmingPercentage(getDimmingPercentage());
                leds[i].setTransparencyPercentage(getTransparencyPercentage());
            }
        }
    }
}


inline void DiscreteBar::setSizes(const QSizeF &sizes)
{
    Bar::setSizes(sizes);
    recalculateLeds();
}

#endif // DISCRETEBAR_HPP
