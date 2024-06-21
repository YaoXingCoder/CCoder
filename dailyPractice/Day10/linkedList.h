#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// 节点
typedef struct node {
	int data;
	struct node* next;
} Node;

// 头插法
void add_before_head(Node** phead, Node** ptail, int val);

// 尾插法
void add_behind_tail(Node** phead, Node** ptail, int val);

// 顺序插入
void add_in_sort(Node** phead, Node** ptail, int val);