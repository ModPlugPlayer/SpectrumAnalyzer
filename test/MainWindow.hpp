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

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    SpectrumAnalyzerAnimator<double> *animator;
    void setValue(double value);
};

#endif // MAINWINDOW_HPP
