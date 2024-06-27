/*********************************
Date:2024.6.27
Title:冒泡排序实现
Author:JiaZiChunQiu
Content:
请实现插入排序，并分析它的时间复杂度，空间复杂度和稳定性
void insertion_sort(int arr[], int n);
时间复杂度：
使用元素后移：最好一次不用移动，但比较仍需要(n-1)
使用元素后移：最坏移动和比较是同步的，都是n*(n-1)/2 次所以：O(n^2^)
空间复杂度：原地算法O(1)
稳定性：稳定，若条件改为（>=  / <=） 带等于则不稳定
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

/* 
* 插入排序
*/
void insertionSort1(int arr[], int len) {
	// 默认第一张有序
	for (int i = 1; i < len; i++) {
		for (int j = i - 1; j >= 0; j--) {
			if (arr[j] > arr[j + 1]) {
				SWAP(arr, j, j + 1);
			}
		}// j = -1 || 
		printAll(arr, len);
	}
}

void insertionSort2(int arr[], int len) {
	// 默认第一张有序
	for (int i = 0; i < len - 1; i++) {
		int tmp = arr[i + 1];
		int j = i;
		for (; j >= 0; j--) {
			if (tmp < arr[j]) {
				arr[j + 1] = arr[j];
			} else {
				break;
			}
		}// j = -1 || tmp = arr[j - 1];
		arr[j+1] = tmp;
		printAll(arr, len);
	}
}

int main(void) {
	int arr[] = { 10,2,5,3,4,5,1,6,3,2 };
	int sz = sizeof(arr) / sizeof(arr[0]);
	//insertionSort1(arr, sz);
	insertionSort2(arr, sz);
	return 0;
}

