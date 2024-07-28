#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#define BITWORD_SHIFT 5 // ����λ����ռ�����ֽ���Ҫ����32�õ�����
#define BIT_PER_WORD 32 // �洢λ�Ļ�����Ԫ���ֽ�
#define BITWORD_MASK 31 // ����%31 ��ȡ�������ֽڵ�λ�ĸ���
#define BITWORDS_NUM(bitSize) ((bitSize + BIT_PER_WORD - 1) >> BITWORD_SHIFT) // ��ȡ�ֽڸ���

/*
* �����n��ʾ�±꣬���㿪ʼ�������Ǵ�1��ʼ�ĵڼ�
* bitSizeΪ0/1bit λ�ĸ���
* BIT_PER_WORD��
* bitSize + BIT_PER_WORD - 1��������32��ʱ���ദΪ0�����Լ���31��������Ӱ��/32�Ľ��
* BITWORD_SHIFT����������λ��5λ���൱�ڳ���32�õ��ֽڸ��������ڶ�λ
* ���ݹ���ÿ�����ݵ�����bit��index��Ҫ��λ��
*/

// λͼ�ṹ�壬Ϊ����
typedef struct {
	uint32_t* bitList; // λͼ
	size_t bitSize; // λ�ĸ���
}BitMap;

// ������ʼ��
BitMap* createBitMap(size_t bitSize);

// ����
bool destoryBitMap(BitMap* bitmap);

// ��1
bool setBit(BitMap* bitmap, size_t index);

// ��0
bool unsetBit(BitMap* bitmap, size_t index);

// ��1
bool isSet(BitMap* bitmap, size_t index);

// ��0
bool clearBitMap(BitMap* bitmap);