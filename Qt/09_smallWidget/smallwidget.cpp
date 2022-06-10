#include "smallwidget.h"
#include "ui_smallwidget.h"

SmallWidget::SmallWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SmallWidget)
{
    ui->setupUi(this);
    //QSpinBox移动，QSlider跟随移动
    void (QSpinBox::*spSignal)(int) = &QSpinBox::valueChanged;
    connect(ui->spinBox, spSignal, ui->horizontalSlider, &QSlider::setValue);
    //QSlider移动，QSpinBox跟随移动
    connect(ui->horizontalSlider, &QSlider::valueChanged, ui->spinBox, &QSpinBox::setValue);
}

void SmallWidget::SetNumber(int num)
{
    ui->spinBox->setValue(num);
}

int SmallWidget::GetNumber()
{
    return ui->spinBox->value();
}

SmallWidget::~SmallWidget()
{
    delete ui;
}


