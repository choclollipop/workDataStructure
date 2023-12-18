#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 16
#define DEFAULT_SIZE 5

/* 结构体 */
/* 什么叫结构体？
    将不同类型的属性封装成一个类型
*/

/* 结构体的定义：*/
typedef struct student
{
    int age;
    int height;
    int weight;
    char sex;
    char name[BUFFER_SIZE];
    char *address;
}student;
/* 结构体会默认进行字节对齐：读取速度快，但会浪费空间 */

/*  取别名：typedef */
//typedef struct student student;

#if 0
/* 值传递:不影响实参的值 */
void printStucture(student stu)
{
    stu.age = 100;
    printf("stu.age:%d\t, stu.height:%d\t, stu.sex:%c\t, stu.weight:%d\t, stu.name:%s\n",
            stu.age, stu.height, stu.sex, stu.weight, stu.name);
}

#endif

/* 传入参数：不改变实参的值，但是使用指针可以极大的节省栈空间 */
void printStucture(const student *stu)
{

    int len = sizeof(stu);
    printf("len : %d\n", len);

    printf("stu.age:%d\t, stu.height:%d\t, stu.sex:%c\t, stu.weight:%d\t, stu.name:%s\n",
            stu->age, stu->height, stu->sex, stu->weight, stu->name);
}

/* 结构体数组做函数参数 */
void printStuctureBuffer(student *stu, int stuSize)
{
    for(int idx = 0; idx < stuSize; idx++)
    {
        printf("stu.age:%d\t, stu.height:%d\t, stu.sex:%c\t, stu.weight:%d\t, stu.name:%s\n",
            stu[idx].age, stu[idx].height, stu[idx].sex, stu[idx].weight, stu[idx].name);
    }
}

int main()
{
    
    student stu;
    memset(&stu, 0, sizeof(stu));
#if 0
    /* 怎么使用结构体 */
    /* 方法一：*/
    

    /* 结构体大小 */
    int len = sizeof(stu);
    printf("len : %d\n", len);

    stu.age = 10;
    stu.height = 50;
    stu.sex = 'm';
    stu.weight = 110;
    strncpy(stu.name, "zhangsan", sizeof(stu.name) - 1);
    //stu.name = "zhangsan";

#endif

#if 1
    /* 结构体数组 */
    student buffer[DEFAULT_SIZE];

    buffer[0].age = 10;
    buffer[0].height = 50;
    buffer[0].sex = 'm';
    buffer[0].weight = 110;
    strncpy(buffer[0].name, "zhangsan", sizeof(buffer[0].name) - 1);

    buffer[1].age = 12;
    buffer[1].height = 130;
    buffer[1].sex = 'm';
    buffer[1].weight = 80;
    strncpy(buffer[1].name, "zhangsan", sizeof(buffer[1].name) - 1);

    printStuctureBuffer(buffer, sizeof(buffer) / sizeof(buffer[0]));

    stu.address = "china";
    stu.address = (char *)malloc(sizeof(char) * BUFFER_SIZE);
    strncpy(stu.address, "china", sizeof(char) * BUFFER_SIZE - 1);

#endif

#if 0

    /* 结构体指针 */
    stu.age = 10;
    stu.height = 50;
    stu.sex = 'm';
    stu.weight = 110;
    strncpy(stu.name, "zhangsan", sizeof(stu.name) - 1);

    student * info = &stu;
    /* 结构体指针 读数据或者写数据都是用-> */
    info->age = 30;

    printStucture(&stu);

    printf("stu.age:%d\t, stu.height:%d\t, stu.sex:%c\t, stu.weight:%d\t, stu.name:%s\n",
            stu.age, stu.height, stu.sex, stu.weight, stu.name);
    
#endif

    return 0;
}