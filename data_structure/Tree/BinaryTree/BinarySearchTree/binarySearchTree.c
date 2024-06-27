/*********************************
Date:2024.6.26
Title:����������ʵ��
Author:JiaZiChunQiu
Content:
1.�������ڵ�
2.�п�
3.����key������
4.
5.
6.
7.
8.
9.
**********************************/

#include "binarySearchTree.h"

static bool isEmpty(const BST* bst); // �п�
static void postOrderDestory(TNode* node); // ������������
static void preOrder(TNode* node); // ����
static void inOrder(TNode* node); // ����
static void postOrder(TNode* node); // ����

/* �������ڵ� */
BST* createBST(void) {
	return calloc(1, sizeof(BST));
}

/* �п� */
static bool isEmpty(const BST* bst) {
	if (bst->root) {
		return false;
	} else {
		printf("Tree has no leaves\n");
		return true;
	}
}

/* �������-���� */
static void postOrderDestory(TNode* node) {
	if (node == NULL) return;
	postOrderDestory(node->left);
	postOrderDestory(node->right);
	free(node);
}

/* ���� */
bool destoryPost(BST* bst) {
	assert(bst);
	// ��Ϊ��
	if (!isEmpty(bst)) {
		postOrderDestory(bst->root); // �������ɾ������ֹuse-after����
	}
	free(bst);
	return true;
}

/* ����key������ */
bool insert(BST* bst, const KeyType key) {
	assert(bst);

	// ��Ϊ��ѭ���ҵ�����λ�ã�������Ҫǰ�ý��
	int diff; // �������������ҽ��
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
			return false; // key������Ѿ��иýڵ�
		}
	}

	// new�����
	TNode* newNode = calloc(1, sizeof(TNode));
	if (!newNode) {
		perror("insert");
		return false;
	}
	newNode->key = key;

	// ��ǰ�ý��ΪNULL����TreeΪ��
	if (!pre) {
		bst->root = newNode;
		return true;
	}

	// ��Ϊ�ղ��뵽curr��λ��
	diff = key - pre->key; // ����λ�ã����¼���diff��������
	if (diff < 0) {
		pre->left = newNode;
	} else if (diff > 0){
		pre->right = newNode;
	}

	return true;
}

/* ����key������㷵��ֵ */
TNode* search(const BST* bst, const KeyType key) {
	assert("bst");

	// �п�
	if (isEmpty(bst)) return NULL;

	// ����
	int diff;
	TNode* curr = bst->root;
	while (curr) {
		diff = key - curr->key;
		if (diff < 0) {
			curr = curr->left;
		} else if (diff > 0) {
			curr = curr->right;
		} else {
			return curr; // �ҵ����ص�ǰ���
		}
	}

	// δ�ҵ�
	printf("The Node is not in Tree\n");
	return NULL;
}

/* ����keyɾ����� */
 TNode removeTNode(BST* bst, const KeyType key) {
	assert(bst);

	// �п�
	if (isEmpty(bst)) return ;

	/*
	* whileѭ������ʱ, �����ֿ�����:
	* 1.�ҵ�Ŀ��key���, ����break����ѭ��.
	*   ��ʱcurrָ��Ŀ����, parentָ��Ŀ����ĸ����
	*
	* 2.Ŀ��key��㲻����, ����curr��һ��NULLʱ����ѭ��
	*   ����ʵ���൱���ڲ�����ʱ,�����ҵ��˲���λ��
	*   ����ɾ��ʱ,���ǲ���Ҫ
	*   �Ҳ���Ŀ����,ֱ�ӷ���false��������,��ʾɾ��ʧ��
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
			break; // �ҵ��󣬸������ɾ��
		}
	}
	
	// �����ӽڵ㶼�ڣ�����Ϊ2�Ľ��ɾ��������ɾ����Ϊ1��0
	if (curr->left && curr->right) {
		TNode* minPre = curr;
		TNode* min = curr->right; // �ҵ�����������Ҷ�ӽ��
		/*
		* curr�����������Ҳ��������,������һ����Ϊ2�Ľ��,���ǽ��н�������
		* ������������:
		* 1.��Ҫ�ҵ�curr������������С���,�Լ�����С����ǰ�����
		* 2.��Ҫ����С����keyֵ����curr����keyֵ
		* �����������̲�Ҫֱ��ʹ��curr��parentָ�����,�����½�������ʱָ��
		* ָ�����ֵ�Ŀ����Ϊ�˴�����õĿɶ���,���Ա�Ҫ��ʱ��,��Ҫ�����������ʱָ��
		*/
		while (min->left) {
			minPre = min;
			min = min->left;
		}
		curr->key = min->key; // �滻��ǰcurr��ֵ
		pre = minPre; // ָ��min�ĸ��ڵ�
		curr = min; // ָ��min���
	}

	/*
	* ����Ĳ���������֪��ǰ���ͺ�̵������,ɾ�������һ�����
	* ��BST���е�����,����Ҫ�ȸ����������ĸ����,���ܹ���ǰ��ָ����
	*/
	TNode* child = curr->left ? curr->left : curr->right; // ��ȡkey���ӽڵ�
	diff = curr->key - pre->key; // ��Ҫ���¼���key��curr��key���ܾ����滻

	if (!pre) {
		bst->root = child; // ��Ϊ�գ�����ڵ�ָ��child
	}else if (diff < 0) {
		pre->left = child;
	} else if (diff > 0) {
		pre->right = child;
	} else {
		pre->right = child;
	} // ��Ƚ������ڶ�Ϊ2�˻�Ϊ1�����������ĵ�һ��Ϊ��Сֵʱ����

	TNode tmp = *curr; // ���淵��ֵ
	free(curr); // �ͷ�
	return tmp;
}

/* ��ȱ���-������� */
static void preOrder(TNode* node) {
	if (!node) return;
	printf("%d ", node->key);
	preOrder(node->left);
	preOrder(node->right);
}

bool preOrderDFS(BST* bst) {
	assert("bst");
	// �п�
	if (isEmpty(bst)) return false;
	// ���õݹ麯��
	preOrder(bst->root);
	return true;
}

/* ��ȱ���-������� */
static void inOrder(TNode* node) {
	if (!node) return;
	inOrder(node->left);
	printf("%d ", node->key);
	inOrder(node->right);
}

bool inOrderDFS(BST* bst) {
	assert("bst");
	// �п�
	if (isEmpty(bst)) return false;
	// ���õݹ麯��
	inOrder(bst->root);
	return true;
}

/* ��ȱ���-������� */
static void postOrder(TNode* node) {
	if (!node) return;
	postOrder(node->left);
	postOrder(node->right);
	printf("%d ", node->key);
}

bool postOrderDFS(BST* bst) {
	assert("bst");
// �п�
	if (isEmpty(bst)) return false;
	// ���õݹ麯��
	postOrder(bst->root);
	return true;
}

/* ��ȱ���-��α��� */
bool levelOrder(BST* bst) {
	QArray* queue = createQueue();
	pushQueue(queue, bst->root);
	while (!isEmpty_Q(queue)) {
		int levelSize = queue->size;
		for (int i = 0; i < levelSize; i++) {
			TNode* node = popQueue(queue); // ����ν������
			printf("%d ", node->key);
			if (node->left) {
				pushQueue(queue, node->left);
			}
			if (node->right) {
				pushQueue(queue, node->right);
			}
		}
		putchar('\n');
	} // ÿ����ӳ��Ӷ������size
	printf("\n");
	destroyQueue(queue);
}