#include "dynamicArrayStack.h"
#include "dynamicArray.h"

#define DEFAULT_SIZE    10

/* 栈的初始化 */
int dynamicArrayStackInit(dynamicArrayStack * pStack)
{
    return dynamicArrayInit(pStack, DEFAULT_SIZE);
}

/* 压栈 */
int dynamicArrayStackPush(dynamicArrayStack * pStack, ELEMENTYP val)
{
    return dynamicArrayInsert(pStack, val);
}

/* 查看栈顶元素 */
int dynamicArrayStackTop(dynamicArrayStack * pStack, ELEMENTYP * pVal)
{
    return dynamicArraySearch(pStack, pStack->len - 1, pVal);
}

/* 出栈 */
int dynamicArrayStackPop(dynamicArrayStack * pStack)
{
    return dynamicArrayDelete(pStack);
}

/* 栈是否为空 */
int dynamicArrayStackIsEmpty(dynamicArrayStack * pStack)
{
    int size = 0;
    dynamicArrayGetSize(pStack, &size);
    return size == 0 ? 1 : 0;
}

/* 获取栈的大小 */
int dynamicArrayStackSize(dynamicArrayStack * pStack, int * pSize)
{
    dynamicArrayGetSize(pStack, pSize);
    return *pSize;
}

/* 销毁栈 */
int dynamicArrayStackDestroy(dynamicArrayStack * pStack)
{
    dynamicArrayDestroy(pStack);
}