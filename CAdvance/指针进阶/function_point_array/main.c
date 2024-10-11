#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/*
函数指针数组用途：转移表
简单计算器，应用函数指针数组
*/
void menu();
int add(int x, int y);
int sub(int x, int y);
int mut(int x, int y);
int div(int x, int y);
void calc(int (*pf)(int, int));

int main(void) {
	int input = 0;
	int x = 0;
	int y = 0;
	int ret = 0;
	int (*pf[5])(int, int) = { 0, add, sub, mut, div };
	do {
		menu();
		printf("Enter options:>");
		scanf("%d", &input);

		if (0 == input) {
			printf("退出~~~~");
		} else if (input >= 1 && input <= 4) {
			printf("Enter two number:>");
			scanf("%d %d", &x, &y);
			ret = pf[input](x, y);
			printf("计算结果为：%d\n", ret);
		}else {
			printf("输入有误。。。");
		}
		
	} while (input);
}

void menu() {
	printf("******************************\n");
	printf("*********1.Add   2.Sub********\n");
	printf("*********3.Mut   4.Div********\n");
	printf("*********0.Exit       ********\n");
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