/*********************************
Date:2024.6.27
Title:选择排序实现
Author:JiaZiChunQiu
Content:
请实现选择排序，并分析它的时间复杂度，空间复杂度和稳定性
void selection_sort(int arr[], int n);
时间复杂度：最好最坏都需要n-1比较，n*(n-1)/2次交换，所以为：O(n^2^)
空间复杂度：因为都在原数组比较交换，为原地算法，所以：O(1)
稳定性：不稳定，即使相同两个元素也需要完成一次交换
**********************************/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define SWAP(arr, i, j) {	\
	int tmp = arr[i];		\
	arr[i] = arr[j];		\
	arr[j] = tmp;			\
} // 交换数组中两个坐标位置

/* 打印所有元素 */
void printAll(int arr[], int n) {
	for (int i = 0; i < n; i++) {
		printf("%d ", arr[i]);
	}
	putchar('\n');
}

/* 选择排序 */
void selectionSort(int arr[], int n) {
	for (int i = 0; i < n; i++) {
		int minIndex = i; // 默认i位置最小
		for (int j = i + 1; j < n; j++) {
			if (arr[j] < arr[minIndex]) {
				minIndex = j; // 获取最小元素的下标
			}
		}
		SWAP(arr, minIndex, i); // i位置的元素与最小元素交换
		printAll(arr, n); // 每确定一位打印一次
	}
}

int main(void) {
	int arr[] = { 1,10,2,5,3,4,5,6,3,2 };
	int sz = sizeof(arr) / sizeof(arr[0]);
	selectionSort(arr, sz);
	return 0;
}
