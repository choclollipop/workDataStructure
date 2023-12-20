#include "LinkList.h"
#include <stdlib.h>
#include <string.h>

/* 状态码 */
enum STATUS_CODE
{
    ON_SUCCESS,
    NULL_PTR,
    MALLOC_ERROR,
    INVALID_ACCESS,
};

/* 链表初始化 */
int LinkListInit(LinkList ** pList)
{
    LinkList * list = (LinkList *)malloc(sizeof(LinkList) * 1);
    if(!list)
    {
        return MALLOC_ERROR;
    }
    /* 清空脏数据 */
    memset(list, 0, sizeof(LinkList) * 1);

    list->head = (LinkNode *)malloc(sizeof(LinkNode) * 1);
    if(!list->head)
    {
        return MALLOC_ERROR;
    }
    memset(list->head, 0, sizeof(LinkNode) * 1);

    /* 初始化链表的长度 */
    list->len = 0;

    /* 初始化头节点 */
    list->head->data = 0;
    list->head->next = NULL;

    *pList = list;

    return ON_SUCCESS;
}

/* 链表头插 */
int LinkListHeadInsert(LinkList * pList, ELEMENTTYPE val)
{
    return LinkListAppointPosInsert(pList, 0, val);
}

/* 链表尾插 */
int LinkListTailInsert(LinkList * pList, ELEMENTTYPE val)
{
    return LinkListAppointPosInsert(pList, pList->len, val);
}

/* 链表指定位置插入 */
int LinkListAppointPosInsert(LinkList * pList,int pos, ELEMENTTYPE val)
{
    if(!pList)
    {
        return NULL_PTR;
    }

    if(pos < 0 || pos > pList->len)
    {
        return INVALID_ACCESS;
    }

    /* 创建新节点 */
    LinkNode * newNode = (LinkNode *)malloc(sizeof(LinkNode) * 1);
    if(!newNode)
    {
        return MALLOC_ERROR;
    }
    memset(newNode, 0, sizeof(LinkNode) * 1);
    newNode->data = 0;
    newNode->next = NULL;

    /* 赋值 */
    newNode->data = val;

    /* 从头结点开始遍历 */
    LinkNode * travel = pList->head;

    while(pos)
    {
        travel = travel->next;
        pos--;
    }

    /* 执行插入操作 */
    newNode = travel->next;
    travel->next = newNode;

    /* 更新链表数据 */
    pList->len++;

    return ON_SUCCESS;
}

/* 链表头删 */
int LinkListHeadDel(LinkList * pList)
{

}

/* 链表尾删 */
int LinkListTailDel(LinkList * pList)
{

}

/* 链表指定位置删除 */
int LinkListAppointPosDel(LinkList * pList, int pos)
{

}

/* 链表删除指定元素 */
int LinkListDelAppointVal(LinkList * pList, ELEMENTTYPE val)
{

}

/* 获取链表长度 */
int LinkListGetLen(LinkList * pList, int * pSize)
{
    if(!pList)
    {
        return NULL_PTR;
    }

    if(pSize)
    {
        *pSize = pList->len;
    }

    return ON_SUCCESS;
}

/* 销毁链表 */
int LinkListDestory(LinkList * pList)
{

}

/* 链表的遍历 */
int LinkListForeach()
{

}

