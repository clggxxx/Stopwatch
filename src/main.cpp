#include "stopwatch.h"
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
//    Stopwatch w;
//    w.show();
    return a.exec();
}
