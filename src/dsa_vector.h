#ifndef DSA_VECTOR_H_
#define DSA_VECTOR_H_

#include "dsa_bool.h"

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
    vector (*copy)(vector vct);                             // 获取 vct 的拷贝
    vectorElemType* (*data)(vector vct);                    // 获取内部储存数组的首地址
    void (*destory)(vector vct);                            // 销毁 vector 对象
    bool (*empty)(vector vct);                              // 判断 vector 是否为空
    void (*erase)(vector vct, int index);                   // 删除第 index 个元素
    vectorElemType (*front)(vector vct);                    // 返回 vector 的第一个元素
    void (*insert)(vector vct, int index, vectorElemType e);// 在第 index 个元素之前插入一个数据
    void (*pop_back)(vector vct);                           // 弹出数组尾部元素
    void (*push_back)(vector vct, vectorElemType e);        // 往 vector 尾部追加 e
    void (*reserve)(vector vct, int n);                     // 将 vector 的容量调整到至少为 n
    void (*resize)(vector vct, int n, vectorElemType e);    // 将 vector 的大小重置为 n，如果 n 大于 vector 中的元素数量，则多出的部分用 e 补充
    void (*set)(vector vct, int index, vectorElemType e);   // 将第 index 个元素置为 x
    void (*shrink_to_fit)(vector vct);                      // 将 vector 的容量调整为合适的大小
    int (*size)(vector vct);                                // 返回 vector 内元素个数
    void (*swap)(vector vct1, vector vct2);                 // 交换 vct1 与 vct2
} Vectors;

// 外部可访问函数
vector newVector(void);                                     // 获取一个新的 vector 对象并初始化

#endif // DSA_VECTOR_H_
