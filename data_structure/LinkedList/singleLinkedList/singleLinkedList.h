#pragma once
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

typedef int E; // �洢����

// ���
typedef struct LNode {
	E data;
	struct LNode* next;
}LNode;

// ����
typedef struct {
	LNode* head; // ͷ�ڵ�
	LNode* tail; // βָ��
	int size; // ������
}LinkedList;

// ������ʼ��
LinkedList* createLinkedList(void); 

// �������н��
void destoryAllNodes(LinkedList* list);

// ��������
void destoryLinkedList(LinkedList* list); 

// ͷ��
bool insert_head(LinkedList* list, const E val);

// β��
bool insert_tail(LinkedList* list, const E val);

// ��λ�ò���
bool insert_pos(LinkedList* list, const int index, const E val);

// ͷɾ
bool delete_head(LinkedList* list);

// βɾ
bool delete_tail(LinkedList* list);

// λ��ɾ
bool delete_pos(LinkedList* list, int index);

// ��ֵɾ
bool delete_val(LinkedList* list, const E val);

// ����val��һ�γ��ֵĽ��
LNode* first_val(const LinkedList* list, const E val);

// ��ӡ���н��
void printAllNodes(const LinkedList* list);