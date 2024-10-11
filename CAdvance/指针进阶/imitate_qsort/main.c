#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

/*
Date:2024.6.13
Title:模拟实现qsort排序函数
Content:
将bubbleSort冒泡排序更改为类似qsort的方式
拓展bubbleSort的排序类型和升序降序
*/
void test_int(void);
void test_struct(void);
int cmp_int(const void* e1, const void* e2);
int cmp_struct_name(const void* e1, const void* e2);
int cmp_struct_age(const void* e1, const void* e2);
void bullbleSort(void* base, size_t num, size_t width, int(*cmp)(const void* e1, const void* e2));
void swap(const void* e1, const void* e2, size_t width);


struct Stu {
	char name[20];
	int age;
};

int main(void) {
	test_int();
	test_struct();
	return 0;
}

void test_int(void) {
	int arr[] = { 9,2,3,7,8,4,6 };
	int sz = sizeof(arr) / sizeof(arr[0]);
	bullbleSort(arr, sz, sizeof(arr[0]), cmp_int);
	for (int i = 0; i < sz; i++) {
		printf("%d ", arr[i]);
	}
}

void test_struct(void) {
	struct Stu s[3] = { {"zhangsan",18},{"lisi",15},{"wangwu",21} };
	int sz = sizeof(s) / sizeof(s[0]);
	bullbleSort(s, sz, sizeof(s[0]), cmp_struct_name);
	//bullbleSort(s, sz, sizeof(s[0]), cmp_struct_age);
}

/*
需要传给qsort函数的比较类型函数
比较int类型数组
*/
int cmp_int(const void* e1, const void* e2) {
	return *(int*)e1 - *(int*)e2;
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

/*
更改bubbleSort模拟qsort

void qsort(void* base,
		   size_t num,
		   size_t width,
		   int (*compare)(const void* e1, const void* e2));

void bullbleSort(void* base,
				 size_t num,
				 size_t width,
				 int(*cmp)(const void* e1, const void* e2))
*/
void bullbleSort(void* base, 
				 size_t num, 
				 size_t width, 
				 int(*cmp)(const void* e1, const void* e2)) {
	for (int i = 0; i < num - 1; i++) {
		int flag = 1;
		for (int j = 0; j < num - 1 - i; j++) {
			// 比较：每次传入需要比较两个元素的首地址，返回值是否大于0，进行交换
			if ((cmp((char*)base+j*width, (char*)base+(j+1)*width)) > 0) {
				swap((char*)base + j * width, (char*)base + (j + 1) * width, width);
				flag = 0;
			}
		}
		if (flag) break;
	}
}

/*
交换函数
因为不确定元素类型，所以需要接受一个类型的宽度
接受为char类型，接受元素首地址+类型宽度就是一个元素
每次替换一个元素内的一个字节地址，替换width大小就是替换一个元素
*/
void swap(char* buf1, char* buf2, size_t width) {
	char temp = 0;
	for (int i = 0; i < width; i++) {
		temp = *buf1;
		*buf1 = *buf2;
		*buf2 = temp;
		buf1++;
		buf2++;
	}
}