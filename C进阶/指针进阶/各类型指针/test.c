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
printf��ʽ�������%s��ȡ���ַ����׵�ַ���Զ������'\0'��
pstrʵ�ʴ洢��Ϊ"hello bit."�� h �ĵ�ַ
*/


//int main() {
//    char str1[] = "hello bit."; // == �׵�ַ�Ա�
//    char str2[] = "hello bit.";
//    const char* str3 = "hello bit.";
//    const char* str4 = "hello bit.";
//    //*str4 = 'H'; // ָ�������Բ��ɸ��ģ�����const�����ɸ���
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
��Ϊ"hello bit."��Ϊ���ɱ�ĳ��������Է����ڴ��е�ֻ���������У����� str3 �� str4ִ�е���ͬһ����ַ���� h �ĵ�ַ
�ַ�����������Դ���뱻���������Ϊ��ִ���ļ��Ĺ����б�������Ƕ�뵽������
str1[] �� str2[] ���ڴ��п��ٿռ���ڿռ��ڷ����ַ�������ÿ�����鶼�Ƕ��Կ��٣��׵�ַ��ͬ
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
p ָ���������飬&arr
*p ָ����������Ҳ��������Ԫ�صĵ�ַ��arr
*/


//int main(void) {
//	int arr[3][5] = { 1,2,3,4,5,2,3,4,5,6,3,4,5,6,7 };
//	//print1(arr, 3, 5);
//	//print2(arr, 3, 5); // ��λ���飬arr��������ʾ���ǵ�һ�еĵ�ַ��������ʵ�δ���ȥ�ľ���һά����ĵ�ַ
//	//print3(&arr[0], 3, 5); // ��print2����arr��ͬ
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
//void print2(int (*parr)[5], int row, int column) { // ��ʱ�βν��ܵľ�ֱ���� �����СΪ5������ָ��
//	for (int i = 0; i < row; i++) {
//		for (int j = 0; j < column; j++) {
//			printf("%d ", (*(parr + i))[j]); // parr = arr, *parr = arr[0]
//			//printf("%d ", parr[i][j]);
//		}
//		printf("\n");
//	}
//}
//
//void print3(int (*parr)[5], int row, int column) { // ��ʱ�βν��ܵľ�ֱ���� �����СΪ5������ָ��
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
//	// parr3 = parr3[10]���׵�ַ
//	// parr3[0] = &arr1 ��������ĵ�ַ
//	// *parr3[0] = arr1 ��Ԫ�ص�ַ
//	// **parr3[0] = 1
//
//	printf("%d\n", **parr3[0]);
//	printf("parr3 = %p\n", parr3);
//	printf("parr3[0] = %p\n", parr3[0]);
//	printf("parr3[0]+1 = %p\n", parr3[0] + 1); // &arr1 + 1
//	printf("*parr3[0] = %p\n", *parr3[0]);
//	return 0;
//}
