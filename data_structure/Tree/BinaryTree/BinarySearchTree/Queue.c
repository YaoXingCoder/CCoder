/*********************************
Date:2024.6.27
Title:队列-实现二叉树的层次遍历
Author:JiaZiChunQiu
Content:
**********************************/

#include "Queue.h"

static bool resize(QArray* qArr);

/* 创建动态数组队列 */
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

	// 初始化
	qArr->capacity = DEFAULE_CAPACITY;

	return qArr;
}

/* 销毁动态数组队列 */ 
bool destroyQueue(QArray* qArr) {
	assert(qArr);
	if (!isEmpty_Q(qArr)) {
		free(qArr->elements);
	}
	free(qArr);
	return true;
}

/* 判空 */ 
bool isEmpty_Q(QArray* qArr) {
	assert(qArr);
	if (qArr->size) {
		return false;
	} else {
		printf("Queue is Empty\n");
		return true;
	}
}

/* 判满 */
bool isFull_Q(QArray* qArr) {
	assert(qArr);
	if (qArr->size == qArr->capacity) {
		printf("Queue is full\n");
		return true;
	} else {
		return false;
	}
}

/* 扩容 */
static bool resize(QArray* qArr) {
	assert(qArr);

	// 新大小
	int oldCapacity = qArr->capacity;
	int newCapacity = oldCapacity < THRESHOLD ? oldCapacity << 1 : (oldCapacity + oldCapacity >> 1);

	// 新数组
	ElementType* newElements = realloc(qArr->elements, sizeof(ElementType) * newCapacity);
	if (!newElements) {
		perror("resize");
		return false;
	}
	qArr->elements = newElements;

	// copy，将旧数组front前的值放到扩容后的数组中
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

/* 入队 */
bool pushQueue(QArray* qArr, ElementType data) {
	assert(qArr);
	
	// 扩容否
	if (isFull_Q(qArr)) {
		if (!resize(qArr)) {
			printf("error:Failed to resize capacity");
			return false;
		}
	}

	// 放入数据
	qArr->elements[qArr->rear] = data;
	qArr->rear = (qArr->rear + 1) % qArr->capacity;
	qArr->size++;
	return true;
}

/* 出队并返回队头值 */ 
ElementType popQueue(QArray* qArr) {
	assert(qArr);
	if (isEmpty_Q(qArr)) exit(1);

	ElementType tmp = qArr->elements[qArr->front];
	qArr->front = (qArr->front + 1) % qArr->capacity;
	qArr->size--;

	return tmp;
}

/* 访问队首元素 */
ElementType peekQueue(const QArray* qArr) {
	assert(qArr);

	if (isEmpty_Q(qArr)) exit(1); // 判空

	return qArr->elements[qArr->front];
}