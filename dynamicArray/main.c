#include <stdio.h>
#include "dynamicArray.h"
#include <string.h>

#define BUFFER_SIZE    10
#define DEFAULT_NUM    5

typedef struct stuInfo
{
    int age;
    char sex;
}stuInfo;


int main()
{
    dynamicArray array;

    dynamicArrayInit(&array, BUFFER_SIZE);

#if 0
    {
        /* 插入数据 */
        for(int idx = 0; idx <= DEFAULT_NUM; idx++)
        {
            dynamicArrayInsertData(&array, idx);
        }
    }

    {
        int size = 0;
        /* 获取数组大小 */
        dynamicArrayGetSize(&array, &size);
        printf("size : %d\n", size);

        /* 打印数据 */
        int val = 0;
        for(int idx = 0; idx < size; idx++)
        {
            dynamicArrayGetAppointVal(&array, idx, &val);
            printf("val : %d\t", val);
        }
        printf("\n");

    }

    {
        /* 删除末尾元素 */
        dynamicArrayDeleteData(&array);

        for(int idx = 0; idx < size; idx++)
        {
            dynamicArrayGetAppointVal(&array, idx, &val);
            printf("val : %d\t", val);
        }
    
        printf("\n");
    }

    /* 删除指定位置的数据 */
    int pos = 1;
    dynamicArrayDeleteAppointData(&array, pos);
    for(int idx = 0; idx < size; idx++)
    {
        dynamicArrayGetAppointVal(&array, idx, &val);
        printf("val : %d\t", val);
    }
    printf("\n");

#endif

#if 0
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

    dynamicArrayInsertData(&array, stu1);
    dynamicArrayInsertData(&array, stu2);
    dynamicArrayInsertData(&array, stu3);

#endif

    return 0;
}