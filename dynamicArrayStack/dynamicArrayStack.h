#ifndef __DYNAMIC_ARRAY_STACK_H_
#define __DYNAMIC_ARRAY_STACK_H_

#include "dynamicArray.h"

typedef dynamicArray dynamicArrayStack;

/* 栈的初始化 */
int dynamicArrayStackInit(dynamicArrayStack * pStack);

/* 压栈 */
int dynamicArrayStackPush(dynamicArrayStack * pStack, ELEMENTYP val);

/* 查看栈顶元素 */
int dynamicArrayStackTop(dynamicArrayStack * pStack, ELEMENTYP * pVal);

/* 出栈 */
int dynamicArrayStackPop(dynamicArrayStack * pStack);

/* 栈是否为空 */
int dynamicArrayStackIsEmpty(dynamicArrayStack * pStack);

/* 获取栈的大小 */
int dynamicArrayStackSize(dynamicArrayStack * pStack, int * pSize);

/* 销毁栈 */
int dynamicArrayStackDestroy(dynamicArrayStack * pStack);

#endif //__DYNAMIC_ARRAY_STACK_H_