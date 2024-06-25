/*********************************
Date:2024.6.25
Title:λͼʵ��
Author:JiaZiChunQiu
Content:
1.������ʼ�� 
2.����
3.����
4.��1
5.��0
6.��1
7.��0
**********************************/

#include "bitMap.h"

static bool extendBitMap(BitMap* bitmap, size_t bitSize);

/* 
* ������ʼ�� 
* ��Ϊ����ʱʹ���޷�����uint32_t��32λΪ��λ����
* Ĭ�ϴ��������Ҫ��λ���ֻ࣬������1����������������
*/
BitMap* createBitMap(size_t bitSize) {
	
	// ����λͼ�ṹ��
	BitMap* bitmap = calloc(1, sizeof(BitMap));
	if (!bitmap) {
		perror("createBitMap");
		return NULL;
	}

	// ��ʼ��
	bitmap->bitSize = bitSize;
	bitmap->bitList = (uint32_t)calloc(BITWORDS_NUM(bitSize), sizeof(uint32_t)); // ��Ҫ��ʼ��Ϊ0�����޷���

	return bitmap;
}

/* ���� */
bool destoryBitMap(BitMap* bitmap) {
	assert(bitmap);
	free(bitmap->bitList);
	free(bitmap);
	return true;
}

/* ���� */
static bool extendBitMap(BitMap* bitmap, size_t bitSize){
	// ����
	uint32_t* newArr = (uint32_t)realloc(bitmap->bitList, BITWORDS_NUM(bitSize) * sizeof(uint32_t));
	if (!newArr) {
		perror("extendBitMap");
		return false;
	}
	bitmap->bitList = newArr;

	// realloc���ܽ������ݵĸ�ʽ��������Ҫ��ʽ��
	// ���������ֽڸ���
	int byteNum = (BITWORDS_NUM(bitSize) - BITWORDS_NUM(bitmap->bitSize)) * sizeof(uint32_t);
	memset(bitmap->bitList + BITWORDS_NUM(bitmap->bitSize), 0, byteNum);

	// ����λ����
	bitmap->bitSize = bitSize;
}

/* ��1 */
bool setBit(BitMap* bitmap, size_t index) {
	assert(bitmap);

	// �Ƿ���Ҫ����
	if (index + 1 > bitmap->bitSize) {
		extendBitMap(bitmap, index + 1);
	}
	
	// ��ȡ���ڵڼ���WORD�еĵڼ���λ
	size_t words = index >> BITWORD_SHIFT;
	size_t offset = index & BITWORD_MASK;

	// ��λͼ�и�λ��λ��1
	bitmap->bitList[words] |= (0x01 << offset);
	return true;
}

/* ��0 */
bool unsetBit(BitMap* bitmap, size_t index) {
	assert(bitmap);

	if (index > bitmap->bitSize - 1) {
		printf("Illegal access location");
		return false;
	}

	// �����ֽ�λ�ú�ƫ����
	size_t words = index >> BITWORD_SHIFT;
	size_t offset = index & BITWORD_MASK;

	// ��0
	bitmap->bitList[words] &= ~(0x01 << offset);
	return true;
}

/* ��1 */
bool isSet(BitMap* bitmap, size_t index) {
	assert(bitmap);

	if (index > bitmap->bitSize - 1) {
		printf("Illegal access location");
		return false;
	}

	// �����ֽ�λ�ú�ƫ����
	size_t words = index >> BITWORD_SHIFT;
	size_t offset = index & BITWORD_MASK;

	if (bitmap->bitList[words] & (0x01 << offset)) {
		return true;
	} else {
		return false;
	}

}

/* ��0 */
bool clearBitMap(BitMap* bitmap) {
	memset(bitmap->bitList, 0, BITWORDS_NUM(bitmap->bitSize));
	return true;
}
