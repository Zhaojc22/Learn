#include "mainwindow.h"
#include <QPushButton>
#include <QTextEdit>
#include <QDockWidget>
#include <QStatusBar>
#include <QMenuBar>
#include <QToolBar>
#include <QAction>
#include <QDebug>
#include <QLabel>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(600, 400);

    //创建菜单栏
    QMenuBar *bar = menuBar();

    //放置菜单栏, 空栏不显示,菜单栏最多只有一个
    setMenuBar(bar);

    //创建菜单
    QMenu *fileMenu = bar->addMenu("文件");
    QMenu *editMenu = bar->addMenu("编辑");

    //创建菜单项
    QAction *newAction = fileMenu->addAction("新建");
    fileMenu->addSeparator();
    QAction *openAction = fileMenu->addAction("打开");
    editMenu->addAction("字体");

    //工具栏
    QToolBar *toolBar = new QToolBar(this);
    addToolBar(Qt::LeftToolBarArea, toolBar);
    //后期设置，只允许左右停靠
    toolBar->setAllowedAreas(Qt::LeftToolBarArea | Qt::RightToolBarArea);
    //设置浮动
    toolBar->setFloatable(false);
    //设置移动
    toolBar->setMovable(false);
    //工具栏添加内容
    toolBar->addAction(newAction);
    toolBar->addSeparator();
    toolBar->addAction(openAction);
    // 工具栏添加控件
    QPushButton *btn = new QPushButton("btn", this);
    toolBar->addWidget(btn);

    //状态栏，最多只有一个
    QStatusBar *stBar = new QStatusBar();
    setStatusBar(stBar);
    //放置标签控件
    QLabel *label = new QLabel("提示信息", this);
    stBar->addWidget(label);

    QLabel *label1 = new QLabel("右侧提示信息", this);
    stBar->addPermanentWidget(label1);

    //铆接部件（浮动窗口） 可以有多个
    QDockWidget *dockWidget = new QDockWidget("浮动", this);
    addDockWidget(Qt::BottomDockWidgetArea, dockWidget);
    dockWidget->setAllowedAreas(Qt::TopDockWidgetArea | Qt::BottomDockWidgetArea);

    //设置中心部件，只能有一个
    QTextEdit *edit = new QTextEdit(this);
    setCentralWidget(edit);
}

MainWindow::~MainWindow()
{

}
