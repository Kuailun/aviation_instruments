#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QPainter>
#include "instrument.h"
#include "xmlreader.h"

class mainwindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit mainwindow(QWidget *parent = nullptr);
signals:

public slots:
    void ChangeDisplayMode();                   //变换显示模式
    void ChangeTitleBar();                      //变换标题栏
    void ChangeFullScreen();                    //变换全屏模式
private:
    //XML记录
    int mode=0;                                 //0=正常运行，1=调试
    int title=1;                                //0=无标题栏，1=有标题栏                                     
    int fullScreen=0;                           //0=窗口化，1=全屏
    int position_x;                             //窗口x坐标
    int position_y;                             //窗口y坐标
    int size_x;                                 //窗口x大小
    int size_y;                                 //窗口y大小
    //XML记录+显示变量区
    XMLReader *xmlreader;                       //XML读写类
    int rate_Data=10;                           //数据频率
    int rate_Frame=40;                          //绘制频率
    //内部不显示变量区
    Instrument *instrument;
    int debug=1;                                //程序调试设置，0=正常运行，1=调试

    //内部功能函数

    //内部响应函数
    void paintEvent(QPaintEvent *event);        //绘制事件
    void SetRightMenu();                        //设置鼠标右键菜单
    void SetTimmer();                           //设置重绘时钟
    void keyPressEvent(QKeyEvent *event);       //快捷键设置


};

#endif // MAINWINDOW_H
