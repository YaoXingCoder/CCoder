/*********************************
Date:2024.6.27
Title:归并排序实现
Author:JiaZiChunQiu
Content:
请实现归并排序，并分析它的时间复杂度，空间复杂度和稳定性
void merge_sort(int arr[], int n);
时间复杂度：
无论什么情况，都会执行递归，深度总会达到logn的高度
每层都会进行n次的比较相乘nlogn
空间复杂度：
递归深度是O(logn)
但需要长度与n相同的数组辅助
所以为O(n)
稳定性：稳定
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
	
	// 复制
	for (int i = left; i <= right; i++) {
		arr[i] = tmp[i];
	}
}

void divideSort(int arr[], int left, int right) {
	if (left >= right) return; // 递归出口
	int mid = left + (right - left >> 1);

	divideSort(arr, left, mid); // 分解到仅有一个元素结束，此时left<=right
	divideSort(arr, mid + 1, right); // 分解

	merge(arr, left, mid, right); // 合并
}

/*
* 归并排序
*/
void mergeSort(int arr[], int len) {
	// 递归函数
	divideSort(arr, 0, len - 1);

}

int main(void) {
	int arr[] = { 10,2,5,3,4,5,1,6,3,2 };
	int sz = sizeof(arr) / sizeof(arr[0]);
	mergeSort(arr, sz);
	printAll(arr, sz);
	return 0;
}
