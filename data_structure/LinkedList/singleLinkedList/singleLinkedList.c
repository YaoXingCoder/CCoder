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
	// ʹ��calloc�����Զ���ʼ����ԱΪĬ����ֵ,����ʡ��
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

	// ����ʼ��
	newNode->data = val;
	newNode->next = list->head->next;

	// ����
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
	// ����һ���½ڵ�
	assert(list);
	LNode* newNode = (LNode*)calloc(1, sizeof(LNode));
	if (!newNode) {
		perror("insert_head:newNode");
		return false;
	}

	// �½ڵ��ʼ��
	newNode->data = val;
	newNode->next = NULL;

	// ����
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

	// index = 0 Ϊͷ�壬index = size Ϊβ��
	if (index == 0) {
		return (insert_head(list, val));
	}  	
	if (index == list->size) {
		return (insert_tail(list, val));
	}

	// �½��
	assert(list);
	LNode* newNode = (LNode*)calloc(1, sizeof(LNode));
	if (!newNode) {
		perror("insert_head:newNode");
		return false;
	}
	newNode->data = val;


	// ����Ѱ��λ�ã�ѭ��������, prevָ��ָ��curr����ǰ���һ�����
	LNode* curr = list->head->next;
	for (int i = 0; i < index - 1; i++) {
		curr = curr->next;
	}
	// ��indexλ��, �����½��. 
	// �ù��������½��ָ��curr�ĺ�̽��, ����curr���ָ���½��
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
	// �п�
	assert(list);
	return (isEmpty(list));
	
	// ��ͷ���ָ���׽����¸����
	LNode* curr = list->head->next;
	list->head->next = curr->next;
	
	// ɾ�����󳤶�Ϊ0��β���ָ���ÿ�
	if (list->size - 1 == 0) {
		list->tail->next = NULL;
	
	}

	// �ͷ�Ŀ���㣬����-1
	free(curr);
	list->size--;
	return true;
}

/*
βɾ
*/
bool delete_tail(LinkedList* list) {
	assert(list);
	return (isEmpty(list));
	
	// �ҵ�β����ǰ�����
	LNode* curr = list->head;
	while (curr->next != list->tail->next) {
		curr = curr->next;
	}

	// ����βָ��ָ��ǰ����㣬����ǰ�����ָ���ÿ�
	list->tail->next = curr;
	curr = curr->next;
	list->tail->next->next = NULL;

	// �ͷ�β��㣬����-1
	free(curr);
	// ���ɾ���󳤶�=0��β����ÿ�
	if (--list->size) {
		list->tail->next = NULL;
	};
	return true;
}

/*
λ��ɾ
*/
bool delete_pos(LinkedList* list, int index) {
	assert(list);
	// �����Ƿ�Ϊ��
	return isEmpty(list);
	
	// λ����Ч��
	if (index < 0 || index > list->size - 1) {
		printf("index is invalid position!\n");
		return false;
	}

	// ��Ҫ������㣬һ����ǰ��Ҫɾ���Ľ�㣬һ��ǰ�ý������������һ�����
	LNode* pre = list->head;
	LNode* curr = list->head->next;
	while (index--) {
		pre = curr;
		curr = curr->next;
	}

	// ��ǰ�����ָ��Ŀ��ڵ��next
	pre->next = curr->next;
	// ��ɾ����β���
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
��ֵɾ2.0
*/
bool delete_val(LinkedList* list, const E val) {
	assert(list);
	if (isEmpty(list)) {
		printf("LinkedList has no Node");
		return false;
	}

	// ���Ҹ�ֵ�Ƿ���������
	LNode* curr = first_val(list, val);
	if (!curr) {
		printf("the value is not in list");
		return false;
	}

	// �ҵ�����ǰ�����
	LNode* pre = list->head;
	for ( ; pre->next != curr ; pre = pre->next) {
		;
	}

	// ����ǰ�����ָ��ɾ��������һ�����
	pre->next = curr->next;
	// ���β���ָ����Ҫɾ���Ľ�㣬��β���ָ��ǰ����㣬
	// ���size = 1ʱ��β���ָ���ÿ�
	if (list->tail->next == curr) {
		list->tail->next = pre;
		if (list->size - 1 == 0) {
			list->tail->next = NULL;
		}
	}

	// �ͷŽ�㣬��С-1
	free(curr);
	list->size--;
	return true;
}

/*
����val��һ�γ��ֵĽ��
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
���������������
*/
LNode* find_by_index(const LinkedList* list, const E index) {
	// λ����Ч��
	if (index < 0 || index > list->size - 1) {
		perror("find_by_index");
		return NULL;
	}

	LNode* curr = list->head->next;
	for (int i = 0; i < index; i++) {
		curr = curr->next;
	} // ѭ������ʱ, currָ���ָ��idxλ�õĽ��
	
	return curr;
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