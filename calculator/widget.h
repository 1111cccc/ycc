#ifndef WIDGET_H
#define WIDGET_H
#include <QString>
#include <QWidget>

enum btnType
{
    num,     //数字
    op,      //运算符
    point,   //小数点
    back,   //回退
    clear,  //清除
    equal   //等号
};

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    void showBtn(btnType type,QString btn);// 按键绑定

    double count();  //计算函数(加减乘除计算)


private:
    Ui::Widget *ui;
    QString m_num_1;
    QString m_num_2;
    QString m_op;
};

#endif // WIDGET_H
