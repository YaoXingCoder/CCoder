/*********************************
Date:2024.6.28
Title:������ʵ��
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
* ���϶��µĶѻ���������Ԫ��������ӽ���Ԫ�صĽ�㿪ʼ
* arr[]����Ҫ�����������
* heapLen������Ԫ�ظ�������������
* rootIdx����ʼ����ķ�Ҷ�ӽ��λ��
*/
static void heapify(int arr[], int heapLen, int rootIdx) {
	if (((rootIdx << 1) + 1) >= heapLen) return; // �ݹ����

	// ��������Ԫ��
	int maxIdx = rootIdx;
	int lchildIdx = (rootIdx << 1) + 1;
	int rchildIdx = (rootIdx << 1) + 2;

	// �ֱ��������ӽڵ�Ƚϣ���ȡ���ֵ���ӽڵ��λ��
	if (lchildIdx < heapLen && arr[maxIdx] < arr[lchildIdx]) maxIdx = lchildIdx;
	if (rchildIdx < heapLen && arr[maxIdx] < arr[rchildIdx]) maxIdx = rchildIdx;

	// �����ֵ�ӽڵ�����ڵ㽻�����������ӽڵ���д�ѻ�
	if (maxIdx != rootIdx) {
		SWAP(arr, maxIdx, rootIdx);
		rootIdx = maxIdx;
		heapify(arr, heapLen, rootIdx);
	}
}

/*
* ���¶�������ѻ�
* arr�����ѻ�����
* len�����鳤��
*/
void firstHeap(int arr[], int len) {
	int lastRootIdx = (len - 2) >> 1;
	// ÿ�����򸸽ڵ�
	for (int i = lastRootIdx; i >= 0; i--) {
		heapify(arr, len, i);
	}
}

/*
* ���������
* arr������������
* len: ���鳤��
*/
void heapSort(int arr[], int len) {
	// ��ȫ����ѻ�
	firstHeap(arr, len);
	
	// ѭ������β���������ѻ���ÿ�γ���-1
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
