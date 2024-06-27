/*********************************
Date:2024.6.27
Title:ѡ������ʵ��
Author:JiaZiChunQiu
Content:
��ʵ��ѡ�����򣬲���������ʱ�临�Ӷȣ��ռ临�ӶȺ��ȶ���
void selection_sort(int arr[], int n);
ʱ�临�Ӷȣ���������Ҫn-1�Ƚϣ�n*(n-1)/2�ν���������Ϊ��O(n^2^)
�ռ临�Ӷȣ���Ϊ����ԭ����ȽϽ�����Ϊԭ���㷨�����ԣ�O(1)
�ȶ��ԣ����ȶ�����ʹ��ͬ����Ԫ��Ҳ��Ҫ���һ�ν���
**********************************/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define SWAP(arr, i, j) {	\
	int tmp = arr[i];		\
	arr[i] = arr[j];		\
	arr[j] = tmp;			\
} // ������������������λ��

/* ��ӡ����Ԫ�� */
void printAll(int arr[], int n) {
	for (int i = 0; i < n; i++) {
		printf("%d ", arr[i]);
	}
	putchar('\n');
}

/* ѡ������ */
void selectionSort(int arr[], int n) {
	for (int i = 0; i < n; i++) {
		int minIndex = i; // Ĭ��iλ����С
		for (int j = i + 1; j < n; j++) {
			if (arr[j] < arr[minIndex]) {
				minIndex = j; // ��ȡ��СԪ�ص��±�
			}
		}
		SWAP(arr, minIndex, i); // iλ�õ�Ԫ������СԪ�ؽ���
		printAll(arr, n); // ÿȷ��һλ��ӡһ��
	}
}

int main(void) {
	int arr[] = { 1,10,2,5,3,4,5,6,3,2 };
	int sz = sizeof(arr) / sizeof(arr[0]);
	selectionSort(arr, sz);
	return 0;
}
