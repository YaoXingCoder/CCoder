#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

/*
Date:2024.6.13 - 2024.6.14
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
//#include <string.h>
//int main(void) {
//	char arr[] = { 'a','b','c','d','e','f' }; // 没有'\0'结尾
//	printf("%d\n", sizeof(arr)); // 6：sizeof中单独的数组名，就是整个数组的大小
//	printf("%d\n", sizeof(arr + 0)); // 4/8：这里arr表示元素首地址
//	printf("%d\n", sizeof(*arr)); // 1：arr=&'a' , *a = 'a';
//	printf("%d\n", sizeof(arr[1])); // 1：arr[1] = 'a'
//	printf("%d\n", sizeof(&arr)); // 4/8：&arr 为指针，指针类型 = char(*)[6]（数组指针），指向arr数组
//	printf("%d\n", sizeof(&arr + 1)); // 4/8：&arr+1 跳过整个数组，指向数组后的地址
//	printf("%d\n", sizeof(&arr[0] + 1)); // 4/8：arr[0] = 'a' , &arr[0] = &'a' , &arr[0] + 1 = &'b'
//	printf("%d\n", strlen(arr)); // 随机值：数组中没有'\0'结尾，strlen会越界访问直至遇到'\0'
//	printf("%d\n", strlen(arr + 0)); // 随机值：arr = &'a'，同上
//	printf("%d\n", strlen(*arr)); // 报错：*arr = 'a'，'a' = 91，strlen(97)相当于从地址为97的地方开始访问，不允许
//	printf("%d\n", strlen(arr[1]));  // 报错：arr[1] = 'b'，strlen(98)
//	printf("%d\n", strlen(&arr)); // 随机值：&arr依旧是首元素地址
//	printf("%d\n", strlen(&arr + 1)); // 随机值-6：&arr+1处开始计算，即跳过数组后第一个地址开始
//	printf("%d\n", strlen(&arr[0] + 1)); // 随机值-1：&arr[0] = &'a'，&arr[0] + 1 = &'b'
//
//	return 0;
//}

//int main(void) {
//	char arr[] = "abcdef"; // 会自动添加'\0'，所以长度会+1char
//	printf("%d\n", sizeof(arr)); // 7：sizeof+单独数组名，表示整个数组的大小，arr = char[]
//	printf("%d\n", sizeof(arr + 0)); // 4/8：'a'地址的大小，arr = &'a'，arr + 0 = arr = &'a'
//	printf("%d\n", sizeof(*arr)); // 1：'a'数据类型的大小，arr = &'a'，*arr = 'a'
//	printf("%d\n", sizeof(arr[1])); // 1：'a'数据类型的大小，arr = &'a'，arr[1] = 'a'
//	printf("%d\n", sizeof(&arr)); // 4/8：数组指针类型的大小，arr类型为:arr[]，&arr类型为：char(*)[7]
//	printf("%d\n", sizeof(&arr + 1)); // 4/8：数组指针类型的大小，不过&arr+1指向的为跳过整个数组后的地址
//	printf("%d\n", sizeof(&arr[0] + 1)); // 4/8：指针类型的大小，&arr[0] = &'a'，&arr[0] + 1 = &'b'
//	printf("------------------------------------------------------------");
//	printf("%d\n", strlen(arr)); // 6：这里的arr = &'a'，然后从地址开始计算到'\0'
//	printf("%d\n", strlen(arr + 0)); // 6：arr + 0 = &'a'，同上
//	printf("%d\n", strlen(*arr)); // 报错：*arr = 'a'，'a' = 97， strlen(97)，访问报错
//	printf("%d\n", strlen(arr[1])); // 报错：arr[1] = 'a'，同上
//	printf("%d\n", strlen(&arr)); // 6：这里&arr的地址 = arr的地址，数组指针 &arr，类型为char(*)[7]
//	printf("%d\n", strlen(&arr + 1)); // 随机值：&arr+1从跳过数组后的第一个地址开始
//	printf("%d\n", strlen(&arr[0] + 1)); // 5：&arr[0] = &'b', &arr[0] + 1 = &'b'
//	return 0;
//}

/*
二维数组
[] [] [] []
[] [] [] []
[] [] [] []
*/
//int main(void) {
//	int a[3][4] = { 0 };
//	printf("%d\n", sizeof(a)); // 48
//	// sizeof + 单独数组名 计算整个数组的大小，3*4*4 = 48
//	printf("%d\n", sizeof(a[0][0])); // 4
//	// a[0] = &a[0][0] 第一行第一列元素的地址，a[0][0] = 0 第一行第一列的元素
//	printf("%d\n", sizeof(a[0])); // 16，a[0]
//	// a[0] = &a[0][0]，第一行首元素的地址，因为单独放在sizeof中，计算第一行的大小
//	// 这里 a[0] 类型为int[4]，但 a[0]（类型int*） 实际地址与 &a[0][0]相同
//	printf("%d\n", sizeof(a[0] + 1)); // 4/8，指针类型 int*类型
//	// a[0] 为第一行首元素的地址，+1则为第一行第二列的地址，为指针指向&a[0][1]
//	printf("%d\n", sizeof(*(a[0] + 1))); // 4，int类型值的大小
//	// a[0] + 1 = &arr[1][0]（int*类型） 第二行首元素的地址，*(a[0] + 1) = arr[1][0] = 0
//	printf("%d\n", sizeof(a + 1)); // 4/8，指针类型(int(*)[4])
//	// a = &a[0]，指针类型为int(*)[4]
//	// a + 1 = &a[0] + 1 ，跳过第一行，指向第二行首数组
//	printf("%d\n", sizeof(*(a + 1))); // 16
//	// a + 1 = &a[1]，第二行整个数组的地址
//	// *(a + 1)：a[1]，第二行首元素的地址，在sizeof中单独的数组名计算整个数组大小
//	printf("%d\n", sizeof(&a[0] + 1)); // 4/8，数组指针(int(*)[4])
//	// &a[0] + 1 = &a[1] = a + 1：第二行整个数组的地址，
//	printf("%d\n", sizeof(*(&a[0] + 1))); // 16
//	// *(&a[0] + 1) = a[1] = &a[1][0]，
//	printf("%d\n", sizeof(*a)); // 16
//	// 这里a = a + 0 = &arr[0]，*a = arr[0]，第一行首元素，在sizeof
//	// sizeof(第一行数组的数组名)计算第一行大小
//	printf("%d\n", sizeof(a[3])); // 16
//	// a[3]，相当于第四行的数组名，sizeof不会检测有没有越界
//	//int (*parr)[3][4] = a;
//	return 0;
//}


