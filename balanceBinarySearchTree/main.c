#include "balanceBinarySearchTree.h"
#include <stdio.h>

#define BUFFER_SIZE    10

int printFunc(void * val)
{
    int * tmp = (int *)val;
    printf("data : %d\n", *tmp);

    return 0;
}

int compare(void * val1, void * val2)
{
    int tmp1 = *(int *)val1;
    int tmp2 = *(int *)val2;

    if(tmp1 - tmp2 < 0)
    {
        return -1;
    }
    else if(tmp1 -tmp2 > 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int main()
{
    BalanceBinarySearchTree * tree = NULL;
    int buffer[BUFFER_SIZE] = {13, 14, 15, 12, 11, 17, 16, 8, 9, 1};

    /* 初始化 */
    balanceBinarySearchTreeInit(&tree, compare, printFunc);

    /* 插入数据 */
    for(int idx = 0; idx < BUFFER_SIZE; idx++)
    {
        balanceBinarySearchTreeInsert(tree, (void *)&buffer[idx]);
    }

    /* 测试删除 */
    balanceBinarySearchTreeDelete(tree, (void *)&buffer[4]);
    balanceBinarySearchTreeDelete(tree, (void *)&buffer[3]);
    balanceBinarySearchTreeDelete(tree, (void *)&buffer[0]);

    /* 中序遍历 */
    balanceBinarySearchTreeInOrderTravel(tree);

    /* 获取高度 */
    int height = 0;
    balanceBinarySearchTreeGetHeight(tree, &height);
    printf("height : %d\n", height);
    

    return 0;
}