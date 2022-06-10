#include "student.h"
#include <QDebug>
Student::Student(QObject *parent) : QObject(parent)
{

}

void Student::fun2()
{
    qDebug() << "学生响应";
}

void Student::fun2(QString str1)
{
    qDebug() << "学生响应->" << str1.toUtf8().data();
}
