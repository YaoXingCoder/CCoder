/*********************************
Date:2024.6.25
Title:HashMap动态数组实现
Author:JiaZiChunQiu
Content:
**********************************/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "dymArr_HashMap.h"

int main(void) {
	//printf("%d\n", 0 % 1);
	DymicHM* hashmap = createHashMap();
	printf("%s\n", putKV(hashmap, "123", "123"));
	printf("%s\n", putKV(hashmap, "234", "123"));
	printf("%s\n", putKV(hashmap, "345", "123"));
	printf("%s\n", putKV(hashmap, "456", "123"));
	printf("%s\n", putKV(hashmap, "678", "123"));
	printf("%s\n", putKV(hashmap, "891", "123"));
	printf("%s\n", putKV(hashmap, "abc", "123"));
	printf("%s\n", putKV(hashmap, "bcd", "123"));
	printf("%s\n", putKV(hashmap, "def", "123"));

	printf("%d\n", removeKV(hashmap, "123"));

	printf("%s\n", getValue(hashmap, "123"));
	printf("%s\n", getValue(hashmap, "abc"));

	printAllKV(hashmap);
	printf("%d\n", destroyHashMap(hashmap));
	return 0;
}
