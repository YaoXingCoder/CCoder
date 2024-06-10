#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<math.h>

void judgeTriangle(const int a, const int b, const int c); // 判断三角形
int aSum(int a, int n); // 求前n项和
int daffodils(int num); // 水仙花数
double myPow(int n, int k); // 求次方
void diamond1(int row); // 菱形
void hollowDiamond1(int row); // 空心菱形
void hollowDiamond2(int row); // 空心菱形2
void hollowDiamond3(int row); // 空心菱形3
int drinkSoda(int money); // 喝水问题

int main(void) {
	//judgeTriangle(3, 4, 5);
	//printf("%d的前%d之和为%d\n", 2, 5, aSum(2, 5));
	/*for (int i = 0; i < 100000; i++) {
		if (daffodils(i))
			printf("%d\t", i);
	}*/
	//diamond1(6);
	//hollowDiamond1(6);
	//hollowDiamond2(4);
	//hollowDiamond3(4);
	//printf("总公共能喝水%d瓶\n", drinkSoda(20));
	return 0;
}
/*
判断三角形的类型
*/
void judgeTriangle(const int a, const int b, const int c) {
	if (a<=0 || b<=0 ||c<=0) {
		printf("输入的三条边有误");
		return;
	}
	if (a + b > c || a + c > b || c + b > a) {
		if (a ==b || b == c || a == c) {
			if (a == b && b == c) {
				printf("该三角形为等边三角形\n");
				return;
			}
			printf("该三角形为等腰三角形\n");
			return;
		}
		if (a * a + b * b == c * c || a * a + c * c == b * b || b * b + c * c == a * a) {
			printf("该三角形为直角三角形\n");
			return;
		}
		printf("三条边能组成三角形\n");
	} else {
		printf("三条边不能组成三角形\n");
	}
}


/*
求 Sn = a + aa + aaa + aaaa + aaaaa; 的前五项之和，a为数字
*/
int aSum(int a, int n) {
	if (a > 10 || a < 1)
		return -1;
	if (n < 1)
		return -1;
	int sum = 0;
	int key = 0;
	for (int i = 0; i < n; i++) {
		key = key * 10 + a;
		sum += key;
	}
	return sum;
}

/*
水仙花数
一个n位数，其各位数字的n次方之和恰好等于该数本身
例如：153 = 1^3 + 5^3 + 3^3;
*/
int daffodils(int num) {
	// 计算这个整数有几位
	int temp = num;
	int n = 1; // 默认有1位数
	while(temp /10){
		n++;
		temp /= 10;
	}
	// 求各位的次方和
	temp = num;
	int sum = 0;
	for (int i = 0; i < n; i++) {
		sum += (int)myPow(temp % 10, n); // 计算取余得到的数的n次方
		temp /= 10;
	}
	if (sum == num) return 1;
	else return 0;
}

double myPow(int n, int k) {
	if (k > 0)
		return n * myPow(n, k - 1);
	else if (0 == k)
		return 1;
	else return 1.0 / myPow(n, -k);
}

/*
打印菱形
第1种，循环
____*
___***
__*****
_*******
*********
_*******
__*****
___***
____*
row指上半部分有多少行
*/
void diamond1(int row) {
	/*
	上半部分：row 行
	打印空格：row - 行号
	打印*：2 * 行号 - 1
	*/
	for (int i = 1; i <= row; i++) {
		for (int j = 1; j <= row - i; j++)
			printf(" ");
		for (int k = 1; k <= (2 * i - 1); k++)
			printf("*");
		printf("\n");
	}
	/*
	下半部分：row - 1 行
	打印空格：row - 行号
	打印*：2 * (row - 行号) - 1
	*/
	for (int i = 1; i <= row - 1; i++) {
		for (int j = 1; j <= i; j++)
			printf(" ");
		for (int k = 1; k <= (2 * (row - i) - 1); k++)
			printf("*");
		printf("\n");
	}
}

/*
空心菱形
*/
void hollowDiamond1(int row) {
		/*
	上半部分：row 行
	打印空格：row - 行号
	打印*：第1个 和 第2 * 行号 - 1个
	*/
	for (int i = 1; i <= row; i++) {
		for (int j = 1; j <= row - i; j++)
			printf(" ");
		for (int k = 1; k <= (2 * i - 1); k++) {
			if (1 == k || (2 * i - 1) == k)
				printf("*");
			else
				printf(" ");
			
		}
		printf("\n");
	}
	/*
	下半部分：row - 1 行
	打印空格：row - 行号
	打印*：2 * (row - 行号) - 1
	*/
	for (int i = 1; i <= row - 1; i++) {
		for (int j = 1; j <= i; j++)
			printf(" ");
		for (int k = 1; k <= (2 * (row - i) - 1); k++) {
			if (1 == k || (2 * (row - i) - 1) == k)
				printf("*");
			else
				printf(" ");
		}
		printf("\n");
	}
}

/*
总行数：2 * row + 1 行，从 -row 开始，到 row 结束
打印空格：abs(i)
打印*：row * 2 - (2 * abs(i) - 1)
*/
void hollowDiamond2(int row) {
	int stars = 2 * row;
	for (int i = -row; i <= row; i++) {
		for (int j = 1; j <= abs(i); j++)
			printf(" ");
		for (int k = 1; k <= stars - (2 * abs(i) - 1); k++) {
			if (1 == k || stars - (2 * abs(i) - 1) == k)
				printf("*");
			else
				printf(" ");
		}
		printf("\n");
	}
}

/*
	   ^y
	   |
	   |
	   |
---------------->
	   |		x
	   |
	   | 
打印*：|x| + |y| = row
*/
void hollowDiamond3(int row) {
	for (int i = -row; i <= row; i++) {
		for (int j = -row; j <= row; j++) {
			if ((i>0?i:-i) + (j>0?j:-j) == row)
			//if (abs(i) + abs(j) == row)
				printf("*");
			else
				printf(" ");
		}
		printf("\n");
	}
}

/*
喝汽水问题：
1瓶汽水1R，2个空瓶可以换1瓶汽水，给20R，可以喝多少汽水
20R：39瓶
*/
int drinkSoda(int money) {
	int total = money; // 默认第一次喝的为所有money买的
	int empty = money;
	while (empty >= 2) {
		total += empty / 2; // 空瓶置换后+原喝的 = 现在喝的
		empty = empty / 2 + empty % 2; // 空瓶/2 + 上次可能余有的 = 这次剩余的空瓶
	}
	return total;
}