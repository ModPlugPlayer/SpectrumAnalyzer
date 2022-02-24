/*
Parameters class declarations and definitions of Spectrum Analyzer
Copyright (C) 2020 Volkan Orhan

This library is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation; either version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with this library; if not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/
#ifndef PARAMETERS_HPP
#define PARAMETERS_HPP
#include <QGradientStops>

struct DiscreteParameters {
    int barLedAmount;
    double ledHeightRatio;
};

struct ContinousParameters {
    double peakHeight;
};

enum class BarType {
    Discrete, Continuous
};

struct SpectrumAnalyzerParameters{
    BarType barType = BarType::Discrete;
    Qt::Orientation barDirection;
    unsigned char dimmingRatio = 0;
    unsigned char dimmedTransparencyRatio = 100;
    double blackCoefficient;
    int barAmount;
    double peakValue;
    double floorValue;
    double barWidthRatio;
    DiscreteParameters discreteParameters;
    ContinousParameters continuousParameters;
    QGradientStops gradientStops;
};

#endif // PARAMETERS_HPP
