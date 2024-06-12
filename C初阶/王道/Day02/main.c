#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/*
Date:2024.06.12
Title:王道Day02作业
Content:
1.写一个程序，实现分数相加。用户以分子 / 分母的形式输入分数，程序打印相加后的结果(化为最简分数)
2.并利用欧几里得算法求最大公约数，进行分数简化
*/

/*
写一个程序，实现分数相加。用户以分子 / 分母的形式输入分数，程序打印相加后的结果(化为最简分数)。如：

输入 :
Enter first fraction : 5 / 6
Enter second fraction : 3 / 4
输出：
The sum is 19 / 12

（注：利用欧几里得算法求最大公约数，进行分数简化）

*/
int main(void) {
	int numerator1 = 0, denominator1 = 0;
	int numerator2 = 0, denominator2 = 0;
	printf("Enter first fraction：");
	scanf("%d / %d", &numerator1, &denominator1);
	printf("Enter second fraction：");
	scanf("%d / %d", &numerator2, &denominator2);
	int retNum = numerator1 * denominator2 + numerator2 * denominator1;
	int	retDen = denominator1 * denominator2;
	// 确定大 小两个数，即确定 被除数 和 除数
	int data1 = (retNum > retDen ? retNum : retDen);
	int data2 = (retNum < retDen ? retNum : retDen);
	int divisor = data1 % data2;
	while (divisor) {
		data1 = data2;
		data2 = divisor;
		divisor = data1 % data2;
	}
	// 最终data2会是最大公约数
	retNum /= data2;
	retDen /= data2;
	printf("The sum is %d / %d", retNum, retDen);

	return 0;
}


//int main(void) {
//	int x = 10, y = 4, z = 1;
//	printf("x & 0x2 = %d\n", x & 0x2);
//	//printf("y >>= 2 = %d\n", y >>= 2);
//	y >>= x & 0x2 && z;
//	printf("x = %d, y = %d, z = %d\n", x, y, z);
//	return 0;
//}