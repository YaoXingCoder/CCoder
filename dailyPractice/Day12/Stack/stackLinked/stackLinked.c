/*********************************
Date:2024.6.21
Title:栈的单链表实现（带头结点）
Author:JiaZiChunQiu
Content:
0.创栈体/销毁栈
1.入栈/压栈
2.出栈/弹栈
3.访问栈顶元素
4.判空
**********************************/

#include "stackLinked.h"

// 创栈体
SFrame* createStack(void) {
	SFrame* s = (SFrame*)calloc(1, sizeof(SFrame));
	if (!s) {
		perror("createStack");
		return NULL;
	}

	s->top = (SNode*)calloc(1, sizeof(SNode));
	if (!s->top) {
		perror("createStack_top");
		free(s);
		return NULL;
	}

	return s;
}

// 销毁栈
bool destoryStack(SFrame* s) {
	assert(s);

	SNode* curr = s->top->next;
	while(curr) {
		SNode* temp = curr->next;
		free(curr);
		curr = temp;
	}

	// 销毁头结点，栈结构
	free(s->top);
	free(s);
	return true;
}

// 入栈/压栈
bool pushStack(SFrame* s, const ElementType data) {
	assert(s);

	// 创建一个栈帧，初始化
	SNode* newNode = calloc(1, sizeof(SNode));
	if (!newNode) {
		perror("pushStack");
		return false;
	}
	newNode->data = data;

	// 插入栈顶，大小+1
	newNode->next = s->top->next;
	s->top->next = newNode;
	s->size++;

	return true;
}

// 出栈/弹栈
ElementType popStack(SFrame* s) {
	assert(s);

	// 判空
	if (isEmpty(s)) return false;

	// 头结点指向目标栈帧的下个节点
	SNode* tmp = s->top->next;
	ElementType data = tmp->data;
	s->top->next = tmp->next;
	
	// 释放释放栈帧，大小-1
	free(tmp);
	s->size--;
	return data;
}

// 访问栈顶元素
ElementType peekStack(const SFrame* s) {
	assert(s);
	// 判空
	if (isEmpty(s)) return false;

	// 返回栈顶帧的值
	return s->top->next->data;
}

// 判空
bool isEmpty(const SFrame* s) {
	if (s->size == 0) {
		printf("Stack is empty\n");
		return true;
	} else {
		return false;
	}
}