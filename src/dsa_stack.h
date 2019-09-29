#ifndef STACK_H_
#define STACK_H_

#include "bool.h"

typedef int SElemType;

typedef struct SNode {
    SElemType elem;                 // 数据项
    struct SNode *next;             // 下一元素地址
} *SNode;

typedef struct Stack {
    SNode top;                      // 栈顶地址，初始化为NULL，next 也为NULL
    int length;                     // 栈长度，初始化长度为0
} *Stack;

// 外部可调用的函数
void InitStack(Stack *S);           // 初始化栈
void DestroyStack(Stack S);         // 销毁栈
void Sclear(Stack S);               // 清空栈
bool Sempty(Stack S);               // 判断栈是否为空
int Slength(Stack S);               // 返回栈的长度
bool Stop(Stack S, SElemType *e);   // 返回栈顶元素到e 并返回true，若栈为空，则输出错误提示信息并返回false，不改变e 指向的值
bool Spush(Stack S, SElemType e);   // 元素e 入栈，返回是否入栈成功，若入栈失败，输出错误提示信息并返回false，不做任何其他操作
bool Spop(Stack S);                 // 弹出栈顶元素，若栈为空，则返回false

#endif // STACK_H_

