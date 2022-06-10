#include "mypushbutton.h"
#include <QDebug>
MyPushButton::MyPushButton(QWidget *parent) : QPushButton(parent)
{
    qDebug() << "MyPushButton 构造调用";
}

MyPushButton::~MyPushButton()
{
    qDebug() << "MyPushButton 析构调用";
}

