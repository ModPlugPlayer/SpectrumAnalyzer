/*
SpectrumAnalyzer class declarations and definitions of Spectrum Analyzer
Copyright (C) 2020 Volkan Orhan

This library is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation; either version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with this library; if not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

#pragma once

#include <QWidget>
#include "Parameters.hpp"
#include "ContinuousBar.hpp"
#include "DiscreteBar.hpp"
#include "Bar.hpp"

#include "SineItem.hpp"
#include <QtGui>
#include <QDebug>
#include <cmath>
#include <MathUtil.hpp>
#include <mutex>

class SpectrumAnalyzer : public QWidget
{
    //Q_OBJECT
public:
    explicit SpectrumAnalyzer(QWidget *parent = nullptr);

    SpectrumAnalyzerParameters getParameters() const;
    void setParameters(const SpectrumAnalyzerParameters &value);

    void setBarValue(size_t barIndex, double value);
    void setBarType(const BarType &barType);
    void setLedAmount(const int &ledAmount);
    void setLedGapRatio(const double &ledGapRatio);
    void setBarGapRatio(const double &barGapRatio);
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
private:
    SpectrumAnalyzerParameters parameters;
    QVector<Bar*> bars;
    QGradientStops gradientStops;
    std::mutex dataMutex;
    void recalculateInternalVariables();

   // void paintContinuous(QPainter &painter, SpectrumAnalyzerParameters &spectrumAnalyzerParameters, double* barValues);
    //void paintDiscrete(QPainter &painter, SpectrumAnalyzerParameters &spectrumAnalyzerParameters, double *barValues);
signals:

};

inline SpectrumAnalyzer::SpectrumAnalyzer(QWidget *parent) : QWidget(parent)
{
    gradientStops.append(QPair<double,QColor>(1.0, Qt::red));
    gradientStops.append(QPair<double,QColor>(0.6, QColor(255, 210, 0)));
    gradientStops.append(QPair<double,QColor>(0.5, Qt::yellow));
    gradientStops.append(QPair<double,QColor>(0.25, QColor(175, 255, 0)));
    gradientStops.append(QPair<double,QColor>(0.0, QColor(0, 200, 0)));

    /*
    for(int i=0; i<2; i++){
    barValues = new double[2];
    barValues[0] = 45;
    barValues[1] = 90;
    */






    //gradient = QGradient::Preset::JuicyCake;

/*
    gradient.setColorAt(0.0, Qt::red);
    gradient.setColorAt(0.5, Qt::yellow);
    gradient.setColorAt(1.0, Qt::green);
    //gradient = QGradient::Seashore;
*/
}

inline SpectrumAnalyzerParameters SpectrumAnalyzer::getParameters() const
{
    return parameters;
}

inline void SpectrumAnalyzer::setParameters(const SpectrumAnalyzerParameters &value)
{
    std::lock_guard<std::mutex> guard(dataMutex);
    parameters = value;
    bars.clear();
    bars.reserve(parameters.barAmount);
    if(parameters.barType == BarType::Discrete){
        for (int i=0; i<parameters.barAmount; i++){
            bars.push_back(new DiscreteBar());
        }
    }
    else if(parameters.barType == BarType::Continuous){
        for (int i=0; i<parameters.barAmount; i++){
            bars.push_back(new ContinuousBar());
        }
    }
}

inline void SpectrumAnalyzer::paintEvent(QPaintEvent *event)
{
    std::lock_guard<std::mutex> guard(dataMutex);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    //paintContinuous(painter, parameters, barValues);
    for(Bar *bar:bars) {
        bar->draw(painter);
    }
    //qDebug()<<"paint";
}

