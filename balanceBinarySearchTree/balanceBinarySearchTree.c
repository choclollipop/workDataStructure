#include "balanceBinarySearchTree.h"
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
static AVLTreeNode * createNewBSTreeNode(ELELMENTTYPE val, AVLTreeNode * parent);
/* 根据指定的值获取二叉搜索树的结点 */
static AVLTreeNode * baseAppointValGetBSTreeNode(BalanceBinarySearchTree * pBstree, ELELMENTTYPE val);
/* 判断二叉搜索树度为0 */
static int balanceBinarySearchTreeNodeIsLeaf(AVLTreeNode *node);
/* 判断二叉搜索树度为1 */
static int balanceBinarySearchTreeHasOnechildren(AVLTreeNode *node);
/* 判断二叉搜索树度为2 */
static int balanceBinarySearchTreeHasTwochildrens(AVLTreeNode *node);
/* 前序遍历 */
static int preOrderTravel(BalanceBinarySearchTree * pBstree , AVLTreeNode * node);
/* 中序遍历 */
static int inOrderTravel(BalanceBinarySearchTree * pBstree , AVLTreeNode * node);
/* 后续遍历 */
static int postOrderTravel(BalanceBinarySearchTree * pBstree , AVLTreeNode * node);
/* 获取当前结点的前驱结点 */
static AVLTreeNode * bstreeNodePreDecessor(AVLTreeNode * node);
/* 获取当前结点的后继节点 */
static AVLTreeNode * bstreeNodeSuccessor(AVLTreeNode * node);
/* 删除结点 */
static int balanceBinarySearchTreeDeleteNode(BalanceBinarySearchTree * pBstree, AVLTreeNode * node);
/* 添加结点后的操作 */
static int insertNodeAfter(BalanceBinarySearchTree * pBstree, AVLTreeNode * node);
/* 删除结点之后的操作 */
static int removeNodeAfter(BalanceBinarySearchTree * pBstree, AVLTreeNode * node);
/* 计算结点的平衡因子 */
static int AVLTreeNodeBalanceFactor(AVLTreeNode * node);
/* 判断结点是否平衡 */
static int AVLTreeNodeIsBalanced(AVLTreeNode * node);
/* 更新结点高度 */
static int AVLTreeNodeUpdateHeight(AVLTreeNode * node);
/* 计算左右子树的最大值 */
static int AVLTreeMax(AVLTreeNode * node);
/* AVL树调整结点的平衡 */
static int AVLTreeNodeAdjustBalance(BalanceBinarySearchTree * pBstree, AVLTreeNode * node);
/* 判断调整结点左右子树谁更高并返回更高的结点 */
static AVLTreeNode * AVLTreeNodeGetChildTaller(AVLTreeNode * node);
/* 当前结点是父节点的左子树 */
static int AVLTreeCurrentNodeIsLeft(AVLTreeNode * node);
/* 当前结点是父节点的是右子树 */
static int AVLTreeCurrentNodeIsRight(AVLTreeNode * node);
/* 右旋 */
static int AVLTreeCurrentNodePotateRight(BalanceBinarySearchTree * pBstree, AVLTreeNode * node);
/* 左旋 */
static int AVLTreeCurrentNodePotateLeft(BalanceBinarySearchTree * pBstree, AVLTreeNode * node);
/* 左右旋的公共代码 */
static int AVLTreeNodePotate(BalanceBinarySearchTree * pBstree, AVLTreeNode * node, AVLTreeNode * parent, AVLTreeNode * child);




/* 创建结点 */
static AVLTreeNode * createNewAVLTreeNode(ELELMENTTYPE val, AVLTreeNode * parent)
{
    /* 给新节点分配空间 */
    AVLTreeNode * newBstNode = (AVLTreeNode *)malloc(sizeof(AVLTreeNode) * 1);
    if(!newBstNode)
    {
        return NULL;
    }
    memset(newBstNode, 0, sizeof(AVLTreeNode) * 1);

    /* 清除新节点数据 */
    newBstNode->data = 0;
    newBstNode->height = 1;
    newBstNode->left = NULL;
    newBstNode->right = NULL;
    newBstNode->parent = NULL;

    newBstNode->data = val;
    newBstNode->parent = parent;

    return newBstNode;
}

/* 判断二叉搜索树度为2 */
static int balanceBinarySearchTreeHasTwochildrens(AVLTreeNode *node)
{
    return node->left != NULL && node->right != NULL;
}

/* 判断二叉搜索树度为1 */
static int balanceBinarySearchTreeHasOnechildren(AVLTreeNode *node)
{
    return (node->left != NULL && node->right == NULL) || (node->left == NULL && node->right != NULL);
}

