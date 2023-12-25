#ifndef __COMMON_H_
#define __COMMON_H_

#define ELEMENTYP void*

typedef struct dynamicArray
{
    ELEMENTYP *data;
    int len;
    int capacity;
}dynamicArray;

#endif //__COMMON_H_