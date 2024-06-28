/*********************************
Date:2024.6.28
Title:二分查找
Author:JiaZiChunQiu
Content:
// 查找最后一个与 key 相等的元素
int binary_search1(int arr[], int n, int key);
// 查找最后一个小于等于 key 值的元素
int binary_search2(int arr[], int n, int key);
**********************************/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define ARRSIZE(arr) (sizeof(arr)/sizeof(arr[0]))


int binaryRecursion(int arr[], int left, int right, int target) {
	if (left > right) return -1;
	int mid = left + (right - left >> 1);
	int diff = target - arr[mid];
	if (diff < 0) {
		return binaryRecursion(arr, left, mid - 1, target);
	} else if (diff > 0) {
		return binaryRecursion(arr, mid + 1, right, target);
	}
	return mid;
}

/* 递归排序 */
int binarySearchRecursion(int arr[], int len, int target) {
	return binaryRecursion(arr, 0, len - 1, target);
}

// 查找最后一个与 key 相等的元素
int binarySearch1(int arr[], int len, int key) {
	int left = 0;
	int right = len - 1;
	int mid = 0;
	
	while (left <= right) {
		mid = left + (right - left >> 1);
		if (arr[mid] < key) {
			left = mid + 1;
		} else if (arr[mid] > key) {
			right = mid - 1;
		} else {
			if (left == right || arr[mid + 1] > key) return mid;
			left++; // 找到但不是最后一个，left++
		}
	} // left >= right 结束
	
	return -1;
}
// 查找最后一个小于等于 key 值的元素
int binarySearch2(int arr[], int len, int key) {
	int left = 0;
	int right = len - 1;
	int mid = 0;

	while (left <= right) {
		mid = left + (right - left >> 1);
		if (arr[mid] > key) {
			right = mid - 1;
		} else {
			if (left == right || arr[mid + 1] > key) return mid;
			left++; // 不是最后一个，left++
		}
	} // left >= right 结束

	return -1;
}

int main(void) {
	int arr[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 50, 50, 50, 50, 100 };
	//int ret = binarySearch1(arr, ARRSIZE(arr), 50);
	//int ret = binarySearch2(arr, ARRSIZE(arr), 15);
	int targetIdx = binarySearchRecursion(arr, ARRSIZE(arr), 8);
	return 0;
}
