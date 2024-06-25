/*********************************
Date:2024.6.25
Title:位图实现
Author:JiaZiChunQiu
Content:
**********************************/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "bitMap.h"

//int main(void) {
//	BitMap* bitmap = createBitMap(120);
//	setBit(bitmap, 0);
//	setBit(bitmap, 1);
//	setBit(bitmap, 33);
//
//	setBit(bitmap, 160);
//
//	printf("%u\n", isSet(bitmap, 0));
//
//	unsetBit(bitmap, 1);
//
//	printf("%d\n", destoryBitMap(bitmap));
//	return 0;
//}

/*
* 给定一个仅包含小写字母的字符串，请去除字符串中的重复字母，使得每个字母只出现一次。
* 并按字母从小到大输出。
* 示例：
* 输入："bcabc"
* 输出："abc"
*/

/* 
比较器
*/ 
int cmpChar(const void* q1, const void* q2) {
	return strcmp((char*)q1, (char*)q2);
}

/* 
逆转函数
*/
void remove_duplicate_and_sort(char* str) {
	int len = strlen(str); // 记
	char* start = str;
	int i = 1;
	BitMap* bitmap = createBitMap(120);

	// 去重
	while (*start != '\n') {
		uint32_t index = (uint32_t)(*start % bitmap->bitSize);
		if (isSet(bitmap, index)) {
			*start = '\0';
			start++;
			i++;
			continue;
		}
		setBit(bitmap, index);
		start++;
	}

	// 排序
	qsort(str, len, sizeof(str[0]), cmpChar);

	// 重定位字符传的头个地址
	str += i;
	printf("%s\n", str);
}

/*
* 主函数
*/
int main(void) {
	char arr[10] = { 0 };
	int i = 0;
	while ((arr[i] = getchar()) != '\n') {
		i++;
	}
	remove_duplicate_and_sort(arr);
	return 0;
}