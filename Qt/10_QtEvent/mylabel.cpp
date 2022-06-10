#include "mylabel.h"
#include <QDebug>
#include <QMouseEvent>
myLabel::myLabel(QWidget *parent) : QLabel(parent)
{
    setMouseTracking(true);
}

void myLabel::enterEvent(QEvent *event)
{
    qDebug() << "鼠标进入";
}

void myLabel::leaveEvent(QEvent *event)
{
    qDebug() << "鼠标离开";
}

void myLabel::mouseMoveEvent(QMouseEvent *ev)
{
    qDebug() << "鼠标移动";
}

void myLabel::mousePressEvent(QMouseEvent *ev)
{
    if(ev->button() == Qt::LeftButton)
    {
        QString str = QString("鼠标按下 x = %1, y = %2, globalX = %3, globalY = %4").arg(ev->x()).arg(ev->y()).arg(ev->globalX()).arg(ev->globalY());
        qDebug() << str;
    }
}

void myLabel::mouseReleaseEvent(QMouseEvent *ev)
{
    qDebug() << "鼠标释放";
}
