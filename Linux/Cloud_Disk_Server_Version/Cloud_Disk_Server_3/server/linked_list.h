/*************************************************************************
    > File Name: linked_list.h
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月04日 星期日 22时29分07秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 链表头文件
    > Content:
 ************************************************************************/
#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__
#include "user.h"
#include <stdio.h>
#include <stdlib.h>

// 定义链表节点结构体
typedef struct ListNode {
    void * val;              // 节点的值
    struct ListNode *next;   // 指向下一个节点的指针
} ListNode;

// 创建新的链表节点
ListNode* createNode(void * val);

// 在链表末尾添加元素
void appendNode(ListNode **head, void *val);

// 删除链表中值为target的节点（假设只删除一个）
void deleteNode(ListNode **head, void * target);

// 删除链表中值为peerfd的节点（假设只删除一个）
void deleteNode2(ListNode **head, int peerfd);

// 根据peerfd的节点, 找到指定的节点
void findByPeerfd(ListNode* head, int peerfd, user_info_t** user);

// 打印链表
void printList(ListNode *head);

// 释放链表内存
void freeList(ListNode *head);

#endif
