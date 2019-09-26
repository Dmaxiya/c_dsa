#ifndef VECTOR_H_
#define VECTOR_H_

#include "bool.h"

typedef int vectorElemType;

typedef struct vector {
    // 数据成员，外部不可访问
    int length;             // 数组当前长度，初始化为 0
    int totalSize;          // 数组总长度，初始化为 initSize
    vectorElemType *elem;   // 数组首地址
} *vector;

// 函数成员，外部可访问
struct {
    void (*assign)(vector vct, int size, vectorElemType e);
    vectorElemType (*at)(vector vct, int index);            // 返回第 index 个元素
    vectorElemType (*back)(vector vct);                     // 返回末尾元素
    int (*capacity)(vector vct);                            // 返回当前 vector 的容量
    void (*clear)(vector vct);                              // 清空 vector
    vector (*copy)(vector vct);
    vectorElemType* (*data)(vector vct);                    // 获取内部储存数组的首地址
    void (*destory)(vector vct);                            // 销毁 vector 对象
    bool (*empty)(vector vct);                              // 判断 vector 是否为空
    void (*erase)(vector vct, int index);// 删除第 index 个元素
    vectorElemType (*front)(vector vct);
    void (*insert)(vector vct, int index, vectorElemType e);// 在第 index 个元素之前插入一个数据
    int (*max_size)(vector vct);
    void (*pop_back)(vector vct);// 弹出数组尾部元素
    void (*push_back)(vector vct, vectorElemType e);// 往 vector 尾部追加 e
    void (*reserve)(vector vct, int size);
    void (*resize)(vector vct, int size, vectorElemType e);
    void (*set)(vector vct, int index, vectorElemType e);// 将第 index 个元素置为 x
    void (*shrink_to_fit)(vector vct);
    int (*size)(vector vct);// 返回 vector 内元素个数
    void (*swap)(vector vct1, vector vct2);
} Vectors;

// 外部可访问函数
vector newVector();                                             // 获取一个新的 vector 对象并初始化

#endif // VECTOR_H_
