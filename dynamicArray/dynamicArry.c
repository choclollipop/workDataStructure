#include "dynamicArray.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 状态码 */
enum STATUS_CODE
{
    ON_SUCCESS,
    NULL_PTR,
    MALLOC_ERROR,
};

#define DEFAULT_SIZE    10

/* 初始化动态数组 */
int dynamicArrayInit(dynamicArray * pArray, int capacity)
{
    if(!pArray)
    {
        return NULL_PTR;
    }

    /* 避免传入非法数据 */
    if(capacity < 0)
    {
        capacity = DEFAULT_SIZE;
    }

    pArray->data = (ELEMENTTYPE *)malloc(sizeof(ELEMENTTYPE) * capacity);
    if(!pArray->data)
    {
        return MALLOC_ERROR; 
    }

    /* 清楚脏数据 */
    memset(pArray->data, 0, sizeof(ELEMENTTYPE) * capacity);

    /* 初始化动态数组的参数属性 */
    pArray->capacity = capacity;
    pArray->len = 0;

    return ON_SUCCESS;
}

/* 动态数组插入数据(默认在末尾位置插入) */
int dynamicArrayInsertData(dynamicArray * pArray, ELEMENTTYPE val);

/* 动态数组在指定位置插入数据 */
int dynamicArrayAppointPosInsertData(dynamicArray * pArray, int pos, ELEMENTTYPE val);

/* 动态数组修改指定位置的数据 */
int dynamicArrayModifyAppointPosData(dynamicArray * pArray, int pos, ELEMENTTYPE val);

/* 动态数组删除数据(默认删除末尾的数据) */
int dynamicArrayDeleteData(dynamicArray * pArray);

/* 动态数组删除指定位置数据 */
int dynamicArrayDeleteAppointPosData(dynamicArray * pArray, int pos);

/* 动态数组删除指定元素 */
int dynamicArrayDeleteAppointData(dynamicArray * pArray, ELEMENTTYPE val);

/* 动态数组的销毁 */
int dynamicArrayDestroy(dynamicArray * pArray);

/* 获取数组的大小 */
int dynamicArrayGetSize(dynamicArray * pArray, int *pSize);

/* 获取数组的容量 */
int dynamicArrayGetCapacity(dynamicArray * pArray, int *pCapacity);
