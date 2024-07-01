/*********************************
Date:2024.6.27
Title:�������������
Author:JiaZiChunQiu
Content:
����һ���ź�������飬�����һ���㷨������������ҡ�
(�����������㹻�ң�Ҳ����˵������Ԫ�ص�ÿһ����������ǵȸ��ʵ�)
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
} // ������������������λ��

/* ��ӡ����Ԫ�� */
void printAll(int arr[], int n) {
	for (int i = 0; i < n; i++) {
		printf("%d ", arr[i]);
	}
	putchar('\n');
}

/* ��������� */
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
