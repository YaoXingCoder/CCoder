/*********************************
Date:2024.6.21
Title:ջ�ĵ�����ʵ�֣���ͷ��㣩
Author:JiaZiChunQiu
Content:
0.��ջ��/����ջ
1.��ջ/ѹջ
2.��ջ/��ջ
3.����ջ��Ԫ��
4.�п�
**********************************/

#include "stackLinked.h"

// ��ջ��
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

// ����ջ
bool destoryStack(SFrame* s) {
	assert(s);

	SNode* curr = s->top->next;
	while(curr) {
		SNode* temp = curr->next;
		free(curr);
		curr = temp;
	}

	// ����ͷ��㣬ջ�ṹ
	free(s->top);
	free(s);
	return true;
}

// ��ջ/ѹջ
bool pushStack(SFrame* s, const ElementType data) {
	assert(s);

	// ����һ��ջ֡����ʼ��
	SNode* newNode = calloc(1, sizeof(SNode));
	if (!newNode) {
		perror("pushStack");
		return false;
	}
	newNode->data = data;

	// ����ջ������С+1
	newNode->next = s->top->next;
	s->top->next = newNode;
	s->size++;

	return true;
}

// ��ջ/��ջ
ElementType popStack(SFrame* s) {
	assert(s);

	// �п�
	if (isEmpty(s)) return false;

	// ͷ���ָ��Ŀ��ջ֡���¸��ڵ�
	SNode* tmp = s->top->next;
	ElementType data = tmp->data;
	s->top->next = tmp->next;
	
	// �ͷ��ͷ�ջ֡����С-1
	free(tmp);
	s->size--;
	return data;
}

// ����ջ��Ԫ��
ElementType peekStack(const SFrame* s) {
	assert(s);
	// �п�
	if (isEmpty(s)) return false;

	// ����ջ��֡��ֵ
	return s->top->next->data;
}

// �п�
bool isEmpty(const SFrame* s) {
	if (s->size == 0) {
		printf("Stack is empty\n");
		return true;
	} else {
		return false;
	}
}