/*
-----------------------------------------------------------------
编程题1
*/
//int main() {
//    int a[5] = { 1, 2, 3, 4, 5 };
//    int* ptr = (int*)(&a + 1); // &a + 1 = 数组后的首个地址
//    printf("%d,%d", *(a + 1), *(ptr - 1)); // 2, 5
//    return 0;
//}


// //结构体的大小是20个字节
// //*p为结构体指针
//struct Test {
//    int Num; // 4
//    char* pcName; // 4
//    short sDate; // 2
//    char cha[2]; // 2
//    short sBa[4]; // 8
//}* p = (struct Test*)0x100000;
// //假设p 的值为0x100000。 如下表表达式的值分别为多少？
// //已知，结构体Test类型的变量大小是20个字节
//int main() {
//    printf("%#p\n", p);
//    printf("%#p\n", p + 0x1); // 0x100014
//    printf("unsigned long 的类型大小:%d\n", sizeof(unsigned long)); // 4
//    printf("%#p\n", (unsigned long)p + 0x1); // 0x100001 
//    // (unsigned long)p的p被强制转换成的整数，所以+1就是整数运算0x100000 + 0x1= 0x100001 
//    // 以地址类型输出，不区分正负
//    printf("%#p\n", (unsigned int*)p + 0x1); // 0x100004
//    return 0;
//}

/*
笔试题3
*/
//int main() {
//    int a[4] = { 1, 2, 3, 4 };
//    int* ptr1 = (int*)(&a + 1); // ptr1 指向 跳过整个数组后的首个地址
//    int* ptr2 = (int*)((int)a + 1); // 因a被强制转换成整数，+1为正常的整数运算
//    printf("%x,%x", ptr1[-1], *ptr2); // 4, 
//    return 0;
//}


/*
笔试题4
*/
//#include <stdio.h>
//int main() {
//    int a[3][2] = { (0, 1), (2, 3), (4, 5) }; // 实际存储为{{1, 3}, {5, 0}, {0, 0}};
//    int* p;
//    p = a[0]; // p指向第一行首元素，
//    printf("%d", p[0]); // 第一行第一列 1
//    return 0;
//}

/*
笔试题5
*/
//int main() {
//    int a[5][5];
//    int(*p)[4];
//    p = a; // a第一行首元素地址 类型 int(*)[5]，p为int(*)[4]可以赋值但类型不变，会警告
//    printf("%p,%d\n", &p[4][2] - &a[4][2], &p[4][2] - &a[4][2]); // FF FF FF FC | -4
//    // p[4]每次会向后移动4*4字节大小，p[4][2]为移动4*4 + 2个字节大小，取该地址表示的元素的地址
//    // -4 按地址类型输出，-4的补码不分正负直接输出
//    // 指针 - 指针 = 元素个数
//    return 0;
//}

/*
笔试题6
*/
//int main() {
//    int aa[2][5] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
//    int* ptr1 = (int*)(&aa + 1); // ptr1跳过整个数组后的首地址
//    int* ptr2 = (int*)(*(aa + 1)); // ptr2 = &6
//    printf("%d,%d", *(ptr1 - 1), *(ptr2 - 1)); // 10, 5
//    return 0;
//}

/*
笔试题7
*/
//int main() {
//    char* a[] = { "work","at","alibaba" }; // a类型为 char(*)[3]，数组指针
//    char** pa = a;
//    pa++; // 跳过第一行，指向"at"的首地址
//    printf("%s\n", *pa); // "at"
//    return 0;
//}


/*
笔试题8
*/
int main() {
    char* c[] = { "ENTER","NEW","POINT","FIRST" }; // 数组指针，类型 char(*)[4]
    char** cp[] = { c + 3,c + 2,c + 1,c }; 
    // c + 3 的 c 为指向首元素的地址，c + 3 指针后移3个指针大小，指向FIRST
    char*** cpp = cp;
    printf("%s\n", **++cpp); // POINT
    printf("%s\n", *-- * ++cpp + 3); // ER
    printf("%s\n", *cpp[-2] + 3); // ST
    printf("%s\n", cpp[-1][-1] + 1); // EW
    return 0;
}


