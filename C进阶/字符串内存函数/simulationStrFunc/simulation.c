#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <assert.h>

/*
Date:2024.6.15
Title:ģ���ַ�������
Content:
my_strlen�����ַ�������
my_strcpy������Ŀ���ַ���
my_strcat���ַ���׷��
my_strcmp���ַ����Ƚ�
my_strstr�����Ӵ�
*/

/*
my_strlen�����ַ�������
const char* str�������ַ���ַ
�������ͣ�unsigned int
1.��������ʽ
2.ָ��-ָ��
3.�ݹ鷽ʽ
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
my_strcpy�������ַ�����Ŀ���ַ���
char* des��Ŀ�꺯����ַ
const char* sou�������Ƶĺ�����ַ
�������ͣ�char*��Ŀ�꺯���ĳ�ʼ��ַ
*/
char* my_strcpy(char* des, const char* sou) {
	char* start = des;
	while (*des++ = *sou++) {
		;
	}
	return start;
}


/*
my_strcat�������ַ���׷�ӵ�Ŀ���ַ���
char* des��Ŀ�꺯����ַ
const char* sou�������Ƶĺ�����ַ
�������ͣ�char*��Ŀ�꺯���ĳ�ʼ��ַ
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
my_strcmp���Ƚ������ַ���
char* str1���ַ���1
char* str2���ַ���2
�������ͣ�int, 1 str1 > str2 ; 0 str1 = str2 ; -1 str1 < str2
ѭ���Ƚ�ÿ���ַ�����ȾͱȽ���һ���ַ������ȷ��� 1 / -1
ֱ���Ƚ�����һ���ַ���'\0'����˵�������ַ����ȽϽ����������൱ 0 
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

// ��һ��
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
ʵ��strstr
��Ŀ���ַ������Ӵ���λ��
����ֵ
Ŀ���ַ������Ӵ���Ԫ�صĵ�ַ
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