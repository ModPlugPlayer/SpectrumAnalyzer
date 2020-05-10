#include "MainWindow.hpp"
#include "ui_MainWindow.h"
#include <SpectrumAnalyzer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    parameters.barDirection = Qt::Orientation::Horizontal;
    parameters.barAmount = 20;
    /*
    parameters.barDirection = ORIENTATION::HORIZONTAL;
    parameters.barAmount = 2;
    parameters.dimmingPercentage = 30;
    parameters.transparencyPercentage = 55;
    */
    parameters.peakValue = 100;
    parameters.barGapRatio = 0.8;
    parameters.dimmingPercentage = 20;
    parameters.transparencyPercentage = 65;
    parameters.discreteParameters.ledGapRatio = 0.8;
    parameters.discreteParameters.barLedAmount = 40;

    barValues = new double[20];
    for(int i=0; i<20; i++) {
        barValues[i] = (i+1)*5;
    }


    //    ui->spectrumAnalyzer->set
}

MainWindow::~MainWindow()
{
    delete ui;
}

