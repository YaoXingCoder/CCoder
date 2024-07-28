#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#define DEFAULT_CAPACITY 8 // Ĭ�ϴ�С
#define LOAD_FACTOR_THRESHOLD  0.75     // �������ӵ���ֵ
#define THRESHOLD 1024 // ��ֵ��δ����1.5�����ݣ���������һ��

typedef char* KeyType;
typedef char* ValType;

// ��ֵ�Խ��ṹ
typedef struct KeyValNode {
	KeyType key; // ��
	ValType value; // ֵ
	struct KeyValNode* next; // �¸�Node
}KVNode;

// ��ϣ��ṹ
typedef struct {
	KVNode** buckets; // ��̬����ָ����KVNode����ָ�������
	int size; // ��ֵ�Ը���
	int capacity; // ���鳤��
	uint32_t hashSeed; // ��ϣ������Ҫ������
}DymicHM;


// ����һ���Ĺ�ϣ�����캯��
DymicHM* createHashMap();

// �п�
bool isEmpty(DymicHM* hashmap);

// ����һ����ϣ����������
bool destroyHashMap(DymicHM* hashmap);

// ��������
double loadFactor(DymicHM* hashmap);

// ���һ����ֵ��
ValType putKV(DymicHM* hashmap, KeyType key, const ValType val);

// ��ѯһ����ֵ��
ValType* getValue(DymicHM* hashmap, KeyType key);

// ɾ��ĳ����ֵ��
bool removeKV(DymicHM* hashmap, KeyType key);

// ��ӡ��ϣ��
void printAllKV(DymicHM* hashMap);