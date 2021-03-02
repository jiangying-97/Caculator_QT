#include "caculate.h"

//构造函数
Caculate::Caculate():string(""),result(0){

}
//析构函数
Caculate::~Caculate(){

}

//接收来自按钮传入的字符，添加到string表达式中
QString Caculate::write_string(QString s){
    string=string+s;
    return string;
}

//计算结果的函数
void Caculate::caculate_result(){
    St st;//初始化一个栈
    set_top(0,&st);
    int i=0;//设置一个计数器，开始遍历表达式
    float num=0;//初始化一个取数字的num
    int j=0;//用于记录上一个运算符的位置
    while(1){//中缀表达式转后缀表达式后计算
        num=0;
        if(string[i] == QChar('+') || string[i] == QChar('-')  || string[i] == QChar('X')  || string[i] == QChar('/') ||string[i] == QChar('=') ){
            num=string.mid(j,i-j).toFloat();
            qDebug()<<"num="<<num<<endl;
            push1(&st,num);//数字直接入栈
//使用栈计算结果-->核心算法；------------------------------------------------------------------------------------------
            if(st.top2<=0){//栈空直接将运算符入栈
                push2(&st,string[i]);
            }
            else {//栈不空，比较栈顶元素
                if(string[i]==QChar('X') || string[i]==QChar('/')){//乘除直接入栈
                    push2(&st,string[i]);
                }
                if(string[i]==QChar('+') || string[i]==QChar('-') ||string[i]==QChar('=')){//需要出栈，出栈就开始计算
                    while(st.top2!=0){//栈不空，循环出栈
                        QChar ch=pop2(&st);
                        if(ch==QChar('X')){//出栈的运算符为乘时
                            float a=pop1(&st);
                            float b=pop1(&st);
                            qDebug()<<"b*a="<<b*a<<endl;
                            push1(&st,b*a);
                        }
                        if(ch==QChar('/')){//出栈的运算符为÷时
                            float a=pop1(&st);
                            float b=pop1(&st);
                            qDebug()<<"b/a="<<b/a<<endl;
                            push1(&st,b/a);
                        }
                        if(ch==QChar('+')){//出栈的运算符为+时
                            float a=pop1(&st);
                            float b=pop1(&st);
                            qDebug()<<"b+a="<<b+a<<endl;
                            push1(&st,b+a);
                        }
                        if(ch==QChar('-')){//出栈的运算符为-时
                            float a=pop1(&st);
                            float b=pop1(&st);
                            qDebug()<<"b-a="<<b-a<<endl;
                            push1(&st,b-a);
                        }
                    }
                    push2(&st,string[i]);
                }
            }
            j=i+1;
        }
        if(string[i]==QChar('=')){
            break;
        }
        i++;
    }
//---------------------------------------------------------------------
    result=pop1(&st);
    qDebug()<<"result_end="<<result<<endl;
}
//入栈的函数,float数入栈
void Caculate::push1(St_p st,float num){
    if(st->top1>100){
        qDebug()<<"计算器的栈空间满了";
        return;
    }
    st->arr1[st->top1++]=num;
}
//入栈的函数，QChar入栈
void Caculate::push2(St_p st,QChar ch){
    if(st->top2>100){
        qDebug()<<"计算器的栈空间满了";
        return;
    }
    st->arr2[st->top2++]=ch;
}
//出栈函数,float数出栈
float Caculate::pop1(St_p st){
    if(st->top1<=0){
        qDebug()<<"计算器的栈空间为空，无法输出";
        return 0;
    }
    float num=st->arr1[--st->top1];
    return num;
}
//出栈函数，QCchar出栈
QChar Caculate::pop2(St_p st){
    if(st->top2<=0){
        qDebug()<<"计算器的栈空间为空，无法输出";
        return 0;
    }
    QChar ch=st->arr2[--st->top2];
    return ch;
}

