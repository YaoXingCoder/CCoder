#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/*
Date:2024.6.16
Title:������ϰ
Content:
1.����ת��
2.
*/

/*
����
*/
void matrixTranspose(int (*dest)[10], int (*src)[3], int row, int column) {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			dest[j][i] = src[i][j];
		}
	}
}


/*
����һ���������У��ж��Ƿ���������
���������е�������С���������Ӵ�С����ͬԪ����Ϊ����

��һ������һ������N(3��N��50)��
�ڶ�������N���������ÿո�ָ�N��������
���Ϊһ�У���������������sorted���������unsorted��

���룺5
1 6 9 22 30
sorted

˼·��
�ж���Ԫ�غ�ĩβԪ���������ǽ���
���ж�����/�������Ƿ��н���/�����һ������
�У�break;
�ޣ�ѭ����������
�ж�count�Ƿ�Ϊlen-1
�ǣ�����1��������/����
�񣺷���0��������������
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
������
*/
int main(void) {
	// 1.����ת��
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

	// 2.�ж�����
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
