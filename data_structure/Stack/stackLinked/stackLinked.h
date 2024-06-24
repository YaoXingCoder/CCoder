#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef int ElementType;

// ������ṹ��
typedef struct StackNode {
	ElementType data;
	struct StackNode* next;
}SNode;

// ջ�ṹ��
typedef struct {
	SNode* top;
	int size;
}SFrame;

// ����ջ
SFrame* createStack(void);

// ����ջ
bool destoryStack(SFrame* s);

// ��ջ/ѹջ
bool pushStack(SFrame* s, const ElementType data);

// ��ջ/��ջ
ElementType popStack(SFrame* s);

// ����ջ��Ԫ��
ElementType peekStack(const SFrame* s);

// �п�
bool isEmpty(const SFrame* s);