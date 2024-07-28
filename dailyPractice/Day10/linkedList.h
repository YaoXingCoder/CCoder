#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// �ڵ�
typedef struct node {
	int data;
	struct node* next;
} Node;

// ͷ�巨
void add_before_head(Node** phead, Node** ptail, int val);

// β�巨
void add_behind_tail(Node** phead, Node** ptail, int val);

// ˳�����
void add_in_sort(Node** phead, Node** ptail, int val);