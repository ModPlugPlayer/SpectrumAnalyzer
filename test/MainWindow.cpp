#include "MainWindow.hpp"
#include "ui_MainWindow.h"
#include "../src/SpectrumAnalyzer.hpp"
#include "TestUtil.hpp"
/*
MainWindow class definitions for the tests of Spectrum Analyzer
Copyright (C) 2020 Volkan Orhan

This library is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation; either version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with this library; if not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    SpectrumAnalyzerParameters parameters;
    parameters.barType = BarType::Discrete;
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
    parameters.gradientStops = TestUtil::getDefaultGradientStops();

    ui->spectrumAnalyzer->setParameters(parameters);
    for(int i=0; i<1; i++) {
        ui->spectrumAnalyzer->setBarValue(i, -20);
    }
    ui->spectrumAnalyzer->update();

    animator = new SpectrumAnalyzerAnimator<double>(1, -20, 0);
    //ui->spectrumAnalyzer->update();
    timer = new QTimer(this);

    connect(timer, &QTimer::timeout, this, &MainWindow::timerEvent);


    MotionProperties r, f;
    r.acceleration = -3;
    //r.initialVelocity = 7;
    r.motionType = MotionType::ConstantAcceleration;
    //r.motionType = MotionType::ConstantVelocity;

    f.acceleration = -3;
    f.motionType = MotionType::ConstantAcceleration;
    //f.initialVelocity = -0.3;

    animator->setFallingMotionProperties(f);
    animator->setRaisingMotionProperties(r);

    animator->start();

    timer->start(10);
}

void MainWindow::timerEvent(){
    double value;
    animator->getValues(&value);
    ui->spectrumAnalyzer->setBarValue(0, value);
    ui->spectrumAnalyzer->update();


    //qDebug()<<"Timeout";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setValue(double value)
{
    animator->setValues(&value);
}

void MainWindow::on_pushButtonMin_clicked()
{
    setValue(-20);
    //ui->spectrumAnalyzer->setBarValue(0, -20);
    //ui->spectrumAnalyzer->update();
}


void MainWindow::on_pushButtonMax_clicked()
{
    setValue(0);
    //ui->spectrumAnalyzer->setBarValue(0, 0);
    //ui->spectrumAnalyzer->update();
}


void MainWindow::on_pushButtonSetValueTo_clicked()
{
    bool ok;
    double value = ui->lineEditValue->text().toDouble(&ok);
    if(ok){
        setValue(value);
    }
}


void MainWindow::on_pushButton0_clicked()
{
    setValue(0);
}


void MainWindow::on_pushButton5_clicked()
{
    setValue(-5.0);
}


void MainWindow::on_pushButton10_clicked()
{
    setValue(-10.0);
}


void MainWindow::on_pushButton15_clicked()
{
    setValue(-15.0);
}


void MainWindow::on_pushButton17_5_clicked()
{
    setValue(-17.5);
}


void MainWindow::on_pushButton20_clicked()
{
    setValue(-20.0);
}
