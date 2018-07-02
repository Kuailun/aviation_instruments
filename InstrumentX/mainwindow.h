#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QPainter>
#include "instrument.h"
#include "xmlcontrol.h"
#include "configuration.h"
#include "printlog.h"

class mainwindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit mainwindow(QWidget *parent = nullptr);
signals:

private slots:
    void ChangeDisplayMode();                   //变换显示模式
    void ChangeTitleBar();                      //变换标题栏
    void ChangeFullScreen();                    //变换全屏模式
    void OpenConfiguration();                   //打开设置界面
    void ReceiveConfig(Config* p_config);            //更新设置
private:
    //数据区域
    Config* m_config;


    //XML记录+显示变量区
    XMLControl *xmlcontrol;                     //XML读写类

    //内部不显示变量区
    Instrument *instrument;
    Configuration *configuration;
    int debug=1;                                //程序编写调试设置，0=正常运行，1=调试
    int mode=0;                                 //0=正常运行，1=调试

    //内部功能函数

    //内部响应函数
    void paintEvent(QPaintEvent *event);        //绘制事件
    void resizeEvent(QResizeEvent *event);      //缩放窗口事件
    void moveEvent(QMoveEvent *event);          //移动窗口事件
    void SetRightMenu();                        //设置鼠标右键菜单
    void SetTimmer();                           //设置重绘时钟
    void keyPressEvent(QKeyEvent *event);       //快捷键设置


};

#endif // MAINWINDOW_H
