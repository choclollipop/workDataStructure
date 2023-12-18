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
    INVALID_ACCESS,
};

#define DEFAULT_SIZE    10

/* 静态函数前置声明 */
static int expendDynamicArray(dynamicArray * pArray);

static int shrinkDynamicCapacity(dynamicArray * pArray);

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
int dynamicArrayInsertData(dynamicArray * pArray, ELEMENTTYPE val)
{
    return dynamicArrayAppointPosInsertData(pArray, pArray->len, val);
}

/* 动态数组扩容 */
static int expendDynamicArray(dynamicArray * pArray)
{
    /* 自己写成了 dynamicArry * pTmp = pArry; 只需要指向数据的指针就好，不是动态数组类型的 */
    ELEMENTTYPE * pTmp = pArray->data;

    int needExpandCapacity = pArray->capacity + (pArray->capacity >> 1);

    /* 将原来的容量增加至增加1.5倍 */
    pArray->data = (dynamicArray *)malloc(sizeof(ELEMENTTYPE) * needExpandCapacity);
    if(!pArray->data)
    {
        return MALLOC_ERROR;
    }

    /* 移动数据 */
    for(int idx = 0; idx < pArray->len; idx++)
    {
        pArray->data[idx] = pTmp[idx];
    }

    /* 释放之前的内存空间 */
    if(!pTmp)
    {
        free(pTmp);
        /* free函数不会将指针释放，只是释放指针所指向的内存空间，不置空指针可能会编程野指针 */
        pTmp = NULL;
    }

    /* 更新数组容量 */
    pArray->capacity = needExpandCapacity;
    
    return 0;
}

/* 动态数组在指定位置插入数据 */
int dynamicArrayAppointPosInsertData(dynamicArray * pArray, int pos, ELEMENTTYPE val)
{
    /* 指针判空 */
    if(!pArray)
    {
        return NULL_PTR;
    }

    /* 判断位置的合法性 */
    if(pos < 0 || pos > pArray->len)
    {
        return INVALID_ACCESS;
    }

    /* 开始扩容:算法是数组扩容的临界值是，数组大小的1.5倍 >= 数组容量 */
    if( pArray->len + (pArray->len >> 1) >= pArray->capacity)
    {
        expendDynamicArray(pArray);
    }
    

    /* 数据后移，留出pos位置插入数据 */
    for(int idx = pArray->len; idx > pos; idx--)
    {
        pArray->data[idx] = pArray->data[idx - 1];
    }

    /* 找到对应的值，写入到数组中 */
    pArray->data[pos] = val;
    pArray->len += 1;

    return ON_SUCCESS;
}

/* 动态数组修改指定位置的数据 */
int dynamicArrayModifyAppointPosData(dynamicArray * pArray, int pos, ELEMENTTYPE val)
{
    /* 指针判空 */
    if(!pArray)
    {
        return NULL_PTR;
    }

    /* 判断位置的合法性 */
    if(pos < 0 || pos > pArray->len)
    {
        return INVALID_ACCESS;
    }

    /* 更新指定位置的数据 */
    pArray->data[pos] = val;

    return ON_SUCCESS;
}

/* 动态数组删除数据(默认删除末尾的数据) */
int dynamicArrayDeleteData(dynamicArray * pArray)
{
    return dynamicArrayDeleteAppointPosData(pArray, pArray->len - 1);
}

static int shrinkDynamicCapacity(dynamicArray * pArray)
{
    ELEMENTTYPE * pTmp = pArray->data;

    /* 缩小1.5倍即减去现有的四分之一 */
    int needShrinkCapacity = pArray->capacity - (pArray->capacity >> 2);

    pArray->data = (ELEMENTTYPE *)malloc(sizeof(ELEMENTTYPE) * needShrinkCapacity);
    if(!pArray->data)
    {
        return MALLOC_ERROR;
    }

    /* 移动之前数据至新内存 */
    for (int idx = 0; idx < pArray->len; idx++)
    {
        pArray->data[idx] = pTmp[idx];
    }

    if(!pTmp)
    {
        free(pTmp);
        pTmp = NULL;
    }

    pArray->capacity = needShrinkCapacity;

    return ON_SUCCESS;
}

/* 动态数组删除指定位置数据 */
int dynamicArrayDeleteAppointPosData(dynamicArray * pArray, int pos)
{
    if(!pArray)
    {
        return NULL_PTR;
    }

    if(pos < 0 || pos > pArray->len)
    {
        return INVALID_ACCESS;
    }

    /* 动态数组缩容 */
    if((pArray->capacity - (pArray->capacity >> 2)) < pArray->len)
    {
        /* 缩容 */
        shrinkDynamicCapacity(pArray);
    }

    /* 数据前移 */
    for(int idx = pos; idx < pArray->len; idx++)
    {
        pArray->data[idx] = pArray->data[idx + 1];
    }

    pArray->len--;

    return ON_SUCCESS;
}

/* 动态数组删除指定元素 */
int dynamicArrayDeleteAppointData(dynamicArray * pArray, ELEMENTTYPE val);

/* 动态数组的销毁 */
int dynamicArrayDestroy(dynamicArray * pArray);

/* 获取数组的大小 */
int dynamicArrayGetSize(dynamicArray * pArray, int *pSize);

/* 获取数组的容量 */
int dynamicArrayGetCapacity(dynamicArray * pArray, int *pCapacity);
