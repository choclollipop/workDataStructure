#ifndef __DOUBLELINK_LIST_H_
#define __DOUBLELINK_LIST_H_

#include "common.h"

/* 链表初始化 */
int DoubleLinkListInit(DoubleLinkList ** pList);

/* 链表头插 */
int DoubleLinkListHeadInsert(DoubleLinkList * pList, ELEMENTTYPE val);

/* 链表尾插 */
int DoubleLinkListTailInsert(DoubleLinkList * pList, ELEMENTTYPE val);

/* 链表指定位置插入 */
int DoubleLinkListAppointPosInsert(DoubleLinkList * pList,int pos, ELEMENTTYPE val);

/* 链表头删 */
int DoubleLinkListHeadDel(DoubleLinkList * pList);

/* 链表尾删 */
int DoubleLinkListTailDel(DoubleLinkList * pList);

/* 链表指定位置删除 */
int DoubleLinkListAppointPosDel(DoubleLinkList * pList, int pos);

/* 链表删除指定元素 */
int DoubleLinkListDelAppointVal(DoubleLinkList * pList, ELEMENTTYPE val);

/* 获取链表长度 */
int DoubleLinkListGetLen(DoubleLinkList * pList, int * pSize);

/* 销毁链表 */
int DoubleLinkListDestory(DoubleLinkList * pList);

/* 链表的遍历 */
int DoubleLinkListForeach(DoubleLinkList * pList, int (*printFunc)(ELEMENTTYPE));

/* 链表的逆序打印 */
int DoubleLinkListReverseForeach(DoubleLinkList * pList, int (*printFunc)(ELEMENTTYPE));

/* 获取链表表头的值 */
int DoubleLinkListGetHeadVal(DoubleLinkList * pList, ELEMENTTYPE * pVal);

/* 获取链表表尾的值 */
int DoubleLinkListGetTailVal(DoubleLinkList * pList, ELEMENTTYPE * pVal);

/* 获取链表指定位置的值 */
int DoubleLinkListGetAppointPosVal(DoubleLinkList * pList, int pos, ELEMENTTYPE * pVal);

#endif //__DOUBLELINK_LIST_H_