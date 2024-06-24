/*********************************
Date:
Title:
Author:
Content:
**********************************/

#include "Linkedlist.h"

void insertTail(ListNode* phead, ListNode* newNode);

void add_before_head(ListNode** phead, int val) {
	// �����ڵ�
	ListNode* newNode = calloc(1, sizeof(ListNode));
	if (!newNode) {
		perror("add_before_head");
		return;
	}
	// �ڵ��ʼ������ͷָ��ΪNULL����βָ��Ҳ��ΪNULL����ʼ��
	if (!*phead) {
		*phead = newNode;
		newNode->data = val;
		newNode->next = NULL;
	} else {
		newNode->next = *phead;
		*phead = newNode;
		newNode->data = val;
	}
}

ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
    if (!list1) // ���list1Ϊ��
        return list2;
    if (!list2) // ���list2Ϊ��
        return list1;
    ListNode* phead = NULL;
    ListNode* ascList1 = list1;
    ListNode* ascList2 = list2;
    ListNode* temp;
    while (ascList1 && ascList2) {
        if (ascList1->data < ascList2->data) {
            temp = ascList1->next;
            insertTail(&phead, ascList1);
            ascList1 = temp;
        } else {
            temp = ascList2->next;
            insertTail(&phead, ascList2);
            ascList2 = temp;
        }
    }
    while (ascList1) {
        temp = ascList1->next;
        insertTail(&phead, ascList1);
        ascList1 = temp;
    }
    while (ascList2) {
        temp = ascList2->next;
        insertTail(&phead, ascList2);
        ascList2 = temp;
    }
    return phead;
}

void insertTail(ListNode** phead, ListNode* newNode) {
    ListNode* curr = *phead;
    if (!curr) {
        curr = newNode;
        newNode->next = NULL;
        *phead = curr;
        return;
    }
    while (curr->next) {
        curr = curr->next;
    }
    curr->next = newNode;
    newNode->next = NULL;
}