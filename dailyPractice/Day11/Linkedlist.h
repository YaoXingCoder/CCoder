#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// 节点
//typedef struct node {
//	int data;
//	struct node* next;
//} Node;

typedef struct ListNode {
	int data;
	struct ListNode* next;
}ListNode;

// 头插法
void add_before_head(ListNode** phead, int val);

ListNode* mergeTwoLists(ListNode* list1, ListNode* list2);