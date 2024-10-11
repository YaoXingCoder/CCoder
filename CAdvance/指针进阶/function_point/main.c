#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

//void test();
//
//int main() {
//	printf("%p\n", test); // 取函数的地址
//	printf("%p\n", &test); // 取出函数的地址
//	return 0;
//}
//&函数名 与 函数名 都是函数的地址，无区别
//void test() {
//	printf("hehe\n");
//}

/*
函数指针的存储和使用
*/
//int Add(int x, int y);
//
//int main(void) {
//	printf("取函数地址：%p\n", &Add);
//
//	// 保存函数地址，类比保存数组地址（数组指针）
//	int arr[5] = { 1,2,3,4,5 };
//	int (*pi1)[5] = &arr; // 保存数组的数组指针
//	printf("pi1 = %p\n", pi1);
//	printf("pi1+1 = %p\n", pi1 + 1);
//
//	//int (*pf)(int, int) = &Add; // 保存函数的函数指针
//	int (*pf)(int, int) = Add; // 保存函数的函数指针，Add与&Add等价
//	// (*pf)表明为指针，后边跟()表明指向的是函数，括号内填入函数的参数类型（形参可写可不写），类型为函数返回值类型
//
//	int ret = (*pf)(3, 2); // (*pf)解引用找到函数，传参调用函数 等价于 Add(3, 2)
//	ret = pf(3, 3); // 可以不写***，这边pf = Add，
//	// 因为使用int (*pf)(int, int) = Add; 保存函数指针时与 int (*pf)(int, int) = &Add;等价 所以 *pf = pf
//	ret = (****pf)(3, 4); // 也可以写多个****，但必须放在()内，方便理解
//	ret = (*Add)(5, 5); // 直接用函数名也可以
//	printf("%d\n", ret);
//	return 0;
//}

//int Add(int x, int y) {
//	return x + y;
//}


/* 
理解代码
*/
// 代码1
//void zeroFunction(void) {
//	( *( void(*)() ) 0 )();
//	// 1.void(*)()：为函数指针类型。类比：int (*p)(int, int);，
//	//	只是没有p变量，变成了函数指针类型，且传参为void，返回值类型为void
//	// 2.(void(*)())0：将int类型的0强制转换为了函数指针类型，0存储的二进制变为函数的地址，0指向该函数地址
//	// 3.(*( void(*)())0)：解引用该地址
//	// 4.(*( void(*)())0)()：调用函数，传参为void
//}

//代码2
//typedef void(*pf_t)(int); // 将 void(*)(int) 重命名为 pf_t 即函数指针类型
//int main(void) {
//	void (*signal(int, void(*)(int)))(int);
//	// 1.signal( int, void(*)(int) )：为函数声明，声明的signal函数的第一个参数为int，
//	//	第二个参数为void(*)(int)函数指针类型，该函数指针指向的函数的参数是int，返回类型是void
//	// 2.void(* signal() )(int)：signal的返回类型也是一个函数指针（即返回类型被声明为了一个函数指针的指针变量）
//	//	该函数指针指向的函数参数是int，返回类型是void
//
//	// 将上述声明简化：
//	pf_t signal(int, pf_t);
//	return 0;
//}

/*
函数指针用途
简单计算器，应用函数指针
*/
void menu();
int add(int x, int y);
int sub(int x, int y);
int mut(int x, int y);
int div(int x, int y);
void calc(int (*pf)(int, int));

int main(void) {
	int input = 0;
	do {
		menu();
		printf("Enter options:>");
		scanf("%d", &input);
		switch (input) {
			case 1:
				calc(add);
				break;
			case 2:
				calc(sub);
				break;
			case 3:
				calc(mut);
				break;
			case 4:
				calc(div);
				break;
			case 0:
				printf("退出程序~~~");
				input = 0;
				break;
			default:
				printf("选择错误~~~");
				break;
		}
	} while (input);
}

void menu() {
	printf("******************************\n");
	printf("*********1.Add   2.Sub********\n");
	printf("*********3.Mut   4.Div********\n");
	printf("*********9.Exit       ********\n");
	printf("******************************\n");
}

int add(int x, int y) {
	return x + y;
}
int sub(int x, int y) {
	return x - y;
}
int mut(int x, int y) {
	return x * y;
}
int div(int x, int y) {
	return x / y;
}

void calc(int (*pf)(int, int)) {
	int x = 0;
	int y = 0;
	int ret = 0;
	printf("Enter two number:>");
	scanf("%d %d", &x, &y);
	ret = pf(x, y);
	printf("结果为：%d\n", ret);
}
