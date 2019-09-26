#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

void InitQue(Queue *Q) {                // 初始化队列
    *Q = (Queue)malloc(sizeof(struct Queue));
    (*Q)->front = (QNode)malloc(sizeof(struct QNode));
    (*Q)->front->next = NULL;
    (*Q)->rear = (*Q)->front;
    (*Q)->length = 0;
}

void DestroyQue(Queue Q) {              // 销毁队列
    QNode p;
    while(Q->front != NULL) {
        p = Q->front;
        Q->front = Q->front->next;
        free(p);
    }
    free(Q);
}

void Qclear(Queue Q) {                  // 清空队列
    QNode p;
    while(Q->front->next != NULL) {
        p = Q->front->next;
        Q->front->next = Q->front->next->next;
        free(p);
    }
    Q->rear = Q->front;
    Q->length = 0;
}

bool Qempty(Queue Q) {                  // 判断队列是否为空
    return Q->length == 0;
}

int Qlength(Queue Q) {                  // 返回队列长度
    return Q->length;
}

bool Qfront(Queue Q, QElemType *e) {    // 返回队首元素到e，若队列为空，则输出错误提示信息，返回false，不修改e 指向的值
    if(Q->length == 0) {
        printf("\nQueue is empty, do not modify parameters.\n");
        return false;
    } else {
        *e = Q->front->next->elem;
        return true;
    }
}

bool Qpush(Queue Q, QElemType e) {      // 向队尾添加e，若添加失败，则输出错误提示信息并返回false，不做任何其他操作
    QNode p = (QNode)malloc(sizeof(struct QNode));
    if(p == NULL) {
        printf("\nInsufficient memory, failed to push!\n");
        return false;
    } else {
        p->elem = e;
        p->next = NULL;
        Q->rear->next = p;
        Q->rear = p;
        ++Q->length;
        return true;
    }
}

bool Qpop(Queue Q) {                    // 弹出队首元素，若队列为空，则返回false
    if(Q->length == 0)
        return false;
    else {
        QNode p = Q->front->next;
        Q->front->next = Q->front->next->next;
        free(p);
        --Q->length;
        if(Q->length == 0)
            Q->rear = Q->front;
        return true;
    }
}

