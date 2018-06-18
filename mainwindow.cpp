#include "mainwindow.h"
#include <QDebug>
#include <QTimer>
#include <QKeyEvent>

mainwindow::mainwindow(QWidget *parent) : QMainWindow(parent)
{
    this->setWindowTitle("FYCYC-Aviation Instruments X");    
    data=new DataStruct();
    xmlcontrol=new XMLControl();
    data=xmlcontrol->ReadFile();
    xmlcontrol->SetDataStruct(data);            //更新XML数据
    SetTimmer();
    SetRightMenu();

    this->resize(QSize(this->data->data_screen.data_width,this->data->data_screen.data_height));
    this->move(this->data->data_screen.data_x,this->data->data_screen.data_y);



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
}
void mainwindow::resizeEvent(QResizeEvent *event)
{
    data->data_screen.data_height=this->height();
    data->data_screen.data_width=this->width();
    xmlcontrol->SetDataStruct(data);            //更新XML数据
}
void mainwindow::moveEvent(QMoveEvent *event)
{
    data->data_screen.data_x=this->x();
    data->data_screen.data_y=this->y();
    xmlcontrol->SetDataStruct(data);            //更新XML数据
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
    data->data_showBorder=1-data->data_showBorder;
    if(data->data_showBorder==0)
    {
        this->setWindowFlags(Qt::FramelessWindowHint);
        show();        
    }
    else
    {
        this->setWindowFlags(windowFlags()&~Qt::FramelessWindowHint);
        show();
    }
    xmlcontrol->SetDataStruct(data);            //更新XML数据
}
void mainwindow::ChangeFullScreen()
{
    data->data_fullscreen=1-data->data_fullscreen;
    if(data->data_fullscreen==0)
    {
        showNormal();
    }
    else
    {
        showFullScreen();
    }
    xmlcontrol->SetDataStruct(data);            //更新XML数据
}
void mainwindow::SetTimmer()
{
    QTimer *timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(update()));
    timer->start((int)(1000/data->data_frameRate));
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
