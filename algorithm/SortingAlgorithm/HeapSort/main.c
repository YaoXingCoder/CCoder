/*********************************
Date:2024.6.28
Title:堆排序实现
Author:JiaZiChunQiu
Content:

**********************************/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define ARRSIZE(arr) (sizeof(arr)/sizeof(arr[0]))
#define SWAP(arr, i, j) {	\
	int tmp = arr[i];		\
	arr[i] = arr[j];		\
	arr[j] = tmp;			\
}

static void heapify(int arr[], int heap_len, int idx);

void printArr(int arr[], int len) {
	for (int i = 0; i < len; i++) {
		printf("%d ", arr[i]);
	}
}

/*
* 自上而下的堆化，若交换元素则继续从交换元素的结点开始
* arr[]，需要推排序的数组
* heapLen，数组元素个数，即结点个数
* rootIdx，开始排序的非叶子结点位置
*/
static void heapify(int arr[], int heapLen, int rootIdx) {
	if (((rootIdx << 1) + 1) >= heapLen) return; // 递归出口

	// 左右子树元素
	int maxIdx = rootIdx;
	int lchildIdx = (rootIdx << 1) + 1;
	int rchildIdx = (rootIdx << 1) + 2;

	// 分别与两个子节点比较，获取最大值的子节点的位置
	if (lchildIdx < heapLen && arr[maxIdx] < arr[lchildIdx]) maxIdx = lchildIdx;
	if (rchildIdx < heapLen && arr[maxIdx] < arr[rchildIdx]) maxIdx = rchildIdx;

	// 将最大值子节点与根节点交换，继续堆子节点进行大堆化
	if (maxIdx != rootIdx) {
		SWAP(arr, maxIdx, rootIdx);
		rootIdx = maxIdx;
		heapify(arr, heapLen, rootIdx);
	}
}

/*
* 自下而上整体堆化
* arr，待堆化数组
* len，数组长度
*/
void firstHeap(int arr[], int len) {
	int lastRootIdx = (len - 2) >> 1;
	// 每次排序父节点
	for (int i = lastRootIdx; i >= 0; i--) {
		heapify(arr, len, i);
	}
}

/*
* 堆排序入口
* arr：待排序数组
* len: 数组长度
*/
void heapSort(int arr[], int len) {
	// 先全部大堆化
	firstHeap(arr, len);
	
	// 循环将首尾交换，并堆化，每次长度-1
	while (len > 0) {
		SWAP(arr, 0, len - 1);
		len--;
		heapify(arr, len, 0);
	}
}


int main(void) {
	int arr[] = { 4, 10, 3, 5, 1, 7, 2};
	//heapify(arr, ARRSIZE(arr), 0);
	heapSort(arr, ARRSIZE(arr));
	printArr(arr, ARRSIZE(arr));
	return 0;
}
