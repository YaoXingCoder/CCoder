/*************************************************************************
    > File Name: hashtable.c
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月03日 星期六 23时47分51秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 哈希表实现
    > Content:
    >   1.用于存储配置文件的键值对信息
    >   2.哈希冲突解决, 线性探测
 ************************************************************************/

#include "hashtable.h"
#include <string.h>


/* hash函数  */
unsigned int hash (const char* key){
    unsigned int hashVal = 0;
    while( *key != '\0' ) {
        hashVal = (hashVal << 5) + hashVal + *key++;
    }
    return hashVal % MAX_SIZE;
}

/* 初始化 */
void initHashTable (HashTable* ht){
    assert(ht);
    for( int i = 0; i < MAX_SIZE; ++i ) {
        strcpy(ht->table[i].key, ""); // 初始化key
        ht->table[i].value = EMPTY; // 初始化value
    }
}

/* 插入键值对 */
void insert(HashTable* ht, const char* key, void* value){
    assert(ht);
    unsigned idx = hash(key); // hash对应的哈希桶下标
    
    /* 哈希冲突 */
    // 因为key被初始化为空字符, 所以使用value判断是否为NULL
    while( ht->table[idx].value != EMPTY ) {
        if ( strcmp(ht->table[idx].key, key ) == 0 ){
            ht->table[idx].value = value; //key值相同, 即哈希冲突, 替换值
            return;
        }
        idx = (idx + 1) % MAX_SIZE; // 每次循环idx都+1
    } // 该哈希后的下标, value == NULL, 不进入

    /* 插入新键值对 */
    strcpy(ht->table[idx].key ,key);
    ht->table[idx].value = value;
    ht->size++;

}

/* 查找值 */
void* find(HashTable* ht, const char* key){
    assert(ht);
    unsigned int idx = hash(key);
    while(ht->table[idx].value != EMPTY) {
        if (strcmp(ht->table[idx].key , key) == 0) {
            return ht->table[idx].value;
        }
        idx = ( idx + 1 ) % MAX_SIZE;
    }
    return EMPTY; // 没有key对应的值
}

/* 根据key, 删除键值对 */
void erase(HashTable* ht, const char* key){
    assert(ht);
    unsigned int idx = hash(key);
    while(ht->table[idx].value != EMPTY) {
        if ( strcmp(ht->table[idx].key, key) == 0 ) {
            strcpy(ht->table[idx].key, "");
            ht->table[idx].value = EMPTY;
            ht->size--;
            return;
        }
        idx = (idx + 1) % MAX_SIZE;
    }
    printf("HashTable hasnt the key %s\n", key);
}

/* 打印哈希表内容 */
void printHashTable(HashTable* ht){
    assert(ht);
    for(int i = 0; i < ht->size; i++) {
        if ( ht->table[i].value != EMPTY ) {
            printf("Key: %s, Value: %s\n", ht->table[i].key, ht->table[i].value);
        }
        putchar('\n');
    }
}

/* 销毁 */
void destroyHashTable(HashTable* ht){
    for( int i = 0; i < MAX_SIZE; ++i) {
        if (ht->table[i].value != EMPTY) {
            strcpy(ht->table[i].key, "");
            free(ht->table[i].value);
            ht->table[i].value = EMPTY;
            ht->size--;
        }
    }
}

