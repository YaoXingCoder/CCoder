#pragma once
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

typedef int E; // 存储类型

// 结点
typedef struct LNode {
	E data;
	struct LNode* next;
}LNode;

// 链表
typedef struct {
	LNode* head; // 头节点
	LNode* tail; // 尾指针
	int size; // 链表长度
}LinkedList;

// 创建初始化
LinkedList* createLinkedList(void); 

// 销毁所有结点
void destoryAllNodes(LinkedList* list);

// 销毁链表
void destoryLinkedList(LinkedList* list); 

// 头插
bool insert_head(LinkedList* list, const E val);

// 尾插
bool insert_tail(LinkedList* list, const E val);

// 按位置插入
bool insert_pos(LinkedList* list, const int index, const E val);

// 头删
bool delete_head(LinkedList* list);

// 尾删
bool delete_tail(LinkedList* list);

// 位置删
bool delete_pos(LinkedList* list, int index);

// 按值删
bool delete_val(LinkedList* list, const E val);

// 返回val第一次出现的结点
LNode* first_val(const LinkedList* list, const E val);

// 打印所有结点
void printAllNodes(const LinkedList* list);