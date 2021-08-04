#ifndef SIMPLEWINDOW_H
#define SIMPLEWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class SimpleWindow; }
QT_END_NAMESPACE

class SimpleWindow : public QMainWindow
{
    Q_OBJECT

public:
    SimpleWindow(QWidget *parent = nullptr);
    ~SimpleWindow();

private:
    Ui::SimpleWindow *ui;
};

#endif // SIMPLEWINDOW_H
