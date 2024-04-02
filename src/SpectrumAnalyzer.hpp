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

    void setBarValue(const size_t &barIndex, const double &value);
    void setBarType(const BarType &barType);
    void setBarAmount(const size_t &barAmount);
    void setLedAmount(const size_t &ledAmount);
    void setLedHeightRatio(const double &ledGapRatio);
    void setBarWidthRatio(const double &barGapRatio);
    void setDimmingRatio(const double &dimmingRatio);
    void setDimmedTransparencyRatio(const double &dimmedTransparencyRatio);
    void setPeakValue(const double &peakValue);
    void setFloorValue(const double &floorValue);
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void setGradient(const QGradientStops &gradient);
    QGradientStops getGradient();
private:
    SpectrumAnalyzerParameters parameters;
    QVector<Bar*> bars;
    std::mutex dataMutex;
    void removeBars();
    void createBars(const BarType &barType, const size_t &barAmount);
    void recalculateInternalVariables();

   // void paintContinuous(QPainter &painter, SpectrumAnalyzerParameters &spectrumAnalyzerParameters, double* barValues);
    //void paintDiscrete(QPainter &painter, SpectrumAnalyzerParameters &spectrumAnalyzerParameters, double *barValues);
signals:

};

inline SpectrumAnalyzer::SpectrumAnalyzer(QWidget *parent) : QWidget(parent)
{
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

inline void SpectrumAnalyzer::removeBars(){
    for(Bar *bar:bars) {
        if(bar != nullptr) {
            if(bar->getBarType() == BarType::Discrete)
                delete (DiscreteBar *) bar;
            else if(bar->getBarType() == BarType::Continuous)
                delete (ContinuousBar *) bar;
        }
    }
    bars.clear();
}

inline void SpectrumAnalyzer::createBars(const BarType &barType, const size_t &barAmount){
    removeBars();
    bars.reserve(parameters.barAmount);
    Bar *bar;
    if(parameters.barType == BarType::Discrete){
        for (int i=0; i<parameters.barAmount; i++){
            bar = new DiscreteBar();
            //bar->setGradientStops(parameters.gradientStops);
            bars.push_back(bar);
        }
    }
    else if(parameters.barType == BarType::Continuous){
        for (int i=0; i<parameters.barAmount; i++){
            bar = new ContinuousBar();
            //bar->setGradientStops(parameters.gradientStops);
            bars.push_back(bar);
        }
    }
}

inline SpectrumAnalyzerParameters SpectrumAnalyzer::getParameters() const
{
    return parameters;
}

inline void SpectrumAnalyzer::setParameters(const SpectrumAnalyzerParameters &value)
{
    std::lock_guard<std::mutex> guard(dataMutex);
    parameters = value;
    createBars(parameters.barType, parameters.barAmount);
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
}

inline void SpectrumAnalyzer::recalculateInternalVariables() {
    qreal barWidth, gapWidth;
    if(parameters.barDirection == Qt::Orientation::Vertical)
        DSP::MathUtil::divideLineIntoSegmentsAndGaps<qreal>(size().width(), parameters.barAmount, parameters.barWidthRatio, barWidth, gapWidth);
    else
        DSP::MathUtil::divideLineIntoSegmentsAndGaps<qreal>(size().height(), parameters.barAmount, parameters.barWidthRatio, barWidth, gapWidth);

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
        bar->setGradientStops(parameters.gradientStops);
        bar->setDimmingPercentage(parameters.dimmingRatio);
        bar->setTransparencyPercentage(parameters.dimmedTransparencyRatio);
        if(bar->getBarType() == BarType::Discrete) {
            DiscreteBar * discreteBar = (DiscreteBar *) bar;
            discreteBar->setLedAmount(parameters.discreteParameters.barLedAmount);
            discreteBar->setLedGapRatio(parameters.discreteParameters.ledHeightRatio);
        }
        i++;
    }
}

inline void SpectrumAnalyzer::resizeEvent(QResizeEvent *event)
{
    std::lock_guard<std::mutex> guard(dataMutex);
    recalculateInternalVariables();
}

inline void SpectrumAnalyzer::setBarValue(const size_t &barIndex, const double &value)
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
            currentBar->setLedGapRatio(parameters.discreteParameters.ledHeightRatio);
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

inline void SpectrumAnalyzer::setBarAmount(const size_t &barAmount) {
    std::lock_guard<std::mutex> guard(dataMutex);
    parameters.barAmount = barAmount;
    removeBars();
    createBars(parameters.barType, barAmount);
    recalculateInternalVariables();
}

inline void SpectrumAnalyzer::setLedAmount(const size_t &ledAmount) {
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

inline void SpectrumAnalyzer::setLedHeightRatio(const double &ledHeightRatio) {
    std::lock_guard<std::mutex> guard(dataMutex);
    parameters.discreteParameters.ledHeightRatio = ledHeightRatio;
    if(parameters.barType == BarType::Discrete) {
        for(qsizetype i = 0; i<bars.size(); i++) {
            DiscreteBar *currentBar = (DiscreteBar *) bars[i];
            currentBar->setLedGapRatio(ledHeightRatio);
        }
    }
    recalculateInternalVariables();
}

inline void SpectrumAnalyzer::setBarWidthRatio(const double &barWidthRatio) {
    std::lock_guard<std::mutex> guard(dataMutex);
    parameters.barWidthRatio = barWidthRatio;
    recalculateInternalVariables();
}

inline void SpectrumAnalyzer::setDimmingRatio(const double &dimmingRatio) {
    std::lock_guard<std::mutex> guard(dataMutex);
    parameters.dimmingRatio = dimmingRatio*100;
    recalculateInternalVariables();
}

inline void SpectrumAnalyzer::setDimmedTransparencyRatio(const double &dimmedTransparencyRatio) {
    std::lock_guard<std::mutex> guard(dataMutex);
    parameters.dimmedTransparencyRatio = dimmedTransparencyRatio*100;
    recalculateInternalVariables();
}

inline void SpectrumAnalyzer::setPeakValue(const double &peakValue) {
    std::lock_guard<std::mutex> guard(dataMutex);
    parameters.peakValue = peakValue;
    for(Bar * bar : bars) {
        bar->setPeakValue(peakValue);
    }
    recalculateInternalVariables();
}

inline void SpectrumAnalyzer::setFloorValue(const double &floorValue){
    std::lock_guard<std::mutex> guard(dataMutex);
    parameters.floorValue = floorValue;
    for(Bar * bar : bars) {
        bar->setFloorValue(floorValue);
    }
    recalculateInternalVariables();
}

inline void SpectrumAnalyzer::setGradient(const QGradientStops &gradient) {
    std::lock_guard<std::mutex> guard(dataMutex);
    this->parameters.gradientStops = gradient;
    for(Bar *bar:bars) {
        bar->setGradientStops(gradient);
    }
    recalculateInternalVariables();
}

inline QGradientStops SpectrumAnalyzer::getGradient() {
    std::lock_guard<std::mutex> guard(dataMutex);
    return parameters.gradientStops;
}
