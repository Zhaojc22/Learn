#include "mywidget.h"
#include <QApplication> //应用程序的头文件

//argc: 命令行变量的数量
//argv: 命令行变量的数组
int main(int argc, char *argv[])
{
    //a: 应用程序对象，有且只有一个
    QApplication a(argc, argv);

    //w: 窗口对象，myWidget类的父类是QWidget
    myWidget w;

    //窗口对象默认不显示，调用show方法显示窗口
    w.show();

    //让应用程序对象进入消息循环
    //让代码阻塞到这行
    return a.exec();
    //类似于
//    while(true)
//    {
//        if(点击叉子)n
//        {
//            break;
//        }
//    }
}
