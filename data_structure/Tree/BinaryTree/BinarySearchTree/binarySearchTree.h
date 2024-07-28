#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "Queue.h"

typedef int KeyType; // 键类型
typedef int ValType; // 值类型

// 结点结构体
typedef struct TreeNode {
	KeyType key; // 结点值
	ValType val; // 结点存的值
	struct TreeNode* left; // 左子树
	struct TreeNode* right; // 右子树
}TNode;

// 树结构体，根节点
typedef struct {
	TNode* root;
}BST;

/* 创建根节点 */
BST* createBST(void);

/* 销毁-后序 */
bool destoryPost(BST* bst);

/* 根据key加入结点 */
bool insert(BST* bst, const KeyType key);

/* 根据key搜索结点返回值 */
TNode* search(const BST* bst, const KeyType key);

/* 根据key删除结点 */
TNode removeTNode(BST* bst, const KeyType key);

/* 深度遍历-先序遍历 */
bool preOrderDFS(BST* bst);

/* 深度遍历-中序遍历 */
bool inOrderDFS(BST* bst);

/* 深度遍历-后序遍历 */
bool postOrderDFS(BST* bst);

/* 广度遍历-层次遍历 */
bool levelOrder(BST* bst);