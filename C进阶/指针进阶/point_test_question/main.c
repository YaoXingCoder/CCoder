#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/*
Date:2024.6.13
Title:ָ������
Content:
1.ָ������������
2.ָ�������
*/

/*
һλ����
*/
//int main(void) {
//	int a[] = { 1,2,3,4 };
//	printf("%d\n", sizeof(a)); // 16��a��ʾ��������a ������Ϊ int[4];
//	printf("%d\n", sizeof(a + 0)); // 4/8������a+0��a��ʾΪ&a[0]��Ԫ�صĵ�ַ����&a[0] + 0
//	printf("%d\n", sizeof(*a)); // 4��*a = 1���ж�1Ϊint����
//	printf("%d\n", sizeof(a + 1)); // 4/8���� &a[0] + 1
//	printf("%d\n", sizeof(a[1])); // 4��a[1] = 2���ж�2����������
//	printf("%d\n", sizeof(&a)); // 4/8��&a ������Ϊ *������Ϊ��ַ���жϵ�ַ�Ĵ�С
//	printf("%d\n", sizeof(*&a)); // 16��&aΪָ�룬ָ������Ϊint(*)[4]�������õĵ���ָ�����飬����ָ��
//	printf("%d\n", sizeof(&a + 1)); // 4/8��ָ������Ϊint(*)[4]��+1����4*int��С�ֽ�
//	printf("%d\n", sizeof(&a[0])); // 4/8��ȡ����Ϊ1�ĵ�ַ &1 + 1
//	printf("%d\n", sizeof(&a[0] + 1)); // 4/8��2�ĵ�ַ��&2 + 1
//	return 0;
//}

/*
�ַ�����
*/
#include <string.h>
int main(void) {
	char arr[] = { 'a','b','c','d','e','f' };
	printf("%d\n", sizeof(arr));
	printf("%d\n", sizeof(arr + 0));
	printf("%d\n", sizeof(*arr));
	printf("%d\n", sizeof(arr[1]));
	printf("%d\n", sizeof(&arr));
	printf("%d\n", sizeof(&arr + 1));
	printf("%d\n", sizeof(&arr[0] + 1));
	printf("%d\n", strlen(arr));
	printf("%d\n", strlen(arr + 0));
	printf("%d\n", strlen(*arr));
	printf("%d\n", strlen(arr[1]));
	printf("%d\n", strlen(&arr));
	return 0;
}

