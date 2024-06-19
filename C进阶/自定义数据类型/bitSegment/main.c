#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/*
Date:2024.6.18
Title:位段学习
Content:
1.内存大小计算
2.内存分配规则
*/

struct S {
	char a : 3;
	char b : 4;
	char c : 5;
	char d : 4;
};
//struct S {
//	char a : 3;
//	char c : 5;
//	char b : 4;
//	char d : 4;
//};

void bitSegmentSize(void) {
	struct S s = { 0 };
	//printf("s的大小为：%d\n", sizeof(s)); // 3byte
	printf("s的大小为：%d\n", sizeof(s)); // 调整顺序后占 2byte
	s.a = 10;
	s.b = 12;
	s.c = 3;
	s.d = 4;
	printf("%u,%u,%u,%u\n", s.a, s.b, s.c, s.d);
	printf("%u\n", s.a);
}

int main(void) {
	bitSegmentSize();
	return 0;
}
