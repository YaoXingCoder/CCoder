#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <assert.h>


int commonMultiple1(int n, int m); // ��С������1
int commonMultiple2(int n, int m); // ��С������2
void reverseWord(char arr[]);
int myStrlen(char str[]);
void reverseStr(char* left, char* right);

int main(void) {
	//printf("��С��������%d\n", commonMultiple2(5, 7));
	char str[100] = { 0 };
	printf("������һ��Ӣ�ľ���:>");
	//fgets(str, sizeof(str), stdin);
	gets(str);
	reverseWord(str);
	printf("��������Ϊ��%s\n", str);
	return 0;
}

/*
��m��n����С������
������⣺�ж�res % n == 0 && res % m == 0;��ѭ������res��ֵ
*/
int commonMultiple1(int n, int m) {
	int res = (n>m?n:m);
	while (!(res % n == 0 && res % m == 0)) {
		res++;
	}
	return res;
}

/*
��m��n����С������
�������� m*i = n*j
�жϣ�m * i % n == 0
�� i*m Ϊ��С������
*/
int commonMultiple2(int n, int m) {
	int i = 1;
	while (m * i % n) 
		i++;
	return i * m;
}

/*
��������еĵ���˳��
i like beijing.
���ú�
beijing. like i
1.�����������ӵ����е��� .gnijieb ekil i
2.����ÿ�����ʣ�beijing. like i
�������ַ�����ַ
*/
void reverseWord(char str[]) {
	// ������������
	reverseStr(str, str + myStrlen(str) - 1);
	// ���򵥴�
	char* start = str; // ��¼���ʵĳ�ʼλ��
	while (*start) { // *start != '\0'
		char* end = start; // ÿ��ѭ��endָ�򵥴ʵ�һ����ĸλ��
		// // ��¼���ʺ�Ŀո�λ�ã����һ������ʱҲ���ж�'\0'
		while ((*end != ' ') && ('\0' != *end)) 
			end++;
		reverseStr(start, end - 1);
		start = ++end; // start��¼��һ��������ʼλ��
	}
}

/*
�����ַ��γ���
�������ַ�����ַ
*/
int myStrlen(char str[]) {
	char* start = str;
	while ('\0' != *str) str++;
	return str - start;
}

/*
�����ַ���
�������ַ�����ʼλ�ã��ַ�������λ��
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