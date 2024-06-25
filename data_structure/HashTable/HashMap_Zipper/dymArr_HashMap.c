/*********************************
Date:2024.6.25
Title:HashMap动态数组实现
Author:JiaZiChunQiu
Content:
**********************************/

#include "dymArr_HashMap.h"

// hashFunc
static uint32_t hash(const void* key, int len, uint32_t seed);

// 扩容
static bool resizeHashMap(DymicHM* hashmap);

// 创建一个的哈希表，构造函数
DymicHM* createHashMap() {
	// 创建哈希表
	DymicHM* hashmap = calloc(1, sizeof(DymicHM));
	if (!hashmap) {
		perror("createHashMap");
		return NULL;
	}

	// 创建桶数组
	KVNode** newBuckets = (KVNode**)calloc(DEFAULT_CAPACITY, sizeof(KVNode*));
	if (!newBuckets) {
		perror("createHashMap_newBuckets");
		free(hashmap);
		return NULL;
	}

	// 初始化
	hashmap->buckets = newBuckets;
	hashmap->capacity = DEFAULT_CAPACITY; // 设置默认容量大小
	hashmap->hashSeed = time(NULL); // 设置种子
	
	// 返回地址
	return hashmap;
}

// 销毁一个哈希表，析构函数
bool destroyHashMap(DymicHM* hashmap) {
	assert(hashmap);

	// 释放键值对结构
	if (!isEmpty(hashmap)) {
		for (int i = 0; i < hashmap->size; i++) {
			KVNode* curr = hashmap->buckets[i];
			while (curr) {
				KVNode* tmp = curr->next;
				free(curr);
				curr = tmp;
			}
		}
	}

	// 释放哈希结构
	free(hashmap->buckets);
	free(hashmap);
	return true;
}

// 判空
bool isEmpty(DymicHM* hashmap) {
	assert(hashmap);
	if (!hashmap->size) {
		printf("HashMap is empty");
		return true;
	} else {
		return false;
	}
}

// 负载因子
double loadFactor(DymicHM* hashmap) {
	assert(hashmap);
	return (double)hashmap->size / (double)hashmap->capacity;
}

// 重新计算哈希值，并将传入的Node放入新的桶数组中
static int rehash(KVNode* kv, KVNode** newBuckets, int newCapacity, uint32_t seed) {
	// 计算key
	int len = strlen(kv->key);
	int idx = hash(kv->key, len, seed) % newCapacity;

	// 头插法
	kv->next = newBuckets[idx];
	newBuckets[idx] = kv;
}

// 扩容哈希表
static bool resizeHashMap(DymicHM* hashmap) {
	assert(hashmap);
	// 判断负载因子
	if (loadFactor(hashmap) < LOAD_FACTOR_THRESHOLD) return false; // 不需要扩容

	// 新容量
	int oldCapacity = hashmap->capacity;
	int newCapacity = oldCapacity > THRESHOLD ? (oldCapacity + oldCapacity >> 1) : (oldCapacity << 1);

	// 分配新的指针数组
	KVNode** newBuckets = (KVNode*)calloc(newCapacity, sizeof(KVNode));
	if (!newBuckets) {
		perror("resizeHashMap_newBuckets");
		return false;
	}

	// 每次扩容重置种子
	uint32_t seed = time(NULL);

	// 遍历所有元素结点，调用rehash()函数
	for (int i = 0; i < hashmap->capacity; i++) {
		KVNode* curr = hashmap->buckets[i];
		while (curr) {
			KVNode* tmp = curr->next;
			rehash(curr, newBuckets, newCapacity, seed); // 注意不要free键值对结点，结点已经被链接到新数组中了
			curr = tmp;
		}
	}

	// 抛弃旧的数组桶
	free(hashmap->buckets);

	// 重置hashmap
	hashmap->buckets = newBuckets;
	hashmap->capacity = newCapacity;
	hashmap->hashSeed = seed;

	return true;
}

