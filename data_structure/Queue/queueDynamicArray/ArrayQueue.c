/*********************************
Date:2024.6.24
Title:队列的动态数组实现
Author:JiaZiChunQiu
Content:
1.创建动态数组队列
2.销毁队
3.判空
4.判满
5.入队
6.出队并返回队头值
7.访问队首元素
**********************************/

#include "ArrayQueue.h"

// 创建动态数组队列
QArray* createQueue(void) {
	// 创建队列并初始化
	QArray* qArr = calloc(1, sizeof(QArray));
	if (!qArr) {
		perror("createQueue");
		return NULL;
	}

	// 创建动态数组并初始化
	qArr->elements = calloc(DEFAULE_CAPACITY, sizeof(ElementType));
	if (!qArr) {
		perror("createQueue_qArr");
		free(qArr);
		return NULL;
	}

	// 容量初始化
	qArr->capacity = DEFAULE_CAPACITY;
	return qArr;
}

// 销毁动态数组队列
bool destroyQueue(QArray* qArr) {
	assert(qArr);
	free(qArr->elements);
	free(qArr);
	return true;
}

// 判空
bool isEmpty(const QArray* qArr) {
	if (!qArr->size) {
		printf("Queue is empty\n");
		return true;
	} else {
		return false;
	}
}

// 判满
bool isFull(const QArray* qArr) {
	if (qArr->size == qArr->capacity) {
		printf("Queue is full\n");
		return true;
	} else {
		return false;
	}
}

// 扩容
static bool resizeQueue(QArray* qArr) {
	assert(qArr);
	if (!isFull(qArr)) return false;

	// 记录旧的容量大小
	int oldCapacity = qArr->capacity;

	// 计算新容量大小
	int newCapacity = oldCapacity < THRESHOL ? oldCapacity << 1 : (oldCapacity + oldCapacity >> 1);

	// 重新分配
	ElementType* ptr = calloc(newCapacity, sizeof(ElementType));
	if (!ptr) {
		perror("resizeQueue");
		return false;
	}

	// 将队列中的值统一移动到数组的开始位置
	// 将qArr中的元素按类型大小依次复制到新数组
	for (int i = 0; i < qArr->size; i++) {
		int offset = (qArr->front + i) % qArr->capacity; // front的偏移量
		ElementType* qArrIndex = qArr->elements + offset;
		memcpy(ptr + i, qArrIndex, sizeof(ElementType));
	}

	// 释放旧数组空间
	free(qArr->elements);

	// 重置
	qArr->elements = ptr;
	qArr->capacity = newCapacity;
	qArr->front = 0;
	qArr->rear = qArr->size;
	
	return true;
}

// 入队
bool pushQueue(QArray* qArr, const ElementType data) {
	assert(qArr);

	// 是否需要扩容
	if (isFull(qArr)) {
		if (!resizeQueue(qArr)) {
			printf("error:Failed to resize capacity");
			return false;
		}
	}

	// 是否需要
	qArr->elements[qArr->rear] = data;
	qArr->rear = (qArr->rear + 1) % qArr->capacity;
	qArr->size++;
	return true;
}

// 出队并返回队头值
ElementType popQueue(QArray* qArr) {
	assert(qArr);
	if (isEmpty(qArr)) exit(1);
	ElementType tmp = qArr->elements[qArr->front]; // 记录值
	qArr->front = (qArr->front + 1) % qArr->capacity;
	qArr->size--;
	return tmp;
}

// 访问队首元素
ElementType peekQueue(const QArray* qArr) {
	assert(qArr);
	if (isEmpty(qArr)) exit(1); // 判空
	return qArr->elements[qArr->front];
}