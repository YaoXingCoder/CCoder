/*********************************
Date:2024.6.22
Title:��ͷ���ĵ�������
Author:JiaZiChunQiu
Content:
**********************************/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "singleLinkedList.h"

/*
������ʼ��
*/
LinkedList* createLinkedList(void) {
	// ���� ���ٿռ� LinkedList
	LinkedList* newList = (LinkedList*)calloc(1, sizeof(LinkedList));
	if (!newList) {
		perror("newList");
		return NULL;
	}
	
	// ͷ�ڵ�/β�ڵ� ���ٿռ� LNode
	newList->head = (LNode*)calloc(1, sizeof(LNode));
	newList->tail = (LNode*)calloc(1, sizeof(LNode));
	if (!newList->head || !newList->tail) {
		free(newList->head);
		free(newList->tail);
		free(newList);
		perror("newList->head or newList -> tail");
		return NULL;
	}

	// ���������ַ
	return newList;
}

/*
�������н��
*/
void destoryAllNodes(LinkedList* list) {
	assert(list);
	// 0�����
	if (!list->size) {
		printf("LinkedList has no Node");
		return;
	}
	LNode* curr = list->head->next;
	while (curr) {
		LNode* temp = curr->next;
		free(curr);
		curr = temp;
	} // curr = NULL����һ�ͷŽ��
	list->head = NULL;
	list->tail = NULL;
	list->size = 0;
}

/*
��������
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
ͷ�巨
*/
bool insert_head(LinkedList* list, const E val) {
	assert(list);
	// �½��
	LNode* newNode = (LNode*)calloc(1, sizeof(LNode));
	if (!newNode) {
		perror("insert_head:newNode");
		return false;
	}
	newNode->data = val;

	// ����
	newNode->next = list->head->next;
	list->head->next = newNode;

	// β�����
	if (!list->tail->next) {
		list->tail->next = newNode;
	}

	// �����С
	list->size++;

	return true;
}

/*
β��
*/
bool insert_tail(LinkedList* list, const E val) {
	// �½��
	assert(list);
	LNode* newNode = (LNode*)calloc(1, sizeof(LNode));
	if (!newNode) {
		perror("insert_head:newNode");
		return false;
	}
	newNode->data = val;

	// ����
	list->tail->next->next = newNode;
	list->tail->next = newNode;

	// ͷ�����
	if (!list->head->next) {
		list->head->next = newNode;
	}

	// �����С++
	list->size++;
	return true;
}

/*
��λ�ò�
*/
bool insert_pos(LinkedList* list, const int index, const E val) {
	// λ����Ч��
	if (index < 0 || index > list->size) {
		printf("index is invalid position!\n");
		return false;
	}

	// �½��
	assert(list);
	LNode* newNode = (LNode*)calloc(1, sizeof(LNode));
	if (!newNode) {
		perror("insert_head:newNode");
		return false;
	}
	newNode->data = val;

	// index = 0 Ϊͷ�壬index = size Ϊβ��
	if (index == 0) {
		if (insert_head(list, val)) return true;
		else return false;
	} else if (index == list->size) {
		if (insert_tail(list, val)) return true;
		else return false;
	}

	// ����Ѱ��λ�ã�������
	LNode* curr = list->head->next;
	for (int i = 0; i < index - 1; i++) {
		curr = curr->next;
	}
	newNode->next = curr->next;
	curr->next = newNode;

	// ����С++
	list->size++;
	return true;
}

/*
ͷɾ
*/
bool delete_head(LinkedList* list) {
	assert(list);
	if (isEmpty(list)) {
		printf("LinkedList has no Node");
		return false;
	}

	// ֻ��һ��������ɾ��
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
βɾ
*/
bool delete_tail(LinkedList* list) {
	assert(list);
	if (!list->size) {
		printf("LinkedList has no Node");
		return false;
	}

	// ֻ��һ��������ɾ��
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
λ��ɾ
*/
bool delete_pos(LinkedList* list, int index) {
	assert(list);
	if (isEmpty(list)) {
		printf("LinkedList has no Node");
		return false;
	}
	// λ����Ч��
	if (index < 0 || index > list->size) {
		printf("index is invalid position!\n");
		return false;
	}

	//index = size Ϊβɾ
	if (index == list->size) {
		if (delete_tail(list)) return true;
		else return false;
	}

	// ��Ҫ������㣬һ����ǰ��Ҫɾ���Ľ�㣬һ��ǰ�ý������������һ�����
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
��ֵɾ2.0
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
����val��һ�γ��ֵĽ��
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
��ӡ���н��ֵ
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
��ֵɾ��1.0
*/
//bool delete_val(LinkedList* list, const E val) {
//	assert(list);
//
//	int index = list->size - 1;
//	// ��Ҫ������㣬һ����ǰ��Ҫɾ���Ľ�㣬һ��ǰ�ý������������һ�����
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