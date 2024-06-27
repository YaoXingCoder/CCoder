/*********************************
Date:2024.6.26
Title:����������ʵ��
Author:JiaZiChunQiu
Content:
����������

**********************************/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "binarySearchTree.h"
#include "Queue.h"

//int main(void) {
	// ��������
	//QArray* queue = createQueue();
	//if (queue == NULL) {
	//	printf("��������ʧ�ܡ�\n");
	//	return 1;
	//}

	//// ��Ӳ���
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

	//// ��ӡ���������ʹ�С
	//printf("��������: %d, ���д�С: %d\n", queue->capacity, queue->size);

	//// ���Ӳ���
	//printf("���ڳ���...\n");
	//while (!isEmpty(queue)) {
	//	printf("�ѳ���: %d\n", popQueue(queue));
	//}

	//// ���ٶ���
	//destroyQueue(queue);

//	return 0;
//}


int main(void) {
	// ����
	BST* bsTree = createBST();
	if (!bsTree) {
		perror("bsTree");
		return 1;
	}

	// ����Ԫ��
	int elements[] = { 50, 30, 70, 20, 40, 60, 80, 30 };
	printf("���ڲ���:>");
	int elemLen = sizeof(elements) / sizeof(elements[0]);
	for (int i = 0; i < elemLen; i++) {
		if (insert(bsTree, elements[i])) {
			printf("%d ", elements[i]); // ��ӡ�ɹ�����Ԫ��
		} else {
			printf("\n�ظ��� %d", elements[i]); // ��ӡ���ظ�Ԫ��
		}
	}
	putchar('\n');

	// �������
	printf("����������Ϊ��");
	preOrderDFS(bsTree);
	putchar('\n');

	// �������
	printf("����������Ϊ��");
	inOrderDFS(bsTree);
	putchar('\n');

	// �������
	printf("����������Ϊ��");
	postOrderDFS(bsTree);
	putchar('\n');

	// ��α������
	printf("��α������Ϊ��");
	levelOrder(bsTree);
	putchar('\n');

	// ����
	int searchKey = 40;
	TNode* searchNode = search(bsTree, searchKey);
	printf("������ %d �Ľ��Ϊ %d", searchKey, searchNode->key);

	searchKey = 100;
	searchNode = search(bsTree, searchKey);
	//printf("������ %d �Ľ��Ϊ %s", searchKey, searchNode->key);

	// ɾ��
	printf("ɾ��70 �� 20\n");
	removeTNode(bsTree, 70);
	removeTNode(bsTree, 20);

	// �ٴν������������֤ɾ������ // Ԥ�ڽ����30, 40, 50, 60, 80
	printf("ɾ��Ԫ�غ�����������: ");
	inOrderDFS(bsTree);
	putchar('\n');

	// ����
	destoryPost(bsTree);

	return 0;
}