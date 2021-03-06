#ifndef SMALLWIDGET_H
#define SMALLWIDGET_H

#include <QWidget>

namespace Ui {
class SmallWidget;
}

class SmallWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SmallWidget(QWidget *parent = 0);
    ~SmallWidget();

    void SetNumber(int num);
    int GetNumber();

private:
    Ui::SmallWidget *ui;
};

#endif // SMALLWIDGET_H
