#include "linkedList.h"

/*
Date:2024.6.21
Title:ÿ����ϰDay10
Content:
1.ͷ�巨
2.β�巨
3.˳�����
*/

/*
1.ͷ����
*/
void add_before_head(Node** phead, Node** ptail, int val) {
	// �����ڵ�
	Node* newNode = malloc(sizeof(Node));
	if (!newNode) {
		perror("add_before_head");
		return;
	}
	// �ڵ��ʼ������ͷָ��ΪNULL����βָ��Ҳ��ΪNULL����ʼ��
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
2.β�巨
*/
void add_behind_tail(Node** phead, Node** ptail, int val) {
	// �����ڵ�
	Node* newNode = malloc(sizeof(Node));
	if (!newNode) {
		perror("add_behind_tail");
		return;
	}
	newNode->data = val;
	newNode->next = NULL;

	// �ڵ��ʼ��
	if (!ptail) {
		*ptail = newNode;
		*phead = newNode;
	} else {
		(*ptail)->next = newNode;
		*ptail = newNode;
	}
}

/*
3.ʵ��˳�����
*/
void add_in_sort(Node** phead, Node** ptail, int val) {
	// �����ڵ�
	Node* newNode = malloc(sizeof(Node));
	if (!newNode) {
		perror("add_in_sort");
		return;
	}
	newNode->data = val;
	newNode->next = NULL;

	// û��ָ�룬��Ϊ��һ������
	if (!*phead) {
		*phead = newNode;
		*ptail = newNode;
		return;
	}

	// ��һ������Ҫ�����λ��
	if ((*phead)->data > val) {
		newNode->next = *phead;
		*phead = newNode;
		return;
	}

	// �ҵ�Ӧ����ڵ�λ��
	Node* curNode = *phead;
	while (curNode->next) {
		if (curNode->next->data > val) break;
		curNode = curNode->next;
	} // curNode.next = NULL || curNode->next->data

	// ����
	newNode->next = curNode->next;
	curNode->next = newNode;

	// �����Ϊ���һ������
	if (curNode == *ptail) {
		*ptail = newNode;
	}
}