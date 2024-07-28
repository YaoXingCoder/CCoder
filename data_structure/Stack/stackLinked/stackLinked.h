#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef int ElementType;

// 链表结点结构体
typedef struct StackNode {
	ElementType data;
	struct StackNode* next;
}SNode;

// 栈结构体
typedef struct {
	SNode* top;
	int size;
}SFrame;

// 创建栈
SFrame* createStack(void);

// 创建栈
bool destoryStack(SFrame* s);

// 入栈/压栈
bool pushStack(SFrame* s, const ElementType data);

// 出栈/弹栈
ElementType popStack(SFrame* s);

// 访问栈顶元素
ElementType peekStack(const SFrame* s);

// 判空
bool isEmpty(const SFrame* s);