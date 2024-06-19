#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/*
Date:2024.6.19
Title:��̬�ڴ溯����������
Content:
1.��NULLָ��Ľ����ò���
2.�Զ�̬���ٿռ��Խ�����
3.�ԷǶ�̬�����ڴ�ʹ��free�ͷ�
4.ʹ��free�ͷ�һ�鶯̬�����ڴ��һ����
5.��ͬһ�鶯̬�ڴ����ͷ�
6.��̬�����ڴ������ͷţ��ڴ�й©��

*/

/*
1.���ܷ���ʧ��, ���Ŀ�ָ��
*/
void nullPoint(void) {
	int* p = (int*)malloc(INT_MAX / 4);
	if (NULL == p) { // ʹ��ָ��ǰ���ж��Ƿ��ָ��
		return;
	}
	*p = 20; // ���p��ֵ��NULL���ͻ������⣬
	free(p);
}

/*
2.Խ�����
*/
void crossBorderVisits(void) {
	int i = 0;
	int* p = (int*)malloc(10 * sizeof(int));
	if (NULL == p) {
		exit(EXIT_FAILURE);
	}
	for (i = 0; i <= 10; i++) {
		*(p + i) = i; // ��i��10��ʱ��Խ�����
	}
	free(p);
}

/*
3.�ԷǶ�̬�����ڴ�ʹ��free�ͷ�
*/
void errorRelease(void) {
	int a = 10;
	int* p = &a;
	free(p); // pָ��Ƕ�̬���ٿռ�
}

/*
4.�ͷ�һ�鶯̬�����ڴ��һ����
*/
void partialFree(void) {
	int* p = (int*)malloc(100);
	if (NULL == p) {
		return;
	}
	p++; // p����ָ��̬�ڴ����ʼλ��
	free(p); 
}

/*
5.����ͷ�
*/
void multipleFree(void) {
	int* p = (int*)malloc(100);
	free(p); // �Ѿ��ͷ�
	free(p); // �ظ��ͷ�ͬһ�ռ�
}

/*
6.�����ͷţ��ڴ�й©��
*/
void forgotToFree(void) {
	int* p = (int*)malloc(100);
	if (NULL != p) {
		*p = 20;
	}
}


int main(void) {
	//crossBorderVisits();
	//errorRelease();
	//partialFree();
	//multipleFree();
	//forgotToFree();
	return 0;
}
