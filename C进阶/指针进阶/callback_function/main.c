#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Date:2024.06.12
Title:�Ż�ð������
Content:
1.��������������ж�����ж�
2.qsort����ʹ�ã��Ƚ���������ͽṹ�����飩
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
ð������bubbleSort��
ȱ��1�����ԭ���������������ɻὫ�жϵ���
ȱ��2��ֻ�������������飨�β��б�����
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
�Ż�ȱ��1
����һ���������������滻����ʱ���ñ������
����һ�ֵ������û�н��뵽�滻������ñ���ֵ����
����һ��������жϸñ�����������Ƿ��˳�ѭ��
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
�Ż�ȱ��2
C�п⺯��qsort����
void qsort(void* base,
		   size_t num,
		   size_t width,
		   int (* compare)(const void* e1, const void* e2));
����1 void* base���������������ʼλ�õĵ�ַ
����2 size_t num������������Ԫ�صĸ���
����3 size_t width������������Ԫ�صĴ�С����λ���ֽڣ�
����4 int (__cdecl* compare)(const void* elem1, const void* elem2))������ָ��-�ȽϺ���
__cdecl����������Լ��
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
��Ҫ����qsort�����ıȽ����ͺ���
�Ƚ�int��������
*/
int cmp_int(const void* e1, const void* e2) {
	return *(int*)e2 - *(int*)e1;
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
