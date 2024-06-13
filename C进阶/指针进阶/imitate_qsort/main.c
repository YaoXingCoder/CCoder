#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

/*
Date:2024.6.13
Title:ģ��ʵ��qsort������
Content:
��bubbleSortð���������Ϊ����qsort�ķ�ʽ
��չbubbleSort���������ͺ�������
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
��Ҫ����qsort�����ıȽ����ͺ���
�Ƚ�int��������
*/
int cmp_int(const void* e1, const void* e2) {
	return *(int*)e1 - *(int*)e2;
}

/*
�ȽϽṹ������
�Ƚ��ַ���ʹ��strcmp(para1, para2);����ֵΪint
*/
int cmp_struct_name(const void* e1, const void* e2) {
	return strcmp(((struct Stu*)e2)->name, ((struct Stu*)e1)->name);
}

int cmp_struct_age(const void* e1, const void* e2) {
	return (((struct Stu*)e1)->age - ((struct Stu*)e1)->age);
}

/*
����bubbleSortģ��qsort

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
			// �Ƚϣ�ÿ�δ�����Ҫ�Ƚ�����Ԫ�ص��׵�ַ������ֵ�Ƿ����0�����н���
			if ((cmp((char*)base+j*width, (char*)base+(j+1)*width)) > 0) {
				swap((char*)base + j * width, (char*)base + (j + 1) * width, width);
				flag = 0;
			}
		}
		if (flag) break;
	}
}

/*
��������
��Ϊ��ȷ��Ԫ�����ͣ�������Ҫ����һ�����͵Ŀ��
����Ϊchar���ͣ�����Ԫ���׵�ַ+���Ϳ�Ⱦ���һ��Ԫ��
ÿ���滻һ��Ԫ���ڵ�һ���ֽڵ�ַ���滻width��С�����滻һ��Ԫ��
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