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
	// 使用calloc可以自动初始化成员为默认零值,更加省事
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

	// 结点初始化
	newNode->data = val;
	newNode->next = list->head->next;

	// 插入
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
	// 分配一个新节点
	assert(list);
	LNode* newNode = (LNode*)calloc(1, sizeof(LNode));
	if (!newNode) {
		perror("insert_head:newNode");
		return false;
	}

	// 新节点初始化
	newNode->data = val;
	newNode->next = NULL;

	// 插入
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

	// index = 0 为头插，index = size 为尾插
	if (index == 0) {
		return (insert_head(list, val));
	}  	
	if (index == list->size) {
		return (insert_tail(list, val));
	}

	// 新结点
	assert(list);
	LNode* newNode = (LNode*)calloc(1, sizeof(LNode));
	if (!newNode) {
		perror("insert_head:newNode");
		return false;
	}
	newNode->data = val;


	// 遍历寻找位置，循环结束后, prev指针指向curr索引前面的一个结点
	LNode* curr = list->head->next;
	for (int i = 0; i < index - 1; i++) {
		curr = curr->next;
	}
	// 在index位置, 插入新结点. 
	// 该过程先让新结点指向curr的后继结点, 再让curr结点指向新结点
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
	// 判空
	assert(list);
	return (isEmpty(list));
	
	// 将头结点指向首结点的下个结点
	LNode* curr = list->head->next;
	list->head->next = curr->next;
	
	// 删除结点后长度为0，尾结点指向置空
	if (list->size - 1 == 0) {
		list->tail->next = NULL;
	
	}

	// 释放目标结点，长度-1
	free(curr);
	list->size--;
	return true;
}

/*
尾删
*/
bool delete_tail(LinkedList* list) {
	assert(list);
	return (isEmpty(list));
	
	// 找到尾结点的前驱结点
	LNode* curr = list->head;
	while (curr->next != list->tail->next) {
		curr = curr->next;
	}

	// 更改尾指针指向前驱结点，并将前驱结点指向置空
	list->tail->next = curr;
	curr = curr->next;
	list->tail->next->next = NULL;

	// 释放尾结点，长度-1
	free(curr);
	// 如果删除后长度=0，尾结点置空
	if (--list->size) {
		list->tail->next = NULL;
	};
	return true;
}

/*
位置删
*/
bool delete_pos(LinkedList* list, int index) {
	assert(list);
	// 链表是否为空
	return isEmpty(list);
	
	// 位置有效性
	if (index < 0 || index > list->size - 1) {
		printf("index is invalid position!\n");
		return false;
	}

	// 需要两个结点，一个当前需要删除的结点，一个前置结点用于链接下一个结点
	LNode* pre = list->head;
	LNode* curr = list->head->next;
	while (index--) {
		pre = curr;
		curr = curr->next;
	}

	// 将前驱结点指向目标节点的next
	pre->next = curr->next;
	// 若删除的尾结点
	if (list->tail->next = curr) {
		list->tail->next = pre;
	}
	free(curr);
	if (--list->size) {
		list->tail->next = NULL;
	}
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

	// 查找该值是否在链表中
	LNode* curr = first_val(list, val);
	if (!curr) {
		printf("the value is not in list");
		return false;
	}

	// 找到结点的前驱结点
	LNode* pre = list->head;
	for ( ; pre->next != curr ; pre = pre->next) {
		;
	}

	// 更新前驱结点指向删除结点的下一个结点
	pre->next = curr->next;
	// 如果尾结点指向需要删除的结点，将尾结点指向前驱结点，
	// 如果size = 1时，尾结点指向置空
	if (list->tail->next == curr) {
		list->tail->next = pre;
		if (list->size - 1 == 0) {
			list->tail->next = NULL;
		}
	}

	// 释放结点，大小-1
	free(curr);
	list->size--;
	return true;
}

/*
返回val第一次出现的结点
*/
LNode* first_val(const LinkedList* list, const E val) {
	assert(list);
	LNode* curr = list->head->next;
	if (!isEmpty(list)) {
		while (curr->next) {
			if (curr->data == val) return curr;
			curr = curr->next;
		}
	}
	return NULL;
}

/*
根据索引搜索结点
*/
LNode* find_by_index(const LinkedList* list, const E index) {
	// 位置有效性
	if (index < 0 || index > list->size - 1) {
		perror("find_by_index");
		return NULL;
	}

	LNode* curr = list->head->next;
	for (int i = 0; i < index; i++) {
		curr = curr->next;
	} // 循环结束时, curr指针就指向idx位置的结点
	
	return curr;
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