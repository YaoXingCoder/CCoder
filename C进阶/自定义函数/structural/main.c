#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stddef.h>
/*
Date：2024.6.16
Title：结构体学习
Content：
1.声明
2.自引用
3.定义/初始化
4.内存对齐（计算结构体类型大小）
5.宏，修改默认对齐数大小
*/
// 不支持匿名结构体重命名的自引用
//typedef struct {
//	int data;
//	Node* next;
//}Node;

/*
学习计算结构体大小
*/
void structureSize(void) {
    // 练习1
    struct S1 {
        char c1;
        int i;
        char c2;
    };
    printf("%d\n", sizeof(struct S1)); // 12

    // 使用macro宏，返回结构体成员类型在结构体中偏移量
    printf("c1在struct S1中的偏移量为：%d\n", offsetof(struct S1, c1)); // 0
    printf("i在struct S1中的偏移量为：%d\n", offsetof(struct S1, i)); // 4
    printf("c2在struct S1中的偏移量为：%d\n", offsetof(struct S1, c2)); // 8

    // 练习2
    struct S2 {
        char c1;
        char c2;
        int i;
    };
    printf("%d\n", sizeof(struct S2)); // 8

    // 练习3
    struct S3 {
        double d;
        char c;
        int i;
    };
    printf("%d\n", sizeof(struct S3)); // 16

    //练习4-结构体嵌套问题
    struct S4 {
        char c1;
        struct S3 s3;
        double d;
    };
    printf("%d\n", sizeof(struct S4)); // 32
}

/*
修改默认对齐数
*/
#pragma pack(1) // 设置默认对齐数为4
void modifyAlignmentNumber(void) {
    struct S1 {
        char c1;
        int i;
        char c2;
    };
#pragma pack(1) // 设置默认对齐数为1
    struct S2 {
        char c1;
        int i;
        char c2;
    };
#pragma pack() // 取消设置的默认对齐数，还原为默认
    printf("%d\n", sizeof(struct S1)); // 12
    printf("%d\n", sizeof(struct S2)); // 6
}



int main(void) {
    //structureSize();
    modifyAlignmentNumber();
	return 0;
}


