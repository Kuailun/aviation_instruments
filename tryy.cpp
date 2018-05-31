#include "tryy.h"

Tryy::Tryy(QWidget *parent)
    : QDialog(parent)
{
    setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    hide();
}

Tryy::~Tryy()
{

}
void Tryy::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.fillRect(QRect(0,0,this->width(),this->height()),QBrush(Qt::black));
    painter.fillRect(QRect(10,10,this->width()/2,this->height()/2),QBrush(Qt::red));
}
void Tryy::mousePressEvent(QMouseEvent *event)
{
    mMoveing = true;
    //记录下鼠标相对于窗口的位置
    //event->globalPos()鼠标按下时，鼠标相对于整个屏幕位置
    //pos() this->pos()鼠标按下时，窗口相对于整个屏幕位置
    mMovePosition = event->globalPos() - pos();
    return QDialog::mousePressEvent(event);
}
void Tryy::mouseMoveEvent(QMouseEvent *event)
{
    //(event->buttons() && Qt::LeftButton)按下是左键
        //鼠标移动事件需要移动窗口，窗口移动到哪里呢？就是要获取鼠标移动中，窗口在整个屏幕的坐标，然后move到这个坐标，怎么获取坐标？
        //通过事件event->globalPos()知道鼠标坐标，鼠标坐标减去鼠标相对于窗口位置，就是窗口在整个屏幕的坐标
        if (mMoveing && (event->buttons() && Qt::LeftButton)
            && (event->globalPos()-mMovePosition).manhattanLength() > QApplication::startDragDistance())
        {
            move(event->globalPos()-mMovePosition);
            mMovePosition = event->globalPos() - pos();
        }
        return QDialog::mouseMoveEvent(event);
}
void Tryy::mouseReleaseEvent(QMouseEvent *event)
{
    mMoveing=false;
}
