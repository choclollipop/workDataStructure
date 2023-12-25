#include "binarySearchTree.h"
#include <stdlib.h>
#include <string.h>

/* 状态码 */
enum STATUS_CODE
{
    ON_SUCCESS,
    NULL_PTR,
    MALLOC_ERROR,
    INVALID_ACCESS,
    NOT_FIND,
};

/* 二叉搜索树的初始化 */
int binarySearchTreeInit(binarySearchTree ** pBstree)
{
    /* 先给二叉树分配空间 */
    binarySearchTree * bstree = (binarySearchTree *)malloc(sizeof(binarySearchTree) * 1);
    if(!bstree)
    {
        return MALLOC_ERROR;
    }
    /* 给分配的空间初始化 */
    memset(bstree, 0, sizeof(binarySearchTree) * 1);

    /* 给树初始化值 */
    bstree->root = NULL;
    bstree->size = 0;

    /* 给根节点分配空间 */
    bstree->root = (BSTreeNode *)malloc(sizeof(BSTreeNode) * 1);
    if(!bstree->root)
    {
        return MALLOC_ERROR;
    }
    memset(bstree->root, 0, sizeof(BSTreeNode) * 1);

    /* 清除根节点数据 */
    bstree->root->data = 0;
    bstree->root->left = NULL;
    bstree->root->right = NULL;
    bstree->root->parent = NULL;

    *pBstree = bstree;

    return ON_SUCCESS;
}

/* 二叉搜索树的插入 */
int binarySearchTreeInsert(binarySearchTree * pBstree, ELELMENTTYPE val)
{
    if(!pBstree)
    {
        return NULL_PTR;
    }

    if(pBstree->size == 0)
    {
        /* 更新树的结点 */
        pBstree->size++;
        pBstree->root->data = val;
        
        return ON_SUCCESS;
    }
    
    /* 从根节点开始遍历 */
    BSTreeNode * travelNode = pBstree->root;

    /* 指向父节点的父指针 */
    BSTreeNode * parentNode = pBstree->root;

    /* 标记传入的参数 */
    int cmp = 0;

    while(travelNode != NULL)
    {
        /* 标记父节点 */
        parentNode = travelNode;

        cmp = val - travelNode->data;

        /* 比较插入的结点与各个结点的大小关系 */
        /* tmp小于0，则放在左子树；大于0，则放在右子树 */
        if(cmp < 0)
        {
            travelNode = travelNode->left;
        }
        else if(cmp > 0)
        {
            travelNode = travelNode->right;
        }
        else
        {
            /* 如果插入结点与遍历到的结点相同，直接返回 */
            return ON_SUCCESS;
        }
    }

    if(cmp < 0)
    {
        parentNode->left = (val的结点);
    }
    else
    {
        parentNode->right = (val的结点);
    }

    return 0;
}