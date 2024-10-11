#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

/*
Date:2024.6.15
Title:字符串函数学习
Content:
了解字符串相关函数
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
strlen，求字符串长度函数
*/
void use_strlen(void) {
	const char* str1 = "abcdef";
	const char* str2 = "bbb";
	printf("length of arr1[] is %u\n", my_strlen1(str1));
	printf("length of arr1[] is %u\n", my_strlen2(str1));
	printf("length of arr1[] is %u\n", my_strlen3(str2));

	char arr1[] = "abc"; // 自动添加'\0'
	char arr2[] = { 'a', 'b', 'c' }; // 无'\0'
	// 传入值为一个字符的地址，以'\0'作为结束标志
	//printf("length of arr2[] is %d\n", strlen(arr2));

	// 因为strlen函数返回的时无符号整数，所以两个函数相减运算的值也是无符号类型，即相减为负数也会按无符号输出
	// 所以应尽量避免两个strlen函数相减，直接比较
	//if (strlen(str2) - strlen(str1) > 0) { 
	//if (strlen(str2) > strlen(str1)) {
	//	printf("str2>str1\n");
	//} else {
	//	printf("srt1>str2\n");
	//}
}

/*
strcpy，字符串复制
*/
void use_strcpy(void) {
	char str1[20];
	const char str2[] = "abcdef";
	//strcpy(str1, str2);
	my_strcpy(str1, str2);
	printf("%s\n", str1);
}

/*
strcat，字符串追加
*/
void use_strcat(void) {
	char str1[20] = "abcdef";
	const char str2[] = "bbb";
	printf("%s\n", my_strcat(str1, str2));
}

/*
strcmp，字符串比较
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

	// 充分利用for循环初始化一次值的特性
	for (ret = strtok(cp, sep); ret != NULL; ret = strtok(NULL, sep)) {
		printf("%s\n", ret);
	}
}

/*
strerror：错误码报告函数
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
memcpy：内存拷贝
*/
void use_memcpy(void) {
	int arr1[] = { 1,2,3,4,5,6,7,8 };
	int arr2[20] = { 0 };
	my_memcpy(arr2, arr1, 32);

	my_memcpy(arr1 + 2, arr1, 16); // 自复制会出先问题
	for (int i = 0; i < 8; i++) {
		printf("%d ", arr1[i]);
	}
}

/*
memmove：内存拷贝
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
memcmp：内存比较
*/
void use_memcmp(void) {
	int arr1[] = { 1,2,3,4 };
	int arr2[] = { 256,2,3,4 };
	// 因为按字节比较所以，一个大数的低字节小于一个小数的低字节，会出现错误判断
	if (memcmp(arr1, arr2, 16) > 0) {
		printf("arr1 > arr2");
	} else if (memcmp(arr1, arr2, 16) < 0) {
		printf("arr2 > arr1");
	} else {
		printf("arr2 == arr1");
	}
}

/*
memset：填充
用memset初始化时，注意该函数为内存一个字节一个字节替换
类型除了char都为一字节以上的
初始化会不如意
*/
void use_memset(void) {
	char arr[] = "hellow,world";
	memset(arr, 'x', 5);
	printf("%s\n", arr);
}

/*
主函数
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

