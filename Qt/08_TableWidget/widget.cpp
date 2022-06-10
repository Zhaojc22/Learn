#include "widget.h"
#include "ui_widget.h"
#include <QMovie>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //tableWidget
    //设置列数
    ui->tableWidget->setColumnCount(3);
    //设置表头
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "性名" << "性别" << "年龄" );

    //设置行数
    ui->tableWidget->setRowCount(5);
//    ui->tableWidget->setItem(0, 0,new QTableWidgetItem("李知恩"));
    QStringList nameList;
    nameList << "李知恩" << "周也" << "刘宝仪" << "影" << "凌华";

    QList<QString> sexList;
    sexList << "女" << "女" << "女" << "女" << "女";

    for(int i = 0; i < 5; i++)
    {
        int col = 0;
        ui->tableWidget->setItem(i, col++, new QTableWidgetItem(nameList[i]));//这种方式访问，超出范围会程序卡死
        ui->tableWidget->setItem(i, col++, new QTableWidgetItem(sexList.at(i)));//这种方式超出范围会报错
        ui->tableWidget->setItem(i, col++, new QTableWidgetItem(QString::number(i+18)));
    }

    //栈控件
    ui->stackedWidget->setCurrentIndex(0);
    connect(ui->btnTable, &QPushButton::clicked, [=](){
        ui->stackedWidget->setCurrentIndex(0);
    });

    connect(ui->btnToolBox, &QPushButton::clicked, [=](){
        ui->stackedWidget->setCurrentIndex(1);
    });

    connect(ui->btnScroll, &QPushButton::clicked, [=](){
        ui->stackedWidget->setCurrentIndex(2);
    });

    connect(ui->btnTabWidget, &QPushButton::clicked, [=](){
        ui->stackedWidget->setCurrentIndex(3);
    });

    //下拉框 comboBox
    ui->comboBox->addItem(nameList.at(0));
    ui->comboBox->addItem(nameList.at(1));
    ui->comboBox->addItem(nameList.at(2));
    ui->comboBox->addItem(nameList.at(3));
    ui->comboBox->addItem(nameList.at(4));

    connect(ui->btnChose, &QPushButton::clicked, [=](){
        ui->comboBox->setCurrentIndex(0);
    });

    //QLabel显示图片
    ui->lbl_img->setPixmap(QPixmap(":/src/img/71574661.jpg"));
    ui->lbl_img->adjustSize();

    //Qlable显示gif
    QMovie *movie = new QMovie(":/src/img/abc.gif");
    ui->lbl_gif->setMovie(movie);
    movie->start();
}

Widget::~Widget()
{
    delete ui;
}
