#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#define DEFAULT_CAPACITY 8 // 默认大小
#define LOAD_FACTOR_THRESHOLD  0.75     // 负载因子的阈值
#define THRESHOLD 1024 // 阈值，未到达1.5倍扩容，否则扩容一倍

typedef char* KeyType;
typedef char* ValType;

// 键值对结点结构
typedef struct KeyValNode {
	KeyType key; // 键
	ValType value; // 值
	struct KeyValNode* next; // 下个Node
}KVNode;

// 哈希表结构
typedef struct {
	KVNode** buckets; // 动态数组指向存放KVNode类型指针的数组
	int size; // 键值对个数
	int capacity; // 数组长度
	uint32_t hashSeed; // 哈希函数需要的种子
}DymicHM;


// 创建一个的哈希表，构造函数
DymicHM* createHashMap();

// 判空
bool isEmpty(DymicHM* hashmap);

// 销毁一个哈希表，析构函数
bool destroyHashMap(DymicHM* hashmap);

// 负载因子
double loadFactor(DymicHM* hashmap);

// 添加一个键值对
ValType putKV(DymicHM* hashmap, KeyType key, const ValType val);

// 查询一个键值对
ValType* getValue(DymicHM* hashmap, KeyType key);

// 删除某个键值对
bool removeKV(DymicHM* hashmap, KeyType key);

// 打印哈希表
void printAllKV(DymicHM* hashMap);