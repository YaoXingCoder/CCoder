/*********************************
Date:2024.6.25
Title:位图实现
Author:JiaZiChunQiu
Content:
1.创建初始化 
2.销毁
3.扩容
4.置1
5.置0
6.判1
7.清0
**********************************/

#include "bitMap.h"

static bool extendBitMap(BitMap* bitmap, size_t bitSize);

/* 
* 创建初始化 
* 因为创建时使用无符号数uint32_t即32位为单位创建
* 默认创建会比需要的位数多，只能做置1，不可做其他操作
*/
BitMap* createBitMap(size_t bitSize) {
	
	// 创建位图结构体
	BitMap* bitmap = calloc(1, sizeof(BitMap));
	if (!bitmap) {
		perror("createBitMap");
		return NULL;
	}

	// 初始化
	bitmap->bitSize = bitSize;
	bitmap->bitList = (uint32_t)calloc(BITWORDS_NUM(bitSize), sizeof(uint32_t)); // 需要初始化为0且是无符号

	return bitmap;
}

/* 销毁 */
bool destoryBitMap(BitMap* bitmap) {
	assert(bitmap);
	free(bitmap->bitList);
	free(bitmap);
	return true;
}

/* 扩容 */
static bool extendBitMap(BitMap* bitmap, size_t bitSize){
	// 扩容
	uint32_t* newArr = (uint32_t)realloc(bitmap->bitList, BITWORDS_NUM(bitSize) * sizeof(uint32_t));
	if (!newArr) {
		perror("extendBitMap");
		return false;
	}
	bitmap->bitList = newArr;

	// realloc不能将新扩容的格式化所以需要格式化
	// 计算新增字节个数
	int byteNum = (BITWORDS_NUM(bitSize) - BITWORDS_NUM(bitmap->bitSize)) * sizeof(uint32_t);
	memset(bitmap->bitList + BITWORDS_NUM(bitmap->bitSize), 0, byteNum);

	// 重置位个数
	bitmap->bitSize = bitSize;
}

/* 置1 */
bool setBit(BitMap* bitmap, size_t index) {
	assert(bitmap);

	// 是否需要扩容
	if (index + 1 > bitmap->bitSize) {
		extendBitMap(bitmap, index + 1);
	}
	
	// 获取到在第几个WORD中的第几个位
	size_t words = index >> BITWORD_SHIFT;
	size_t offset = index & BITWORD_MASK;

	// 将位图中该位置位置1
	bitmap->bitList[words] |= (0x01 << offset);
	return true;
}

/* 置0 */
bool unsetBit(BitMap* bitmap, size_t index) {
	assert(bitmap);

	if (index > bitmap->bitSize - 1) {
		printf("Illegal access location");
		return false;
	}

	// 计算字节位置和偏移量
	size_t words = index >> BITWORD_SHIFT;
	size_t offset = index & BITWORD_MASK;

	// 置0
	bitmap->bitList[words] &= ~(0x01 << offset);
	return true;
}

/* 判1 */
bool isSet(BitMap* bitmap, size_t index) {
	assert(bitmap);

	if (index > bitmap->bitSize - 1) {
		printf("Illegal access location");
		return false;
	}

	// 计算字节位置和偏移量
	size_t words = index >> BITWORD_SHIFT;
	size_t offset = index & BITWORD_MASK;

	if (bitmap->bitList[words] & (0x01 << offset)) {
		return true;
	} else {
		return false;
	}

}

/* 清0 */
bool clearBitMap(BitMap* bitmap) {
	memset(bitmap->bitList, 0, BITWORDS_NUM(bitmap->bitSize));
	return true;
}
