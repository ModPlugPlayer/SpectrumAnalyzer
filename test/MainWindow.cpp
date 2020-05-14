#include "MainWindow.hpp"
#include "ui_MainWindow.h"
#include "SpectrumAnalyzer.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    SpectrumAnalyzerParameters parameters;
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

    ui->spectrumAnalyzer->setParameters(parameters);
    for(int i=0; i<20; i++) {
        ui->spectrumAnalyzer->setBarValue(i, (i+1)*5);
    }
    ui->spectrumAnalyzer->update();


}

MainWindow::~MainWindow()
{
    delete ui;
}

