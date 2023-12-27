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
/* 判断二叉搜索树度为0 */
static int binarySearchTreeNodeIsLeaf(BSTreeNode *node);
/* 判断二叉搜索树度为1 */
static int binarySearchTreeHasOnechildren(BSTreeNode *node);
/* 判断二叉搜索树度为2 */
static int binarySearchTreeHasTwochildrens(BSTreeNode *node);
/* 前序遍历 */
static int preOrderTravel(binarySearchTree * pBstree , BSTreeNode * node);
/* 中序遍历 */
static int inOrderTravel(binarySearchTree * pBstree , BSTreeNode * node);
/* 后续遍历 */
static int postOrderTravel(binarySearchTree * pBstree , BSTreeNode * node);
/* 获取当前结点的前驱结点 */
static BSTreeNode * bstreeNodePreDecessor(BSTreeNode * node);
/* 获取当前结点的后继节点 */
static BSTreeNode * bstreeNodeSuccessor(BSTreeNode * node);
/* 删除结点 */
static int binarySearchTreeDeleteNode(binarySearchTree * pBstree, BSTreeNode * node);



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

/* 判断二叉搜索树度为2 */
static int binarySearchTreeHasTwochildrens(BSTreeNode *node)
{
    return node->left != NULL && node->right != NULL;
}

/* 判断二叉搜索树度为1 */
static int binarySearchTreeHasOnechildren(BSTreeNode *node)
{
    return (node->left != NULL && node->right == NULL) || (node->left == NULL && node->right != NULL);
}

/* 判断二叉搜索树度为0 */
static int binarySearchTreeNodeIsLeaf(BSTreeNode *node)
{
    return node->left == NULL && node->right == NULL;
}

/* 获取当前结点的中序前驱结点 */
static BSTreeNode * bstreeNodePreDecessor(BSTreeNode * node)
{
    BSTreeNode * travelNode = node;
    /* 指定结点有左子树 */
    if(travelNode->left)
    {
        travelNode = travelNode->left;
        while(travelNode->right)
        {
            travelNode = travelNode->right;
        }
        return NULL;
    }

    /* 指定结点没有左子树 */
    while(travelNode->parent != NULL && travelNode == travelNode->parent->left)
    {
        travelNode = travelNode->parent;
    }
    return travelNode->parent;

}

/* 获取当前结点的中序后继节点 */
static BSTreeNode * bstreeNodeSuccessor(BSTreeNode * node)
{
    BSTreeNode * travelNode = node;
    /* 指定结点右子树不为空 */
    if(travelNode->right)
    {
        travelNode = travelNode->right;
        while(travelNode->left)
        {
            travelNode = travelNode->left;
        }
        return travelNode;
    }

    /* 指定结点没有右子树 */
    while(travelNode->parent != NULL && travelNode == travelNode->parent->right)
    {
        travelNode = travelNode->parent;
    }
    return travelNode->parent;

}


/* 二叉搜索树的初始化 */
int binarySearchTreeInit(binarySearchTree ** pBstree, int (*compareFunc)(ELELMENTTYPE val1, ELELMENTTYPE val2), int (*printFunc)(ELELMENTTYPE val))
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
    bstree->printFunc = printFunc;

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

    /* 从根结点开始遍历 */
    BSTreeNode * travelNode = pBstree->root;
    /* 根节点为空插入根节点中 */
    if(pBstree->size == 0)
    {
        travelNode->data = val;
        pBstree->size++;

        return ON_SUCCESS;
    }

    /* 比较插入的值与结点大小 */
    int cmp = 0;

    BSTreeNode * parentNode = NULL;
    while(travelNode != NULL)
    {
        parentNode = travelNode;

        cmp = pBstree->compareFunc(val, travelNode->data);

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
            /* 相同时不做插入操作直接返回 */
            return ON_SUCCESS;
        }
    }

    BSTreeNode * newNode = createNewBSTreeNode(val, parentNode);
    if(!newNode)
    {
        return MALLOC_ERROR;
    }

    if(cmp < 0)
    {
        parentNode->left = newNode;
    }
    else
    {
        parentNode->right = newNode;
    }

    /* 更新树的结点个数 */
    pBstree->size++;

    return ON_SUCCESS;
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

