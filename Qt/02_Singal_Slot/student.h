#ifndef STUDENT_H
#define STUDENT_H

#include <QObject>

class Student : public QObject
{
    Q_OBJECT
public:
    explicit Student(QObject *parent = nullptr);

signals:

public slots:
    //早起QT，槽函数必须再次，高版本也可以写到public下
    //返回值void，需要声明，也要实现， 可以有参数据，可以发生重载
    void fun2();
    void fun2(QString str1);
};

#endif // STUDENT_H
