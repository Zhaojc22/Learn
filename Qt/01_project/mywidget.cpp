#include "mywidget.h"
#include "mypushbutton.h"

#include <QPushButton>
#include <QDebug>
myWidget::myWidget(QWidget *parent)
    : QWidget(parent)
{
    QPushButton *btn = new QPushButton;
//    btn->show();    //show以顶层的方式弹出窗口控件
    btn->setParent(this);

    //显示按钮
    btn->setText("按钮");

    //创建Button2
    QPushButton *btn2 = new QPushButton("按钮2", this);

    //移动button2到100， 100,
    btn2->move(100, 100);

    //设置窗口大小，用户可调节
    resize(600, 400);

    //设置窗口固定大小
    setFixedSize(600, 400);

    //设置窗口标题
    setWindowTitle("窗口1");

    MyPushButton *btn3 = new MyPushButton();
    btn3->setText("按钮3");
    btn3->move(200,0);
    btn3->setParent(this);

    //需求：点击按钮1，关闭窗口
    //信号和槽：singal 和 slot
    //松散耦合
    connect(btn, &MyPushButton::clicked, this, &myWidget::close);
}

myWidget::~myWidget()
{
    qDebug() << "myWidget 析构调用";
}
