#include <stdio.h>
#include "LinkList.h"

#define BUFFER_SIZE 3

int main()
{
    LinkList * list = NULL;
    
    /* 测试链表初始化 */
    LinkListInit(&list);
    printf("list.len : %d\n", list->len);

    /* 测试头插 */
    for(int idx = 0; idx < BUFFER_SIZE; idx++)
    {
        LinkListHeadInsert(list, idx);
    }

    /* 获取链表长度 */
    int len = 0;
    LinkListGetLen(list, &len);
    printf("len : %d\n", len);

    /* 测试链表遍历 */
    LinkListForeach(list);

    return 0;
}