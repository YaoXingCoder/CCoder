#pragma once

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

typedef int ElementType; // ֵ����

// ������ʽ���
typedef struct QueueNode {
	ElementType element; // �洢����
	struct QueueNode* next;
}QNode;

// ��ʽ�ṹ��
typedef struct {
	QNode* head;
	QNode* tail;
	int size; // ��¼������
}QLinkedList;

/* ���� */
QLinkedList* createQueueLinked(void);

/* �п� */
bool isEmpty(const QLinkedList* QLinked);

/* ���� */
bool destoryQueue(QLinkedList* QLinked);

/* ��� - ͷ�� */
bool pushQueue(QLinkedList* QLinked, const ElementType element);

/* ���� - βɾ */
ElementType popQueue(QLinkedList* QLinked);

/* ���ʶ��� */
ElementType peekQueue(const QLinkedList* QLinked);