/* 前序遍历 */
static int preOrderTravel(binarySearchTree * pBstree , BSTreeNode * node)
{
    while(node == NULL)
    {
        return 0;
    }
    pBstree->printFunc(node->data);
    preOrderTravel(pBstree, node->left);
    preOrderTravel(pBstree, node->right);

    return 0;
}

/* 中序遍历 */
static int inOrderTravel(binarySearchTree * pBstree , BSTreeNode * node)
{
    while(node == NULL)
    {
        return 0;
    }
    inOrderTravel(pBstree, node->left);
    pBstree->printFunc(node->data);
    inOrderTravel(pBstree, node->right);
}

/* 后序遍历 */
static int postOrderTravel(binarySearchTree * pBstree , BSTreeNode * node)
{
    while(node == NULL)
    {
        return 0;
    }
    postOrderTravel(pBstree, node->left);
    postOrderTravel(pBstree, node->right);
    pBstree->printFunc(node->data);
}

/* 二叉搜索树的前序遍历 */
int binarySearchTreePreOrderTravel(binarySearchTree * pBstree)
{
    preOrderTravel(pBstree, pBstree->root);
    return 0;
}

/* 二叉搜索树的中序遍历 */
int binarySearchTreeInOrderTravel(binarySearchTree * pBstree)
{
    inOrderTravel(pBstree, pBstree->root);

    return 0;
}

/* 二叉搜索树的后序遍历*/
int binarySearchTreePostOrderTravel(binarySearchTree * pBstree)
{
    postOrderTravel(pBstree, pBstree->root);

    return 0;
}

/* 二叉搜索树的层序遍历并获取最后对应结点 */
int binarySearchTreeLevelOrderTravel(binarySearchTree * pBstree, BSTreeNode ** node)
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
        doubleLinkListQueueTop(queue, (void **)&val);
        pBstree->printFunc(val->data);

        /* 出队，队头元素变化，取出的是结点 */
        doubleLinkListQueuePop(queue);

        /* 左右子树入队 */
        if(val->left)
        {
            doubleLinkListQueuePush(queue, val->left);
        }
        if(val->right)
        {
            doubleLinkListQueuePush(queue, val->right);
        }
    }

    *node = val;

    /* 释放队列 */
    doubleLinkListQueueDestroy(queue);

    return ON_SUCCESS;
}

/* 获取二叉搜索树的结点个数 */
int binarySearchTreeGetNodeSize(binarySearchTree * pBstree, int * pSize)
{
    if(!pBstree)
    {
        return NULL_PTR;
    }

    if(pSize)
    {
        *pSize = pBstree->size;
    }

    return pBstree->size;
}

/* 获取二叉搜索树的高度 */
int binarySearchTreeGetHeight(binarySearchTree * pBstree, int * pHeight)
{
    if(!pBstree)
    {
        return NULL_PTR;
    }
    /* 指向最后的结点位置 */
    /* 赋空值，避免野指针 */
    doubleLinkListQueue * queue = NULL;

    doubleLinkListQueueInit(&queue);

    /* 根节点入队 */
    doubleLinkListQueuePush(queue, pBstree->root);
    
    BSTreeNode * val = NULL;
    int levelSize = 1;
    int height = 0;
    while(!doubleLinkListQueueIsEmpty(queue))
    {
        /* 读取对头元素 */
        doubleLinkListQueueTop(queue, (void **)&val);

        /* 出队，队头元素变化，取出的是结点 */
        doubleLinkListQueuePop(queue);

        levelSize--;

        /* 左右子树入队 */
        if(val->left)
        {
            doubleLinkListQueuePush(queue, val->left);
        }
        if(val->right)
        {
            doubleLinkListQueuePush(queue, val->right);
        }

        if(levelSize == 0)
        {
            height++;
            doubleLinkListQueueGetSize(queue, &levelSize);
        }
    }

    *pHeight = height;

    /* 释放队列 */
    doubleLinkListQueueDestroy(queue);

    return 0;
}

