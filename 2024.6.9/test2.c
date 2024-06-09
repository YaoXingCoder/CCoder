#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <assert.h>


int commonMultiple1(int n, int m); // 最小公倍数1
int commonMultiple2(int n, int m); // 最小公倍数2
void reverseWord(char arr[]);
int myStrlen(char str[]);
void reverseStr(char* left, char* right);

int main(void) {
	//printf("最小公倍数是%d\n", commonMultiple2(5, 7));
	char str[100] = { 0 };
	printf("请输入一个英文句子:>");
	//fgets(str, sizeof(str), stdin);
	gets(str);
	reverseWord(str);
	printf("逆序后句子为：%s\n", str);
	return 0;
}

/*
求m和n的最小公倍数
暴力求解：判断res % n == 0 && res % m == 0;并循环增加res的值
*/
int commonMultiple1(int n, int m) {
	int res = (n>m?n:m);
	while (!(res % n == 0 && res % m == 0)) {
		res++;
	}
	return res;
}

/*
求m和n的最小公倍数
假设满足 m*i = n*j
判断：m * i % n == 0
则 i*m 为最小公倍数
*/
int commonMultiple2(int n, int m) {
	int i = 1;
	while (m * i % n) 
		i++;
	return i * m;
}

/*
逆序句子中的单词顺序
i like beijing.
逆置后：
beijing. like i
1.逆序整个句子的所有单词 .gnijieb ekil i
2.逆序每个单词：beijing. like i
参数：字符串地址
*/
void reverseWord(char str[]) {
	// 逆序整个句子
	reverseStr(str, str + myStrlen(str) - 1);
	// 逆序单词
	char* start = str; // 记录单词的初始位置
	while (*start) { // *start != '\0'
		char* end = start; // 每次循环end指向单词第一个字母位置
		// // 记录单词后的空格位置，最后一个单词时也许判断'\0'
		while ((*end != ' ') && ('\0' != *end)) 
			end++;
		reverseStr(start, end - 1);
		start = ++end; // start记录下一个单词起始位置
	}
}

/*
计算字符段长度
参数：字符串地址
*/
int myStrlen(char str[]) {
	char* start = str;
	while ('\0' != *str) str++;
	return str - start;
}

/*
逆序字符串
参数：字符串起始位置，字符串结束位置
*/
void reverseStr(char* left, char* right) {
	assert(left);
	assert(right);
	while (left < right) {
		char temp = *right;
		*right = *left;
		*left = temp;
		right--;
		left++;
	}
}