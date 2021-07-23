#include "MainWindow.hpp"
#include "ui_MainWindow.h"
#include "../src/SpectrumAnalyzer.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
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
    parameters.barGapRatio = 0.8;
    parameters.dimmingPercentage = 20;
    parameters.transparencyPercentage = 65;
    parameters.discreteParameters.ledGapRatio = 0.8;
    parameters.discreteParameters.barLedAmount = 40;

    ui->spectrumAnalyzer->setParameters(parameters);
    for(int i=0; i<1; i++) {
        ui->spectrumAnalyzer->setBarValue(i, -10);
    }

    animator = new SpectrumAnalyzerAnimator<double>(1, -20, 0);
    //ui->spectrumAnalyzer->update();
    timer = new QTimer(this);

    connect(timer, &QTimer::timeout, this, &MainWindow::timerEvent);


    MotionProperties r, f;
    r.acceleration = 0;
    r.initialVelocity = 7;
    r.motionType = MotionType::ConstantVelocity;

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


void MainWindow::on_pushButtonMin_clicked()
{
    double value = -20;
    animator->setValues(&value);
    //ui->spectrumAnalyzer->setBarValue(0, -20);
    //ui->spectrumAnalyzer->update();
}


void MainWindow::on_pushButtonMax_clicked()
{
    double value = 0;
    animator->setValues(&value);
    //ui->spectrumAnalyzer->setBarValue(0, 0);
    //ui->spectrumAnalyzer->update();
}


void MainWindow::on_pushButtonSetValueTo_clicked()
{
    bool ok;
    double value = ui->lineEditValue->text().toDouble(&ok);
    if(ok){
        animator->setValues(&value);
    }
}

