/*********************************
Date:2024.6.22
Title:带头结点的单向链表
Author:JiaZiChunQiu
Content:
**********************************/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "singleLinkedList.h"

/*
创建初始化
*/
LinkedList* createLinkedList(void) {
	// 链表 开辟空间 LinkedList
	LinkedList* newList = (LinkedList*)calloc(1, sizeof(LinkedList));
	if (!newList) {
		perror("newList");
		return NULL;
	}
	
	// 头节点/尾节点 开辟空间 LNode
	newList->head = (LNode*)calloc(1, sizeof(LNode));
	newList->tail = (LNode*)calloc(1, sizeof(LNode));
	if (!newList->head || !newList->tail) {
		free(newList->head);
		free(newList->tail);
		free(newList);
		perror("newList->head or newList -> tail");
		return NULL;
	}

	// 返回链表地址
	return newList;
}

/*
销毁所有结点
*/
void destoryAllNodes(LinkedList* list) {
	assert(list);
	// 0个结点
	if (!list->size) {
		printf("LinkedList has no Node");
		return;
	}
	LNode* curr = list->head->next;
	while (curr) {
		LNode* temp = curr->next;
		free(curr);
		curr = temp;
	} // curr = NULL，逐一释放结点
	list->head = NULL;
	list->tail = NULL;
	list->size = 0;
}

/*
销毁链表
*/
void destoryLinkedList(LinkedList* list) {
	assert(list);
	if (!list) {
		printf("LinkedList is NULL");
		return;
	}
	destoryAllNodes(list);
	free(list->head);
	free(list->tail);
	free(list);
}

bool isEmpty(LinkedList* list) {
	if (!list) {
		return true;
	}
	if (!list->size) {
		return true;
	}
	return false;
}

/*
头插法
*/
bool insert_head(LinkedList* list, const E val) {
	assert(list);
	// 新结点
	LNode* newNode = (LNode*)calloc(1, sizeof(LNode));
	if (!newNode) {
		perror("insert_head:newNode");
		return false;
	}
	newNode->data = val;

	// 插入
	newNode->next = list->head->next;
	list->head->next = newNode;

	// 尾结点检查
	if (!list->tail->next) {
		list->tail->next = newNode;
	}

	// 链表大小
	list->size++;

	return true;
}

/*
尾插
*/
bool insert_tail(LinkedList* list, const E val) {
	// 新结点
	assert(list);
	LNode* newNode = (LNode*)calloc(1, sizeof(LNode));
	if (!newNode) {
		perror("insert_head:newNode");
		return false;
	}
	newNode->data = val;

	// 插入
	list->tail->next->next = newNode;
	list->tail->next = newNode;

	// 头结点检查
	if (!list->head->next) {
		list->head->next = newNode;
	}

	// 链表大小++
	list->size++;
	return true;
}

/*
按位置插
*/
bool insert_pos(LinkedList* list, const int index, const E val) {
	// 位置有效性
	if (index < 0 || index > list->size) {
		printf("index is invalid position!\n");
		return false;
	}

	// 新结点
	assert(list);
	LNode* newNode = (LNode*)calloc(1, sizeof(LNode));
	if (!newNode) {
		perror("insert_head:newNode");
		return false;
	}
	newNode->data = val;

	// index = 0 为头插，index = size 为尾插
	if (index == 0) {
		if (insert_head(list, val)) return true;
		else return false;
	} else if (index == list->size) {
		if (insert_tail(list, val)) return true;
		else return false;
	}

	// 遍历寻找位置，并插入
	LNode* curr = list->head->next;
	for (int i = 0; i < index - 1; i++) {
		curr = curr->next;
	}
	newNode->next = curr->next;
	curr->next = newNode;

	// 结点大小++
	list->size++;
	return true;
}

