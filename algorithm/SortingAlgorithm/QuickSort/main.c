/*********************************
Date:2024.6.27
Title:快速排序实现
Author:JiaZiChunQiu
Content:
请实现快速排序，并分析它的时间复杂度，空间复杂度和稳定性
void quickSort(int arr[], int len);

时间复杂度：
最好基准值每次在中间：递归深度为O(logn)；比较次数为约n/2；赋值次数，比较即赋值为n/2。总操作次数为nlogn
最差基准值每次在最左/右：递归深度为O(n)；比较次数为n*(n-1)/2；赋值次数，比较即赋值n(n-1)/2。总操作次数为n^2^
空间复杂度：
最好：O(logn)
最坏：O(n)
稳定性：不稳定
**********************************/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>


/* 打印所有元素 */
void printAll(int arr[], int n) {
	for (int i = 0; i < n; i++) {
		printf("%d ", arr[i]);
	}
	putchar('\n');
}


/*
* 分区
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
* 递归
*/
void partRecursion(int arr[], int left, int right) {
	if (left >= right) return; // 出口
	
	// 获取分区的点
	int idx = partition(arr, left, right);
	partRecursion(arr, left, idx - 1); // 分区不包括基准点
	partRecursion(arr, idx + 1, right);
}

/*
* 快速排序
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

