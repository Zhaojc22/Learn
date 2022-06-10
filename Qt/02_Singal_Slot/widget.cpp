#include "widget.h"
#include <QPushButton>
//需求：
// Teacher类
// Student类
// Teacher触发信号，Student响应信号
Widget::Widget(QWidget *parent)
    : QWidget(parent)
{

    this->teacher = new Teacher(this);
    this->student = new Student(this);

//    connect(teacher, &Teacher::fun1, student, &Student::fun2);
//    funcTrigger();

    void(Teacher::*teacherSingal)(QString) = &Teacher::fun1;
    void(Student::*StudentSlot)(QString) = &Student::fun2;
    connect(teacher, teacherSingal, student, StudentSlot);

    QPushButton *btn = new QPushButton("Trigger", this);
    this->resize(600, 400);
//    connect(btn, &QPushButton::clicked, this, &Widget::funcTrigger);

    void(Teacher::*teacherSingal2)(void) = &Teacher::fun1;
    void(Student::*StudentSlot2)(void) = &Student::fun2;
    connect(teacher, teacherSingal2, student, StudentSlot2);
//    connect(teacher, SIGNAL(fun1(), student, SLOT(fun2());  //QT4写法，当前5无法运行
    connect(btn, &QPushButton::clicked, teacher, teacherSingal2);
    //拓展
    //1、信号可以连接信号
    //2、一个信号可以连接多个槽函数
    //3、多个信号可以连接同一个槽函数
    //4、槽函数的参数列表必须是对应的,信号的参数可以多于槽函数，槽函数可以不接，但你不能不发

    QPushButton *btn1 = new QPushButton("Open", this);
    btn1->move(100, 100);
    QPushButton *btn2 = new QPushButton("Close", this);
    btn2->move(200, 200);
    QWidget *w1 = new QWidget;
    w1->setWindowTitle("Window 2");
    w1->resize(600, 400);
    connect(btn1, &QPushButton::clicked, [=](){
        btn->setText("c1");
        w1->show();
    });
    connect(btn2, &QPushButton::clicked,[=](){
        btn->setText("c2");
        w1->close();
    });
}

void Widget::funcTrigger()
{
//    emit teacher->fun1();
    emit teacher->fun1("有参数的");
}

Widget::~Widget()
{

}
