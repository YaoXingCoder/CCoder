#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

/*
Date:2024.06.12
Title:�Ż�ð������
Content:
1.��������������ж�����ж�
2.qsort����ʹ��
*/

void bullbleSort1(int arr[], int sz);
void bullbleSort2(int arr[], int sz);
int cmp_int(const void* e1, const void* e2);

int main(void) {
	int arr[] = { 9,2,3,7,8,4,6 };
	int sz = sizeof(arr) / sizeof(arr[0]);
	qsort(arr, sz, sizeof(arr[0]), cmp_int);
	for (int i = 0; i < sz; i++) {
		printf("%d ", arr[i]);
	}
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
			if (arr[i] > arr[j]) {
				int temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
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
		int flag = 0;
		for (int j = 0; j < sz - 1 - i; j++) {
			if (arr[i] > arr[j]) {
				int temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
				flag = 1;
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
/*
��Ҫ����qsort�����ıȽ����ͺ���
*/
int cmp_int(const void* e1, const void* e2) {
	return *(int*)e2 - *(int*)e1;
}
