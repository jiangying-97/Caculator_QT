#ifndef CACULATE_H
#define CACULATE_H

#include <QDialog>
#include <QDebug>
#include <QChar>

class Caculate
{
private:
    QString string;//一个记录表达式的字符串
    float result;//计算的结果保存在这里
    typedef struct stack{//定义一个栈
        float arr1[100];
        QChar arr2[100];
        int top1;
        int top2;
    }St,*St_p;
public:
    //构造和析构函数
    Caculate();
    ~Caculate();

    //接口函数
    void set_string(QString s){
        string=s;
    }

    QString get_string(){
        return string;
    }

    float get_result(){
        return result;
    }

    void set_result(int n){
        result=n;
    }

    void set_top(int n,St_p st){
        st->top1=n;
        st->top2=n;
    }

    //功能函数
    QString write_string(QString);//改变string的表达式的哑元函数;
    void caculate_result();//计算string中的jieguo

    //栈函数
    void push1(St_p,float);//入栈函数1
    void push2(St_p,QChar);//入栈函数2
    float pop1(St_p);//出栈函数1
    QChar pop2(St_p);//出栈函数2
};

#endif // CACULATE_H