/* 判断二叉搜索树度为0 */
static int balanceBinarySearchTreeNodeIsLeaf(AVLTreeNode *node)
{
    return node->left == NULL && node->right == NULL;
}

/* 获取当前结点的中序前驱结点 */
static AVLTreeNode * bstreeNodePreDecessor(AVLTreeNode * node)
{
    AVLTreeNode * travelNode = node;
    /* 指定结点有左子树 */
    if(travelNode->left)
    {
        travelNode = travelNode->left;
        while(travelNode->right)
        {
            travelNode = travelNode->right;
        }
        return travelNode;
    }

    /* 指定结点没有左子树 */
    while(travelNode->parent != NULL && travelNode == travelNode->parent->left)
    {
        travelNode = travelNode->parent;
    }
    return travelNode->parent;

}

/* 获取当前结点的中序后继节点 */
static AVLTreeNode * bstreeNodeSuccessor(AVLTreeNode * node)
{
    AVLTreeNode * travelNode = node;
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
int balanceBinarySearchTreeInit(BalanceBinarySearchTree ** pBstree, int (*compareFunc)(ELELMENTTYPE val1, ELELMENTTYPE val2), int (*printFunc)(ELELMENTTYPE val))
{
    /* 先给二叉树分配空间 */
    BalanceBinarySearchTree * bstree = (BalanceBinarySearchTree *)malloc(sizeof(BalanceBinarySearchTree) * 1);
    if(!bstree)
    {
        return MALLOC_ERROR;
    }
    /* 给分配的空间初始化 */
    memset(bstree, 0, sizeof(BalanceBinarySearchTree) * 1);

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

/* 当前结点是父节点的左子树还是右子树 */
static int AVLTreeCurrentNodeIsLeft(AVLTreeNode * node)
{
    return (node->parent != NULL) && node == node->parent->left;
}

/* 当前结点是父节点的是右子树 */
static int AVLTreeCurrentNodeIsRight(AVLTreeNode * node)
{
    return (node->parent != NULL) && node == node->parent->right;
}

/* 判断调整结点左右子树谁更高并返回更高的结点 */
static AVLTreeNode * AVLTreeNodeGetChildTaller(AVLTreeNode * node)
{
    /* 左子树高度 */
    int leftHeight = node->left == NULL ? 0 : node->left->height;

    /* 右子树高度 */
    int rightHeight = node->right == NULL ? 0 : node->right->height;

    if(leftHeight > rightHeight)
    {
        return node->left;
    }
    else if(leftHeight < rightHeight)
    {
        return node->right;
    }
    else
    {
        if(AVLTreeCurrentNodeIsLeft(node))
        {
            return node->left;
        }
        else
        {
            return node->right;
        }
    }
}

/* 左右旋的公共代码 */
static int AVLTreeNodePotate(BalanceBinarySearchTree * pBstree, AVLTreeNode * node, AVLTreeNode * parent, AVLTreeNode * child)
{
    parent->parent = node->parent;

    /* 开始移动父指针 */
    if(AVLTreeCurrentNodeIsLeft(node))
    {
        node->parent->left = parent;
    }
    else if(AVLTreeCurrentNodeIsRight(node))
    {
        node->parent->right = parent;
    }
    else
    {
        /* node是根节点 */
        pBstree->root = parent;
    }
    node->parent = parent;
    if(child)
    {
        child->parent = node;
    }

    /* 更新高度:先更新旋转后较低的结点 */
    AVLTreeNodeUpdateHeight(node);
    AVLTreeNodeUpdateHeight(parent);
    
    return ON_SUCCESS;
}

/* 右旋 */
static int AVLTreeCurrentNodePotateRight(BalanceBinarySearchTree * pBstree, AVLTreeNode * node)
{
    AVLTreeNode * parent = node->left;
    AVLTreeNode * child = parent->right;

    node->left = child;
    parent->right = node;
    
    AVLTreeNodePotate(pBstree, node, parent, child);

    return ON_SUCCESS;
}

/* 左旋 */
static int AVLTreeCurrentNodePotateLeft(BalanceBinarySearchTree * pBstree, AVLTreeNode * node)
{
    AVLTreeNode * parent = node->right;
    AVLTreeNode * child = parent->left;

    node->right = child;
    parent->left = node;
    
    AVLTreeNodePotate(pBstree, node, parent, child);

    return ON_SUCCESS;
}

/* AVL树调整结点的平衡 */
static int AVLTreeNodeAdjustBalance(BalanceBinarySearchTree * pBstree, AVLTreeNode * node)
{
    /* LL型、LR、RL、RR */
    AVLTreeNode * parent = AVLTreeNodeGetChildTaller(node);
    AVLTreeNode * child = AVLTreeNodeGetChildTaller(parent);

    if(AVLTreeCurrentNodeIsLeft(parent))
    {
        if(AVLTreeCurrentNodeIsLeft(child))
        {
            /* LL - 右旋 */
            AVLTreeCurrentNodePotateRight(pBstree, node);
        }
        else
        {
            /* LR */
            AVLTreeCurrentNodePotateLeft(pBstree, parent);
            AVLTreeCurrentNodePotateRight(pBstree, node);
        }
    }
    else
    {
        if(AVLTreeCurrentNodeIsLeft(child))
        {
            /* RL */
            AVLTreeCurrentNodePotateRight(pBstree, parent);
            AVLTreeCurrentNodePotateLeft(pBstree, node);
        }
        else
        {
            /* RR - 左旋 */
            AVLTreeCurrentNodePotateLeft(parent, node);
        }
    }

    return ON_SUCCESS;
}

/* 添加结点后的操作 */
static int insertNodeAfter(BalanceBinarySearchTree * pBstree, AVLTreeNode * node)
{
    int ret = 0;

    /* 从父结点开始调整 */
    while(node = node->parent)
    {
        if(AVLTreeNodeIsBalanced(node))
        {
            /* 更新结点高度 */
            AVLTreeNodeUpdateHeight(node);
        }
        else
        {
            /* 不平衡开始旋转调整 */
            AVLTreeAdjustBalance(pBstree, node);

            break;
        }
    }

    return 0;
}

/* 计算结点的平衡因子 */
static int AVLTreeNodeBalanceFactor(AVLTreeNode * node)
{
    /* 左子树高度 */
    int leftHeight = node->left == NULL ? 0 : node->left->height;

    /* 右子树高度 */
    int rightHeight = node->right == NULL ? 0 : node->right->height;

    /* 结点的平衡因子 */
    return leftHeight - rightHeight;
}

/* 判断结点是否平衡 */
static int AVLTreeNodeIsBalanced(AVLTreeNode * node)
{
    return abs(AVLTreeNodeBalanceFactor(node)) <= 1;
}

/* 判断左右子树的最大值 */
static int AVLTreeMax(AVLTreeNode * node)
{
    /* 左子树高度 */
    int leftHeight = node->left == NULL ? 0 : node->left->height;

    /* 右子树高度 */
    int rightHeight = node->right == NULL ? 0 : node->right->height;

    return leftHeight - rightHeight >= 0 ? leftHeight : rightHeight;
}

/* 更新结点高度 */
static int AVLTreeNodeUpdateHeight(AVLTreeNode * node)
{
    int height = AVLTreeMax(node);

    node->height = height + 1;

    return ON_SUCCESS;
}

/* AVL树的插入 */
int balanceBinarySearchTreeInsert(BalanceBinarySearchTree * pBstree, ELELMENTTYPE val)
{
    if(!pBstree)
    {
        return NULL_PTR;
    }

    /* 从根结点开始遍历 */
    AVLTreeNode * travelNode = pBstree->root;
    /* 根节点为空插入根节点中 */
    if(pBstree->size == 0)
    {
        travelNode->data = val;
        pBstree->size++;

        insertNodeAfter(pBstree->root, pBstree->root);

        return ON_SUCCESS;
    }

    /* 比较插入的值与结点大小 */
    int cmp = 0;

    AVLTreeNode * parentNode = NULL;
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

    AVLTreeNode * newNode = createNewBSTreeNode(val, parentNode);
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

    insertNodeAfter(pBstree, newNode);

    /* 更新树的结点个数 */
    pBstree->size++;

    return ON_SUCCESS;
}

/* 二叉搜索树根据指定的值获取结点*/
static AVLTreeNode * baseAppointValGetBSTreeNode(BalanceBinarySearchTree * pBstree, ELELMENTTYPE val)
{
    AVLTreeNode * travelNode = pBstree->root;

    int cmp = 0;
    while(travelNode)
    {
        cmp = pBstree->compareFunc(val, travelNode->data);
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
int balanceBinarySearchTreeIsContainAppointVal(BalanceBinarySearchTree * pBstree, ELELMENTTYPE val)
{
    if(!pBstree)
    {
        return NULL_PTR;
    }
    return baseAppointValGetBSTreeNode(pBstree, val) == NULL ? 0 : 1;
}

/* 前序遍历 */
static int preOrderTravel(BalanceBinarySearchTree * pBstree , AVLTreeNode * node)
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
static int inOrderTravel(BalanceBinarySearchTree * pBstree , AVLTreeNode * node)
{
    if(node == NULL)
    {
        return 0;
    }
    inOrderTravel(pBstree, node->left);
    pBstree->printFunc(node->data);
    inOrderTravel(pBstree, node->right);
}

/* 后序遍历 */
static int postOrderTravel(BalanceBinarySearchTree * pBstree , AVLTreeNode * node)
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
int balanceBinarySearchTreePreOrderTravel(BalanceBinarySearchTree * pBstree)
{
    preOrderTravel(pBstree, pBstree->root);
    return 0;
}

/* 二叉搜索树的中序遍历 */
int balanceBinarySearchTreeInOrderTravel(BalanceBinarySearchTree * pBstree)
{
    inOrderTravel(pBstree, pBstree->root);

    return 0;
}

/* 二叉搜索树的后序遍历*/
int balanceBinarySearchTreePostOrderTravel(BalanceBinarySearchTree * pBstree)
{
    postOrderTravel(pBstree, pBstree->root);

    return 0;
}

/* 二叉搜索树的层序遍历 */
int balanceBinarySearchTreeLevelOrderTravel(BalanceBinarySearchTree * pBstree)
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
    
    AVLTreeNode * val = NULL;
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

    /* 释放队列 */
    doubleLinkListQueueDestroy(queue);

    return ON_SUCCESS;
}

/* 获取二叉搜索树的结点个数 */
int balanceBinarySearchTreeGetNodeSize(BalanceBinarySearchTree * pBstree, int * pSize)
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
int balanceBinarySearchTreeGetHeight(BalanceBinarySearchTree * pBstree, int * pHeight)
{
    if(!pBstree)
    {
        return NULL_PTR;
    }

    int height = 0;

    /* 空树 */
    if(pBstree->size == 0)
    {
        *pHeight = height;
        return height;
    }

    height = pBstree->root->height;
    *pHeight = height;

    return height;
}

/* 删除结点之后的操作 */
/* node是要删除的结点 */
static int removeNodeAfter(BalanceBinarySearchTree * pBstree, AVLTreeNode * node)
{
    /* 从父结点开始调整 */
    while(node = node->parent)
    {
        if(AVLTreeNodeIsBalanced(node))
        {
            /* 更新结点高度 */
            AVLTreeNodeUpdateHeight(node);
        }
        else
        {
            /* 不平衡开始旋转调整 */
            AVLTreeAdjustBalance(pBstree, node);
        }
    }

    return ON_SUCCESS;
}

/* 删除结点 */
static int balanceBinarySearchTreeDeleteNode(BalanceBinarySearchTree * pBstree, AVLTreeNode * node)
{
    int ret = 0;
    if(!node)
    {
        return 0;
    }

    AVLTreeNode * delNode = node;
    AVLTreeNode * preNode = NULL;
    AVLTreeNode * child = NULL;

    /* 度为2 */
    if(balanceBinarySearchTreeHasTwochildrens(delNode))
    {
        preNode = bstreeNodePreDecessor(node);
        delNode->data = preNode->data;
        delNode = preNode;
    }
#if 0
    /* 度为1 */
    if(balanceBinarySearchTreeHasOnechildren(delNode))
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
    else if(balanceBinarySearchTreeNodeIsLeaf(delNode))
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
        AVLTreeNode * parent = delNode->parent;
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
    else
    {
        if(delNode == delNode->parent->left)
        {
            delNode->parent->left = NULL;
        }
        else if (delNode == delNode->parent->right)
        {
            delNode->parent->right = NULL;
        }
    }

    removeNodeAfter(pBstree, delNode);

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
int balanceBinarySearchTreeDelete(BalanceBinarySearchTree * pBstree, ELELMENTTYPE val)
{
    if(!pBstree)
    {
        return NULL_PTR;
    }

    return balanceBinarySearchTreeDeleteNode(pBstree, baseAppointValGetBSTreeNode(pBstree, val));

}

/* 二叉搜索树的销毁 */
int balanceBinarySearchTreeDestroy(BalanceBinarySearchTree * pBstree)
{
    if(!pBstree)
    {
        return NULL_PTR;
    }

    doubleLinkListQueue * queue = NULL;
    doubleLinkListQueueInit(&queue);
    doubleLinkListQueuePush(queue, pBstree->root);

    AVLTreeNode * val = NULL;
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
int balanceBinarySearchTreeIsCompelete(BalanceBinarySearchTree * pBstree)
{
    
    return 0;
}

