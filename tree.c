#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

void InitTree(Tree *T) {                            // 初始化树
    *T = (Tree)malloc(sizeof(struct Tree));
    (*T)->root = NULL;
    (*T)->pos = NULL;
    (*T)->length = 0;
    (*T)->changed = false;
    (*T)->depth = 0;
}

void DestroyTree(Tree T) {                          // 销毁树
    Nergodic(T->root, Free);
    free(T);
}

void Free(TNode t) {                                // 调用free 函数，该函数不允许外部调用
    free(t);
}

bool Tempty(Tree T) {                               // 判断树是否为空
    return T->length == 0;
}

int Tdepth(Tree T) {                                // 返回树的深度，若在上一次调用该函数之后树被改变，则更新depth
    if(T->changed) {
        T->depth = Ndepth(T->root);
        T->changed = false;
        return T->depth;
    }
    return T->depth;
}

int Ndepth(TNode N) {                               // 返回以节点N 为根的子树深度，该函数不允许外部调用
    if(N != NULL) {
        int depth1 = Ndepth(N->lchild) + 1;
        int depth2 = Ndepth(N->rchild) + 1;
        return depth1 > depth2? depth1: depth2;
    } else
        return 0;
}

bool Tvalue(Tree T, TElemType *e) {                 // 返回当前结点元素值，若当前节点为空，则输出错误提示并返回false
    if(T->pos != NULL) {
        *e = T->pos->elem;
        return true;
    } else {
        printf("\nPointer points null, do not modify parameters\n");
        return false;
    }
}

bool Tparent(Tree T) {                              // 令当前结点指向其父节点，无父节点则不移动当前结点并返回false
    if(T->pos != NULL && T->pos->parent != NULL) {
        T->pos = T->pos->parent;
        return true;
    } else
        return false;
}

bool Tlchild(Tree T) {                              // 令当前节点指向其左子节点，无左子节点则不移动当前结点并返回false
    if(T->pos != NULL && T->pos->lchild != NULL) {
        T->pos = T->pos->lchild;
        return true;
    } else
        return false;
}

bool Trchild(Tree T) {                              // 令当前结点指向其右子节点，无右子节点则不移动当前结点并返回false
    if(T->pos != NULL && T->pos->rchild != NULL) {
        T->pos = T->pos->rchild;
        return true;
    } else
        return false;
}

bool Tbrother(Tree T) {                             // 令当前结点指向其兄弟节点，若无兄弟节点则不移动并返回false
    if(T->pos != NULL && T->pos->loc == RIGHT) {
        if(T->pos->parent->lchild != NULL) {
            T->pos = T->pos->parent->lchild;
            return true;
        } else
            return false;
    } else if(T->pos != NULL && T->pos->loc == LEFT) {
        if(T->pos->parent->rchild != NULL) {
            T->pos = T->pos->parent->rchild;
            return true;
        } else
            return false;
    } else
        return false;
}

bool Troot(Tree T) {                                // 令当前结点指向根节点，若无根节点则返回false
    T->pos = T->root;
    if(T->root == NULL)
        return false;
    return true;
}

bool Tinsert(Tree T, Locate lr, TElemType e) {      // 向当前结点添加左/右子节点，若其子节点已存在或开辟空间失败则不添加且返回false
    TNode p = (TNode)malloc(sizeof(struct TNode));
    if(p == NULL) {
        printf("\nInsufficient memory, failed to insert!\n");
        return false;
    } else {
        p->elem = e;
        p->lchild = NULL;
        p->rchild = NULL;
        p->parent = T->pos;
        p->loc = lr;
        if(lr == LEFT) {
            if(T->pos != NULL && T->pos->lchild == NULL) {
                p->depth = T->pos->depth + 1;
                ++T->length;
                T->pos->lchild = p;
                if(T->changed == false)
                    T->depth =  p->depth > T->depth? p->depth: T->depth;
                return true;
            } else {
                free(p);
                printf("\nThe location is not appropriate, failed to insert!\n");
                return false;
            }
        } else if(lr == RIGHT) {
            if(T->pos != NULL && T->pos->rchild == NULL) {
                p->depth = T->pos->depth + 1;
                ++T->length;
                T->pos->rchild = p;
                if(T->changed == false)
                    T->depth =  p->depth > T->depth? p->depth: T->depth;
                return true;
            } else {
                free(p);
                printf("\nThe location is not appropriate, failed to insert!\n");
                return false;
            }
        } else {
            if(T->pos == NULL) {
                p->depth = 1;
                T->root = p;
                T->depth = 1;
                T->pos = p;
                ++T->length;
                T->changed = false;
            } else {
                free(p);
                printf("\nThe location is not appropriate, failed to insert!\n");
                return false;
            }
        }
        return true;
    }
}

bool Tdelete(Tree T) {                              // 删除当前结点，并将当前结点移动至其父节点，必须为叶子结点才允许删除
    if(T->pos == NULL || T->pos->lchild != NULL || T->pos->rchild != NULL) {
        printf("\nThe location is not appropriate, failed to delete!\n");
        return false;
    } else {
        TNode p = T->pos->parent;
        Locate loc = T->pos->loc;
        T->changed = true;
        free(T->pos);
        T->pos = p;
        if(T->pos != NULL) {
            switch(loc) {
            case LEFT:
                T->pos->lchild = NULL;
                break;
            case RIGHT:
                T->pos->rchild = NULL;
                break;
            case ROOT:
                break;
            }
        } else
            T->root = T->pos;
        --T->length;
        return true;
    }
}

bool Tchange(Tree T, TElemType e) {                 // 改变当前结点的值
    if(T->pos != NULL) {
        T->pos->elem = e;
        return true;
    } else {
        printf("Pointer points null, failed to change element\n");
        return false;
    }
}

void Tergodic(Tree T, void (*visit)(TNode t)) {     // 提供外部调用的树的后序遍历
    Nergodic(T->pos, visit);
}

void Nergodic(TNode root, void (*visit)(TNode t)) { // 后序遍历树，该函数不允许外部调用
    if(root != NULL) {
        Nergodic(root->lchild, visit);
        Nergodic(root->rchild, visit);
        visit(root);
    }
}

