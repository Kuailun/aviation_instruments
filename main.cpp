#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mainwindow w;
    QPalette pal(w.palette());
    pal.setColor(QPalette::Background,Qt::black);


    w.show();

    return a.exec();
}
