#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
Date:2024.6.19
Title:��̬�ڴ������
Content:
*/


/*
1.ͨ������������̬���ٿռ�
*/
//void GetMemory1(char** p) {
//	//p = (char*)malloc(100); // p��ָ��str����Ϊָ���¿��ٵĿռ��ַ
//	 *p = (char*)malloc(100); // ����Ϊ����ָ��ָ��&str�������õõ�p = str, �����ٿռ丳ֵ��p��str
//	// ��������p���٣����ٵĿռ�û�ͷţ�й¶
//}
void* GetMemory1(void) {
	 char* p = (char*)malloc(100); // ֱ�ӷ���ָ��
	 return p;
}

void Test1(void) {
	char* str = NULL;
	//GetMemory1(str); // str��NULL
	//GetMemory1(&str); // ����1����str��ַ��Ϊʵ�δ���
	str = GetMemory1(); // ����2����������Ϊ����ָ�룬����ָ�뼴��
	strcpy(str, "hello world\n"); // strcpy�����У���ֵ��Ҫָ������ã�strΪNULL���Ա����������
	printf(str);

	// �ͷ�
	free(str);
	str = NULL;
}

/*
2.
*/
//int* f2(void) {
//	int* ptr; // ����д��һ��δ����򲻿ɷ��ʵ��ڴ�λ�ã���ͨ���ᵼ�³���������������Ԥ�����Ϊ
//	*ptr = 10; // ��������ptr��ֵ����һ��ָ������ڴ�λ�õ�ָ�롣
//	// �������ָ��û�б���ȷ��ʼ�������Է��ص�ָ������Ч�ģ��κγ���ʹ�����ָ�����Ϊ��������Σ�յġ�
//	return ptr;
//}
//
//void wildPointer(void) {
//	int* p = f2();
//	printf("%d\n", *p);
//}

/*
3.
*/
char* GetMemory3(void) {
	char p[] = "hello world";
	return p;
}

void Test3(void) {
	char* str = NULL;
	str = GetMemory3();
	printf(str);
}


/*
4.û�ͷ�
*/

void GetMemory4(char** p, int num) {
	*p = (char*)malloc(num);
}
void Test4(void) {
	char* str = NULL;
	GetMemory4(&str, 100);
	strcpy(str, "hello");
	printf(str);
	
	// �ͷ�
	free(str);
	str = NULL;
}

/*
5
*/
void Test5(void) {
	char* str = (char*)malloc(100);
	strcpy(str, "hello");
	free(str); // ָ��ռ䱻�ͷţ�Ұָ��
	//str = NULL;
	if (str != NULL) {
		strcpy(str, "world");
		printf(str);
	} // strҰָ�룬�ͷź󣬿ռ䶼Ϊddddddddddddddddddd��һ�������ж�����
}

int main(void) {
	//Test();
	//wildPointer();
	//Test3();
	//Test4();
	//Test5();
	return 0;
}
