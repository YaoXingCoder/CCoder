#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

//typedef enum month {
//	January = 1,
//	February,
//	March,
//	April,
//	May,
//	June,
//	July,
//	August,
//	September,
//	Octobar,
//	November,
//	December
//}Month;


#define INIT_CAPACITY 8
#define MAX_CAPACITY 1024

typedef int E;

typedef struct {
    E* elements;   // ָ��ѿռ������
    int size;	// Ԫ�صĸ���
    int capacity; // ���������
} Vector;

// ���캯������ȡ�ռ�
Vector* vectorCreate(void);

// �������������ٿռ�
void destoryVector(Vector* v);

// ��������������Ԫ��
void push_back(Vector* v, E val);

// ��������ǰ�����Ԫ�أ�����Ԫ�����κ���
void push_front(Vector* v, E val);

// ɾ�����һ��Ԫ��, �������һ��Ԫ�ط���
E pop_back(Vector* v);

// ɾ����һ��Ԫ�أ����ѵ�һ��Ԫ�ط���
E pop_front(Vector* v);
