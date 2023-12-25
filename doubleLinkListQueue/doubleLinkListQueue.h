#ifndef __DOUBLELINKLIST_QUEUE_H_
#define __DOUBLELINKLIST_QUEUE_H_

#include "common.h"

typedef DoubleLinkList doubleLinkListQueue;

/* 队列初始化 */
int doubleLinkListQueueInit(doubleLinkListQueue * pQueue);

/* 入队 */
int doubleLinkListQueuePush(doubleLinkListQueue * pQueue, ELEMENTTYPE val);

/* 出队 */
int doubleLinkListQueuePop();

/* 查看队头元素 */
int doubleLinkListQueueTop();

/* 查看对位元素 */
int doubleLinkListQueueRear();

/* 获取队列大小 */
int doubleLinkListQueueGetSize();

/* 队列是否为空 */
int doubleLinkListQueueIsEmpty();

/* 队列销毁 */
int doubleLinkListQueueDestroy();

#endif //__DOUBLELINKLIST_QUEUE_H_