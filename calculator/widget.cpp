#include "widget.h"
#include "ui_widget.h"
#include <QString>
#include<QDebug>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //设置窗口
    setWindowTitle("计算器");
    setFixedSize(356,442);

    //绑定数值按键
    connect(ui->num_0,&QPushButton::clicked,this,[=](){showBtn(num,"0");});
    connect(ui->num_1,&QPushButton::clicked,this,[=](){showBtn(num,"1");});
    connect(ui->num_2,&QPushButton::clicked,this,[=](){showBtn(num,"2");});
    connect(ui->num_3,&QPushButton::clicked,this,[=](){showBtn(num,"3");});
    connect(ui->num_4,&QPushButton::clicked,this,[=](){showBtn(num,"4");});
    connect(ui->num_5,&QPushButton::clicked,this,[=](){showBtn(num,"5");});
    connect(ui->num_6,&QPushButton::clicked,this,[=](){showBtn(num,"6");});
    connect(ui->num_7,&QPushButton::clicked,this,[=](){showBtn(num,"7");});
    connect(ui->num_8,&QPushButton::clicked,this,[=](){showBtn(num,"8");});
    connect(ui->num_9,&QPushButton::clicked,this,[=](){showBtn(num,"9");});
    //绑定运算符
    connect(ui->sum,&QPushButton::clicked,this,[=](){showBtn(op,"+");});
    connect(ui->sub,&QPushButton::clicked,this,[=](){showBtn(op,"-");});
    connect(ui->mul,&QPushButton::clicked,this,[=](){showBtn(op,"*");});
    connect(ui->dvi,&QPushButton::clicked,this,[=](){showBtn(op,"/");});
    //绑定其他
    connect(ui->point,&QPushButton::clicked,this,[=](){showBtn(point,".");});
    connect(ui->back,&QPushButton::clicked,this,[=](){showBtn(back,"back");});
    connect(ui->clear,&QPushButton::clicked,this,[=](){showBtn(clear,"clear");});
    connect(ui->equal,&QPushButton::clicked,this,[=](){showBtn(equal,"equal");});
}

Widget::~Widget()
{
    delete ui;
}

void Widget::showBtn(btnType type, QString btn)
{
    //运算顺序是：数字1 运算符 数字2，按顺序输入
    switch(type)
    {
        case num: //type类型是num
        {
            if(m_op.isEmpty())//运算符为空，则表示当前输入的数字是数字1
            {
                m_num_1 += btn;
            }
            else
            {
                m_num_2 +=btn;
            }
            break;
        }
        case op: //操作运算符
        {

        if(!m_num_1.isEmpty()&&!m_num_2.isEmpty()) //连续运算
        {
            double t = count();
            ui->lineEdit->setText(QString::number(t));
            m_num_1 = QString::number(t);
            m_num_2.clear();

        }
            m_op = btn;
            break;
        }
        case clear://清空
        {
            m_num_1.clear();
            m_num_2.clear();
            m_op.clear();
            break;
        }
        case back: //退格
        {
            if(!m_num_1.isEmpty()&&!m_num_2.isEmpty()&&!m_op.isEmpty())
            {
                m_num_2.chop(1);//数字2尾部删除一个字符
            }
            else if(!m_num_1.isEmpty()&&!m_op.isEmpty())
            {
                m_op.chop(1);//删除运算符
            }
            else if(!m_num_1.isEmpty())
            {
                m_num_1.chop(1);//数字1尾部删除一个字符
            }
            break;
        }
        case point:  //小数点
        {
            if(m_op.isEmpty())
            {
                if(!m_num_1.isEmpty()&&!m_num_1.contains("."))
                {
                    m_num_1 += btn;
                }
            }
            else
            {
                    if(!m_num_2.isEmpty()&&!m_num_2.contains("."))
                    {
                        m_num_2 += btn;
                    }
            }
            break;
        }
        case equal:  //等于
        {
            double t = count();
            ui->lineEdit->setText(QString::number(t));  //显示结果（数字转字符串）
            m_num_1.clear();      //清除屏幕上之前输入的数据
            m_num_2.clear();
            m_op.clear();
            return;  //按等号退出这个循环，输出结果
        }
    }
    ui->lineEdit->setText(m_num_1+m_op +m_num_2);

}

double Widget::count()
{
    double result = 0.0;
    double num1 = m_num_1.toDouble();
    double num2 = m_num_2.toDouble();
    if(m_op == "+")
    {
        result = num1+num2;
    }
    else if(m_op == "-")
    {
        result = num1-num2;
    }
    else if(m_op == "*")
    {
        result = num1*num2;
    }
    else if(m_op == "/")
    {
        if(num2 == 0.0)
        {
            ui->lineEdit->setText("除数不能为0");
        }
        result = num1/num2;
    }
    return result;
}

