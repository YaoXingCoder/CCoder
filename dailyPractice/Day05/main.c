#include "gameDice.h"
#include "gameTexasPoker.h"

/*
Date:2024.6.15
Title:每日练习 day05
Content:
1.掷骰子
2.德州扑克
3.简答题
*/

int main(void) {
	//start(); // 掷骰子游戏入口
	printf("%d\n", fibonacci(3));
	return 0;
}

/*
斐波那契数列
*/
int fibonacci(int num) {
	if (num <= 2) return 1;
	return fibonacci(num - 1) + fibonacci(num - 2);
}
