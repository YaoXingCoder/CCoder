#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

#define DEFAULE_CAPACITY 6 // 队列初始长度
#define THRESHOL 1000 // 阈值，超过1.5扩容，否则2倍括

typedef int ElementType;

typedef struct {
	ElementType* elements;
	int front; // 队首指针
	int rear; // 尾指针
	int size; // 当前队列中元素数量
	int capacity; // 队列容量
}QArray;

// 创建动态数组队列
QArray* createQueue();

// 销毁动态数组队列
bool destroyQueue(QArray* qArr);

// 判空
bool isEmpty(QArray* qArr);

// 判满
bool isFull(QArray* qArr);

// 入队
bool pushQueue(QArray* qArr, ElementType data);

// 出队并返回队头值
ElementType popQueue(QArray* qArr);

// 访问队首元素
ElementType peekQueue(const QArray* qArr);