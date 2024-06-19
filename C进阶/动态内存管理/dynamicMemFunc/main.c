#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/*
Date:2024.6.19
Title:��̬�ڴ����
Content:
1.��̬�ڴ溯��
	malloc
	calloc
	realloc
	free
2.
*/

// �䳤���飺ͨ������ָ�����鳤�ȵķ�ʽ
// C99��׼��vs��֧�֣�gcc֧��
//int n = 0;
//scanf("%d", &n);
//int arr[n];

/*
malloc ����
*/
void learnMalloc(void) {
	int arr[10] = { 0 }; // ��̬���飬ջ��
	//int* p = (int*)malloc(INT_MAX); // ����ʧ�ܣ����ؿ�ָ�룬����p = NULL
	int* p = (int*)malloc(40); // ��̬���飬����
	if (NULL == p) {
		printf("%s\n", strerror(errno));
		return;
	} else {
		printf("allocate successfully\n");
	}

	// ʹ��
	for (int i = 0; i < 10; i++) {
		*(p + i) = i;
	}
	for (int i = 0; i < 10; i++) {
		printf("%d ", p[i]);
	}

	// ���û��free�������˳�ʱ��ϵͳ���Զ������ڴ�ռ�
	free(p); // pָ��Ŀռ䱻�ͷţ���pָ����ָ���ͷŵĿռ�
	p = NULL; // ��p��NULL
}

void learnCalloc(void) {

	// ���ٿռ�
	int* p = (int*)calloc(10, sizeof(int));
	if (NULL == p) {
		printf("%s\n", strerror(errno));
	} else {
		printf("allocate successfully\n");
	}

	// ʹ��
	for (int i = 0; i < 10; i++) {
		*(p + i) = i;
	}
	for (int i = 0; i < 10; i++) {
		printf("%d ", p[i]);
	}

	// �ͷſռ�
	free(p);
	p = NULL;
}

void learnRealloc(void) {
	int* p = (int*)realloc(NULL, 40);
	if (NULL == p) {
		printf("%s\n", strerror(errno));
	} else {
		printf("allocate successfully\n");
	}

	// ʹ��
	for (int i = 0; i < 10; i++) {
		*(p + i) = i;
	}
	for (int i = 0; i < 10; i++) {
		printf("%d ", p[i]);
	}
	putchar('\n');

	// �����ռ�
	int* ptr = (int*)realloc(p, 80); // ע����ܻ᷵�ؿ�ָ�룬���Բ�Ҫ��ԭָ��ֱ�ӽ���
	if (NULL == ptr) {
		p = ptr;
	}
	// ʹ��
	for (int i = 0; i < 20; i++) {
		printf("%d ", p[i]);
	}

	// �ͷ�
	free(p);
	p = NULL;
}

/*
������
*/
int main(void) {
	//learnMalloc();
	//learnCalloc();
	learnRealloc();
	return 0;
}