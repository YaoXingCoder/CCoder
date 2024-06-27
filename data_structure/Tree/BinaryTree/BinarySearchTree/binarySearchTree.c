/*********************************
Date:2024.6.26
Title:二叉搜索树实现
Author:JiaZiChunQiu
Content:
1.创建根节点
2.判空
3.根据key加入结点
4.
5.
6.
7.
8.
9.
**********************************/

#include "binarySearchTree.h"

static bool isEmpty(const BST* bst); // 判空
static void postOrderDestory(TNode* node); // 后续遍历销毁
static void preOrder(TNode* node); // 先序
static void inOrder(TNode* node); // 中序
static void postOrder(TNode* node); // 后序

/* 创建根节点 */
BST* createBST(void) {
	return calloc(1, sizeof(BST));
}

/* 判空 */
static bool isEmpty(const BST* bst) {
	if (bst->root) {
		return false;
	} else {
		printf("Tree has no leaves\n");
		return true;
	}
}

/* 后序遍历-销毁 */
static void postOrderDestory(TNode* node) {
	if (node == NULL) return;
	postOrderDestory(node->left);
	postOrderDestory(node->right);
	free(node);
}

/* 销毁 */
bool destoryPost(BST* bst) {
	assert(bst);
	// 不为空
	if (!isEmpty(bst)) {
		postOrderDestory(bst->root); // 后序遍历删除，防止use-after问题
	}
	free(bst);
	return true;
}

/* 根据key加入结点 */
bool insert(BST* bst, const KeyType key) {
	assert(bst);

	// 不为空循环找到插入位置，插入需要前置结点
	int diff; // 根据正负找左右结点
	TNode* pre = NULL;
	TNode* curr = bst->root;
	while (curr) {
		int diff = key - curr->key;
		if (diff < 0) {
			pre = curr;
			curr = curr->left;
		} else if (diff > 0) {
			pre = curr;
			curr = curr->right;
		} else {
			printf("\nThis key is already in Tree\n");
			return false; // key相等则已经有该节点
		}
	}

	// new个结点
	TNode* newNode = calloc(1, sizeof(TNode));
	if (!newNode) {
		perror("insert");
		return false;
	}
	newNode->key = key;

	// 若前置结点为NULL，则Tree为空
	if (!pre) {
		bst->root = newNode;
		return true;
	}

	// 不为空插入到curr的位置
	diff = key - pre->key; // 到新位置，重新计算diff决定左右
	if (diff < 0) {
		pre->left = newNode;
	} else if (diff > 0){
		pre->right = newNode;
	}

	return true;
}

/* 根据key搜索结点返回值 */
TNode* search(const BST* bst, const KeyType key) {
	assert("bst");

	// 判空
	if (isEmpty(bst)) return NULL;

	// 遍历
	int diff;
	TNode* curr = bst->root;
	while (curr) {
		diff = key - curr->key;
		if (diff < 0) {
			curr = curr->left;
		} else if (diff > 0) {
			curr = curr->right;
		} else {
			return curr; // 找到返回当前结点
		}
	}

	// 未找到
	printf("The Node is not in Tree\n");
	return NULL;
}

/* 根据key删除结点 */
 TNode removeTNode(BST* bst, const KeyType key) {
	assert(bst);

	// 判空
	if (isEmpty(bst)) return ;

	/*
	* while循环结束时, 有两种可能性:
	* 1.找到目标key结点, 于是break结束循环.
	*   此时curr指向目标结点, parent指向目标结点的父结点
	*
	* 2.目标key结点不存在, 于是curr是一个NULL时结束循环
	*   这其实就相当于在插入结点时,我们找到了插入位置
	*   但在删除时,我们不需要
	*   找不到目标结点,直接返回false结束函数,表示删除失败
	*/
	int diff;
	TNode* pre = NULL;
	TNode* curr = bst->root;
	while (curr) {
		diff = key - curr->key;
		if (diff < 0) {
			pre = curr;
			curr = curr->left;
		} else if (diff > 0) {
			pre = curr;
			curr = curr->right;
		} else {
			break; // 找到后，根据情况删除
		}
	}
	
	// 左右子节点都在，将度为2的结点删除降级成删除度为1或0
	if (curr->left && curr->right) {
		TNode* minPre = curr;
		TNode* min = curr->right; // 找到子树的最左叶子结点
		/*
		* curr结点有左子树也有右子树,它就是一个度为2的结点,于是进行降级处理
		* 降级处理最终:
		* 1.需要找到curr结点的右子树最小结点,以及该最小结点的前驱结点
		* 2.需要用最小结点的key值覆盖curr结点的key值
		* 所以整个过程不要直接使用curr和parent指针遍历,而是新建两个临时指针
		* 指针名字的目的是为了代码更好的可读性,所以必要的时候,不要不舍得申请临时指针
		*/
		while (min->left) {
			minPre = min;
			min = min->left;
		}
		curr->key = min->key; // 替换当前curr的值
		pre = minPre; // 指向min的父节点
		curr = min; // 指向min结点
	}

	/*
	* 这里的操作就是在知道前驱和后继的情况下,删除链表的一个结点
	* 但BST又有点特殊,你需要先搞清楚后继是哪个结点,才能够让前驱指向后继
	*/
	TNode* child = curr->left ? curr->left : curr->right; // 获取key的子节点
	diff = curr->key - pre->key; // 需要重新计算key，curr的key可能经过替换

	if (!pre) {
		bst->root = child; // 若为空，则根节点指向child
	}else if (diff < 0) {
		pre->left = child;
	} else if (diff > 0) {
		pre->right = child;
	} else {
		pre->right = child;
	} // 相等仅出现在度为2退化为1，且右子树的第一个为最小值时出现

	TNode tmp = *curr; // 保存返回值
	free(curr); // 释放
	return tmp;
}

/* 深度遍历-先序遍历 */
static void preOrder(TNode* node) {
	if (!node) return;
	printf("%d ", node->key);
	preOrder(node->left);
	preOrder(node->right);
}

bool preOrderDFS(BST* bst) {
	assert("bst");
	// 判空
	if (isEmpty(bst)) return false;
	// 调用递归函数
	preOrder(bst->root);
	return true;
}

/* 深度遍历-中序遍历 */
static void inOrder(TNode* node) {
	if (!node) return;
	inOrder(node->left);
	printf("%d ", node->key);
	inOrder(node->right);
}

bool inOrderDFS(BST* bst) {
	assert("bst");
	// 判空
	if (isEmpty(bst)) return false;
	// 调用递归函数
	inOrder(bst->root);
	return true;
}

/* 深度遍历-后序遍历 */
static void postOrder(TNode* node) {
	if (!node) return;
	postOrder(node->left);
	postOrder(node->right);
	printf("%d ", node->key);
}

bool postOrderDFS(BST* bst) {
	assert("bst");
// 判空
	if (isEmpty(bst)) return false;
	// 调用递归函数
	postOrder(bst->root);
	return true;
}

/* 广度遍历-层次遍历 */
bool levelOrder(BST* bst) {
	QArray* queue = createQueue();
	pushQueue(queue, bst->root);
	while (!isEmpty_Q(queue)) {
		int levelSize = queue->size;
		for (int i = 0; i < levelSize; i++) {
			TNode* node = popQueue(queue); // 依层次进入队列
			printf("%d ", node->key);
			if (node->left) {
				pushQueue(queue, node->left);
			}
			if (node->right) {
				pushQueue(queue, node->right);
			}
		}
		putchar('\n');
	} // 每次入队出队都会更改size
	printf("\n");
	destroyQueue(queue);
}