inline void SpectrumAnalyzer::recalculateInternalVariables() {
    qreal barWidth, gapWidth;
    if(parameters.barDirection == Qt::Orientation::Vertical)
        DSP::MathUtil::divideLineIntoSegmentsAndGaps<qreal>(size().width(), parameters.barAmount, parameters.barGapRatio, barWidth, gapWidth);
    else
        DSP::MathUtil::divideLineIntoSegmentsAndGaps<qreal>(size().height(), parameters.barAmount, parameters.barGapRatio, barWidth, gapWidth);

    int i=0;
    for(Bar *bar:bars) {
        bar->setOrientation(parameters.barDirection);
        bar->setPeakValue(parameters.peakValue);
        bar->setFloorValue(parameters.floorValue);
        if(parameters.barDirection == Qt::Orientation::Vertical){
            bar->setSizes(QSizeF(barWidth, size().height()));
            bar->setCoordinates(QPointF((barWidth + gapWidth)*i, 0));
        }
        else {
            bar->setSizes(QSizeF(size().width(), barWidth));
            bar->setCoordinates(QPointF(0, (barWidth + gapWidth)*i));
        }
        bar->setGradientStops(gradientStops);
        bar->setDimmingPercentage(parameters.dimmingPercentage);
        bar->setTransparencyPercentage(parameters.transparencyPercentage);
        if(bar->getBarType() == BarType::Discrete) {
            DiscreteBar * discreteBar = (DiscreteBar *) bar;
            discreteBar->setLedAmount(parameters.discreteParameters.barLedAmount);
            discreteBar->setLedGapRatio(parameters.discreteParameters.ledGapRatio);
        }
        i++;
    }
}

inline void SpectrumAnalyzer::resizeEvent(QResizeEvent *event)
{
    std::lock_guard<std::mutex> guard(dataMutex);
    recalculateInternalVariables();
}

inline void SpectrumAnalyzer::setBarValue(size_t barIndex, double value)
{
    std::lock_guard<std::mutex> guard(dataMutex);
    bars[barIndex]->setValue(value);
}

inline void SpectrumAnalyzer::setBarType(const BarType & barType)
{
    std::lock_guard<std::mutex> guard(dataMutex);
    parameters.barType = barType;
    QVector<Bar *> oldBars = bars;
    for(qsizetype i = 0; i<bars.size(); i++) {
        Bar *oldBar = bars[i];
        Bar *newBar;
        if(barType == BarType::Continuous) {
            ContinuousBar *currentBar = new ContinuousBar(*oldBar);
            newBar = currentBar;
            bars[i] = newBar;
        }
        else {
            DiscreteBar *currentBar = new DiscreteBar(*oldBar);
            currentBar->setLedAmount(parameters.discreteParameters.barLedAmount);
            currentBar->setLedGapRatio(parameters.discreteParameters.ledGapRatio);
            newBar = currentBar;
            bars[i] = newBar;
        }
    }
    recalculateInternalVariables();

    for(Bar * bar : oldBars) {
        if(bar->getBarType() == BarType::Continuous)
            delete (ContinuousBar*) bar;
        else if(bar->getBarType() == BarType::Discrete)
            delete (DiscreteBar*) bar;
    }
}

inline void SpectrumAnalyzer::setLedAmount(const int &ledAmount) {
    std::lock_guard<std::mutex> guard(dataMutex);
    parameters.discreteParameters.barLedAmount = ledAmount;
    if(parameters.barType == BarType::Discrete) {
        for(qsizetype i = 0; i<bars.size(); i++) {
            DiscreteBar *currentBar = (DiscreteBar *) bars[i];
            currentBar->setLedAmount(ledAmount);
        }
    }
    recalculateInternalVariables();
}

inline void SpectrumAnalyzer::setLedGapRatio(const double &ledGapRatio) {
    std::lock_guard<std::mutex> guard(dataMutex);
    parameters.discreteParameters.ledGapRatio = ledGapRatio;
    if(parameters.barType == BarType::Discrete) {
        for(qsizetype i = 0; i<bars.size(); i++) {
            DiscreteBar *currentBar = (DiscreteBar *) bars[i];
            currentBar->setLedGapRatio(ledGapRatio);
        }
    }
    recalculateInternalVariables();
}

inline void SpectrumAnalyzer::setBarGapRatio(const double &barGapRatio) {
    std::lock_guard<std::mutex> guard(dataMutex);
    parameters.barGapRatio = barGapRatio;
    recalculateInternalVariables();
}
