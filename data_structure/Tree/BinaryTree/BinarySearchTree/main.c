/*********************************
Date:2024.6.26
Title:二叉搜索树实现
Author:JiaZiChunQiu
Content:
二叉树测试

**********************************/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "binarySearchTree.h"
#include "Queue.h"

//int main(void) {
	// 创建队列
	//QArray* queue = createQueue();
	//if (queue == NULL) {
	//	printf("创建队列失败。\n");
	//	return 1;
	//}

	//// 入队测试
	//pushQueue(queue, 1);
	//pushQueue(queue, 2);
	//pushQueue(queue, 3);
	//popQueue(queue);
	//popQueue(queue);
	//pushQueue(queue, 4);
	//pushQueue(queue, 5);
	//pushQueue(queue, 6);
	//popQueue(queue);
	//pushQueue(queue, 7);
	//pushQueue(queue, 8);
	//pushQueue(queue, 9);
	//pushQueue(queue, 10);
	//pushQueue(queue, 11);

	//// 打印队列容量和大小
	//printf("队列容量: %d, 队列大小: %d\n", queue->capacity, queue->size);

	//// 出队测试
	//printf("正在出队...\n");
	//while (!isEmpty(queue)) {
	//	printf("已出队: %d\n", popQueue(queue));
	//}

	//// 销毁队列
	//destroyQueue(queue);

//	return 0;
//}


int main(void) {
	// 创建
	BST* bsTree = createBST();
	if (!bsTree) {
		perror("bsTree");
		return 1;
	}

	// 插入元素
	int elements[] = { 50, 30, 70, 20, 40, 60, 80, 30 };
	printf("正在插入:>");
	int elemLen = sizeof(elements) / sizeof(elements[0]);
	for (int i = 0; i < elemLen; i++) {
		if (insert(bsTree, elements[i])) {
			printf("%d ", elements[i]); // 打印成功插入元素
		} else {
			printf("\n重复的 %d", elements[i]); // 打印出重复元素
		}
	}
	putchar('\n');

	// 先序遍历
	printf("先序遍历结果为：");
	preOrderDFS(bsTree);
	putchar('\n');

	// 中序遍历
	printf("中序遍历结果为：");
	inOrderDFS(bsTree);
	putchar('\n');

	// 后序遍历
	printf("后序遍历结果为：");
	postOrderDFS(bsTree);
	putchar('\n');

	// 层次遍历输出
	printf("层次遍历结果为：");
	levelOrder(bsTree);
	putchar('\n');

	// 查找
	int searchKey = 40;
	TNode* searchNode = search(bsTree, searchKey);
	printf("搜索键 %d 的结果为 %d", searchKey, searchNode->key);

	searchKey = 100;
	searchNode = search(bsTree, searchKey);
	//printf("搜索键 %d 的结果为 %s", searchKey, searchNode->key);

	// 删除
	printf("删除70 和 20\n");
	removeTNode(bsTree, 70);
	removeTNode(bsTree, 20);

	// 再次进行中序遍历验证删除操作 // 预期结果：30, 40, 50, 60, 80
	printf("删除元素后中序遍历输出: ");
	inOrderDFS(bsTree);
	putchar('\n');

	// 销毁
	destoryPost(bsTree);

	return 0;
}