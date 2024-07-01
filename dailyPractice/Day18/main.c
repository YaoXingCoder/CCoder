/*********************************
Date:2024.7.1
Title:ÿ����ϰ
Author:JiaZiChunQiu
Content:
**********************************/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define ARR_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))
#define SWAP(arr, i, j) {	\
		int tmp = arr[i];	\
		arr[i] = arr[j];	\
		arr[j] = tmp;		\
}

/*
����һ�����飬������������תkλ.

void rotateLeft(int arr[], int n, int k);

���룺[0, 1, 2, 3, 4, 5, 6, 7, 8], k = 0
�����[0, 1, 2, 3, 4, 5, 6, 7, 8]

���룺[0, 1, 2, 3, 4, 5, 6, 7, 8], k = 3
�����[3, 4, 5, 6, 7, 8, 0, 1, 2]

���룺[0, 1, 2, 3, 4, 5, 6, 7, 8], k = 10
�����[1, 2, 3, 4, 5, 6, 7, 8, 0]
*/


// /* ������ӡ */
//void printArr(int arr[], int len) {
//	for (int i = 0; i < len; i++) {
//		printf("%d ", arr[i]);
//	}
//}
//
// /* ���齻�� */
//void reverseArr(int arr[], int left, int right) {
//	int tmp;
//	while (left < right) {
//		SWAP(arr, left, right);
//		left++;
//		right--;
//	}
//}
//
// /* �������� */
//void rotateLeftArr(int arr[], int len, int k) {
//	k %= len; // ��ֹԽ�����
//	
//	reverseArr(arr, 0, k - 1); // ���
//	reverseArr(arr, k, len - 1); // �ұ�
//	reverseArr(arr, 0, len - 1); // ����
//}
//
// /* ������ */
//int main(void) {
//	int arr[9] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
//	rotateLeftArr(arr, ARR_SIZE(arr), 10);
//	printArr(arr, ARR_SIZE(arr));
//	return 0;
//}


/*
����һ������������������ת k λ

Node* rotateRight(Node* head, int k);

����: 2 --> 3 --> 5 --> 4 --> 9 --> 6, k = 0
�����2 --> 3 --> 5 --> 4 --> 9 --> 6

����: 2 --> 3 --> 5 --> 4 --> 9 --> 6, k = 2
�����9 --> 6 --> 2 --> 3 --> 5 --> 4

����: 2 --> 3 --> 5 --> 4 --> 9 --> 6, k = 9
�����4 --> 9 --> 6 --> 2 --> 3 --> 5
*/

//typedef int ElementType;
//
//typedef struct LinkedNode {
//	ElementType key;
//	struct LinkedNode* next;
//}LNode;
//
//typedef struct {
//	int size;
//	LNode* head;
//}LinkedList;
//
// /* ����ͷβ��� */
//void reverseNode(LinkedList* list) {
//	LNode* prev = NULL;
//	LNode* curr = list->head;
//
//	// �ҵ�β���
//	while (curr->next) {
//		prev = curr;
//		curr = curr->next;
//	}
//
//	// ����
//	curr->next = list->head;
//	prev->next = NULL;
//	list->head = curr;
//}
//
// /* �������� */
//void rotateRight(LinkedList* list, int k) {
//	k %= list->size;
//	while (k) {
//		reverseNode(list);
//		k--;
//	}
//}
//
//
// /* ������ */
//int main(void) {
//	LNode n6 = { 6, NULL};
//	LNode n9 = { 9, &n6};
//	LNode n4 = { 4, &n9};
//	LNode n5 = { 5, &n4};
//	LNode n3 = { 3, &n5};
//	LNode n2 = { 2, &n3};
//	LinkedList list = { 6, &n2 };
//
//	rotateRight(&list, 9);
//
//	return 0;
//}
