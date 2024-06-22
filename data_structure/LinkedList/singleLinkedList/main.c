/*********************************
Date:2024.6.22
Title:带头结点链表实现
Author:JiaZiChunQiu
Content:
**********************************/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "singleLinkedList.h"

int main(void) {
	LinkedList* list = createLinkedList();

	// 头插入数据
	//for (int i = 10; i > 0; i = i - 3) {
	//	printf("insert_head is %d\n", insert_head(list, i)); // 1 --> 4 --> 7 --> 10
	//}
	insert_head(list, 1);
	// 尾插
	//printf("insert_head is %d\n", insert_tail(list, 20)); // 1 --> 4 --> 7 --> 10 --> 20
	//printf("insert_head is %d\n", insert_tail(list, 30)); // 1 --> 4 --> 7 --> 10 --> 20 --> 30

	//// 位置插
	//printf("insert_head is %d\n", insert_pos(list, 5, 25)); // 1 --> 4 --> 7 --> 10 --> 20 --> 25 --> 30
	//
	//// 头删
	//printf("insert_head is %d\n", delete_head(list)); // 4 --> 7 --> 10 --> 20 --> 25 --> 30

	// 尾删
	printf("insert_head is %d\n", delete_tail(list)); // 4 --> 7 --> 10 --> 20 --> 25

	// 位置删
	printf("insert_head is %d\n", delete_pos(list, 2)); // 4 --> 10 --> 20 --> 25

	// 值删
	printf("insert_head is %d\n", delete_val(list, 10)); // 4 --> 20 --> 25\


	destoryLinkedList(list);
	list = NULL;
	return 0;
}
