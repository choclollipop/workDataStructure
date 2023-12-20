#ifndef __LINK_LIST_H_
#define __LINK_LIST_H_

#define ELEMENTTYPE int

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
    int len;
}LinkList;

/* 链表初始化 */
int LinkListInit();

/* 链表头插 */
int LinkListHeadInsert();

/* 链表尾插 */
int LinkListTailInsert();

/* 链表指定位置插入 */
int LinkListAppointPosInsert();

/* 链表头删 */
int LinkListHeadDel();

/* 链表尾删 */
int LinkListTailDel();

/* 链表指定位置删除 */
int LinkListAppointPosDel();

/* 链表删除指定元素 */
int LinkListDelAppointVal();

/* 获取链表长度 */
int LinkListGetLen();

/* 销毁链表 */
int LinkListDestory();

#endif //__LINK_LIST_H_