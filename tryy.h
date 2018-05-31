#ifndef TRYY_H
#define TRYY_H

#include <QDialog>
#include <QPainter>
#include <QMouseEvent>
#include <QApplication>

class Tryy : public QDialog
{
    Q_OBJECT

public:
    Tryy(QWidget *parent = 0);
    ~Tryy();
protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
private:
    void paintEvent(QPaintEvent *event);

    bool mMoveing;
    QPoint mMovePosition;
};

#endif // TRYY_H
