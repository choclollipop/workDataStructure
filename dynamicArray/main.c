#include <stdio.h>
#include "dynamicArray.h"

#define BUFFER_SIZE    10
#define DEFAULT_NUM    3

int main()
{
    dynamicArray array;

    dynamicArrayInit(&array, BUFFER_SIZE);

    for(int idx = 0; idx < DEFAULT_NUM; idx++)
    {
        dynamicArrayInsertData(&array, idx);
    }

    int size = 0;
    dynamicArrayGetSize(&array, &size);
    printf("size : %d\n", size);

    int val = 0;
    for(int idx = 0; idx < size; idx++)
    {
        dynamicArrayGetAppointVal(&array, idx, &val);
        printf("val : %d\n", val);
    }
    

    return 0;
}