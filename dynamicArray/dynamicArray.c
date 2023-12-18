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

#define FREE_PTR(ptr)   \
do {                    \
    if(ptr)             \
    {                   \
        free(ptr);      \
        ptr = NULL;     \
    }                   \ 
}while(0);

#define CHECK_PTR(ptr)  \
do{                     \
    if(!ptr){           \
        return NULL_PTR;\
    }                   \
}while(0);

#define CHECK_MALLOC(ptr)  \
do{                         \
    if(!ptr){               \
        return MALLOC_ERROR;\
    }                       \
}while(0);

#define CHECK_POS(pos)              \
do{                                 \
    if(pos < 0 || pos > pArray->len)\
    {                               \
        return INVALID_ACCESS;      \
    }                               \
}while(0);

/* 静态函数前置声明 */
static int expendDynamicArray(dynamicArray * pArray);

static int shrinkDynamicCapacity(dynamicArray * pArray);

/* 初始化动态数组 */
int dynamicArrayInit(dynamicArray * pArray, int capacity)
{
    CHECK_PTR(pArray);

    /* 避免传入非法数据 */
    if(capacity < 0)
    {
        capacity = DEFAULT_SIZE;
    }

    pArray->data = (ELEMENTTYPE *)malloc(sizeof(ELEMENTTYPE) * capacity);
    CHECK_MALLOC(pArray->data);

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
    pArray->data = (ELEMENTTYPE *)malloc(sizeof(ELEMENTTYPE) * needExpandCapacity);
    CHECK_MALLOC(pArray->data);

    /* 移动数据 */
    for(int idx = 0; idx < pArray->len; idx++)
    {
        pArray->data[idx] = pTmp[idx];
    }

    /* 释放之前的内存空间 */
    /* free函数不会将指针释放，只是释放指针所指向的内存空间，不置空指针可能会编程野指针 */
    FREE_PTR(pTmp);

    /* 更新数组容量 */
    pArray->capacity = needExpandCapacity;
    
    return 0;
}

/* 动态数组在指定位置插入数据 */
int dynamicArrayAppointPosInsertData(dynamicArray * pArray, int pos, ELEMENTTYPE val)
{
    /* 指针判空 */
    CHECK_PTR(pArray);

    /* 判断位置的合法性 */
    CHECK_POS(pos);

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
    CHECK_PTR(pArray);

    /* 判断位置的合法性 */
    CHECK_POS(pos);

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
    ELEMENTTYPE *pTmp = pArray->data;

    /* 缩小1.5倍即减去现有的四分之一 */
    int needShrinkCapacity = pArray->capacity - (pArray->capacity >> 2);

    pArray->data = (ELEMENTTYPE *)malloc(sizeof(ELEMENTTYPE) * needShrinkCapacity);
    CHECK_MALLOC(pArray->data);
    
    /* 移动之前数据至新内存 */
    for (int idx = 0; idx < pArray->len; idx++)
    {
        pArray->data[idx] = pTmp[idx];
    }

    FREE_PTR(pTmp);

    pArray->capacity = needShrinkCapacity;

    return ON_SUCCESS;
}

/* 动态数组删除指定位置数据 */
int dynamicArrayDeleteAppointPosData(dynamicArray * pArray, int pos)
{
    CHECK_PTR(pArray);

    CHECK_POS(pos);

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
int dynamicArrayDeleteAppointData(dynamicArray * pArray, ELEMENTTYPE val)
{
    CHECK_PTR(pArray);

    for(int idx = pArray->len - 1; idx >= 0; idx--)
    {
        if(val == pArray->data[idx])
        {
            dynamicArrayDeleteAppointPosData(pArray, idx);
        }
    }

    return ON_SUCCESS;
}

/* 动态数组的销毁 */
int dynamicArrayDestroy(dynamicArray * pArray)
{
    CHECK_PTR(pArray);

    if(pArray)
    {
        free(pArray->data);
        pArray->data = NULL;
    }

    return ON_SUCCESS;
    
}

/* 获取数组的大小 */
int dynamicArrayGetSize(dynamicArray * pArray, int *pSize)
{
    CHECK_PTR(pArray);

    if(pSize)
    {
        *pSize = pArray->len;
    }
    
    return ON_SUCCESS;
}

/* 获取数组的容量 */
int dynamicArrayGetCapacity(dynamicArray * pArray, int *pCapacity)
{
    CHECK_PTR(pArray);

    if(pCapacity)
    {
        *pCapacity = pArray->capacity;
    }

    return ON_SUCCESS;
}

int dynamicArrayGetAppointVal(dynamicArray *pArray, int pos, ELEMENTTYPE *pVal)
{
    /* 判空 */
    CHECK_PTR(pArray);

    /* 判断位置是否合法 */
    CHECK_POS(pos);

    if(pVal)
    {
        *pVal = pArray->data[pos];
    }

    return ON_SUCCESS;
}
