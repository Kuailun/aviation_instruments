#include "mainwindow.h"
#include <QApplication>

// Main entry
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mainwindow w;
    w.show();
    return a.exec();
}