/* 删除结点 */
static int binarySearchTreeDeleteNode(binarySearchTree * pBstree, BSTreeNode * node)
{
    int ret = 0;
    if(!node)
    {
        return 0;
    }

    BSTreeNode * delNode = node;
    BSTreeNode * preNode = NULL;
    BSTreeNode * child = NULL;

    /* 度为2 */
    if(binarySearchTreeHasTwochildrens(delNode))
    {
        preNode = bstreeNodePreDecessor(node);
        delNode->data = preNode->data;
        delNode = preNode;
    }
#if 0
    /* 度为1 */
    if(binarySearchTreeHasOnechildren(delNode))
    {
        if(delNode->left)
        {
            child = delNode->left;
            child->parent = delNode->parent;
        }
        else if (delNode->right)
        {
            child = delNode->right;
            child->parent = delNode->parent;
        }
        if(delNode == delNode->parent->left)
        {
            delNode->parent->left = child;
        }
        else if(delNode == delNode->parent->right)
        {
            delNode->parent->right = child;
        }

        free(delNode);
        delNode = NULL;

        return ON_SUCCESS;
    }
    /* 度为0 */
    else if(binarySearchTreeNodeIsLeaf(delNode))
    {
        delNode->parent = NULL;
        free(delNode);
        delNode = NULL;

        return ON_SUCCESS;
    }
#endif

    child = delNode->left != NULL ? delNode->left : delNode->right;

    if(child)
    {
        /* 度为1 */
        child->parent = delNode->parent;
        BSTreeNode * parent = delNode->parent;
        if(parent)
        {
            if(delNode == parent->left)
            {
                delNode->parent->left = child;
            }
            else
            {
                delNode->parent->right = child;
            }
        }
        else
        {
            /* 根节点 */
            pBstree->root = child;
        }
    }

    /* 释放结点 */
    if(delNode)
    {
        free(delNode);
        delNode = NULL;
    }
    
    /* 更新树的大小 */
    pBstree->size--;

    return ON_SUCCESS;
}

/* 二叉搜索树删除指定的值 */
int binarySearchTreeDelete(binarySearchTree * pBstree, ELELMENTTYPE val)
{
    if(!pBstree)
    {
        return NULL_PTR;
    }

    return binarySearchTreeDeleteNode(pBstree, baseAppointValGetBSTreeNode(pBstree, val));

}

/* 二叉搜索树的销毁 */
int binarySearchTreeDestroy(binarySearchTree * pBstree)
{
    if(!pBstree)
    {
        return NULL_PTR;
    }

    doubleLinkListQueue * queue = NULL;
    doubleLinkListQueueInit(&queue);
    doubleLinkListQueuePush(queue, pBstree->root);

    BSTreeNode * val = NULL;
    while(!doubleLinkListQueueIsEmpty(queue))
    {
        doubleLinkListQueueTop(queue, (void **)&val);
        doubleLinkListQueuePop(queue);

        if(val->left)
        {
            doubleLinkListQueuePush(queue, val->left);
        }
        else if (val->right)
        {
            doubleLinkListQueuePush(queue, val->right);
        }

        if(val)
        {
            free(val);
            val = NULL;
        }
    }

    /* 销毁队列 */
    doubleLinkListQueueDestroy(queue);

    /* 释放树 */
    if(pBstree)
    {
        free(pBstree);
        pBstree->root = NULL;
    }

    return ON_SUCCESS;
}


/* 判断搜索二叉树是否是完全二叉树 */
int binarySearchTreeIsCompelete(binarySearchTree * pBstree)
{
    
    return 0;
}

