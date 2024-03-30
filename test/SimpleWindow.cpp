/*
SimpleWindow class definitions for the tests of Spectrum Analyzer
Copyright (C) 2020 Volkan Orhan

This library is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation; either version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with this library; if not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

#include "SimpleWindow.hpp"
#include "ui_SimpleWindow.h"
#include "../src/SpectrumAnalyzer.hpp"

SimpleWindow::SimpleWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SimpleWindow)
{
    ui->setupUi(this);
    SpectrumAnalyzerParameters parameters;
    parameters.barDirection = Qt::Orientation::Vertical;
    parameters.barAmount = 1;
    /*
    parameters.barDirection = ORIENTATION::HORIZONTAL;
    parameters.barAmount = 2;
    parameters.dimmingPercentage = 30;
    parameters.transparencyPercentage = 55;
    */
    parameters.peakValue = 0;
    parameters.floorValue = -20;
    parameters.barWidthRatio = 0.8;
    parameters.dimmingRatio = 20;
    parameters.dimmedTransparencyRatio = 65;
    parameters.discreteParameters.ledHeightRatio = 0.8;
    parameters.discreteParameters.barLedAmount = 40;

    ui->spectrumAnalyzer->setParameters(parameters);
    for(int i=0; i<1; i++) {
        ui->spectrumAnalyzer->setBarValue(i, -10);
    }
    //ui->spectrumAnalyzer->update();


}

SimpleWindow::~SimpleWindow()
{
    delete ui;
}
