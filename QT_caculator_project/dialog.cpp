#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    //连接按钮与发送信号的槽函数
    connect(ui->num1_Button,SIGNAL(clicked()),this,SLOT(emitSlot()));//1
    connect(ui->num2_Button,SIGNAL(clicked()),this,SLOT(emitSlot()));//2
    connect(ui->num3_Button,SIGNAL(clicked()),this,SLOT(emitSlot()));//3
    connect(ui->num4_Button,SIGNAL(clicked()),this,SLOT(emitSlot()));//4
    connect(ui->num5_Button,SIGNAL(clicked()),this,SLOT(emitSlot()));//5
    connect(ui->num6_Button,SIGNAL(clicked()),this,SLOT(emitSlot()));//6
    connect(ui->num7_Button,SIGNAL(clicked()),this,SLOT(emitSlot()));//7
    connect(ui->num8_Button,SIGNAL(clicked()),this,SLOT(emitSlot()));//8
    connect(ui->num9_Button,SIGNAL(clicked()),this,SLOT(emitSlot()));//9
    connect(ui->zero_Button,SIGNAL(clicked()),this,SLOT(emitSlot()));//0
    connect(ui->C_Button,SIGNAL(clicked()),this,SLOT(emitSlot()));//C
    connect(ui->divide_Button,SIGNAL(clicked()),this,SLOT(emitSlot()));//÷
    connect(ui->delete_Button,SIGNAL(clicked()),this,SLOT(emitSlot()));//<-
    connect(ui->X_Button,SIGNAL(clicked()),this,SLOT(emitSlot()));//X
    connect(ui->add_Button,SIGNAL(clicked()),this,SLOT(emitSlot()));//+
    connect(ui->sub_Button,SIGNAL(clicked()),this,SLOT(emitSlot()));//-
    connect(ui->pointer_Button,SIGNAL(clicked()),this,SLOT(emitSlot()));//.
    connect(ui->equal_Button,SIGNAL(clicked()),this,SLOT(emitSlot()));//=

    //连接发送信号的emitSlot与writeSlot槽函数
    connect(this,SIGNAL(writeSignal(QString)),this, SLOT(writeSlot(QString)));
    //连接发送信号的deleteSignal与deleteSlot
    connect(this,SIGNAL(deleteSignal()),this,SLOT(deleteSlot()));
    //连接发送信号的equalSignal和equalSlot
    connect(this,SIGNAL(equalSignal()),this,SLOT(equalSlot()));

}

//text接收到的信号的槽函数
void Dialog::writeSlot(QString string){
    ui->textBrowser->append(string);
}
//点击按键发送一个带有按钮信息的信号的槽函数
void Dialog::emitSlot(){
    ui->textBrowser->clear();//清空屏幕；
    QPushButton *btn = qobject_cast<QPushButton *>(sender());//获取当前信号的发送者

    //判断是哪些按键被按下，然后发送不同的信号
    QString s=btn->text();
    if((s.toInt()>0) && (s.toInt()<=9)){//如果数字键被按下
        qDebug()<<"数字键被按下";
        emit writeSignal(ca.write_string(s));
    }
    if(s=="0"){//判断数字0
        qDebug()<<"数字键被按下";
        emit writeSignal(ca.write_string(s));
    }
    if(s=="C"){//判断是否为Clear按钮
        qDebug()<<"C键被按下";
        ca.set_string("");//将字符串清空
        ca.set_result(0);//将结果清空
    }
    if(s=="<-"){//判断是否为delete按键
        qDebug()<<"delete键被按下";
        emit deleteSignal();//是则发送delete信号，调用deleteSlot函数;
    }
    if(s=="÷"){
        qDebug()<<"÷键被按下";
        emit writeSignal(ca.write_string("/"));
    }
    if(s=="X"){
        qDebug()<<"X键被按下";
        emit writeSignal(ca.write_string(s));
    }
    if(s=="+"){
        qDebug()<<"+键被按下";
        emit writeSignal(ca.write_string(s));
    }
    if(s=="-"){
        qDebug()<<"-键被按下";
        emit writeSignal(ca.write_string(s));
    }
    if(s=="."){
        qDebug()<<"小数点被按下";
        emit writeSignal(ca.write_string(s));
    }
    if(s=="="){//判断“=”号键是否被按下
        qDebug()<<"=键被按下";
        emit writeSignal(ca.write_string(s));
        emit equalSignal();//开始计算表示的值
    }

}

//delete的槽函数
void Dialog::deleteSlot(){
    QString string=ca.get_string();
    string.chop(1);
    ca.set_string(string);
    ui->textBrowser->clear();
    ui->textBrowser->append(ca.get_string());
}

//“=”号的槽函数
void Dialog::equalSlot(){
    qDebug()<<"开始计算表达式";
    ca.caculate_result();//开始计算结果
    float result=ca.get_result();//获取结果;
    QString string=QString("%1").arg(result);//将浮点型转化为字符串
    //简单申明一个样式
    ui->textBrowser->append("<font style='color:red;font-size:50px'>"+string);//写道textBrower中
    ca.set_string(string);//从新设置string的内容;
}

//C键的功能
void Dialog::C_func(){
    qDebug()<<"执行C_func";
    //下面写功能

}

//delete键的功能
void Dialog::delete_func(){
    qDebug()<<"执行delete_func";
    //下面写功能
    emit deleteSlot();
}

Dialog::~Dialog()
{
    delete ui;
}
