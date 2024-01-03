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

int compare(void * val1, void * val2)
{
    int * tmp1 = (int *)val1;
    int * tmp2 = (int *)val2;
    if(*tmp1 <= *tmp2)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int mergeList(DoubleLinkList * list1, DoubleLinkList * list2, DoubleLinkList * result)
{
    int * val1 = NULL;
    int * val2 = NULL;
    int one = 1;
    int two = 1;
    int pos = 0;
    while(result->len < list1->len + list2->len)
    {
        if(one <= list1->len || two <= list2->len)
        {
            if(one <= list1->len)
            {
                DoubleLinkListGetAppointPosVal(list1, one, (void **)&val1);
            }
            if(two <= list2->len)
            {
                DoubleLinkListGetAppointPosVal(list2, two, (void **)&val2);
            }     
        }
        

        if (compare(val1, val2) && one <= list1->len)
        {
            DoubleLinkListAppointPosInsert(result, pos, (void *)val1);
            pos++;
            one++;
        }
        else
        {
            DoubleLinkListAppointPosInsert(result, pos, (void *)val2);
            pos++;
            two++;
        }
        
    }

}

int main()
{
    DoubleLinkList * list1 = NULL;
    DoubleLinkList * list2 = NULL;

    DoubleLinkList * result = NULL;

    int buffer1[] = {1, 2, 4, 5};
    int len1 = sizeof(buffer1) / sizeof(buffer1[0]);
    int buffer2[] = {1, 3, 4, 7, 9};
    int len2 = sizeof(buffer2) / sizeof(buffer2[0]);
    
    /* 测试链表初始化 */
    DoubleLinkListInit(&list1);
    DoubleLinkListInit(&list2);
    DoubleLinkListInit(&result);
    
    /* 尾插 */
    for (int idx = 0; idx < len1; idx++)
    {
        DoubleLinkListTailInsert(list1, (void *)&buffer1[idx]);
    }
    for (int idx = 0; idx < len2; idx++)
    {
        DoubleLinkListTailInsert(list2, (void *)&buffer2[idx]);
    }

    mergeList(list1, list2, result);
    
    DoubleLinkListForeach(result, printFunc);
    
    return 0;
}