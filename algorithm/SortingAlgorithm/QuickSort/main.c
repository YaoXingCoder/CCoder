/*********************************
Date:2024.6.27
Title:��������ʵ��
Author:JiaZiChunQiu
Content:
��ʵ�ֿ������򣬲���������ʱ�临�Ӷȣ��ռ临�ӶȺ��ȶ���
void quickSort(int arr[], int len);

ʱ�临�Ӷȣ�
��û�׼ֵÿ�����м䣺�ݹ����ΪO(logn)���Ƚϴ���ΪԼn/2����ֵ�������Ƚϼ���ֵΪn/2���ܲ�������Ϊnlogn
����׼ֵÿ��������/�ң��ݹ����ΪO(n)���Ƚϴ���Ϊn*(n-1)/2����ֵ�������Ƚϼ���ֵn(n-1)/2���ܲ�������Ϊn^2^
�ռ临�Ӷȣ�
��ã�O(logn)
���O(n)
�ȶ��ԣ����ȶ�
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


/*
* ����
*/
int partition(int arr[], int left, int right) {
	int pivot = arr[left];
	int low = left, high = right;
	while (low < high) {
		while (low < high && arr[high] >= pivot) {
			high--;
		}
		arr[low] = arr[high];
		while (low < high && arr[low] <= pivot) {
			low++;
		}
		arr[high] = arr[low];
	} // low = high
	arr[low] = pivot;
	return low;
}

/*
* �ݹ�
*/
void partRecursion(int arr[], int left, int right) {
	if (left >= right) return; // ����
	
	// ��ȡ�����ĵ�
	int idx = partition(arr, left, right);
	partRecursion(arr, left, idx - 1); // ������������׼��
	partRecursion(arr, idx + 1, right);
}

/*
* ��������
*/
void quickSort(int arr[], int len) {
	partRecursion(arr, 0, len - 1);
}

int main(void) {
	int arr[] = { 10,2,5,3,4,5,1,6,3,2 };
	int sz = sizeof(arr) / sizeof(arr[0]);
	quickSort(arr, sz);
	printAll(arr, sz);
	return 0;
}

