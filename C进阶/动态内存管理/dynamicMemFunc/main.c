#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/*
Date:2024.6.19
Title:动态内存管理
Content:
1.动态内存函数
	malloc
	calloc
	realloc
	free
2.
*/

// 变长数组：通过变量指定数组长度的方式
// C99标准，vs不支持，gcc支持
//int n = 0;
//scanf("%d", &n);
//int arr[n];

/*
malloc 函数
*/
void learnMalloc(void) {
	int arr[10] = { 0 }; // 静态数组，栈区
	//int* p = (int*)malloc(INT_MAX); // 开辟失败，返回空指针，即：p = NULL
	int* p = (int*)malloc(40); // 动态数组，堆区
	if (NULL == p) {
		printf("%s\n", strerror(errno));
		return;
	} else {
		printf("allocate successfully\n");
	}

	// 使用
	for (int i = 0; i < 10; i++) {
		*(p + i) = i;
	}
	for (int i = 0; i < 10; i++) {
		printf("%d ", p[i]);
	}

	// 如果没有free，程序退出时，系统会自动回收内存空间
	free(p); // p指向的空间被释放，但p指针扔指向被释放的空间
	p = NULL; // 将p置NULL
}

void learnCalloc(void) {

	// 开辟空间
	int* p = (int*)calloc(10, sizeof(int));
	if (NULL == p) {
		printf("%s\n", strerror(errno));
	} else {
		printf("allocate successfully\n");
	}

	// 使用
	for (int i = 0; i < 10; i++) {
		*(p + i) = i;
	}
	for (int i = 0; i < 10; i++) {
		printf("%d ", p[i]);
	}

	// 释放空间
	free(p);
	p = NULL;
}

void learnRealloc(void) {
	int* p = (int*)realloc(NULL, 40);
	if (NULL == p) {
		printf("%s\n", strerror(errno));
	} else {
		printf("allocate successfully\n");
	}

	// 使用
	for (int i = 0; i < 10; i++) {
		*(p + i) = i;
	}
	for (int i = 0; i < 10; i++) {
		printf("%d ", p[i]);
	}
	putchar('\n');

	// 调整空间
	int* ptr = (int*)realloc(p, 80); // 注意可能会返回空指针，所以不要用原指针直接接受
	if (NULL == ptr) {
		p = ptr;
	}
	// 使用
	for (int i = 0; i < 20; i++) {
		printf("%d ", p[i]);
	}

	// 释放
	free(p);
	p = NULL;
}

/*
主函数
*/
int main(void) {
	//learnMalloc();
	//learnCalloc();
	learnRealloc();
	return 0;
}