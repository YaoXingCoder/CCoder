#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

//void test();
//
//int main() {
//	printf("%p\n", test); // 取函数的地址
//	printf("%p\n", &test); // 取出函数的地址
//	return 0;
//}
//
//
//&函数名 与 函数名 都是函数的地址，无区别
//
//void test() {
//	printf("hehe\n");
//}

int Add(int x, int y);

int main(void) {
	printf("取函数地址：%p\n", &Add);

	// 保存函数地址，类比保存数组地址（数组指针）
	int arr[5] = { 1,2,3,4,5 };
	int (*pi1)[5] = &arr; // 保存数组的数组指针
	printf("pi1 = %p\n", pi1);
	printf("pi1+1 = %p\n", pi1 + 1);

	//int (*pf)(int, int) = &Add; // 保存函数的函数指针
	int (*pf)(int, int) = Add; // 保存函数的函数指针，Add与&Add等价
	// (*pf)表明为指针，后边跟()表明指向的是函数，括号内填入函数的参数类型（形参可写可不写），类型为函数返回值类型

	int ret = (*pf)(3, 2); // (*pf)解引用找到函数，传参调用函数 等价于 Add(3, 2)
	ret = pf(3, 3); // 可以不写***，这边pf = Add，
	// 因为使用int (*pf)(int, int) = Add; 保存函数指针时与 int (*pf)(int, int) = &Add;等价 所以 *pf = pf
	ret = (****pf)(3, 4); // 也可以写多个****，但必须放在()内，方便理解
	ret = (*Add)(5, 5); // 直接用函数名也可以
	printf("%d\n", ret);
	return 0;
}

int Add(int x, int y) {
	return x + y;
}