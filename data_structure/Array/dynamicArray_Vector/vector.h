#pragma once
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <assert.h>

#define INIT_CAPA 8
#define MAX_PREALLOC  1024

typedef int E; // 便于更改创建的数组类型
typedef struct {
	E* elements;
	int capacity;
	int size;
}Vector;

// 构造函数：创建空的动态数组
Vector* createNullVec(void);

// 析构函数：销毁动态数组
void destoryVec(Vector* v);

// 实现在数组最后 追加值
void appendVal(Vector* v, E val);

// 在数组最前追加值
void appendFirst(Vector* v, E val);

// 删除最后一个元素
void deleteLast(Vector* v);

// 删除指定位置元素
void deleteIndex(Vector* v, int index);