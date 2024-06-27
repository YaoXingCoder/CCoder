/*********************************
Date:2024.6.26
Title:���е���ʽʵ��
Author:JiaZiChunQiu
Content:
˼·��
���У�ͷ���+β���
��ʽ����������������
FIFO��ͷ��+βɾ
**********************************/

#include "LinkedQueue.h"

/* ���� */
QLinkedList* createQueueLinked(void) {
	QLinkedList* QLinked = calloc(1, sizeof(QLinkedList));
	if (!QLinked) {
		perror("createQueueLinked");
		return NULL;
	}

	QLinked->head = calloc(1, sizeof(QNode));
	if (!QLinked->head) {
		perror("createQueue_head");
		free(QLinked);
		return NULL;
	}

	QLinked->tail = calloc(1, sizeof(QNode));
	if (!QLinked->tail) {
		perror("createQueue_head");
		free(QLinked->head);
		free(QLinked);
		return NULL;
	}

	return QLinked;
}

/* �п� */
bool isEmpty(const QLinkedList* QLinked) {
	assert(QLinked);
	if (QLinked->size) {
		return false;
	} else {
		printf("Queue is Empty\n");
		return true;
	}
}

/* ���� */
bool destoryQueue(QLinkedList* QLinked) {
	assert(QLinked);

	// ��Ϊ�գ��ͷŸ����
	if (!isEmpty(QLinked)) {
		QNode* curr = QLinked->head->next;
		while (curr) {
			QNode* tmp = curr->next;
			free(curr);
			tmp = curr;
		}
	}

	// �ͷŶ��нṹ
	free(QLinked->head);
	free(QLinked->tail);
	free(QLinked);
	return true;
}

/* ��� - ͷ�� */
bool pushQueue(QLinkedList* QLinked, const ElementType element) {
	assert(QLinked);
	
	// �����½ڵ�
	QNode* newNode = calloc(1, sizeof(QNode));
	if (!newNode) {
		perror("pushQueue");
		return false;
	}
	newNode->element = element;

	// ͷ��
	newNode->next = QLinked->head->next;
	QLinked->head->next = newNode;

	// ���½����Ϣ
	if (QLinked->size == 0) QLinked->tail->next = newNode;
	QLinked->size++;

	return true;
}

/* ���� - βɾ */
ElementType popQueue(QLinkedList* QLinked) {
	assert("popQueue");

	// �п�
	if (isEmpty(QLinked)) return false;

	// �ҵ�β���
	QNode* curr = QLinked->head;
	while (curr->next != QLinked->tail->next) {
		curr = curr->next;
	}
	
	// ���½����Ϣ
	QLinked->tail->next = curr;
	curr = curr->next;
	QLinked->tail->next->next = curr->next;
	ElementType tmp = curr->element; // ������ֵ
	free(curr);

	// ɾ�������Ϊ�գ�ͷβ�ÿ�
	QLinked->size--;
	if (QLinked->size == 0) {
		QLinked->head->next = NULL;
		QLinked->tail->next = NULL;
	}

	return tmp;
}

/* ���ʶ�ͷ-�����е�β��� */
ElementType peekQueue(const QLinkedList* QLinked) {
	assert(QLinked);

	// �п�
	if (isEmpty(QLinked)) return false;

	return QLinked->tail->next->element;
}