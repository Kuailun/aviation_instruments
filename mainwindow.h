#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QPainter>

class mainwindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit mainwindow(QWidget *parent = nullptr);

signals:

public slots:
    void ChangeDisplayMode();                   //变换显示模式
private:
    int mode=0;                                 //0=正常运行，1=调试
    int rate_Data=10;                           //数据频率
    int rate_Frame=40;                          //绘制频率
    void paintEvent(QPaintEvent *event);        //绘制事件
    void SetRightMenu();                        //设置鼠标右键菜单
    void SetTimmer();                           //设置重绘时钟

};

#endif // MAINWINDOW_H
