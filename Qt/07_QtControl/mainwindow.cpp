#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->rBtnMan->setChecked(true);
    ui->rbtnWoman->setChecked(true);
    connect(ui->rbtnWoman, &QRadioButton::clicked,[=](){
        qDebug() << "Chose Woman";
    });
    //treeWidget
    ui->treeWidget->setHeaderLabels(QStringList() << "位置" << "队伍");
    QTreeWidgetItem *itemTOP = new QTreeWidgetItem(QStringList() << "上单");
    QTreeWidgetItem *itemJUG = new QTreeWidgetItem(QStringList() << "打野");
    QTreeWidgetItem *itemMID = new QTreeWidgetItem(QStringList() << "中单");
    QTreeWidgetItem *itemADC = new QTreeWidgetItem(QStringList() << "射手");
    QTreeWidgetItem *itemSUP = new QTreeWidgetItem(QStringList() << "辅助");
    ui->treeWidget->addTopLevelItem(itemTOP);
    ui->treeWidget->addTopLevelItem(itemJUG);
    ui->treeWidget->addTopLevelItem(itemMID);
    ui->treeWidget->addTopLevelItem(itemADC);
    ui->treeWidget->addTopLevelItem(itemSUP);
    QTreeWidgetItem *Bin = new QTreeWidgetItem(QStringList() << "陈泽彬" << "RNG");
    itemTOP->addChild(Bin);
}

MainWindow::~MainWindow()
{
    delete ui;
}