// 添加一个键值对
ValType putKV(DymicHM* hashmap, KeyType key, const ValType val) {
	assert(hashmap);
	// 计算hash值
	int idx = hash(key, strlen(key), hashmap->hashSeed) % (hashmap->capacity);

	// 循环遍历桶数组，有相同的key则更新value，返回旧value，若没有进行下面步骤
	KVNode* curr = hashmap->buckets[idx];
	while (curr) {
		if (strcmp(key, curr->key) == 0) {
			ValType oldVal = curr->value;
			curr->value = val;
			return oldVal;
		}
		curr = curr->next;
	}

	// 判断需不需要扩容，扩容则需要重新计算hash
	if (resizeHashMap(hashmap)) {
		hash(key, strlen(key), hashmap->hashSeed);
	}

	// 桶中没有该Key，创建KVNode，遍历查看是否有该key的结点
	KVNode* newNode = calloc(1, sizeof(KVNode));
	if (!newNode) {
		perror("putKV");
		return NULL;
	}

	// 初始化结点
	newNode->key = key;
	newNode->value = val;

	// 头插插入桶中
	newNode->next = hashmap->buckets[idx];
	hashmap->buckets[idx] = newNode;

	// 结点大小+1
	hashmap->size++;
	
	return newNode->value;
}

// 查询一个键值对
ValType* getValue(DymicHM* hashmap, KeyType key) {
	assert(hashmap);
	// 判空
	if (isEmpty(hashmap)) return NULL;

	// 获取到key对应的桶数组索引
	int idx = hash(key, strlen(key), hashmap->hashSeed) % (hashmap->capacity);

	// 在桶中查找是否存在该KVNode
	KVNode* curr = hashmap->buckets[idx];
	while (curr) {
		if (strcmp(key, curr->key) == 0) {
			return curr->value;
		}
		curr = curr->next;
	}

	return NULL;
}

// 删除某个键值对
bool removeKV(DymicHM* hashmap, KeyType key) {
	assert(hashmap);
	// 判空
	if (isEmpty(hashmap)) return NULL;

	// 获取到key对应的桶数组索引
	int idx = hash(key, strlen(key), hashmap->hashSeed) % (hashmap->capacity);

	// 在桶中查找是否存在该KVNode
	KVNode* prev = NULL;
	KVNode* curr = hashmap->buckets[idx];
	while (curr) {
		// 找到
		if (strcmp(key, curr->key) == 0) {
			if (!prev) {
				hashmap->buckets[idx] = curr->next;
			} else {
				prev->next = curr->next;
			}
			free(curr);
			hashmap->size--;
			return true;
		}
		prev = curr;
		curr = curr->next;
	}

	printf("the key is not in hashmap\n");
	return false;
}

// 打印哈希表
void printAllKV (DymicHM* hashmap) {
	assert(hashmap);
	if (isEmpty(hashmap)) return;
	for (int i = 0; i < hashmap->capacity; i++) {
		KVNode* curr = hashmap->buckets[i];
		while (curr) {
			printf("%s->%s\n", curr->key, curr->value);
			curr = curr->next;
		}
	}
	printf("All key-value pairs have been printed\n");
}

// HashFunction
/* murmur_hash2 */
static uint32_t hash(const void* key, int len, uint32_t seed) {
	const uint32_t m = 0x5bd1e995;
	const int r = 24;
	uint32_t h = seed ^ len;
	const unsigned char* data = (const unsigned char*)key;

	while (len >= 4) {
		uint32_t k = *(uint32_t*)data;
		k *= m;
		k ^= k >> r;
		k *= m;
		h *= m;
		h ^= k;
		data += 4;
		len -= 4;
	}

	switch (len) {
		case 3: h ^= data[2] << 16;
		case 2: h ^= data[1] << 8;
		case 1: h ^= data[0];
			h *= m;
	};

	h ^= h >> 13;
	h *= m;
	h ^= h >> 15;

	return h;
}