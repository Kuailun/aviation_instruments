#include "mainwindow.h"
#include <QDebug>
#include <QTimer>

mainwindow::mainwindow(QWidget *parent) : QMainWindow(parent)
{
    this->resize(QSize(1600,900));    

    SetTimmer();
    SetRightMenu();


}
void mainwindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    //设置背景颜色
    if(mode==0)
    {
        painter.fillRect(QRect(0,0,this->width(),this->height()),QBrush(Qt::black));
    }
    else if(mode==1)
    {
        painter.fillRect(QRect(0,0,this->width(),this->height()),QBrush(Qt::blue));
    }


}
void mainwindow::SetRightMenu()
{
    QAction *paConfiguration=new QAction("Configuration",this);
    QAction *paDisplayMode=new QAction("Display Mode F12",this);

    addAction(paConfiguration);
    addAction(paDisplayMode);


    connect(paConfiguration,SIGNAL(triggered()),this,SLOT(close()));
    connect(paDisplayMode,SIGNAL(triggered()),this,SLOT(ChangeDisplayMode()));

    setContextMenuPolicy(Qt::ActionsContextMenu);
}
void mainwindow::ChangeDisplayMode()
{
    mode=1-mode;
    //qDebug()<<"slotB() is called.";
}
void mainwindow::SetTimmer()
{
    QTimer *timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(update()));
    timer->start(1000/rate_Frame);
}
