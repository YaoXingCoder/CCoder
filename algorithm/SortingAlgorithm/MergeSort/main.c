/*********************************
Date:2024.6.27
Title:�鲢����ʵ��
Author:JiaZiChunQiu
Content:
��ʵ�ֹ鲢���򣬲���������ʱ�临�Ӷȣ��ռ临�ӶȺ��ȶ���
void merge_sort(int arr[], int n);
ʱ�临�Ӷȣ�
����ʲô���������ִ�еݹ飬����ܻ�ﵽlogn�ĸ߶�
ÿ�㶼�����n�εıȽ����nlogn
�ռ临�Ӷȣ�
�ݹ������O(logn)
����Ҫ������n��ͬ�����鸨��
����ΪO(n)
�ȶ��ԣ��ȶ�
**********************************/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/* ��ӡ����Ԫ�� */
void printAll(int arr[], int n) {
	for (int i = 0; i < n; i++) {
		printf("%d ", arr[i]);
	}
	putchar('\n');
}

int tmp[10];

void merge(int arr[], int left, int mid, int right) {
	int tmpIdx = left, leftIdx = left, rightIdx = mid + 1;
	while (leftIdx <= mid && rightIdx <= right) {
		if (arr[leftIdx] <= arr[rightIdx]) {
			tmp[tmpIdx++] = arr[leftIdx++];
		} else {
			tmp[tmpIdx++] = arr[rightIdx++];
		}
	}
	while (leftIdx <= mid) {
		tmp[tmpIdx++] = arr[leftIdx++];
	}
	while (rightIdx <= right) {
		tmp[tmpIdx++] = arr[rightIdx++];
	}
	
	// ����
	for (int i = left; i <= right; i++) {
		arr[i] = tmp[i];
	}
}

void divideSort(int arr[], int left, int right) {
	if (left >= right) return; // �ݹ����
	int mid = left + (right - left >> 1);

	divideSort(arr, left, mid); // �ֽ⵽����һ��Ԫ�ؽ�������ʱleft<=right
	divideSort(arr, mid + 1, right); // �ֽ�

	merge(arr, left, mid, right); // �ϲ�
}

/*
* �鲢����
*/
void mergeSort(int arr[], int len) {
	// �ݹ麯��
	divideSort(arr, 0, len - 1);

}

int main(void) {
	int arr[] = { 10,2,5,3,4,5,1,6,3,2 };
	int sz = sizeof(arr) / sizeof(arr[0]);
	mergeSort(arr, sz);
	printAll(arr, sz);
	return 0;
}
