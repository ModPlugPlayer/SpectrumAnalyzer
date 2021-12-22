/*
MainWindow class declarations for the tests of Spectrum Analyzer
Copyright (C) 2020 Volkan Orhan

This library is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation; either version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with this library; if not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QTimer>
#include "../../SpectrumAnalyzerAnimator/src/SpectrumAnalyzerAnimator"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonMin_clicked();

    void on_pushButtonMax_clicked();

    void on_pushButtonSetValueTo_clicked();

    void timerEvent();

    void on_pushButton0_clicked();

    void on_pushButton5_clicked();

    void on_pushButton10_clicked();

    void on_pushButton15_clicked();

    void on_pushButton17_5_clicked();

    void on_pushButton20_clicked();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    SpectrumAnalyzerAnimator<double> *animator;
    void setValue(double value);
};

#endif // MAINWINDOW_HPP
