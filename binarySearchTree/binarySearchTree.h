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
    /* 钩子函数/比较器 */
    int (*compareFunc)(ELELMENTTYPE val1, ELELMENTTYPE val2);
    /* 钩子函数/包装器（实现自定义打印） */
    int (*printFunc)(ELELMENTTYPE val);
}binarySearchTree;

/* 二叉搜索树的初始化 */
int binarySearchTreeInit(binarySearchTree ** pBstree, int (*compareFunc)(ELELMENTTYPE val1, ELELMENTTYPE val2), int (*printFunc)(ELELMENTTYPE val));

/* 二叉搜索树的插入 */
int binarySearchTreeInsert(binarySearchTree * pBstree, ELELMENTTYPE val);

/* 二叉搜索树是否包含指定元素 */
int binarySearchTreeIsContainAppointVal(binarySearchTree * pBstree, ELELMENTTYPE val);

/* 二叉搜索树的前序遍历 */
int binarySearchTreePreOrderTravel(binarySearchTree * pBstree);

/* 二叉搜索树的中序遍历 */
int binarySearchTreeInOrderTravel(binarySearchTree * pBstree);

/* 二叉搜索树的后序遍历*/
int binarySearchTreePostOrderTravel(binarySearchTree * pBstree);

/* 二叉搜索树的层序遍历 */
int binarySearchTreeLevelOrderTravel(binarySearchTree * pBstree, BSTreeNode ** node);

/* 获取二叉搜索树的高度 */
int binarySearchTreeGetHeight(binarySearchTree * pBstree, int * height);

/* 二叉搜索树删除指定的值 */
int binarySearchTreeDelete(binarySearchTree * pBstree, ELELMENTTYPE val);

#endif //__BINARY_SEARCHTREE_H_