/*
头删
*/
bool delete_head(LinkedList* list) {
	assert(list);
	if (isEmpty(list)) {
		printf("LinkedList has no Node");
		return false;
	}

	// 只有一个结点可以删除
	LNode* curr = list->head->next;
	if (list->size == 1) {
		free(curr);
		list->head->next = NULL;
		list->tail->next = NULL;
		list->size--;
		return true;
	}

	list->head->next = curr->next;
	list->size--;
	free(curr);
	return true;
}

/*
尾删
*/
bool delete_tail(LinkedList* list) {
	assert(list);
	if (!list->size) {
		printf("LinkedList has no Node");
		return false;
	}

	// 只有一个结点可以删除
	LNode* curr;
	if (list->size == 1) {
		curr = list->tail->next;
		free(curr);
		list->head->next = NULL;
		list->tail->next = NULL;
		list->size--;
		return true;
	}

	curr = list->head->next;
	while (curr->next->next) {
		curr = curr->next;
	}
	list->tail->next = curr;
	curr = curr->next;
	list->tail->next->next = NULL;
	free(curr);
	list->size--;
	return true;
}

/*
位置删
*/
bool delete_pos(LinkedList* list, int index) {
	assert(list);
	if (isEmpty(list)) {
		printf("LinkedList has no Node");
		return false;
	}
	// 位置有效性
	if (index < 0 || index > list->size) {
		printf("index is invalid position!\n");
		return false;
	}

	//index = size 为尾删
	if (index == list->size) {
		if (delete_tail(list)) return true;
		else return false;
	}

	// 需要两个结点，一个当前需要删除的结点，一个前置结点用于链接下一个结点
	LNode* pre = list->head;
	LNode* curr = list->head->next;
	while (--index) {
		pre = curr;
		curr = curr->next;
	}
	pre->next = curr->next;
	free(curr);
	list->size--;
	return true;
}

/*
按值删2.0
*/
bool delete_val(LinkedList* list, const E val) {
	assert(list);
	if (isEmpty(list)) {
		printf("LinkedList has no Node");
		return false;
	}
	LNode* curr = first_val(list, val);
	if (!curr) {
		printf("the value is not in list");
		return false;
	}
	LNode* pre = list->head->next;
	for ( ; pre->next != curr ; pre = pre->next) {
		;
	}
	if (list->tail->next == curr) {
		list->tail->next = pre;
	}
	pre->next = curr->next;
	free(curr);
	list->size--;
	return true;
}

/*
返回val第一次出现的结点
*/
LNode* first_val(const LinkedList* list, const E val) {
	assert(list);
	if (isEmpty(list)) {
		printf("LinkedList has no Node");
		return NULL;
	}

	LNode* curr = list->head->next;
	while (curr->next) {
		if (curr->data == val) return curr;
		curr = curr->next;
	}
	return NULL;
}

/*
打印所有结点值
*/
void printAllNodes(const LinkedList* list) {
	if (isEmpty(list)) {
		printf("LinkedList has no Node");
		return;
	}

	LNode* curr = list->head->next;
	for (int i = 0; i < list->size; i++) {
		printf("%d", curr->data);
		if (i != list->size - 2) {
			printf("-->");
		}
		curr = curr->next;
	}
}


/*
按值删除1.0
*/
//bool delete_val(LinkedList* list, const E val) {
//	assert(list);
//
//	int index = list->size - 1;
//	// 需要两个结点，一个当前需要删除的结点，一个前置结点用于链接下一个结点
//	LNode* pre = list->head;
//	LNode* curr = list->head->next;
//	while (index--) {
//		if (curr->data == val) break;
//		pre = curr;
//		curr = curr->next;
//	}
//	if (!index) {
//		printf("The value is not in list\n");
//		return false;
//	} else {
//		if (curr = list->tail->next) {
//			list->tail->next = pre;
//			free(curr);
//			list->size--;
//			return true;
//		} else {
//			pre->next = curr->next;
//			free(curr);
//			list->size--;
//			return true;
//		}
//	}
//}