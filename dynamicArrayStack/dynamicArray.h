#ifndef __DYNAMIC_ARRAY_H_
#define __DYNAMIC_ARRAY_H_

#define ELEMENTYP void*

typedef struct dynamicArray
{
    ELEMENTYP *data;
    int len;
    int capacity;
}dynamicArray;

/* 动态数组初始化 */
int dynamicArrayInit(dynamicArray * pArray, int capacity);

/* 动态数组的插入操作（默认插入位置末尾） */
int dynamicArrayInsert(dynamicArray * pArray, ELEMENTYP val);

/* 动态数组指定位置插入数据 */
int dynamicArrayInsertAppointPosData(dynamicArray * pArray, ELEMENTYP val, int pos);

/* 动态数组的删除操作(默认删除末尾元素) */
int dynamicArrayDelete(dynamicArray * pArray);

/* 动态数组删除指定位置数据 */
int dynamicArrayDeleteAppointPosData(dynamicArray * pArray, int pos);

/* 删除指定元素 */
int dynamicArrayDeleteAppointVal(dynamicArray * pArray, ELEMENTYP val, int (* compareFunc)(ELEMENTYP val1, ELEMENTYP val2));

/* 动态数组的查询指定位置的数值操作 */
int dynamicArraySearch(dynamicArray * pArray, int pos, ELEMENTYP *val);

/* 修改动态数组指定位置的数值 */
int dynamicArrayModifyAppiontPosVal(dynamicArray * pArray, ELEMENTYP val, int pos);

/* 动态数组的销毁 */
int dynamicArrayDestroy(dynamicArray * pArray);

/* 获取数组的大小 */
int dynamicArrayGetSize(dynamicArray * pArray, int *pSize);

/* 获取数组的容量 */
int dynamicArrayGetCapacity(dynamicArray * pArray, int *pCapacity);

#endif  //__DYNAMIC_ARRAY_H_