#ifndef __LINK_LIST_H_
#define __LINK_LIST_H_

#define ELEMENTTYPE void *

/* 链表结点 */
typedef struct LinkNode
{
    ELEMENTTYPE data;
    struct LinkNode * next;
}LinkNode;

/* 链表 */
typedef struct LinkList
{
    LinkNode * head;
    LinkNode * tail;
    int len;
}LinkList;

/* 链表初始化 */
int LinkListInit(LinkList ** pList);

/* 链表头插 */
int LinkListHeadInsert(LinkList * pList, ELEMENTTYPE val);

/* 链表尾插 */
int LinkListTailInsert(LinkList * pList, ELEMENTTYPE val);

/* 链表指定位置插入 */
int LinkListAppointPosInsert(LinkList * pList,int pos, ELEMENTTYPE val);

/* 链表头删 */
int LinkListHeadDel(LinkList * pList);

/* 链表尾删 */
int LinkListTailDel(LinkList * pList);

/* 链表指定位置删除 */
int LinkListAppointPosDel(LinkList * pList, int pos);

/* 链表删除指定元素 */
int LinkListDelAppointVal(LinkList * pList, ELEMENTTYPE val);

/* 获取链表长度 */
int LinkListGetLen(LinkList * pList, int * pSize);

/* 销毁链表 */
int LinkListDestory(LinkList * pList);

/* 链表的遍历 */
int LinkListForeach(LinkList * pList, int (*printFunc)(ELEMENTTYPE));

#endif //__LINK_LIST_H_