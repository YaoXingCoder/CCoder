#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

//typedef enum month {
//	January = 1,
//	February,
//	March,
//	April,
//	May,
//	June,
//	July,
//	August,
//	September,
//	Octobar,
//	November,
//	December
//}Month;


#define INIT_CAPACITY 8
#define MAX_CAPACITY 1024

typedef int E;

typedef struct {
    E* elements;   // 指向堆空间的数组
    int size;	// 元素的个数
    int capacity; // 数组的容量
} Vector;

// 构造函数，获取空间
Vector* vectorCreate(void);

// 析构函数，销毁空间
void destoryVector(Vector* v);

// 在数组最后面添加元素
void push_back(Vector* v, E val);

// 在数组最前面添加元素，所有元素依次后移
void push_front(Vector* v, E val);

// 删除最后一个元素, 并把最后一个元素返回
E pop_back(Vector* v);

// 删除第一个元素，并把第一个元素返回
E pop_front(Vector* v);
