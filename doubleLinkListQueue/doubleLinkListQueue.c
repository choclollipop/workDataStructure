#include "doubleLinkListQueue.h"
#include "doubleLinkList.h"

typedef DoubleLinkList doubleLinkListQueue;

/* 队列初始化 */
int doubleLinkListQueueInit(doubleLinkListQueue ** pQueue)
{
    return DoubleLinkListInit(pQueue);
}

/* 入队 */
int doubleLinkListQueuePush(doubleLinkListQueue * pQueue, ELEMENTTYPE val)
{
    /* 尾插 */
    return DoubleLinkListTailInsert(pQueue, val);
}

/* 出队 */
int doubleLinkListQueuePop(doubleLinkListQueue * pQueue)
{
    /* 头删 */
    return DoubleLinkListHeadDel(pQueue);
}

/* 查看队头元素 */
int doubleLinkListQueueTop(doubleLinkListQueue * pQueue, ELEMENTTYPE * pVal)
{
    return DoubleLinkListGetHeadVal(pQueue, pVal);
}

/* 查看队尾元素 */
int doubleLinkListQueueRear(doubleLinkListQueue * pQueue, ELEMENTTYPE * pVal)
{
    return DoubleLinkListGetTailVal(pQueue, pVal);
}

/* 获取队列大小 */
int doubleLinkListQueueGetSize(doubleLinkListQueue * pQueue, int *pSize)
{
    return DoubleLinkListGetLen(pQueue, pSize);
}

/* 队列是否为空 */
int doubleLinkListQueueIsEmpty(doubleLinkListQueue * pQueue)
{
    int size = 0;
    DoubleLinkListGetLen(pQueue, &size);
    return size == 0 ? 1 : 0;
}

/* 队列销毁 */
int doubleLinkListQueueDestroy(doubleLinkListQueue * pQueue)
{
    return DoubleLinkListDestory(pQueue);
}

