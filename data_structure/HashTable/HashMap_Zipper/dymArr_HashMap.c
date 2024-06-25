/*********************************
Date:2024.6.25
Title:HashMap��̬����ʵ��
Author:JiaZiChunQiu
Content:
**********************************/

#include "dymArr_HashMap.h"

// hashFunc
static uint32_t hash(const void* key, int len, uint32_t seed);

// ����
static bool resizeHashMap(DymicHM* hashmap);

// ����һ���Ĺ�ϣ�����캯��
DymicHM* createHashMap() {
	// ������ϣ��
	DymicHM* hashmap = calloc(1, sizeof(DymicHM));
	if (!hashmap) {
		perror("createHashMap");
		return NULL;
	}

	// ����Ͱ����
	KVNode** newBuckets = (KVNode**)calloc(DEFAULT_CAPACITY, sizeof(KVNode*));
	if (!newBuckets) {
		perror("createHashMap_newBuckets");
		free(hashmap);
		return NULL;
	}

	// ��ʼ��
	hashmap->buckets = newBuckets;
	hashmap->capacity = DEFAULT_CAPACITY; // ����Ĭ��������С
	hashmap->hashSeed = time(NULL); // ��������
	
	// ���ص�ַ
	return hashmap;
}

// ����һ����ϣ����������
bool destroyHashMap(DymicHM* hashmap) {
	assert(hashmap);

	// �ͷż�ֵ�Խṹ
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

	// �ͷŹ�ϣ�ṹ
	free(hashmap->buckets);
	free(hashmap);
	return true;
}

// �п�
bool isEmpty(DymicHM* hashmap) {
	assert(hashmap);
	if (!hashmap->size) {
		printf("HashMap is empty");
		return true;
	} else {
		return false;
	}
}

// ��������
double loadFactor(DymicHM* hashmap) {
	assert(hashmap);
	return (double)hashmap->size / (double)hashmap->capacity;
}

// ���¼����ϣֵ�����������Node�����µ�Ͱ������
static int rehash(KVNode* kv, KVNode** newBuckets, int newCapacity, uint32_t seed) {
	// ����key
	int len = strlen(kv->key);
	int idx = hash(kv->key, len, seed) % newCapacity;

	// ͷ�巨
	kv->next = newBuckets[idx];
	newBuckets[idx] = kv;
}

// ���ݹ�ϣ��
static bool resizeHashMap(DymicHM* hashmap) {
	assert(hashmap);
	// �жϸ�������
	if (loadFactor(hashmap) < LOAD_FACTOR_THRESHOLD) return false; // ����Ҫ����

	// ������
	int oldCapacity = hashmap->capacity;
	int newCapacity = oldCapacity > THRESHOLD ? (oldCapacity + oldCapacity >> 1) : (oldCapacity << 1);

	// �����µ�ָ������
	KVNode** newBuckets = (KVNode*)calloc(newCapacity, sizeof(KVNode));
	if (!newBuckets) {
		perror("resizeHashMap_newBuckets");
		return false;
	}

	// ÿ��������������
	uint32_t seed = time(NULL);

	// ��������Ԫ�ؽ�㣬����rehash()����
	for (int i = 0; i < hashmap->capacity; i++) {
		KVNode* curr = hashmap->buckets[i];
		while (curr) {
			KVNode* tmp = curr->next;
			rehash(curr, newBuckets, newCapacity, seed); // ע�ⲻҪfree��ֵ�Խ�㣬����Ѿ������ӵ�����������
			curr = tmp;
		}
	}

	// �����ɵ�����Ͱ
	free(hashmap->buckets);

	// ����hashmap
	hashmap->buckets = newBuckets;
	hashmap->capacity = newCapacity;
	hashmap->hashSeed = seed;

	return true;
}

// ���һ����ֵ��
ValType putKV(DymicHM* hashmap, KeyType key, const ValType val) {
	assert(hashmap);
	// ����hashֵ
	int idx = hash(key, strlen(key), hashmap->hashSeed) % (hashmap->capacity);

	// ѭ������Ͱ���飬����ͬ��key�����value�����ؾ�value����û�н������沽��
	KVNode* curr = hashmap->buckets[idx];
	while (curr) {
		if (strcmp(key, curr->key) == 0) {
			ValType oldVal = curr->value;
			curr->value = val;
			return oldVal;
		}
		curr = curr->next;
	}

	// �ж��費��Ҫ���ݣ���������Ҫ���¼���hash
	if (resizeHashMap(hashmap)) {
		hash(key, strlen(key), hashmap->hashSeed);
	}

	// Ͱ��û�и�Key������KVNode�������鿴�Ƿ��и�key�Ľ��
	KVNode* newNode = calloc(1, sizeof(KVNode));
	if (!newNode) {
		perror("putKV");
		return NULL;
	}

	// ��ʼ�����
	newNode->key = key;
	newNode->value = val;

	// ͷ�����Ͱ��
	newNode->next = hashmap->buckets[idx];
	hashmap->buckets[idx] = newNode;

	// ����С+1
	hashmap->size++;
	
	return newNode->value;
}

// ��ѯһ����ֵ��
ValType* getValue(DymicHM* hashmap, KeyType key) {
	assert(hashmap);
	// �п�
	if (isEmpty(hashmap)) return NULL;

	// ��ȡ��key��Ӧ��Ͱ��������
	int idx = hash(key, strlen(key), hashmap->hashSeed) % (hashmap->capacity);

	// ��Ͱ�в����Ƿ���ڸ�KVNode
	KVNode* curr = hashmap->buckets[idx];
	while (curr) {
		if (strcmp(key, curr->key) == 0) {
			return curr->value;
		}
		curr = curr->next;
	}

	return NULL;
}

// ɾ��ĳ����ֵ��
bool removeKV(DymicHM* hashmap, KeyType key) {
	assert(hashmap);
	// �п�
	if (isEmpty(hashmap)) return NULL;

	// ��ȡ��key��Ӧ��Ͱ��������
	int idx = hash(key, strlen(key), hashmap->hashSeed) % (hashmap->capacity);

	// ��Ͱ�в����Ƿ���ڸ�KVNode
	KVNode* prev = NULL;
	KVNode* curr = hashmap->buckets[idx];
	while (curr) {
		// �ҵ�
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

// ��ӡ��ϣ��
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