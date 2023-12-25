#ifndef __BINARY_SEARCHTREE_H_
#define __BINARY_SEARCHTREE_H_

#define ELELMENTTYPE int

typedef struct BSTreeNode
{
    ELELMENTTYPE data;
    struct BSTreeNode * left;   /* 左子树 */
    struct BSTreeNode * right;  /* 右子树 */
    struct BSTreeNode * parent; /* 父结点 */

}BSTreeNode;

typedef struct binarySearchTree
{
    /* 根节点 */
    BSTreeNode * root;
    /* 树的结点个数 */
    int size;

}binarySearchTree;

/* 二叉搜索树的初始化 */
int binarySearchTreeInit(binarySearchTree ** pBstree);

/* 二叉搜索树的插入 */
int binarySearchTreeInsert(binarySearchTree * pBstree, ELELMENTTYPE val);

#endif //__BINARY_SEARCHTREE_H_