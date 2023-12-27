#ifndef __BALANCE_BINARY_SEARCHTREE_H_
#define __BALANCE_BINARY_SEARCHTREE_H_

#define ELELMENTTYPE void *

typedef struct AVLTreeNode
{
    ELELMENTTYPE data;
    /* 结点高度 */
    int height;
    struct AVLTreeNode * left;   /* 左子树 */
    struct AVLTreeNode * right;  /* 右子树 */
    struct AVLTreeNode * parent; /* 父结点 */

}AVLTreeNode;

typedef struct BalanceBinarySearchTree
{
    /* 根节点 */
    AVLTreeNode * root;
    /* 树的结点个数 */
    int size;
    /* 钩子函数/比较器 */
    int (*compareFunc)(ELELMENTTYPE val1, ELELMENTTYPE val2);
    /* 钩子函数/包装器（实现自定义打印） */
    int (*printFunc)(ELELMENTTYPE val);
}BalanceBinarySearchTree;

/* 二叉搜索树的初始化 */
int balanceBinarySearchTreeInit(BalanceBinarySearchTree ** pBstree, int (*compareFunc)(ELELMENTTYPE val1, ELELMENTTYPE val2), int (*printFunc)(ELELMENTTYPE val));

/* 二叉搜索树的插入 */
int balanceBinarySearchTreeInsert(BalanceBinarySearchTree * pBstree, ELELMENTTYPE val);

/* 二叉搜索树是否包含指定元素 */
int balanceBinarySearchTreeIsContainAppointVal(BalanceBinarySearchTree * pBstree, ELELMENTTYPE val);

/* 二叉搜索树的前序遍历 */
int balanceBinarySearchTreePreOrderTravel(BalanceBinarySearchTree * pBstree);

/* 二叉搜索树的中序遍历 */
int balanceBinarySearchTreeInOrderTravel(BalanceBinarySearchTree * pBstree);

/* 二叉搜索树的后序遍历*/
int balanceBinarySearchTreePostOrderTravel(BalanceBinarySearchTree * pBstree);

/* 二叉搜索树的层序遍历 */
int balanceBinarySearchTreeLevelOrderTravel(BalanceBinarySearchTree * pBstree);

/* 获取二叉搜索树的结点个数 */
int balanceBinarySearchTreeGetNodeSize(BalanceBinarySearchTree * pBstree, int * pSize);

/* 获取二叉搜索树的高度 */
int balanceBinarySearchTreeGetHeight(BalanceBinarySearchTree * pBstree, int * pHeight);

/* 二叉搜索树删除指定的值 */
int balanceBinarySearchTreeDelete(BalanceBinarySearchTree * pBstree, ELELMENTTYPE val);

/* 二叉搜索树的销毁 */
int balanceBinarySearchTreeDestroy(BalanceBinarySearchTree * pBstree);

/* 判断搜索二叉树是否是完全二叉树 */
int balanceBinarySearchTreeIsCompelete(BalanceBinarySearchTree * pBstree);

#endif //__BALANCE_BINARY_SEARCHTREE_H_