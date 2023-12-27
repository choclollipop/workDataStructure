#include <stdio.h>
#include "binarySearchTree.h"

#define BUFFER_SIZE    5

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
    binarySearchTree * tree = NULL;
    int buffer[BUFFER_SIZE] = {56, 28, 75, 73, 77};

    /* 测试初始化函数 */
    binarySearchTreeInit(&tree, compare, printFunc);

    /* 测试插入函数 */
    for (int idx = 0; idx < BUFFER_SIZE; idx++)
    {
        binarySearchTreeInsert(tree, (void *)&buffer[idx]);
    }

    /* 测试获取节点个数 */
    int size = 0;
    binarySearchTreeGetNodeSize(tree, &size);
    printf("size : %d\n", size);

    /* 测试获取二叉搜索树的高度 */
    int height = 0;
    binarySearchTreeGetHeight(tree, &height);
    printf("height : %d\n", height);

    /* 测试删除指定元素 */
    binarySearchTreeDelete(tree, (void *)&buffer[3]);
    binarySearchTreeDelete(tree, (void *)&buffer[2]);

    /* 测试中序打印 */
    binarySearchTreeInOrderTravel(tree);
    printf("\n");

    /* 测试后序遍历 */
    binarySearchTreePostOrderTravel(tree);
    printf("\n");

    /* 测试前序遍历 */
    binarySearchTreePreOrderTravel(tree);
    printf("\n");

    /* 测试层序遍历 */
    binarySearchTreeLevelOrderTravel(tree);

    /* 测试是否包含指定元素 */
    int res = binarySearchTreeIsContainAppointVal(tree, (void *)&buffer[1]);
    printf("res : %d\n", res);

    return 0;
}