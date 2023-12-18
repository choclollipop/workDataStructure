#ifndef __DYNAMIC_ARRAY_H_
#define __DYNAMIC_ARRAY_H_

typedef int ELEMENTTYPE;

typedef struct dynamicArray
{
    ELEMENTTYPE *data;
    int len;
    int capacity;
}dynamicArray;


#endif // __DYNAMIC_ARRAY_H_