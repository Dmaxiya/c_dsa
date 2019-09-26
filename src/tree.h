#ifndef TREE_H_
#define TREE_H_

#include "bool.h"

typedef int TElemType;
typedef enum {ROOT, LEFT, RIGHT} Locate;

typedef struct TNode {
    TElemType elem;                                 // 数据项
    int depth;                                      // 节点所在深度
    Locate loc;                                     // 节点位置
    struct TNode *lchild;                           // 节点的左子节点
    struct TNode *rchild;                           // 节点的右子节点
    struct TNode *parent;                           // 节点的父节点
} *TNode;

typedef struct Tree {
    TNode root;                                     // 树的根节点，初始化为空
    TNode pos;                                      // 树的当前结点，初始化为根节点
    int length;                                     // 树的节点数，初始化为0
    bool changed;                                   // 标记在改变树的结构后深度是否更新，初始化为false
    int depth;                                      // 树的深度，初始化为0
} *Tree;

// 外部可访问的函数
void InitTree(Tree *T);                             // 初始化树
void DestroyTree(Tree T);                           // 销毁树
bool Tempty(Tree T);                                // 判断树是否为空
int Tdepth(Tree T);                                 // 返回树的深度，若在上一次调用该函数之后树被改变，则更新depth
bool Tvalue(Tree T, TElemType *e);                  // 返回当前结点元素值，若当前节点为空，则输出错误提示并返回false
bool Tparent(Tree T);                               // 令当前结点指向其父节点，无父节点则不移动当前结点并返回false
bool Tlchild(Tree T);                               // 令当前节点指向其左子节点，无左子节点则不移动当前结点并返回false
bool Trchild(Tree T);                               // 令当前结点指向其右子节点，无右子节点则不移动当前结点并返回false
bool Tbrother(Tree T);                              // 令当前结点指向其兄弟节点，若无兄弟节点则不移动并返回false
bool Troot(Tree T);                                 // 令当前结点指向根节点，若无根节点则返回false
bool Tinsert(Tree T, Locate lr, TElemType e);       // 向当前结点添加左/右子节点，若其子节点已存在或开辟空间失败则不添加且返回false
bool Tdelete(Tree T);                               // 删除当前结点，并将当前结点移动至其父节点，必须为叶子结点才允许删除
bool Tchange(Tree T, TElemType e);                  // 改变当前结点的值
void Tergodic(Tree T, void (*visit)(TNode t));      // 提供外部调用的从当前结点开始的后序遍历

// 外部不可访问的函数
void Free(TNode t);                                 // 调用free 函数，该函数不允许外部调用
int Ndepth(TNode N);                                // 返回以节点N 为根的子树深度，该函数不允许外部调用
void Nergodic(TNode root, void (*visit)(TNode t));  // 后序遍历树，该函数不允许外部调用

#endif // TREE_H_

