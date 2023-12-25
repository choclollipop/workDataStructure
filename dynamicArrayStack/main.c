#include <stdio.h>
#include "dynamicArrayStack.h"

#define BUFFER_SIZE 5

int main()
{
    /* 怎么解决套壳问题 */
    dynamicArrayStack stack;
    int buffer[BUFFER_SIZE] = {5, 32, 21, 56, 87};

    /* 数组初始化 */
    dynamicArrayStackInit(&stack);

    for(int idx = 0; idx < BUFFER_SIZE; idx++)
    {
        dynamicArrayStackPush(&stack, &buffer[idx]);
    }

    int *val = NULL;
    while(!dynamicArrayStackIsEmpty(&stack))
    {
        dynamicArrayStackTop(&stack, (void **)&val);
        printf("val : %d\n", *val);
        dynamicArrayStackPop(&stack);
    }

    int size = 0;
    dynamicArrayStackSize(&stack, &size);
    printf("size : %d\n", size);

    /* 栈的销毁 */
    dynamicArrayStackDestroy(&stack);

    return 0;
}