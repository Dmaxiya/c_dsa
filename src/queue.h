#ifndef QUEUE_H_
#define QUEUE_H_

#include "bool.h"

typedef int QElemType;

typedef struct QNode {
    QElemType elem;                     // 数据项
    struct QNode *next;                 // 下一元素的地址
} *QNode;

typedef struct Queue {
    QNode front;                        // 队首元素地址，初始化为一个指向QNode 变量的指针并始终指向这一元素，无赋值，next 为空
    QNode rear;                         // 队尾元素地址，初始化为与front 相同的指针，若队列非空，则指向最后一个元素
    int length;                         // 队列长度，初始化为0
} *Queue;

// 外部可调用的函数
void InitQue(Queue *Q);                 // 初始化队列
void DestroyQue(Queue Q);               // 销毁队列
void Qclear(Queue Q);                   // 清空队列
bool Qempty(Queue Q);                   // 判断队列是否为空
int Qlength(Queue Q);                   // 返回队列长度
bool Qfront(Queue Q, QElemType *e);     // 返回队首元素到e，若队列为空，则输出错误提示信息，返回false，不修改e 指向的值
bool Qpush(Queue Q, QElemType e);       // 向队尾添加e，若添加失败，则输出错误提示信息并返回false，不做任何其他操作
bool Qpop(Queue Q);                     // 弹出队首元素，若队列为空，则返回false

#endif // QUEUE_H_

