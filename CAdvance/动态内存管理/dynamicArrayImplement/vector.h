#pragma once
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <assert.h>

#define INIT_CAPA 8
#define MAX_PREALLOC  1024

typedef int E; // ���ڸ��Ĵ�������������
typedef struct {
	E* elements;
	int capacity;
	int size;
}Vector;

// ���캯���������յĶ�̬����
Vector* createNullVec(void);

// �������������ٶ�̬����
void destoryVec(Vector* v);

// ʵ����������� ׷��ֵ
void appendVal(Vector* v, E val);