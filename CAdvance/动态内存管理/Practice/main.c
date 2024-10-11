#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/*
Date:2024.6.19
Title:每日练习
Content:
1.最大公约数与最小公倍数之和
*/

/*
最大公约数与最小公倍数之和
*/
int minComMul(int left, int right) {
	int temp = 1;
	while (left * temp % right) temp++;
	return temp * left;
}

int maxComDiv(int left, int right) {
	int temp = 0;
	if (left < right) {
		temp = left;
		left = right;
		right = temp;
	}
	while (temp = left % right) {
		left = right;
		right = temp;
	}
	return right;
}

void minAndMax(void) {
	int n1 = 0, n2 = 0;
	printf("Enter two numbers:");
	if (scanf("%d%d", &n1, &n2) == 2) {
		int comDiv = maxComDiv(n1, n2);
		int comMul = minComMul(n1, n2);
		printf("minComMul + maxComDiv = %d\n", comDiv + comMul);
	} else {
		printf("Enter Error\n");
	}
}

/*
2.空心正方形
*/
void hollowSquare(void) {
	int n = 0;
	printf("Enter number:");
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (0 == i || n - 1 == i || 0 == j || n - 1 == j) {
				printf("* ");
			} else {
				printf("  ");
			}
		}
		putchar('\n');
	}
}

/*
3.
*/


/*
主函数
*/
int main(void) {
	//minAndMax();
	//hollowSquare();
	return 0;
}
