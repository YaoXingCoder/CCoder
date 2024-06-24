/*********************************
Date:2024.6.24
Title:���еĶ�̬����ʵ��
Author:JiaZiChunQiu
Content:
1.������̬�������
2.���ٶ�
3.�п�
4.����
5.���
6.���Ӳ����ض�ͷֵ
7.���ʶ���Ԫ��
**********************************/

#include "ArrayQueue.h"

// ������̬�������
QArray* createQueue(void) {
	// �������в���ʼ��
	QArray* qArr = calloc(1, sizeof(QArray));
	if (!qArr) {
		perror("createQueue");
		return NULL;
	}

	// ������̬���鲢��ʼ��
	qArr->elements = calloc(DEFAULE_CAPACITY, sizeof(ElementType));
	if (!qArr) {
		perror("createQueue_qArr");
		free(qArr);
		return NULL;
	}

	// ������ʼ��
	qArr->capacity = DEFAULE_CAPACITY;
	return qArr;
}

// ���ٶ�̬�������
bool destroyQueue(QArray* qArr) {
	assert(qArr);
	free(qArr->elements);
	free(qArr);
	return true;
}

// �п�
bool isEmpty(const QArray* qArr) {
	if (!qArr->size) {
		printf("Queue is empty\n");
		return true;
	} else {
		return false;
	}
}

// ����
bool isFull(const QArray* qArr) {
	if (qArr->size == qArr->capacity) {
		printf("Queue is full\n");
		return true;
	} else {
		return false;
	}
}

// ����
static bool resizeQueue(QArray* qArr) {
	assert(qArr);
	if (!isFull(qArr)) return false;

	// ��¼�ɵ�������С
	int oldCapacity = qArr->capacity;

	// ������������С
	int newCapacity = oldCapacity < THRESHOL ? oldCapacity << 1 : (oldCapacity + oldCapacity >> 1);

	// ���·���
	ElementType* ptr = calloc(newCapacity, sizeof(ElementType));
	if (!ptr) {
		perror("resizeQueue");
		return false;
	}

	// �������е�ֵͳһ�ƶ�������Ŀ�ʼλ��
	// ��qArr�е�Ԫ�ذ����ʹ�С���θ��Ƶ�������
	for (int i = 0; i < qArr->size; i++) {
		int offset = (qArr->front + i) % qArr->capacity; // front��ƫ����
		ElementType* qArrIndex = qArr->elements + offset;
		memcpy(ptr + i, qArrIndex, sizeof(ElementType));
	}

	// �ͷž�����ռ�
	free(qArr->elements);

	// ����
	qArr->elements = ptr;
	qArr->capacity = newCapacity;
	qArr->front = 0;
	qArr->rear = qArr->size;
	
	return true;
}

// ���
bool pushQueue(QArray* qArr, const ElementType data) {
	assert(qArr);

	// �Ƿ���Ҫ����
	if (isFull(qArr)) {
		if (!resizeQueue(qArr)) {
			printf("error:Failed to resize capacity");
			return false;
		}
	}

	// �Ƿ���Ҫ
	qArr->elements[qArr->rear] = data;
	qArr->rear = (qArr->rear + 1) % qArr->capacity;
	qArr->size++;
	return true;
}

// ���Ӳ����ض�ͷֵ
ElementType popQueue(QArray* qArr) {
	assert(qArr);
	if (isEmpty(qArr)) exit(1);
	ElementType tmp = qArr->elements[qArr->front]; // ��¼ֵ
	qArr->front = (qArr->front + 1) % qArr->capacity;
	qArr->size--;
	return tmp;
}

// ���ʶ���Ԫ��
ElementType peekQueue(const QArray* qArr) {
	assert(qArr);
	if (isEmpty(qArr)) exit(1); // �п�
	return qArr->elements[qArr->front];
}