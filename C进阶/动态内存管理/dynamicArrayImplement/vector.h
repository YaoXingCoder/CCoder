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