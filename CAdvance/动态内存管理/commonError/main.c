#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/*
Date:2024.6.19
Title:动态内存函数常见错误
Content:
1.对NULL指针的解引用操作
2.对动态开辟空间的越界访问
3.对非动态开辟内存使用free释放
4.使用free释放一块动态开辟内存的一部分
5.对同一块动态内存多次释放
6.动态开辟内存忘记释放（内存泄漏）

*/

/*
1.可能分配失败, 传的空指针
*/
void nullPoint(void) {
	int* p = (int*)malloc(INT_MAX / 4);
	if (NULL == p) { // 使用指针前先判断是否空指针
		return;
	}
	*p = 20; // 如果p的值是NULL，就会有问题，
	free(p);
}

/*
2.越界访问
*/
void crossBorderVisits(void) {
	int i = 0;
	int* p = (int*)malloc(10 * sizeof(int));
	if (NULL == p) {
		exit(EXIT_FAILURE);
	}
	for (i = 0; i <= 10; i++) {
		*(p + i) = i; // 当i是10的时候越界访问
	}
	free(p);
}

/*
3.对非动态开辟内存使用free释放
*/
void errorRelease(void) {
	int a = 10;
	int* p = &a;
	free(p); // p指向非动态开辟空间
}

/*
4.释放一块动态开辟内存的一部分
*/
void partialFree(void) {
	int* p = (int*)malloc(100);
	if (NULL == p) {
		return;
	}
	p++; // p不再指向动态内存的起始位置
	free(p); 
}

/*
5.多次释放
*/
void multipleFree(void) {
	int* p = (int*)malloc(100);
	free(p); // 已经释放
	free(p); // 重复释放同一空间
}

/*
6.忘记释放（内存泄漏）
*/
void forgotToFree(void) {
	int* p = (int*)malloc(100);
	if (NULL != p) {
		*p = 20;
	}
}


int main(void) {
	//crossBorderVisits();
	//errorRelease();
	//partialFree();
	//multipleFree();
	//forgotToFree();
	return 0;
}
