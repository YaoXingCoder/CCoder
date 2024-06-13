#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Date:2024.06.12
Title:优化冒泡排序
Content:
1.不对有序数组进行多余的判断
2.qsort函数使用（比较整型数组和结构体数组）
*/

void bullbleSort1(int arr[], int sz);
void bullbleSort2(int arr[], int sz);
void test_int(void);
void test_struct(void);
int cmp_int(const void* e1, const void* e2);
int cmp_struct_name(const void* e1, const void* e2);
int cmp_struct_age(const void* e1, const void* e2);


struct Stu {
	char name[20];
	int age;
};

int main(void) {
	//test_int();
	test_struct();
	return 0;
}

/*
冒泡排序（bubbleSort）
缺陷1：如果原本数组有序，则依旧会将判断到底
缺陷2：只能排序整型数组（形参列表定死）
*/
void bullbleSort1(int arr[], int sz) {
	for (int i = 0; i < sz - 1; i++) {
		for (int j = 0; j < sz - 1 - i; j++) {
			if (arr[j] > arr[j + 1]) {
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}

/*
优化缺陷1
增加一个变量，当进行替换操作时，该变量变更
进行一轮的排序后，没有进入到替换操作则该变量值不变
并在一轮排序后判断该变量，视情况是否退出循环
*/
void bullbleSort2(int arr[], int sz) {
	for (int i = 0; i < sz - 1; i++) {
		int flag = 1;
		for (int j = 0; j < sz - 1 - i; j++) {
			if (arr[j] > arr[j + 1]) {
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
				flag = 0;
			}
		}
		if (flag) break;
	}
}

/*
优化缺陷2
C有库函数qsort函数
void qsort(void* base,
		   size_t num,
		   size_t width,
		   int (* compare)(const void* e1, const void* e2));
参数1 void* base：待排序数组的起始位置的地址
参数2 size_t num：待排序数组元素的个数
参数3 size_t width：待排序数组元素的大小（单位：字节）
参数4 int (__cdecl* compare)(const void* elem1, const void* elem2))：函数指针-比较函数
__cdecl：函数调用约定
*/

void test_int(void) {
	int arr[] = { 9,2,3,7,8,4,6 };
	int sz = sizeof(arr) / sizeof(arr[0]);
	qsort(arr, sz, sizeof(arr[0]), cmp_int);
	for (int i = 0; i < sz; i++) {
		printf("%d ", arr[i]);
	}
}

void test_struct(void) {
	struct Stu s[3] = { {"zhangsan",18},{"lisi",15},{"wangwu",21} };
	int sz = sizeof(s) / sizeof(s[0]);
	//qsort(s, sz, sizeof(s[0]), cmp_struct_name);
	qsort(s, sz, sizeof(s[0]), cmp_struct_age);
}

/*
需要传给qsort函数的比较类型函数
比较int类型数组
*/
int cmp_int(const void* e1, const void* e2) {
	return *(int*)e2 - *(int*)e1;
}

/*
比较结构体类型
比较字符串使用strcmp(para1, para2);返回值为int
*/
int cmp_struct_name(const void* e1, const void* e2) {
	return strcmp(((struct Stu*)e2)->name, ((struct Stu*)e1)->name);
}

int cmp_struct_age(const void* e1, const void* e2) {
	return (((struct Stu*)e1)->age - ((struct Stu*)e1)->age);
}
