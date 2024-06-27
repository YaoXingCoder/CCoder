#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "Queue.h"

typedef int KeyType; // ������
typedef int ValType; // ֵ����

// ���ṹ��
typedef struct TreeNode {
	KeyType key; // ���ֵ
	ValType val; // �����ֵ
	struct TreeNode* left; // ������
	struct TreeNode* right; // ������
}TNode;

// ���ṹ�壬���ڵ�
typedef struct {
	TNode* root;
}BST;

/* �������ڵ� */
BST* createBST(void);

/* ����-���� */
bool destoryPost(BST* bst);

/* ����key������ */
bool insert(BST* bst, const KeyType key);

/* ����key������㷵��ֵ */
TNode* search(const BST* bst, const KeyType key);

/* ����keyɾ����� */
TNode removeTNode(BST* bst, const KeyType key);

/* ��ȱ���-������� */
bool preOrderDFS(BST* bst);

/* ��ȱ���-������� */
bool inOrderDFS(BST* bst);

/* ��ȱ���-������� */
bool postOrderDFS(BST* bst);

/* ��ȱ���-��α��� */
bool levelOrder(BST* bst);