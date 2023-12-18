#ifndef __DYNAMIC_ARRAY_H_
#define __DYNAMIC_ARRAY_H_

#if 1

#define ELEMENTTYPE void*

#else

typedef void * ELEMENTTYPE;
#endif

/* 动态数组结构体 */
typedef struct dynamicArray
{
    ELEMENTTYPE *data;   /* 数组的空间 */
    int len;             /* 数组的大小 */
    int capacity;        /* 数组的容量 */
}dynamicArray;

/* 初始化动态数组 */
int dynamicArrayInit(dynamicArray * pArray, int capacity);

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
int dynamicArrayDeleteAppointData(dynamicArray * pArray, ELEMENTTYPE val);  //有问题

/* 动态数组的销毁 */
int dynamicArrayDestroy(dynamicArray * pArray);

/* 获取数组的大小 */
int dynamicArrayGetSize(dynamicArray * pArray, int *pSize);

/* 获取数组的容量 */
int dynamicArrayGetCapacity(dynamicArray * pArray, int *pCapacity);

/* 获取指定位置的数据元素 */
int dynamicArrayGetAppointVal(dynamicArray * pArray, int pos, ELEMENTTYPE *pVal); 

#endif // __DYNAMIC_ARRAY_H_