#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

/*
Date:2024.6.13 - 2024.6.14
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
//#include <string.h>
//int main(void) {
//	char arr[] = { 'a','b','c','d','e','f' }; // û��'\0'��β
//	printf("%d\n", sizeof(arr)); // 6��sizeof�е�������������������������Ĵ�С
//	printf("%d\n", sizeof(arr + 0)); // 4/8������arr��ʾԪ���׵�ַ
//	printf("%d\n", sizeof(*arr)); // 1��arr=&'a' , *a = 'a';
//	printf("%d\n", sizeof(arr[1])); // 1��arr[1] = 'a'
//	printf("%d\n", sizeof(&arr)); // 4/8��&arr Ϊָ�룬ָ������ = char(*)[6]������ָ�룩��ָ��arr����
//	printf("%d\n", sizeof(&arr + 1)); // 4/8��&arr+1 �����������飬ָ�������ĵ�ַ
//	printf("%d\n", sizeof(&arr[0] + 1)); // 4/8��arr[0] = 'a' , &arr[0] = &'a' , &arr[0] + 1 = &'b'
//	printf("%d\n", strlen(arr)); // ���ֵ��������û��'\0'��β��strlen��Խ�����ֱ������'\0'
//	printf("%d\n", strlen(arr + 0)); // ���ֵ��arr = &'a'��ͬ��
//	printf("%d\n", strlen(*arr)); // ����*arr = 'a'��'a' = 91��strlen(97)�൱�ڴӵ�ַΪ97�ĵط���ʼ���ʣ�������
//	printf("%d\n", strlen(arr[1]));  // ����arr[1] = 'b'��strlen(98)
//	printf("%d\n", strlen(&arr)); // ���ֵ��&arr��������Ԫ�ص�ַ
//	printf("%d\n", strlen(&arr + 1)); // ���ֵ-6��&arr+1����ʼ���㣬������������һ����ַ��ʼ
//	printf("%d\n", strlen(&arr[0] + 1)); // ���ֵ-1��&arr[0] = &'a'��&arr[0] + 1 = &'b'
//
//	return 0;
//}

//int main(void) {
//	char arr[] = "abcdef"; // ���Զ����'\0'�����Գ��Ȼ�+1char
//	printf("%d\n", sizeof(arr)); // 7��sizeof+��������������ʾ��������Ĵ�С��arr = char[]
//	printf("%d\n", sizeof(arr + 0)); // 4/8��'a'��ַ�Ĵ�С��arr = &'a'��arr + 0 = arr = &'a'
//	printf("%d\n", sizeof(*arr)); // 1��'a'�������͵Ĵ�С��arr = &'a'��*arr = 'a'
//	printf("%d\n", sizeof(arr[1])); // 1��'a'�������͵Ĵ�С��arr = &'a'��arr[1] = 'a'
//	printf("%d\n", sizeof(&arr)); // 4/8������ָ�����͵Ĵ�С��arr����Ϊ:arr[]��&arr����Ϊ��char(*)[7]
//	printf("%d\n", sizeof(&arr + 1)); // 4/8������ָ�����͵Ĵ�С������&arr+1ָ���Ϊ�������������ĵ�ַ
//	printf("%d\n", sizeof(&arr[0] + 1)); // 4/8��ָ�����͵Ĵ�С��&arr[0] = &'a'��&arr[0] + 1 = &'b'
//	printf("------------------------------------------------------------");
//	printf("%d\n", strlen(arr)); // 6�������arr = &'a'��Ȼ��ӵ�ַ��ʼ���㵽'\0'
//	printf("%d\n", strlen(arr + 0)); // 6��arr + 0 = &'a'��ͬ��
//	printf("%d\n", strlen(*arr)); // ����*arr = 'a'��'a' = 97�� strlen(97)�����ʱ���
//	printf("%d\n", strlen(arr[1])); // ����arr[1] = 'a'��ͬ��
//	printf("%d\n", strlen(&arr)); // 6������&arr�ĵ�ַ = arr�ĵ�ַ������ָ�� &arr������Ϊchar(*)[7]
//	printf("%d\n", strlen(&arr + 1)); // ���ֵ��&arr+1�����������ĵ�һ����ַ��ʼ
//	printf("%d\n", strlen(&arr[0] + 1)); // 5��&arr[0] = &'b', &arr[0] + 1 = &'b'
//	return 0;
//}

/*
��ά����
[] [] [] []
[] [] [] []
[] [] [] []
*/
//int main(void) {
//	int a[3][4] = { 0 };
//	printf("%d\n", sizeof(a)); // 48
//	// sizeof + ���������� ������������Ĵ�С��3*4*4 = 48
//	printf("%d\n", sizeof(a[0][0])); // 4
//	// a[0] = &a[0][0] ��һ�е�һ��Ԫ�صĵ�ַ��a[0][0] = 0 ��һ�е�һ�е�Ԫ��
//	printf("%d\n", sizeof(a[0])); // 16��a[0]
//	// a[0] = &a[0][0]����һ����Ԫ�صĵ�ַ����Ϊ��������sizeof�У������һ�еĴ�С
//	// ���� a[0] ����Ϊint[4]���� a[0]������int*�� ʵ�ʵ�ַ�� &a[0][0]��ͬ
//	printf("%d\n", sizeof(a[0] + 1)); // 4/8��ָ������ int*����
//	// a[0] Ϊ��һ����Ԫ�صĵ�ַ��+1��Ϊ��һ�еڶ��еĵ�ַ��Ϊָ��ָ��&a[0][1]
//	printf("%d\n", sizeof(*(a[0] + 1))); // 4��int����ֵ�Ĵ�С
//	// a[0] + 1 = &arr[1][0]��int*���ͣ� �ڶ�����Ԫ�صĵ�ַ��*(a[0] + 1) = arr[1][0] = 0
//	printf("%d\n", sizeof(a + 1)); // 4/8��ָ������(int(*)[4])
//	// a = &a[0]��ָ������Ϊint(*)[4]
//	// a + 1 = &a[0] + 1 ��������һ�У�ָ��ڶ���������
//	printf("%d\n", sizeof(*(a + 1))); // 16
//	// a + 1 = &a[1]���ڶ�����������ĵ�ַ
//	// *(a + 1)��a[1]���ڶ�����Ԫ�صĵ�ַ����sizeof�е������������������������С
//	printf("%d\n", sizeof(&a[0] + 1)); // 4/8������ָ��(int(*)[4])
//	// &a[0] + 1 = &a[1] = a + 1���ڶ�����������ĵ�ַ��
//	printf("%d\n", sizeof(*(&a[0] + 1))); // 16
//	// *(&a[0] + 1) = a[1] = &a[1][0]��
//	printf("%d\n", sizeof(*a)); // 16
//	// ����a = a + 0 = &arr[0]��*a = arr[0]����һ����Ԫ�أ���sizeof
//	// sizeof(��һ�������������)�����һ�д�С
//	printf("%d\n", sizeof(a[3])); // 16
//	// a[3]���൱�ڵ����е���������sizeof��������û��Խ��
//	//int (*parr)[3][4] = a;
//	return 0;
//}


