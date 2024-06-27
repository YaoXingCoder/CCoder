/*********************************
Date:2024.6.27
Title:ð������ʵ��
Author:JiaZiChunQiu
Content:
��ʵ��ð�����򣬲���������ʱ�临�Ӷȣ��ռ临�ӶȺ��ȶ���
void bubble_sort(int arr[], int n);
ʱ�临�Ӷȣ�
	��������Ҫ�Ƚ� n*(n-1) / 2��
	��ý�����0��
	�������n -1 ��
	���ԣ�O(n^2^)
�ռ临�Ӷȣ�
	ԭ���㷨��O(1)
�ȶ��ԣ�
	�ȶ���
**********************************/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define SWAP(arr, i, j) {	\
	int tmp = arr[i];		\
	arr[i] = arr[j];		\
	arr[j] = tmp;			\
} // ������������������λ��

/* ��ӡ����Ԫ�� */
void printAll(int arr[], int len) {
	for (int i = 0; i < len; i++) {
		printf("%d ", arr[i]);
	}
	putchar('\n');
}

/* ð������ */
void bubbleSort(int arr[], int len) {
	for (int i = 0; i < len - 1; i++) {
		for (int j = 0; j < len - 1 - i; j++) {
			if (arr[j] > arr[j + 1]) {
				SWAP(arr, j, j + 1);
			}
		}
		printAll(arr, len);
	}
}

int main(void) {
	int arr[] = { 1,10,2,5,3,4,5,6,3,2 };
	int sz = sizeof(arr) / sizeof(arr[0]);
	bubbleSort(arr, sz);
	return 0;
}