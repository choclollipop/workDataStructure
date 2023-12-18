#ifndef __DYNAMIC_ARRAY_H_
#define __DYNAMIC_ARRAY_H_

typedef int ELEMENTTYPE;

/* 动态数组结构体 */
typedef struct dynamicArray
{
    ELEMENTTYPE *data;   /* 数组的空间 */
    int len;             /* 数组的大小 */
    int capacity;        /* 数组的容量 */
}dynamicArray;

/* 初始化动态数组 */
int dynamicArrayInit();

/* 动态数组插入数据(默认在末尾位置插入) */
int dynamicArrayInsertData();

/* 动态数组在指定位置插入数据 */
int dynamicArrayAppointPosInsertData();

/* 动态数组修改指定位置的数据 */
int dynamicArrayModifyAppointPosData();

/* 动态数组删除数据(默认删除末尾的数据) */
int dynamicArrayDeleteData();

/* 动态数组删除指定位置数据 */
int dynamicArrayDeleteAppointPosData();

/* 动态数组的销毁 */
int dynamicArrayDestroy();

/* 获取数组的大小 */
int dynamicArrayGetSize();

/* 获取数组的容量 */
int dynamicArrayGetCapacity();

#endif // __DYNAMIC_ARRAY_H_