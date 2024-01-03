#include <stdio.h>
#include "doubleLinkList.h"
#include <string.h>

#define BUFFER_SIZE 3

int printFunc(void * val)
{
    int ret = 0;

    int * tmp = (int *)val;
    printf("data : %d\n", *tmp);
    
    return 0;
}

int main()
{
    DoubleLinkList * list1 = NULL;
    DoubleLinkList * list2 = NULL;

    DoubleLinkList * result = NULL;

    int buffer1[BUFFER_SIZE] = {1, 2, 4};
    int buffer2[BUFFER_SIZE] = {1, 3, 4};
    
    /* 测试链表初始化 */
    DoubleLinkListInit(&list1);
    DoubleLinkListInit(&list2);
    DoubleLinkListInit(&result);


    /* 尾插 */
    for (int idx = 0; idx < BUFFER_SIZE; idx++)
    {
        DoubleLinkListTailInsert(list1, (void *)&buffer1[idx]);
    }
    for (int idx = 0; idx < BUFFER_SIZE; idx++)
    {
        DoubleLinkListTailInsert(list2, (void *)&buffer2[idx]);
    }

    /* 遍历打印链表 */
    DoubleLinkListForeach(list1, printFunc);
    printf("\n");
    DoubleLinkListForeach(list2, printFunc);
    printf("\n");

    int * val1 = NULL;
    int * val2 = NULL;
    int tmp1= 0;
    int tmp2 = 0;
    for (int idx = 1; idx <= list1->len; idx++)
    {
        DoubleLinkListGetAppointPosVal(list1, idx, (void **)&val1);
        /* 先将链表1的所有结点插入到最终链表中 */
        DoubleLinkListTailInsert(result, (void *)val1);
    }

    int pos = 1;
    int idx = 1;
    while (pos <= list2->len)
    {
        DoubleLinkListGetAppointPosVal(result, idx, (void **)&val1);
        tmp1 = *val1;
        DoubleLinkListGetAppointPosVal(list2, pos, (void **)&val2);
        tmp2 = *val2;
        if(tmp1 <= tmp2)
        {
            DoubleLinkListAppointPosInsert(result, idx, (void *)val2);
        }
        pos++;
        idx += 2;
    }
    
    DoubleLinkListForeach(result, printFunc);
    
    return 0;
}