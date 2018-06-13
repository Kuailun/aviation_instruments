#include "mainwindow.h"
#include <QDebug>
#include <QTimer>
#include <QKeyEvent>

mainwindow::mainwindow(QWidget *parent) : QMainWindow(parent)
{
    this->setWindowTitle("FYCYC-Aviation Instruments X");
    this->resize(QSize(1600,900));
    SetTimmer();
    SetRightMenu();
    xmlreader=new XMLReader();
    xmlreader->ReadFile();
    xmlreader->WriteFile();

    if(debug)
    {
        instrument=new Instrument(this);
        instrument->move(30,30);
        instrument->resize(300,100);
        instrument->show();
    }
    else
    {

    }





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
    //设置标题栏
    if(title==0)
    {
        //mainwindow->setWindowFlags(Qt::FramelessWindowHint);
    }
    else if(title==1)
    {
        //this->setWindowFlags(Qt::);
    }
}
void mainwindow::SetRightMenu()
{
    QAction *paConfiguration=new QAction("Configuration",this);
    QAction *paDisplayMode=new QAction("Display Mode    F12",this);
    QAction *paTitle=new QAction("TitleBar",this);
    QAction *paFullScreen=new QAction( "FullScreen      F11",this);

    addAction(paConfiguration);
    addAction(paDisplayMode);
    addAction(paTitle);
    addAction(paFullScreen);


    connect(paConfiguration,SIGNAL(triggered()),this,SLOT(close()));
    connect(paDisplayMode,SIGNAL(triggered()),this,SLOT(ChangeDisplayMode()));
    connect(paTitle,SIGNAL(triggered()),this,SLOT(ChangeTitleBar()));
    connect(paFullScreen,SIGNAL(triggered()),this,SLOT(ChangeFullScreen()));

    setContextMenuPolicy(Qt::ActionsContextMenu);
}
void mainwindow::ChangeDisplayMode()
{
    mode=1-mode;
    if(debug)
    {
        instrument->SetDisplayMode(mode);
    }
    else
    {

    }

    //qDebug()<<"slotB() is called.";
}
void mainwindow::ChangeTitleBar()
{
    title=1-title;
    if(title==0)
    {
        this->setWindowFlags(Qt::FramelessWindowHint);
        show();
    }
    else
    {
        this->setWindowFlags(windowFlags()&~Qt::FramelessWindowHint);
        show();
    }
}
void mainwindow::ChangeFullScreen()
{
    fullScreen=1-fullScreen;
    if(fullScreen==0)
    {
        showNormal();
    }
    else
    {
        showFullScreen();
    }
}
void mainwindow::SetTimmer()
{
    QTimer *timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(update()));
    timer->start(1000/rate_Frame);
}
void mainwindow::keyPressEvent(QKeyEvent *event)
{
    if(Qt::Key_F12==event->key())
    {
        ChangeDisplayMode();
        return;
    }
    if(Qt::Key_F11==event->key())
    {
        ChangeFullScreen();
        return;
    }

}
