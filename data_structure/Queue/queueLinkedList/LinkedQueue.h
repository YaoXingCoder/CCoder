#pragma once

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

typedef int ElementType; // 值类型

// 创建链式结点
typedef struct QueueNode {
	ElementType element; // 存储类型
	struct QueueNode* next;
}QNode;

// 链式结构体
typedef struct {
	QNode* head;
	QNode* tail;
	int size; // 记录结点个数
}QLinkedList;

/* 创建 */
QLinkedList* createQueueLinked(void);

/* 判空 */
bool isEmpty(const QLinkedList* QLinked);

/* 销毁 */
bool destoryQueue(QLinkedList* QLinked);

/* 入队 - 头插 */
bool pushQueue(QLinkedList* QLinked, const ElementType element);

/* 出队 - 尾删 */
ElementType popQueue(QLinkedList* QLinked);

/* 访问队首 */
ElementType peekQueue(const QLinkedList* QLinked);