#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QDebug>
#include "caculate.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private:
    Ui::Dialog *ui;
    Caculate ca;
    void C_func();//C键的功能
    void delete_func();//<-键的功能

private slots:
    void emitSlot();//按键按下时响应的槽函数
    void writeSlot(QString);//将string写到textBrower的槽函数
    void deleteSlot();//delete的槽函数
    void equalSlot();//“=”号的槽函数

signals:
    void writeSignal(QString);//发送string的信号
    void deleteSignal();//delete键的信号
    void equalSignal();//“=”号的信号
};


#endif // DIALOG_H
