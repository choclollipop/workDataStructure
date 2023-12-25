#include "binarySearchTree.h"
#include "doubleLinkListQueue.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* 状态码 */
enum STATUS_CODE
{
    ON_SUCCESS,
    NULL_PTR,
    MALLOC_ERROR,
    INVALID_ACCESS,
    NOT_FIND,
};

/* 静态函数前置声明 */
static BSTreeNode * createNewBSTreeNode(ELELMENTTYPE val, BSTreeNode * parent);
/* 根据指定的值获取二叉搜索树的结点 */
static BSTreeNode * baseAppointValGetBSTreeNode(binarySearchTree * pBstree, ELELMENTTYPE val);

/* 创建结点 */
static BSTreeNode * createNewBSTreeNode(ELELMENTTYPE val, BSTreeNode * parent)
{
    /* 给新节点分配空间 */
    BSTreeNode * newBstNode = (BSTreeNode *)malloc(sizeof(BSTreeNode) * 1);
    if(!newBstNode)
    {
        return NULL;
    }
    memset(newBstNode, 0, sizeof(BSTreeNode) * 1);

    /* 清除新节点数据 */
    newBstNode->data = 0;
    newBstNode->left = NULL;
    newBstNode->right = NULL;
    newBstNode->parent = NULL;

    newBstNode->data = val;
    newBstNode->parent = parent;

    return newBstNode;
}

/* 二叉搜索树的初始化 */
int binarySearchTreeInit(binarySearchTree ** pBstree, int (*compareFunc)(ELELMENTTYPE val1, ELELMENTTYPE val2))
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
    bstree->compareFunc = compareFunc;

    /* 给根节点分配空间 */
    bstree->root = createNewBSTreeNode(0, NULL);
    if(!bstree->root)
    {
        return MALLOC_ERROR;
    }

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

        cmp = pBstree->compareFunc(val, travelNode->data);

        /* 比较插入的结点与各个结点的大小关系 */
        /* cmp小于0，则放在左子树；大于0，则放在右子树 */
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

    /* 给新插入的结点分配空间 */
    BSTreeNode * newBstNode = createNewBSTreeNode(val, parentNode);

    if(cmp < 0)
    {
        parentNode->left = newBstNode;
    }
    else
    {
        parentNode->right = newBstNode;
    }

    /* 更新树的结点大小 */
    pBstree->size++;

    return 0;
}

/* 二叉搜索树根据指定的值获取结点*/
static BSTreeNode * baseAppointValGetBSTreeNode(binarySearchTree * pBstree, ELELMENTTYPE val)
{
    BSTreeNode * travelNode = pBstree->root;

    int cmp = 0;
    while(travelNode)
    {
        cmp = pBstree->compareFunc(travelNode->data, val);
        if(cmp < 0)
        {
            travelNode = travelNode->left;
        }
        else if (cmp > 0)
        {
            travelNode = travelNode->right;
        }
        else
        {
            /* 找到指定元素的结点 */
            return travelNode;
        }
    }

    return NULL;
}

/* 二叉搜索树是否包含指定元素 */
int binarySearchTreeIsContainAppointVal(binarySearchTree * pBstree, ELELMENTTYPE val)
{
    return baseAppointValGetBSTreeNode(pBstree, val) == NULL ? 0 : 1;
}

/* 二叉搜索树的前序遍历 */
int binarySearchTreePreOrderTravel(binarySearchTree * pBstree)
{

    return 0;
}

/* 二叉搜索树的中序遍历 */
int binarySearchTreeInOrderTravel(binarySearchTree * pBstree)
{
    return 0;
}

/* 二叉搜索树的后序遍历*/
int binarySearchTreePostOrderTravel(binarySearchTree * pBstree)
{
    return 0;
}

/* 二叉搜索树的层序遍历 */
int binarySearchTreeLevelOrderTravel(binarySearchTree * pBstree)
{
    if(!pBstree)
    {
        return NULL_PTR;
    }

    /* 赋空值，避免野指针 */
    doubleLinkListQueue * queue = NULL;

    doubleLinkListQueueInit(&queue);

    /* 根节点入队 */
    doubleLinkListQueuePush(queue, pBstree->root);
    
    BSTreeNode * val = NULL;
    while(!doubleLinkListQueueIsEmpty(queue))
    {
        /* 读取对头元素 */
        doubleLinkListQueueTop(queue, (void *)&val);
        printf("data : %d\n", val->data);

        /* 出队，队头元素变化，取出的是结点 */
        doubleLinkListQueuePop(queue);

        /* 左右子树入队 */
        if(val->left)
        {
            doubleLinkListQueuePush(queue, val->left);
        }
        else if(val->right)
        {
            doubleLinkListQueuePush(queue, val->right);
        }
    }

    /* 释放队列 */
    doubleLinkListQueueDestroy(queue);

    return ON_SUCCESS;
}