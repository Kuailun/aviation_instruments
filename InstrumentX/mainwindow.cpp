#include "mainwindow.h"
#include <QDebug>
#include <QTimer>
#include <QKeyEvent>

mainwindow::mainwindow(QWidget *parent) : QMainWindow(parent)
{
    this->setWindowTitle("FYCYC-Aviation Instruments X");    
    m_config=new Config();
    configuration=new Configuration();
    xmlcontrol=new XMLControl();

    m_config=xmlcontrol->ReadFile();
    xmlcontrol->SetDataStruct(m_config);            //更新XML数据

    connect(configuration,SIGNAL(SendConfig(Config*)),this,SLOT(ReceiveConfig(Config*)));    //子窗体回传设置

    SetTimmer();
    SetRightMenu();

    this->resize(QSize(this->m_config->config_screen.data_width,this->m_config->config_screen.data_height));
    this->move(this->m_config->config_screen.data_x,this->m_config->config_screen.data_y);



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
    (void)event;                                    //去掉报警信息

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
    (void)event;                                    //去掉报警信息

    m_config->config_screen.data_height=this->height();
    m_config->config_screen.data_width=this->width();
    xmlcontrol->SetDataStruct(m_config);            //更新XML数据
}
void mainwindow::moveEvent(QMoveEvent *event)
{
    (void)event;                                    //去掉报警信息

    m_config->config_screen.data_x=this->x();
    m_config->config_screen.data_y=this->y();
    xmlcontrol->SetDataStruct(m_config);            //更新XML数据
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


    connect(paConfiguration,SIGNAL(triggered()),this,SLOT(OpenConfiguration()));
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
    m_config->config_showBorder=1-m_config->config_showBorder;
    if(m_config->config_showBorder==0)
    {
        this->setWindowFlags(Qt::FramelessWindowHint);
        show();        
    }
    else
    {
        this->setWindowFlags(windowFlags()&~Qt::FramelessWindowHint);
        show();
    }
    xmlcontrol->SetDataStruct(m_config);            //更新XML数据
}
void mainwindow::ChangeFullScreen()
{
    m_config->config_fullscreen=1-m_config->config_fullscreen;
    if(m_config->config_fullscreen==0)
    {
        showNormal();
    }
    else
    {
        showFullScreen();
    }
    xmlcontrol->SetDataStruct(m_config);            //更新XML数据
}
void mainwindow::SetTimmer()
{
    QTimer *timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(update()));
    timer->start((int)(1000/m_config->config_frameRate));
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
void mainwindow::OpenConfiguration()
{
    configuration->setWindowTitle("Configuration");

    configuration->show();
    configuration->SetConfig(m_config);
}
void mainwindow::ReceiveConfig(Config* p_config)
{
    m_config=p_config;
    xmlcontrol->SetDataStruct(m_config);            //更新XML数据
    qDebug()<<"returned"<<endl;
}
