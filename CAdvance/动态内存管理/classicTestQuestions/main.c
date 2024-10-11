#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
Date:2024.6.19
Title:动态内存测试题
Content:
*/


/*
1.通过函数方法动态开辟空间
*/
//void GetMemory1(char** p) {
//	//p = (char*)malloc(100); // p从指向str，变为指向新开辟的空间地址
//	 *p = (char*)malloc(100); // 更改为二级指针指向&str，解引用得到p = str, 将开辟空间赋值给p即str
//	// 函数结束p销毁，开辟的空间没释放，泄露
//}
void* GetMemory1(void) {
	 char* p = (char*)malloc(100); // 直接返回指针
	 return p;
}

void Test1(void) {
	char* str = NULL;
	//GetMemory1(str); // str仍NULL
	//GetMemory1(&str); // 方法1：将str地址作为实参传递
	str = GetMemory1(); // 方法2：将函数改为返回指针，接受指针即可
	strcpy(str, "hello world\n"); // strcpy函数中，赋值需要指针解引用，str为NULL所以报错，程序崩溃
	printf(str);

	// 释放
	free(str);
	str = NULL;
}

/*
2.
*/
//int* f2(void) {
//	int* ptr; // 尝试写入一个未定义或不可访问的内存位置，这通常会导致程序崩溃或产生不可预测的行为
//	*ptr = 10; // 函数返回ptr的值，即一个指向随机内存位置的指针。
//	// 由于这个指针没有被正确初始化，所以返回的指针是无效的，任何尝试使用这个指针的行为都可能是危险的。
//	return ptr;
//}
//
//void wildPointer(void) {
//	int* p = f2();
//	printf("%d\n", *p);
//}

/*
3.
*/
char* GetMemory3(void) {
	char p[] = "hello world";
	return p;
}

void Test3(void) {
	char* str = NULL;
	str = GetMemory3();
	printf(str);
}


/*
4.没释放
*/

void GetMemory4(char** p, int num) {
	*p = (char*)malloc(num);
}
void Test4(void) {
	char* str = NULL;
	GetMemory4(&str, 100);
	strcpy(str, "hello");
	printf(str);
	
	// 释放
	free(str);
	str = NULL;
}

/*
5
*/
void Test5(void) {
	char* str = (char*)malloc(100);
	strcpy(str, "hello");
	free(str); // 指向空间被释放，野指针
	//str = NULL;
	if (str != NULL) {
		strcpy(str, "world");
		printf(str);
	} // str野指针，释放后，空间都为ddddddddddddddddddd，一定符合判断条件
}

int main(void) {
	//Test();
	//wildPointer();
	//Test3();
	//Test4();
	//Test5();
	return 0;
}
