/*********************************
Date:2024.7.1
Title:每日练习
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
给定一个数组，将数组向左旋转k位.

void rotateLeft(int arr[], int n, int k);

输入：[0, 1, 2, 3, 4, 5, 6, 7, 8], k = 0
输出：[0, 1, 2, 3, 4, 5, 6, 7, 8]

输入：[0, 1, 2, 3, 4, 5, 6, 7, 8], k = 3
输出：[3, 4, 5, 6, 7, 8, 0, 1, 2]

输入：[0, 1, 2, 3, 4, 5, 6, 7, 8], k = 10
输出：[1, 2, 3, 4, 5, 6, 7, 8, 0]
*/


// /* 遍历打印 */
//void printArr(int arr[], int len) {
//	for (int i = 0; i < len; i++) {
//		printf("%d ", arr[i]);
//	}
//}
//
// /* 数组交换 */
//void reverseArr(int arr[], int left, int right) {
//	int tmp;
//	while (left < right) {
//		SWAP(arr, left, right);
//		left++;
//		right--;
//	}
//}
//
// /* 左旋数组 */
//void rotateLeftArr(int arr[], int len, int k) {
//	k %= len; // 防止越界访问
//	
//	reverseArr(arr, 0, k - 1); // 左边
//	reverseArr(arr, k, len - 1); // 右边
//	reverseArr(arr, 0, len - 1); // 整体
//}
//
// /* 主函数 */
//int main(void) {
//	int arr[9] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
//	rotateLeftArr(arr, ARR_SIZE(arr), 10);
//	printArr(arr, ARR_SIZE(arr));
//	return 0;
//}


/*
给定一个链表，将链表向右旋转 k 位

Node* rotateRight(Node* head, int k);

输入: 2 --> 3 --> 5 --> 4 --> 9 --> 6, k = 0
输出：2 --> 3 --> 5 --> 4 --> 9 --> 6

输入: 2 --> 3 --> 5 --> 4 --> 9 --> 6, k = 2
输出：9 --> 6 --> 2 --> 3 --> 5 --> 4

输入: 2 --> 3 --> 5 --> 4 --> 9 --> 6, k = 9
输出：4 --> 9 --> 6 --> 2 --> 3 --> 5
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
// /* 交换头尾结点 */
//void reverseNode(LinkedList* list) {
//	LNode* prev = NULL;
//	LNode* curr = list->head;
//
//	// 找到尾结点
//	while (curr->next) {
//		prev = curr;
//		curr = curr->next;
//	}
//
//	// 交换
//	curr->next = list->head;
//	prev->next = NULL;
//	list->head = curr;
//}
//
// /* 右旋链表 */
//void rotateRight(LinkedList* list, int k) {
//	k %= list->size;
//	while (k) {
//		reverseNode(list);
//		k--;
//	}
//}
//
//
// /* 主函数 */
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
