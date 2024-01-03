#include <stdio.h>
#include "dynamicArrayStack.h"

#define BUFFER_SIZE 6
#define FREQUENT    3

int isValied(dynamicArrayStack *stack, char * array, int len)
{
    char * val = NULL; 
    int idx = 0;
    while(idx < len)
    {
        if (array[idx] == '(' || array[idx] == '[' || array[idx] == '{')
        {
            /* 入栈 */
            dynamicArrayStackPush(stack, (void *)&array[idx]);
        }
        else
        {
            if(dynamicArrayStackIsEmpty(stack))
            {
                printf("false\n");
                return 0;
            }
            dynamicArrayStackTop(stack, (void **)&val);
            /* 找到右括号，此时栈顶的元素必须是对应的左括号 */
            if (array[idx] == ')')
            {
                if (*val != '(')
                {
                    printf("false\n");
                    return 0;
                }
            }
            else if (array[idx] == ']')
            {
                if (*val != '[')
                {
                    printf("false\n");
                    return 0;
                }
            }
            else if (array[idx] == '}')
            {
                if (*val != '{')
                {
                    printf("false\n");
                    return 0;
                }
            }
            /* 若此时栈为空的情况下，仍然有右括号则，不符合要求 */
            if (idx <= len - 1 && dynamicArrayStackIsEmpty(stack))
            {
                printf("false\n");
                return 0;
            }

            dynamicArrayStackPop(stack);  
        }
        idx++;
    }

    /* 若字符串符合要求此时栈内所有对应的左括号应已经全部出栈并且已经遍历完全数组 */
    if(idx == len && dynamicArrayStackIsEmpty(stack))
    {
        printf("true\n");
    }
    else
    {
        printf("false\n");
    }

    return 0;
}

int main()
{
    /* 怎么解决套壳问题 */
    dynamicArrayStack stack;
    char array[] = "{{}()()}";
    int len = sizeof(array) / sizeof(array[0]) - 1;
    

    /* 数组初始化 */
    dynamicArrayStackInit(&stack);
    
    isValied(&stack, array, len);
    

    /* 销毁栈 */
    dynamicArrayStackDestroy(&stack);

    return 0;
}