/*************************************************************************
    > File Name: hashtable.h
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月03日 星期六 23时25分32秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 哈希表头文件, 用于存放配置信息
    > Content:
    >   1.哈希表结构
    >   2.哈希表函数
 ************************************************************************/

#ifndef __HASH_TABLE_H__
#define __HASH_TABLE_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_SIZE 100
#define EMPTY NULL

/* 键值对  */
typedef struct{
    char key[50]; // 存放配置文件的键
    void* value; // 存放配置文件的值, 从文件读取为字符串
}KeyValue;

/* 哈希表结构体, 只有桶没有链表 */
typedef struct {
    KeyValue table[MAX_SIZE];
    int size;
}HashTable;

/* hash函数  */
unsigned int hash (const char* key);

/* 初始化 */
void initHashTable (HashTable* ht);

/* 插入键值对 */
void insert(HashTable* ht, const char* key, void* value);

/* 查找值 */
void* find(HashTable* ht, const char* key);

/* 根据key, 删除键值对 */
void erase(HashTable* ht, const char* key);

/* 打印哈希表内容 */
void printHashTable(HashTable* ht);

/* 销毁 */
void destroyHashTable(HashTable* ht);


#endif
