#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#define BITWORD_SHIFT 5 // 计算位个数占几个字节需要除以32得到整数
#define BIT_PER_WORD 32 // 存储位的基本单元的字节
#define BITWORD_MASK 31 // 用于%31 获取到多余字节的位的个数
#define BITWORDS_NUM(bitSize) ((bitSize + BIT_PER_WORD - 1) >> BITWORD_SHIFT) // 获取字节个数

/*
* 输入的n表示下标，从零开始，并不是从1开始的第几
* bitSize为0/1bit 位的个数
* BIT_PER_WORD：
* bitSize + BIT_PER_WORD - 1：当不足32个时，相处为0，所以加上31凑数，不影响/32的结果
* BITWORD_SHIFT：作用向左位移5位，相当于除以32得到字节个数，便于定位
* 扩容规则每次扩容到设置bit的index需要的位置
*/

// 位图结构体，为数组
typedef struct {
	uint32_t* bitList; // 位图
	size_t bitSize; // 位的个数
}BitMap;

// 创建初始化
BitMap* createBitMap(size_t bitSize);

// 销毁
bool destoryBitMap(BitMap* bitmap);

// 置1
bool setBit(BitMap* bitmap, size_t index);

// 置0
bool unsetBit(BitMap* bitmap, size_t index);

// 判1
bool isSet(BitMap* bitmap, size_t index);

// 清0
bool clearBitMap(BitMap* bitmap);