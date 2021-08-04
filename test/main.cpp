#include "MainWindow.hpp"
#include "SimpleWindow.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    SimpleWindow s;
    s.show();
    return a.exec();
}
