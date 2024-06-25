/*********************************
Date:2024.6.25
Title:λͼʵ��
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
* ����һ��������Сд��ĸ���ַ�������ȥ���ַ����е��ظ���ĸ��ʹ��ÿ����ĸֻ����һ�Ρ�
* ������ĸ��С���������
* ʾ����
* ���룺"bcabc"
* �����"abc"
*/

/* 
�Ƚ���
*/ 
int cmpChar(const void* q1, const void* q2) {
	return strcmp((char*)q1, (char*)q2);
}

/* 
��ת����
*/
void remove_duplicate_and_sort(char* str) {
	int len = strlen(str); // ��
	char* start = str;
	int i = 1;
	BitMap* bitmap = createBitMap(120);

	// ȥ��
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

	// ����
	qsort(str, len, sizeof(str[0]), cmpChar);

	// �ض�λ�ַ�����ͷ����ַ
	str += i;
	printf("%s\n", str);
}

/*
* ������
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