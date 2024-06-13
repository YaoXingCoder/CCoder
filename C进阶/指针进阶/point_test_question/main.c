#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/*
Date:2024.6.13
Title:指针试题
Content:
1.指针和数组笔试题
2.指针程序题
*/

/*
一位数组
*/
//int main(void) {
//	int a[] = { 1,2,3,4 };
//	printf("%d\n", sizeof(a)); // 16：a表示整个数组a 的类型为 int[4];
//	printf("%d\n", sizeof(a + 0)); // 4/8：这里a+0，a表示为&a[0]首元素的地址，即&a[0] + 0
//	printf("%d\n", sizeof(*a)); // 4：*a = 1；判断1为int类型
//	printf("%d\n", sizeof(a + 1)); // 4/8：即 &a[0] + 1
//	printf("%d\n", sizeof(a[1])); // 4：a[1] = 2，判断2的数据类型
//	printf("%d\n", sizeof(&a)); // 4/8：&a 的类型为 *，本质为地址，判断地址的大小
//	printf("%d\n", sizeof(*&a)); // 16：&a为指针，指针类型为int(*)[4]，解引用的到该指针数组，数组指针
//	printf("%d\n", sizeof(&a + 1)); // 4/8：指针类型为int(*)[4]，+1跳过4*int大小字节
//	printf("%d\n", sizeof(&a[0])); // 4/8：取到的为1的地址 &1 + 1
//	printf("%d\n", sizeof(&a[0] + 1)); // 4/8：2的地址，&2 + 1
//	return 0;
//}

/*
字符数组
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