/*
-----------------------------------------------------------------
�����1
*/
//int main() {
//    int a[5] = { 1, 2, 3, 4, 5 };
//    int* ptr = (int*)(&a + 1); // &a + 1 = �������׸���ַ
//    printf("%d,%d", *(a + 1), *(ptr - 1)); // 2, 5
//    return 0;
//}


// //�ṹ��Ĵ�С��20���ֽ�
// //*pΪ�ṹ��ָ��
//struct Test {
//    int Num; // 4
//    char* pcName; // 4
//    short sDate; // 2
//    char cha[2]; // 2
//    short sBa[4]; // 8
//}* p = (struct Test*)0x100000;
// //����p ��ֵΪ0x100000�� ���±���ʽ��ֵ�ֱ�Ϊ���٣�
// //��֪���ṹ��Test���͵ı�����С��20���ֽ�
//int main() {
//    printf("%#p\n", p);
//    printf("%#p\n", p + 0x1); // 0x100014
//    printf("unsigned long �����ʹ�С:%d\n", sizeof(unsigned long)); // 4
//    printf("%#p\n", (unsigned long)p + 0x1); // 0x100001 
//    // (unsigned long)p��p��ǿ��ת���ɵ�����������+1������������0x100000 + 0x1= 0x100001 
//    // �Ե�ַ�������������������
//    printf("%#p\n", (unsigned int*)p + 0x1); // 0x100004
//    return 0;
//}

