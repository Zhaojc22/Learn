#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->actionNew->setIcon(QIcon(":/src/img/71574661.jpg"));
}

MainWindow::~MainWindow()
{
    delete ui;
}
