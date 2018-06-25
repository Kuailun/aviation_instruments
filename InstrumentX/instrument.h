#ifndef Instrument_H
#define Instrument_H

#include <QDialog>
#include <QPainter>
#include <QMouseEvent>
#include <QApplication>

class Instrument : public QDialog
{
    Q_OBJECT

public:
    Instrument(QWidget *parent = 0);
    ~Instrument();

    //接口函数区
    void SetDisplayMode(int m);          //设置显示模式
protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
private:
    void paintEvent(QPaintEvent *event);

    bool mMoveing=false;
    QPoint mMovePosition;

    int mode=0;             //设置显示模式   0=正常运行，1=调试
    char* instrument_Name;  //窗口名称
};

#endif // Instrument_H
