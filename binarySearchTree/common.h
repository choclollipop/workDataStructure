#ifndef __COMMON_H_
#define __COMMON_H_

#define ELEMENTTYPE void *

/* 链表结点 */
typedef struct DoubleLinkNode
{
    ELEMENTTYPE data;
    struct DoubleLinkNode * prev;
    struct DoubleLinkNode * next;
}DoubleLinkNode;

/* 链表 */
typedef struct DoubleLinkList
{
    DoubleLinkNode * head;
    DoubleLinkNode * tail;
    int len;
}DoubleLinkList;

#endif //__COMMON_H_