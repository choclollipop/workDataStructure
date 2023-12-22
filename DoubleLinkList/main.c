#include <stdio.h>
#include "doubleLinkList.h"
#include <string.h>

#define BUFFER_SIZE 3

typedef struct stuInfo
{
    int age;
    char sex;
}stuInfo;

int printfStruct(void *arg)
{
    stuInfo *info = (stuInfo*) arg;

    printf("age:%d,\t sex:%c\n", info->age, info->sex);
}

int main()
{
    DoubleLinkList * list = NULL;
    
    /* 测试链表初始化 */
    DoubleLinkListInit(&list);
    printf("list.len : %d\n", list->len);

#if 0
    /* 测试头插 */
    for(int idx = 0; idx < BUFFER_SIZE; idx++)
    {
        DoubleLinkListHeadInsert(list, idx);
    }

    /* 获取链表长度 */
    int len = 0;
    DoubleLinkListGetLen(list, &len);
    printf("len : %d\n", len);

    /* 测试链表遍历 */
    DoubleLinkListForeach(list);
#endif

    stuInfo stu1,stu2,stu3;
    memset(&stu1, 0, sizeof(stu1));
    memset(&stu2, 0, sizeof(stu2));
    memset(&stu3, 0, sizeof(stu3));

    stu1.age = 10;
    stu1.sex = 'm';

    stu2.age = 20;
    stu2.sex = 'f';

    stu3.age = 30;
    stu3.sex = 'm';

    stuInfo buffer[BUFFER_SIZE] = {stu1, stu2, stu3};

    for(int idx = 0; idx < BUFFER_SIZE; idx++)
    {
        DoubleLinkListHeadInsert(list, (void*)&buffer[idx]);
    }

    /* 获取链表长度 */
    int len = 0;
    DoubleLinkListGetLen(list, &len);
    printf("len : %d\n", len);

#if 1
    /* 测试链表遍历 */
    DoubleLinkListReverseForeach(list, printfStruct);
#else
    DoubleLinkListForeach(list, printfStruct);

#endif

    return 0;
}