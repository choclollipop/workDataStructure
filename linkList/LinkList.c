#include "LinkList.h"
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

    /* 初始化链表的长度和尾指针 */
    list->len = 0;
    list->tail = list->head;

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

    /* 改变尾指针的情况 */
    int flag = 0;
    if(pos == pList->len)
    {
        travel = pList->tail;
        flag = 1;
    }
    else
    {
        while(pos)
        {
            travel = travel->next;
            pos--;
        }
    }
    /* 执行插入操作 */
    newNode = travel->next;
    travel->next = newNode;
    if(flag)
    {
        pList->tail = newNode;
    }

    /* 更新链表数据 */
    pList->len++;

    return ON_SUCCESS;
}

/* 链表头删 */
int LinkListHeadDel(LinkList * pList)
{
    return LinkListAppointPosDel(pList, 1);
}

/* 链表尾删 */
int LinkListTailDel(LinkList * pList)
{
    return LinkListAppointPosDel(pList, pList->len);
}

/* 链表指定位置删除 */
int LinkListAppointPosDel(LinkList * pList, int pos)
{
    if(!pList)
    {
        return NULL_PTR;
    }

    if(pos <= 0 || pos > pList->len)
    {
        return INVALID_ACCESS;
    }

    /* 从头结点开始遍历 */
    LinkNode * travel = pList->head;

    while(--pos)
    {
        travel = travel->next;
    }
    LinkNode * needDelNode = travel->next;
    travel->next = needDelNode->next;

    /* 释放内存 */
    if(needDelNode)
    {
        free(needDelNode);
        needDelNode = NULL;
    }
    

    /* 更新链表信息 */
    pList->len--;
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
int LinkListForeach(LinkList * pList)
{
    if(!pList)
    {
        return NULL_PTR;
    }

    /* 从头结点开始遍历 */
    LinkNode * travel = pList->head;

    /* 结束条件：下一个结点的指针域为空，即来到了表尾结点 */
    while(travel->next != NULL)
    {
        travel = travel->next;
        printf("trave->data:%d\n", travel->data);
    }

    return ON_SUCCESS;
}

