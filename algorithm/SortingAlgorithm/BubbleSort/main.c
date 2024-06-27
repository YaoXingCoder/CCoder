/*********************************
Date:2024.6.27
Title:冒泡排序实现
Author:JiaZiChunQiu
Content:
请实现冒泡排序，并分析它的时间复杂度，空间复杂度和稳定性
void bubble_sort(int arr[], int n);
时间复杂度：
	最好最坏都需要比较 n*(n-1) / 2次
	最好交换：0次
	最坏交换：n -1 次
	所以：O(n^2^)
空间复杂度：
	原地算法，O(1)
稳定性：
	稳定的
**********************************/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define SWAP(arr, i, j) {	\
	int tmp = arr[i];		\
	arr[i] = arr[j];		\
	arr[j] = tmp;			\
} // 交换数组中两个坐标位置

/* 打印所有元素 */
void printAll(int arr[], int len) {
	for (int i = 0; i < len; i++) {
		printf("%d ", arr[i]);
	}
	putchar('\n');
}

/* 冒泡排序 */
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