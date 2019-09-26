#ifndef LIST_H_
#define LIST_H_

#include "bool.h"

typedef int LElemType;

typedef struct LNode {
    LElemType elem;                     // 数据项
    struct LNode *next;                 // 下一元素的地址
    struct LNode *prio;                 // 上一元素的地址
} *LNode;

typedef struct List {
    LNode head;                         // 头指针，初始化为一个指向LNode 变量的指针并始终指向这一元素，无赋值，next 和prio 都为空
    LNode tail;                         // 尾指针，初始化为与head 相同的指针，若链表非空，则指向最后一个元素
    int length;                         // 链表长度，初始化为0
} *List;

void InitList(List *L);                 // 初始化链表
void DestroyList(List L);               // 销毁链表
bool Lpush_back(List L, LElemType x);   // 从链表尾部追加x，返回是否追加成功，若失败则输出错误提示信息，不做任何其他操作
bool Lpush_front(List L, LElemType x);  // 从链表头部添加x，返回与添加失败处理方式同上
bool Lpop_back(List L);                 // 弹出链表尾部元素，若链表为空，则返回false
bool Lpop_front(List L);                // 弹出链表首元素，若链表为空，则返回false
bool Lat(List L, int e, LElemType *x);  // 返回从1 开始数第e 个元素，为提高效率，离哪一端近从哪一段开始寻找
// 若e 值非法，则输出错误提示信息并返回false，不做其他任何操作
void Lclear(List L);                    // 清空链表
bool Lempty(List L);                    // 判断链表是否为空
int Llength(List L);                    // 返回链表长度
void Lsort(List L, int(*cmp)(const void *a, const void *b));
// 将链表元素复制到新开辟的length 长度的数组中并清空链表
// 用stdlib.h 中的qsort 函数给数组内容排序，将数组元素依次添加到链表中

#endif // LIST_H_

