#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void InitList(List *L) {                 // 初始化链表
    (*L) = (List)malloc(sizeof(struct List));
    (*L)->head = (LNode)malloc(sizeof(LNode));
    (*L)->head->next = NULL;
    (*L)->head->prio = NULL;
    (*L)->tail = (*L)->head;
    (*L)->length = 0;
}

void DestroyList(List L) {              // 销毁链表
    LNode p = L->head;
    while(L->head != NULL) {
        L->head = L->head->next;
        free(p);
        p = L->head;
    }
    free(L);
}

bool Lpush_back(List L, LElemType x) {  // 从链表尾部追加x，返回是否追加成功，若失败则输出错误提示信息，不做任何其他操作
    LNode p = (LNode)malloc(sizeof(struct LNode));
    if(p == NULL) {
        printf("Insufficient memory, failed to push back!\n");
        return false;
    }
    p->elem = x;
    p->next = NULL;
    p->prio = L->tail;
    L->tail->next = p;
    L->tail = p;
    ++L->length;
    return true;
}

bool Lpush_front(List L, LElemType x) { // 从链表头部添加x，返回与添加失败处理方式同上
    LNode p = (LNode)malloc(sizeof(struct LNode));
    if(p == NULL) {
        printf("Insufficient memory, failed to push back!\n");
        return false;
    }
    p->elem = x;
    p->prio = L->head;
    p->next = L->head->next;
    if(L->head->next != NULL)
        L->head->next->prio = p;
    L->head->next = p;
    if(L->length == 0)
        L->tail = p;
    ++L->length;
    return true;
}

bool Lpop_back(List L) {                // 弹出链表尾部元素，若链表尾空，则返回false
    LNode p;
    if(L->length == 0)
        return false;
    p = L->tail;
    L->tail = L->tail->prio;
    L->tail->next = NULL;
    free(p);
    --L->length;
    return true;
}

bool Lpop_front(List L) {               // 弹出链表首元素，若链表尾空，则返回false
    LNode p;
    if(L->length == 0)
        return false;
    p = L->head->next;
    L->head->next = p->next;
    if(L->length == 1)
        L->tail = L->head;
    else
        p->next->prio = L->head;
    free(p);
    --L->length;
    return true;
}

bool Lat(List L, int e, LElemType *x)   // 返回从1 开始数第e 个元素，为提高效率，离哪一端近从哪一段开始寻找
// 若e 值非法，则输出错误提示信息并返回false，不做其他任何操作
{
    LNode p;
    int i;
    if(e < 1 || e > L->length) {
        printf("The address is illegal!\n");
        return false;
    }
    if(e > L->length - e) {
        e = L->length - e;
        p = L->tail;
        for(i = 0; i < e; ++i)
            p = p->prio;
    } else {
        p = L->head;
        for(i = 0; i < e; ++i)
            p = p->next;
    }
    *x = p->elem;
    return true;
}

void Lclear(List L) {                   // 清空链表
    LNode p, q;
    p = L->head->next;
    while(p != NULL) {
        q = p->next;
        free(p);
        p = q;
    }
    L->head->next = NULL;
    L->tail = L->head;
    L->length = 0;
}

bool Lempty(List L) {                   // 判断链表是否为空
    return L->length == 0;
}

int Llength(List L) {                   // 返回链表长度
    return L->length;
}

void Lsort(List L, int(*cmp)(const void *a, const void *b))
// 将链表元素复制到新开辟的length 长度的数组中并清空链表
// 用stdlib.h 中的qsort 函数给数组内容排序，将数组元素以此添加到链表中
{
    int i = 0, l = L->length;
    LElemType *temp = (LElemType*)malloc(sizeof(LElemType));
    LNode p, q;
    p = L->head->next;
    while(p != NULL) {
        q = p->next;
        temp[i] = p->elem;
        ++i;
        free(p);
        p = q;
    }
    L->head->next = NULL;
    L->tail = L->head;
    L->length = 0;
    qsort(temp, l, sizeof(LElemType), cmp);
    for(i = 0; i < l; ++i)
        Lpush_back(L, temp[i]);
    free(temp);
}

