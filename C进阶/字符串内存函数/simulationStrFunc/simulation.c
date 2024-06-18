#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <assert.h>

/*
Date:2024.6.15
Title:模拟字符串函数
Content:
my_strlen：求字符串长度
my_strcpy：复制目标字符串
my_strcat：字符串追加
my_strcmp：字符串比较
my_strstr：找子串
*/

/*
my_strlen：求字符串长度
const char* str：传入字符地址
返回类型：unsigned int
1.计算器方式
2.指针-指针
3.递归方式
*/
unsigned int my_strlen1(const char* str) {
	unsigned int count = 0;
	while (*(str) != '\0') {
		count++;
		str++;
	}
	return count;
}

unsigned int my_strlen2(const char* str) {
	char* start = str;
	while (*(str) != '\0') {
		str++;
	}
	return str - start;
}

unsigned int my_strlen3(const char* str) {
	if (*(str) == '\0')	return 0;
	return 1 + my_strlen3(str + 1);
}


/*
my_strcpy：复制字符串到目标字符串
char* des：目标函数地址
const char* sou：被复制的函数地址
返回类型：char*，目标函数的初始地址
*/
char* my_strcpy(char* des, const char* sou) {
	char* start = des;
	while (*des++ = *sou++) {
		;
	}
	return start;
}


/*
my_strcat：复制字符串追加到目标字符串
char* des：目标函数地址
const char* sou：被复制的函数地址
返回类型：char*，目标函数的初始地址
*/
char* my_strcat(char* des, const char* sou) {
	char* start = des;
	while (*des != '\0') {
		des++;
	}
	my_strcpy(des, sou);
	return start;
}

/*
my_strcmp：比较两个字符串
char* str1：字符串1
char* str2：字符串2
返回类型：int, 1 str1 > str2 ; 0 str1 = str2 ; -1 str1 < str2
循环比较每个字符，相等就比较下一个字符，不等返回 1 / -1
直到比较完有一个字符是'\0'，则说明两个字符串比较结束，返回相当 0 
*/
int my_strcmp1(const char* str1, const char* str2) {
	assert(str1 && str2);
	while (*str1 == *str2) {
		if ('\0' == *str1) return 0;
		str1++;
		str2++;
	}
	if (*str1 > *str2)
		return 1;
	else 
		return -1;
}

// 简化一下
int my_strcmp2(const char* str1, const char* str2) {
	assert(str1 && str2);
	while (*str1 == *str2) {
		if ('\0' == *str1) return 0;
		str1++;
		str2++;
	}
	return (*str1 - *str2);
}


/*
实现strstr
在目标字符串找子串的位置
返回值
目标字符串中子串首元素的地址
*/
char* my_strstr(const char* str1, const char* str2) {
	const char* s1 = str1;
	const char* p = str1;
	const char* s2 = str2;
	while (*p) {
		s1 = p;
		s2 = str2;
		while (*s1 == *s2) {
			s1++;
			s2++;
		}
		if ('\0' == *s2) return (char*)p;
		p++;
	}
	return NULL;
}