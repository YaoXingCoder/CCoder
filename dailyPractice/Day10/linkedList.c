#include "linkedList.h"

/*
Date:2024.6.21
Title:每日练习Day10
Content:
1.头插法
2.尾插法
3.顺序插入
*/

/*
1.头插入
*/
void add_before_head(Node** phead, Node** ptail, int val) {
	// 创建节点
	Node* newNode = malloc(sizeof(Node));
	if (!newNode) {
		perror("add_before_head");
		return;
	}
	// 节点初始化，若头指针为NULL，则尾指针也定为NULL，初始化
	if (!*phead) {
		*phead = newNode;
		*ptail = newNode;
		newNode->data = val;
	} else {
		newNode->next = *phead;
		*phead = newNode;
		newNode->data = val;
	}
}

/*
2.尾插法
*/
void add_behind_tail(Node** phead, Node** ptail, int val) {
	// 创建节点
	Node* newNode = malloc(sizeof(Node));
	if (!newNode) {
		perror("add_behind_tail");
		return;
	}
	newNode->data = val;
	newNode->next = NULL;

	// 节点初始化
	if (!ptail) {
		*ptail = newNode;
		*phead = newNode;
	} else {
		(*ptail)->next = newNode;
		*ptail = newNode;
	}
}

/*
3.实现顺序插入
*/
void add_in_sort(Node** phead, Node** ptail, int val) {
	// 创建节点
	Node* newNode = malloc(sizeof(Node));
	if (!newNode) {
		perror("add_in_sort");
		return;
	}
	newNode->data = val;
	newNode->next = NULL;

	// 没有指针，作为第一个插入
	if (!*phead) {
		*phead = newNode;
		*ptail = newNode;
		return;
	}

	// 第一个就是要插入的位置
	if ((*phead)->data > val) {
		newNode->next = *phead;
		*phead = newNode;
		return;
	}

	// 找到应插入节点位置
	Node* curNode = *phead;
	while (curNode->next) {
		if (curNode->next->data > val) break;
		curNode = curNode->next;
	} // curNode.next = NULL || curNode->next->data

	// 插入
	newNode->next = curNode->next;
	curNode->next = newNode;

	// 如果作为组后一个插入
	if (curNode == *ptail) {
		*ptail = newNode;
	}
}