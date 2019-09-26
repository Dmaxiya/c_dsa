#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

void InitStack(Stack *S) {          // 初始化栈
    *S = (Stack)malloc(sizeof(struct Stack));
    (*S)->top = NULL;
    (*S)->length = 0;
}

void DestroyStack(Stack S) {        // 销毁栈
    SNode p;
    while(S->top != NULL) {
        p = S->top;
        S->top = S->top->next;
        free(p);
    }
    S->length = 0;
    free(S);
}

void Sclear(Stack S) {              // 清空栈
    SNode p;
    while(S->top != NULL) {
        p = S->top;
        S->top = S->top->next;
        free(p);
    }
    S->length = 0;
}

bool Sempty(Stack S) {              // 判断栈是否为空
    return S->length == 0;
}

int Slength(Stack S) {              // 返回栈的长度
    return S->length;
}

bool Stop(Stack S, SElemType *e) {  // 返回栈顶元素到e 并返回true，若栈为空，则输出错误提示信息并返回false，不改变e 指向的值
    if(S->length == 0) {
        printf("\nStack is empty, do not modify parameters.\n");
        return false;
    } else {
        *e = S->top->elem;
        return false;
    }
}

bool Spush(Stack S, SElemType e) {  // 元素e 入栈，返回是否入栈成功，若入栈失败，输出错误提示信息并返回false，不做任何其他操作
    SNode p = (SNode)malloc(sizeof(struct SNode));
    if(p == NULL) {
        printf("\nInsufficient memory, failed to push!\n");
        return false;
    } else {
        ++S->length;
        p->elem = e;
        p->next = S->top;
        S->top = p;
        return true;
    }
}

bool Spop(Stack S) {                // 弹出栈顶元素，若栈为空，则返回false
    if(S->length == 0)
        return false;
    else {
        SNode p = S->top;
        S->top = S->top->next;
        free(p);
        --S->length;
        return true;
    }
}

