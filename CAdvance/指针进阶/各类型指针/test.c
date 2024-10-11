#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void print1(int arr[][5], int row, int column);
void print2(int (*parr)[5], int row, int column);
void print3(int (*parr)[5], int row, int column);

//int main() {
//    const char* pstr = "hello bit.";
//    printf("%s\n", pstr);
//    return 0;
//}
/*
printf格式化输出，%s读取到字符串首地址后自动输出到'\0'；
pstr实际存储的为"hello bit."中 h 的地址
*/


//int main() {
//    char str1[] = "hello bit."; // == 首地址对比
//    char str2[] = "hello bit.";
//    const char* str3 = "hello bit.";
//    const char* str4 = "hello bit.";
//    //*str4 = 'H'; // 指向常量所以不可更改，有无const都不可更改
//    //printf("%s\n", str4);
//    if (str1 == str2)
//        printf("str1 and str2 are same\n");
//    else
//        printf("str1 and str2 are not same\n");
//
//    if (str3 == str4)
//        printf("str3 and str4 are same\n");
//    else
//        printf("str3 and str4 are not same\n");
//
//    return 0;
//}
/*
因为"hello bit."，为不可变的常量，所以放在内存中的只读数据区中，所以 str3 与 str4执行的是同一个地址，即 h 的地址
字符串字面量在源代码被编译和链接为可执行文件的过程中被创建并嵌入到程序中
str1[] 与 str2[] 在内存中开辟空间后在空间内放入字符，所以每个数组都是独自开辟，首地址不同
*/

//int main(void) {
//	int* p1[10];
//	int (*p2)[10];
//	return 0;
//}


//#include <stdio.h>
//int main() {
//	int arr[10] = { 0 };
//	int* p = arr;
//	int* p1 = &arr;
//	int (*p2)[10] = &arr;

	//printf("arr = %p\n", arr);
	//printf("arr+1 = %p\n", arr + 1);

	//printf("&arr[0] = %p\n", &arr[0]);
	//printf("&arr[0]+1 = %p\n", &arr[0] + 1);

	//printf("&arr= %p\n", &arr);
	//printf("&arr+1= %p\n", &arr + 1);

//	return 0;
//}

//int main(void) {
//	int arr[] = { 1,2,3,4,5,6,7,8,9,10 };
//	int (*p)[10] = &arr;
//	for (int i = 0; i < 10; i++) {
//		printf("%d ", *(*p + i)); // p = &arr, *p = arr, **p = 1
//	}
//	return 0;
//}
/*
p 指向整个数组，&arr
*p 指向数组名，也是数组首元素的地址，arr
*/


//int main(void) {
//	int arr[3][5] = { 1,2,3,4,5,2,3,4,5,6,3,4,5,6,7 };
//	//print1(arr, 3, 5);
//	//print2(arr, 3, 5); // 二位数组，arr数组名表示的是第一行的地址，则这里实参传过去的就是一维数组的地址
//	//print3(&arr[0], 3, 5); // 与print2传的arr相同
//	return 0;
//}
//
//void print1(int arr[][5], int row, int column) {
//	for (int i = 0; i < row; i++) {
//		for (int j = 0; j < column; j++) {
//			printf("%d ", arr[i][j]);
//		}
//		printf("\n");
//	}
//}
//
//void print2(int (*parr)[5], int row, int column) { // 这时形参接受的就直接数 数组大小为5的数组指针
//	for (int i = 0; i < row; i++) {
//		for (int j = 0; j < column; j++) {
//			printf("%d ", (*(parr + i))[j]); // parr = arr, *parr = arr[0]
//			//printf("%d ", parr[i][j]);
//		}
//		printf("\n");
//	}
//}
//
//void print3(int (*parr)[5], int row, int column) { // 这时形参接受的就直接数 数组大小为5的数组指针
//	for (int i = 0; i < row; i++) {
//		for (int j = 0; j < column; j++) {
//			//printf("%d ", (*(parr + i))[j]); // parr = &arr[0] parr + 1 = &arr[1], *parr = arr[0]
//			printf("%d ", parr[i][j]);
//		}
//		printf("\n");
//	}
//}


//int main(void) {
//	int arr1[5] = {1,2,3,4,5};
//	int arr2[5] = {2,3,4,5,6};
//	int arr3[5] = {3,4,5,6,7};
//
//	int (*parr3[10])[5] = { &arr1, &arr2, &arr3 }; 
//	// parr3 = parr3[10]的首地址
//	// parr3[0] = &arr1 整个数组的地址
//	// *parr3[0] = arr1 首元素地址
//	// **parr3[0] = 1
//
//	printf("%d\n", **parr3[0]);
//	printf("parr3 = %p\n", parr3);
//	printf("parr3[0] = %p\n", parr3[0]);
//	printf("parr3[0]+1 = %p\n", parr3[0] + 1); // &arr1 + 1
//	printf("*parr3[0] = %p\n", *parr3[0]);
//	return 0;
//}
