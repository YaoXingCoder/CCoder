/*********************************
Date:2024.6.27
Title:将数组随机打乱
Author:JiaZiChunQiu
Content:
给定一个排好序的数组，请设计一个算法将数组随机打乱。
(尽量让数组足够乱，也就是说，数组元素的每一种排列最好是等概率的)
void shuffle(int arr[], int n)
**********************************/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

/* 将数组打乱 */
void shuffle(int arr[], int len) {
	int randNum;
	for (int i = 0; i < len; i++) {
		randNum = rand() % len;
		SWAP(arr, i, randNum);
	}
}

int main(void) {
	srand((unsigned int)time(NULL));
	int arr[] = { 1,2,3,4,5,6,7,8,9,10 };
	int sz = sizeof(arr) / sizeof(arr[0]);
	shuffle(arr, sz);
	printAll(arr, sz);
	return 0;
}
