#ifndef __DOUBLELINKLIST_QUEUE_H_
#define __DOUBLELINKLIST_QUEUE_H_

#include "common.h"

typedef DoubleLinkList doubleLinkListQueue;

/* 队列初始化 */
int doubleLinkListQueueInit(doubleLinkListQueue ** pQueue);

/* 入队 */
int doubleLinkListQueuePush(doubleLinkListQueue * pQueue, ELEMENTTYPE val);

/* 出队 */
int doubleLinkListQueuePop(doubleLinkListQueue * pQueue);

/* 查看队头元素 */
int doubleLinkListQueueTop(doubleLinkListQueue * pQueue, ELEMENTTYPE * pVal);

/* 查看队尾元素 */
int doubleLinkListQueueRear(doubleLinkListQueue * pQueue, ELEMENTTYPE * pVal);

/* 获取队列大小 */
int doubleLinkListQueueGetSize(doubleLinkListQueue * pQueue, int *pSize);

/* 队列是否为空 */
int doubleLinkListQueueIsEmpty(doubleLinkListQueue * pQueue);

/* 队列销毁 */
int doubleLinkListQueueDestroy(doubleLinkListQueue * pQueue);

#endif //__DOUBLELINKLIST_QUEUE_H_