/*
������3
*/
//int main() {
//    int a[4] = { 1, 2, 3, 4 };
//    int* ptr1 = (int*)(&a + 1); // ptr1 ָ�� ���������������׸���ַ
//    int* ptr2 = (int*)((int)a + 1); // ��a��ǿ��ת����������+1Ϊ��������������
//    printf("%x,%x", ptr1[-1], *ptr2); // 4, 
//    return 0;
//}


/*
������4
*/
//#include <stdio.h>
//int main() {
//    int a[3][2] = { (0, 1), (2, 3), (4, 5) }; // ʵ�ʴ洢Ϊ{{1, 3}, {5, 0}, {0, 0}};
//    int* p;
//    p = a[0]; // pָ���һ����Ԫ�أ�
//    printf("%d", p[0]); // ��һ�е�һ�� 1
//    return 0;
//}

/*
������5
*/
//int main() {
//    int a[5][5];
//    int(*p)[4];
//    p = a; // a��һ����Ԫ�ص�ַ ���� int(*)[5]��pΪint(*)[4]���Ը�ֵ�����Ͳ��䣬�ᾯ��
//    printf("%p,%d\n", &p[4][2] - &a[4][2], &p[4][2] - &a[4][2]); // FF FF FF FC | -4
//    // p[4]ÿ�λ�����ƶ�4*4�ֽڴ�С��p[4][2]Ϊ�ƶ�4*4 + 2���ֽڴ�С��ȡ�õ�ַ��ʾ��Ԫ�صĵ�ַ
//    // -4 ����ַ���������-4�Ĳ��벻������ֱ�����
//    // ָ�� - ָ�� = Ԫ�ظ���
//    return 0;
//}

/*
������6
*/
//int main() {
//    int aa[2][5] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
//    int* ptr1 = (int*)(&aa + 1); // ptr1���������������׵�ַ
//    int* ptr2 = (int*)(*(aa + 1)); // ptr2 = &6
//    printf("%d,%d", *(ptr1 - 1), *(ptr2 - 1)); // 10, 5
//    return 0;
//}

/*
������7
*/
//int main() {
//    char* a[] = { "work","at","alibaba" }; // a����Ϊ char(*)[3]������ָ��
//    char** pa = a;
//    pa++; // ������һ�У�ָ��"at"���׵�ַ
//    printf("%s\n", *pa); // "at"
//    return 0;
//}


/*
������8
*/
int main() {
    char* c[] = { "ENTER","NEW","POINT","FIRST" }; // ����ָ�룬���� char(*)[4]
    char** cp[] = { c + 3,c + 2,c + 1,c }; 
    // c + 3 �� c Ϊָ����Ԫ�صĵ�ַ��c + 3 ָ�����3��ָ���С��ָ��FIRST
    char*** cpp = cp;
    printf("%s\n", **++cpp); // POINT
    printf("%s\n", *-- * ++cpp + 3); // ER
    printf("%s\n", *cpp[-2] + 3); // ST
    printf("%s\n", cpp[-1][-1] + 1); // EW
    return 0;
}


