/*********************************
Date:2024.6.27
Title:����-ʵ�ֶ������Ĳ�α���
Author:JiaZiChunQiu
Content:
**********************************/

#include "Queue.h"

static bool resize(QArray* qArr);

/* ������̬������� */
QArray* createQueue() {
	QArray* qArr = calloc(1, sizeof(QArray));
	if (!qArr) {
		perror("createQueue");
		return NULL;
	}
	
	qArr->elements = calloc(DEFAULE_CAPACITY, sizeof(ElementType));
	if (!qArr->elements) {
		perror("createQueue_elements");
		free(qArr);
		return NULL;
	}

	// ��ʼ��
	qArr->capacity = DEFAULE_CAPACITY;

	return qArr;
}

/* ���ٶ�̬������� */ 
bool destroyQueue(QArray* qArr) {
	assert(qArr);
	if (!isEmpty_Q(qArr)) {
		free(qArr->elements);
	}
	free(qArr);
	return true;
}

/* �п� */ 
bool isEmpty_Q(QArray* qArr) {
	assert(qArr);
	if (qArr->size) {
		return false;
	} else {
		printf("Queue is Empty\n");
		return true;
	}
}

/* ���� */
bool isFull_Q(QArray* qArr) {
	assert(qArr);
	if (qArr->size == qArr->capacity) {
		printf("Queue is full\n");
		return true;
	} else {
		return false;
	}
}

/* ���� */
static bool resize(QArray* qArr) {
	assert(qArr);

	// �´�С
	int oldCapacity = qArr->capacity;
	int newCapacity = oldCapacity < THRESHOLD ? oldCapacity << 1 : (oldCapacity + oldCapacity >> 1);

	// ������
	ElementType* newElements = realloc(qArr->elements, sizeof(ElementType) * newCapacity);
	if (!newElements) {
		perror("resize");
		return false;
	}
	qArr->elements = newElements;

	// copy����������frontǰ��ֵ�ŵ����ݺ��������
	int newRear = qArr->capacity;
	int cpyNums = (qArr->front + qArr->capacity) % qArr->capacity;
	for (int i = 0; i < cpyNums; i++) {
		qArr->elements[newRear] = qArr->elements[i];
		newRear = (newRear + 1) % newCapacity;
	}

	qArr->rear = newRear;
	qArr->capacity = newCapacity;
	
	return true;
}

/* ��� */
bool pushQueue(QArray* qArr, ElementType data) {
	assert(qArr);
	
	// ���ݷ�
	if (isFull_Q(qArr)) {
		if (!resize(qArr)) {
			printf("error:Failed to resize capacity");
			return false;
		}
	}

	// ��������
	qArr->elements[qArr->rear] = data;
	qArr->rear = (qArr->rear + 1) % qArr->capacity;
	qArr->size++;
	return true;
}

/* ���Ӳ����ض�ͷֵ */ 
ElementType popQueue(QArray* qArr) {
	assert(qArr);
	if (isEmpty_Q(qArr)) exit(1);

	ElementType tmp = qArr->elements[qArr->front];
	qArr->front = (qArr->front + 1) % qArr->capacity;
	qArr->size--;

	return tmp;
}

/* ���ʶ���Ԫ�� */
ElementType peekQueue(const QArray* qArr) {
	assert(qArr);

	if (isEmpty_Q(qArr)) exit(1); // �п�

	return qArr->elements[qArr->front];
}