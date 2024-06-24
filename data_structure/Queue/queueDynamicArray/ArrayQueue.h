#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

#define DEFAULE_CAPACITY 6 // ���г�ʼ����
#define THRESHOL 1000 // ��ֵ������1.5���ݣ�����2����

typedef int ElementType;

typedef struct {
	ElementType* elements;
	int front; // ����ָ��
	int rear; // βָ��
	int size; // ��ǰ������Ԫ������
	int capacity; // ��������
}QArray;

// ������̬�������
QArray* createQueue();

// ���ٶ�̬�������
bool destroyQueue(QArray* qArr);

// �п�
bool isEmpty(QArray* qArr);

// ����
bool isFull(QArray* qArr);

// ���
bool pushQueue(QArray* qArr, ElementType data);

// ���Ӳ����ض�ͷֵ
ElementType popQueue(QArray* qArr);

// ���ʶ���Ԫ��
ElementType peekQueue(const QArray* qArr);