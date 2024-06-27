/*********************************
Date:2024.6.26
Title:队列的链式实现
Author:JiaZiChunQiu
Content:
思路：
队列：头结点+尾结点
链式：不考虑扩容问题
FIFO：头插+尾删
**********************************/

#include "LinkedQueue.h"

/* 创建 */
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

/* 判空 */
bool isEmpty(const QLinkedList* QLinked) {
	assert(QLinked);
	if (QLinked->size) {
		return false;
	} else {
		printf("Queue is Empty\n");
		return true;
	}
}

/* 销毁 */
bool destoryQueue(QLinkedList* QLinked) {
	assert(QLinked);

	// 不为空，释放各结点
	if (!isEmpty(QLinked)) {
		QNode* curr = QLinked->head->next;
		while (curr) {
			QNode* tmp = curr->next;
			free(curr);
			tmp = curr;
		}
	}

	// 释放队列结构
	free(QLinked->head);
	free(QLinked->tail);
	free(QLinked);
	return true;
}

/* 入队 - 头插 */
bool pushQueue(QLinkedList* QLinked, const ElementType element) {
	assert(QLinked);
	
	// 创建新节点
	QNode* newNode = calloc(1, sizeof(QNode));
	if (!newNode) {
		perror("pushQueue");
		return false;
	}
	newNode->element = element;

	// 头插
	newNode->next = QLinked->head->next;
	QLinked->head->next = newNode;

	// 更新结点信息
	if (QLinked->size == 0) QLinked->tail->next = newNode;
	QLinked->size++;

	return true;
}

/* 出队 - 尾删 */
ElementType popQueue(QLinkedList* QLinked) {
	assert("popQueue");

	// 判空
	if (isEmpty(QLinked)) return false;

	// 找到尾结点
	QNode* curr = QLinked->head;
	while (curr->next != QLinked->tail->next) {
		curr = curr->next;
	}
	
	// 更新结点信息
	QLinked->tail->next = curr;
	curr = curr->next;
	QLinked->tail->next->next = curr->next;
	ElementType tmp = curr->element; // 保存结点值
	free(curr);

	// 删除后队列为空，头尾置空
	QLinked->size--;
	if (QLinked->size == 0) {
		QLinked->head->next = NULL;
		QLinked->tail->next = NULL;
	}

	return tmp;
}

/* 访问队头-链表中的尾结点 */
ElementType peekQueue(const QLinkedList* QLinked) {
	assert(QLinked);

	// 判空
	if (isEmpty(QLinked)) return false;

	return QLinked->tail->next->element;
}