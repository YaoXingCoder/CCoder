#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

/*
Date:2024.6.15
Title:�ַ�������ѧϰ
Content:
�˽��ַ�����غ���
*/

unsigned int my_strlen1(const char* str);
unsigned int my_strlen2(const char* str);
unsigned int my_strlen3(const char* str);
char* my_strcpy(char* des, const char* sou);
char* my_strcat(char* des, const char* sou);
int my_strcmp1(const char* str1, const char* str2);
int my_strcmp2(const char* str1, const char* str2);
char* my_strstr(const char* str1, const char* str2);
void* my_memcpy(void* dest, void* src, int size);
void* my_memmove(void* dest, void* src, int size);


/*
strlen�����ַ������Ⱥ���
*/
void use_strlen(void) {
	const char* str1 = "abcdef";
	const char* str2 = "bbb";
	printf("length of arr1[] is %u\n", my_strlen1(str1));
	printf("length of arr1[] is %u\n", my_strlen2(str1));
	printf("length of arr1[] is %u\n", my_strlen3(str2));

	char arr1[] = "abc"; // �Զ����'\0'
	char arr2[] = { 'a', 'b', 'c' }; // ��'\0'
	// ����ֵΪһ���ַ��ĵ�ַ����'\0'��Ϊ������־
	//printf("length of arr2[] is %d\n", strlen(arr2));

	// ��Ϊstrlen�������ص�ʱ�޷�����������������������������ֵҲ���޷������ͣ������Ϊ����Ҳ�ᰴ�޷������
	// ����Ӧ������������strlen���������ֱ�ӱȽ�
	//if (strlen(str2) - strlen(str1) > 0) { 
	//if (strlen(str2) > strlen(str1)) {
	//	printf("str2>str1\n");
	//} else {
	//	printf("srt1>str2\n");
	//}
}

/*
strcpy���ַ�������
*/
void use_strcpy(void) {
	char str1[20];
	const char str2[] = "abcdef";
	//strcpy(str1, str2);
	my_strcpy(str1, str2);
	printf("%s\n", str1);
}

/*
strcat���ַ���׷��
*/
void use_strcat(void) {
	char str1[20] = "abcdef";
	const char str2[] = "bbb";
	printf("%s\n", my_strcat(str1, str2));
}

/*
strcmp���ַ����Ƚ�
*/
void use_strcmp(coid) {
	char arr1[20] = "zhangsan";
	char arr2[] = "zhangsanfeng";
	if (my_strcmp2(arr2, arr1) > 0) {
		printf(">\n");
	} else if (0 == my_strcmp2(arr2, arr1)) {
		printf("=\n");
	} else {
		printf("<\n");
	}
}

/*
strncat
*/
void use_strncat(void) {
	char str1[20];
	char str2[20];
	strcpy (str1, "To be ");
	strcpy (str2, "or not to be");
	strncat (str1, str2, 6);
	puts (str1);
	return 0;
}

/*
strncmp
*/
void use_strncmp(void) {
	char str[][5] = { "R2D2" , "C3PO" , "R2A6" };
	int n;
	puts ("Looking for R2 astromech droids...");
	for (n = 0; n < 3; n++) {
		if (strncmp (str[n], "R2xx", 2) == 0) {
			printf ("found %s\n", str[n]);
		}
	}
}

/*
strstr
return: Find the first 
*/
void use_strstr(void) {
	char str[] = "This is a simple string";
	char* pch;
	pch = my_strstr (str, "simple");
	strncpy (pch, "sample", 6);
	puts (pch);
	return 0;
}

/*
strtok
*/
void use_strtok(void) {
	const char* sep = "@.";
	char email[] = "zhangpengwei@@bitejiuyeke.com";
	char cp[30] = { 0 };
	strcpy(cp, email);
	char* ret;
	//printf("%s\n", ret); // zhangpengwei
	//ret = strtok(NULL, sep);
	//printf("%s\n", ret); // bitejiuyeke
	//ret = strtok(NULL, sep);
	//printf("%s\n", ret); // com

	// �������forѭ����ʼ��һ��ֵ������
	for (ret = strtok(cp, sep); ret != NULL; ret = strtok(NULL, sep)) {
		printf("%s\n", ret);
	}
}

/*
strerror�������뱨�溯��
*/
void use_strerror(void) {
	FILE* pFile;
	pFile = fopen ("unexist.ent", "r");
	if (pFile == NULL)
		printf ("Error opening file unexist.ent: %s\n", strerror(errno));
		//errno: Last error number
	return 0;
}

/*
memcpy���ڴ濽��
*/
void use_memcpy(void) {
	int arr1[] = { 1,2,3,4,5,6,7,8 };
	int arr2[20] = { 0 };
	my_memcpy(arr2, arr1, 32);

	my_memcpy(arr1 + 2, arr1, 16); // �Ը��ƻ��������
	for (int i = 0; i < 8; i++) {
		printf("%d ", arr1[i]);
	}
}

/*
memmove���ڴ濽��
*/
void use_memmove(void) {
	int arr1[] = { 1,2,3,4,5,6,7,8 };
	//my_memmove(arr1 + 2, arr1, 16); 
	memmove(arr1 + 2, arr1, 16);
	for (int i = 0; i < 8; i++) {
		printf("%d ", arr1[i]);
	}
}

/*
memcmp���ڴ�Ƚ�
*/
void use_memcmp(void) {
	int arr1[] = { 1,2,3,4 };
	int arr2[] = { 256,2,3,4 };
	// ��Ϊ���ֽڱȽ����ԣ�һ�������ĵ��ֽ�С��һ��С���ĵ��ֽڣ�����ִ����ж�
	if (memcmp(arr1, arr2, 16) > 0) {
		printf("arr1 > arr2");
	} else if (memcmp(arr1, arr2, 16) < 0) {
		printf("arr2 > arr1");
	} else {
		printf("arr2 == arr1");
	}
}

/*
memset�����
��memset��ʼ��ʱ��ע��ú���Ϊ�ڴ�һ���ֽ�һ���ֽ��滻
���ͳ���char��Ϊһ�ֽ����ϵ�
��ʼ���᲻����
*/
void use_memset(void) {
	char arr[] = "hellow,world";
	memset(arr, 'x', 5);
	printf("%s\n", arr);
}

/*
������
*/
int main(void) {
	//use_strlen();
	//use_strcpy();
	//use_strcat();
	//use_strcmp();
	//use_strncat();
	//use_strncmp();
	//use_strstr();
	//use_strtok();
	//use_strerror();
	//use_memcpy();
	//use_memmove();
	//use_memcmp();
	use_memset();
	return 0;
}

