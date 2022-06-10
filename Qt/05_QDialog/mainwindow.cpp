#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDialog>
#include <QDebug>
#include <QColor>
#include <QFont>
#include <QMessageBox>
#include <QColorDialog>
#include <QFileDialog>
#include <QFontDialog>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(960, 540);
    //点击按钮弹出对话框
    connect(ui->actionNew, &QAction::triggered, [=](){
    //对话框
    //非模态对话框：可以对其他窗口操作
    //模态对话框: 不可以对其他窗口操作

        //创建模态
//      QDialog dlg(this);
//      dlg.resize(200, 100);
//      dlg.exec();
//      qDebug() << "模态对话框弹出了";

        //创建非模态
//      QDialog *dlg1 = new QDialog(this);
//      dlg1->resize(200, 100);
//      dlg1->show();
//      dlg1->setAttribute(Qt::WA_DeleteOnClose);
//       qDebug() << "非模态对话框弹出了";
        //消息对话框
//        QMessageBox::critical(this, "提示", "Error");
//        QMessageBox::information(this, "信息", "信息");
//        if(QMessageBox::Save == QMessageBox::question(this, "提问", "Question",(QMessageBox::Save | QMessageBox::Cancel), QMessageBox::Cancel))
//        {
//            qDebug() << "保存";
//        }
//        else
//        {
//            qDebug() << "不保存";
//        }
//        QMessageBox::warning(this, "warrning", "警告");

        //其他对话框
        //颜色对话框 返回值是QColor类的实例
//        QColor color = QColorDialog::getColor(QColor(255,0,0));
//        qDebug() << "r=" <<color.red()<< "g=" <<color.green()<< "r=" <<color.blue();
        //文件对话框, 返回值是路径
//        QString str = QFileDialog::getOpenFileName(this, "选择文件", "F:/", "(*.txt)");
//        qDebug() << str;

        //字体对话框
        bool flag;
        QFont font = QFontDialog::getFont(&flag, QFont("华文彩云", 36));
        qDebug() << "字体:" <<font.family() << ",字号:" << font.pointSize();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
