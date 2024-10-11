#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/*
Date:2024.6.16
Title:代码练习
Content:
1.矩阵转置
2.
*/

/*
矩阵
*/
void matrixTranspose(int (*dest)[10], int (*src)[3], int row, int column) {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			dest[j][i] = src[i][j];
		}
	}
}


/*
输入一个整数序列，判断是否有序序列
有序，序列中的整数从小到大排序或从大到小（相同元素视为有序）

第一行输入一个整数N(3≤N≤50)。
第二行输入N个整数，用空格分隔N个整数。
输出为一行，如果序列有序输出sorted，否则输出unsorted。

输入：5
1 6 9 22 30
sorted

思路：
判断首元素和末尾元素是升序还是降序
再判断升序/降序中是否有降序/升序的一对数字
有：break;
无：循环遍历结束
判断count是否为len-1
是：返回1，是升序/降序
否：返回0，不是有序序列
*/
int judgeSequence(int arr[], int sz) {
	int count = 0;
	int len = sz - 1;
	if (arr[0] > arr[sz-1]) {
		for (int i = 0; i < sz - 1; ++i) {
			if (arr[i] < arr[i + 1]) break;
			count++;
		}
	}
	if (arr[0] < arr[sz-1]) {
		for (int i = 0; i < sz - 1; ++i) {
			if (arr[i] > arr[i + 1]) break;
			count++;
		}
	}
	if (count == len - 1) return 1;
	else return 0;
}

/*
主函数
*/
int main(void) {
	// 1.矩阵转置
	//int arr1[2][3] = { 1,2,3,4,5,6 };
	//int arr2[10][10] = { 0 };
	//int row = sizeof(arr1) / sizeof(arr1[0]);
	//int column = sizeof(arr1[0]) / sizeof(arr1[0][0]);
	//matrixTranspose(arr2, arr1, row, column);
	//for (int i = 0; i < 10; i++) {
	//	for (int j = 0; j < 10; j++) {
	//		printf("%d ", arr2[i][j]);
	//	}
	//	putchar('\n');
	//}

	// 2.判断序列
	int arr[] = { 1,2,9,4,5,6 };
	int sz = sizeof(arr) / sizeof(arr[0]);
	int ret = judgeSequence(arr, sz);
	if (ret) {
		printf("is Ordered sequence\n");
	} else {
		printf("Not ordered sequence\n");
	}
	return 0;
}
