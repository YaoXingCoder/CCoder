/*********************************
Date:2024.6.22
Title:每日练习Day11
Author:JiaZiChunQiu
Content:
求链表中间结点 (876. 链表的中间结点)
判断单链表是否有环?(141. 环形链表)
反转单链表 (206. 反转链表)
合并两条有序链表 (21. 合并两个有序链表）
**********************************/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "Linkedlist.h"


int main(void) {
	ListNode* list1 = NULL;
	ListNode* list2 = NULL;
	add_before_head(&list1, 4);
	add_before_head(&list1, 2);
	add_before_head(&list1, 1);

	add_before_head(&list2, 4);
	add_before_head(&list2, 3);
	add_before_head(&list2, 1);
	
	ListNode* newList = mergeTwoLists(list1, list2);
	return 0;
}

/*
求链表中间结点 (876. 链表的中间结点)
*/
// 计数器方法
//struct ListNode* middleNode(struct ListNode* head) {
//    int size = 0;
//    struct ListNode* curr = head;
//    while (curr) {
//        size++;
//        curr = curr->next;
//    }
//    size /= 2;
//    curr = head;
//    while (size--) {
//        curr = curr->next;
//    }
//    return curr;
//}

// 快慢指针
//struct ListNode* middleNode(struct ListNode* head) {
//    struct ListNode* fast = head;
//    struct ListNode* slow = head;
//    while (fast->next && fast->next->next) {
//        fast = fast->next->next;
//        slow = slow->next;
//    }
//    if (fast->next) {
//        slow = slow->next;
//    }
//    return slow;
//}

/*
判断单链表是否有环?(141. 环形链表)
*/
// 添加数组中，循环比较
//bool hasCycle(struct ListNode* head) {
//    struct ListNode* arr[10000] = { 0 };
//    struct ListNode* curr = head;
//    int i = 0;
//    while (curr) {
//        for (int j = 0; j <= i; j++) {
//            if (arr[j] == curr) return true;
//        }
//        arr[i++] = curr;
//        curr = curr->next;
//    }
//    return false;
//}

// 快慢指针
//bool hasCycle(struct ListNode* head) {
//    if (!head) return false;
//    struct ListNode* fast = head;
//    struct ListNode* slow = head;
//    while (fast->next && fast->next->next) {
//        slow = slow->next;
//        fast = fast->next->next;
//        if (slow == fast) return true;
//    }
//    return false;
//}

/*
反转单链表 (206. 反转链表)
*/
// 双指针
//struct ListNode* reverseList(struct ListNode* head) {
//    if (!head) return head;
//    struct ListNode* newHead = NULL;
//    struct ListNode* curr = head;
//    struct ListNode* temp;
//    while (curr) {
//        temp = curr->next;
//        insertHead(&newHead, curr);
//        curr = temp;
//    }
//    return newHead;
//}
//
//void insertHead(struct ListNode** phead, struct ListNode* newNode) {
//    newNode->next = *phead;
//    *phead = newNode;
//}


/*
合并两条有序链表 (21. 合并两个有序链表）
*/
//struct ListNode* mergeTwoLists(struct ListNode* list1, struct ListNode* list2) {
//    if (!list1) // 如果list1为空
//        return list2;
//    if (!list2) // 如果list2为空
//        return list1;
//    struct ListNode temp = { 0 };
//    struct ListNode* tail = &temp;
//    struct ListNode* ascList1 = list1;
//    struct ListNode* ascList2 = list2;
//    while (ascList1 && ascList2) {
//        if (ascList1->val < ascList2->val) {
//            tail->next = ascList1;
//            ascList1 = ascList1->next;
//        } else {
//            tail->next = ascList2;
//            ascList2 = ascList2->next;
//        }
//        tail = tail->next;
//    }
//    if (ascList1) {
//        tail->next = ascList1;
//    }
//    if (ascList2) {
//        tail->next = ascList2;
//    }
//    return temp.next;
//}





//void insertTail(struct ListNode** phead, struct ListNode* newNode) {
//    struct ListNode* curr = *phead;
//    if (!curr) {
//        curr = newNode;
//        newNode->next = NULL;
//        return;
//    }
//    while (curr->next) {
//        curr = curr->next;
//    }
//    curr->next = newNode;
//    newNode->next = NULL;
//}