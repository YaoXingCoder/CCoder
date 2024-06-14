#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

/*
Date:2024.6.14
Title:wangdaoDay04
Content:编程作业
*/



/*
现在请开发一个记账程序。
程序将为用户提供选择菜单：
清空账户余额，
往账户上存钱，
从账户上取钱，
显示当前余额，
退出程序。
选择项分别用整数 0、1、2、3 和 4 表示。

程序的会话类似这样：
*** checkbook-balancing program ***
Commands: 0=clear, 1=credit, 2=debit, 3=balance, 4=exit
Enter command: 1
Enter amount of credit: 1000.0
Enter command: 2
Enter amount of debit: 100.0
Enter command: 3
Current balance: $900.00
Enter command: 9
Commands: 0=clear, 1=credit, 2=debit, 3=balance, 4=exit

Enter command: 0
Enter command: 3
Current balance: $0.00
Enter command: 4
*/
//void menu(void);
//void clearAmount(float* amo);
//void saveMoney(float* amo);
//void withcdrawMoney (float* amo);
//void showCurrentBalance(float* amo);
//
//int main(void) {
//	int input = 1;
//	float amount = 0;
//	printf("*** checkbook-balancing program ***\n");
//	do {
//		menu();
//		printf("Enter command:");
//		scanf("%d", &input);
//		switch (input) {
//			case 0:
//				clearAmount(&amount);
//				input = 1;
//				break;
//			case 1:
//				saveMoney(&amount);
//				break;
//			case 2:
//				withcdrawMoney(&amount);
//				break;
//			case 3:
//				showCurrentBalance(&amount);
//				break;
//			case 4:
//				input = 0;
//				break;
//			default:
//				break;
//		}
//	} while (input);
//	return 0;
//}

/*
菜单
*/
//void menu(void) {
//	printf("Commands: 0=clear, 1=credit, 2=debit, 3=balance, 4=exit\n");
//}

/*
清空账户余额
*/
//void clearAmount(float* amo) {
//	*amo = 0;
//}

/*
往账户上存钱
*/
//void saveMoney(float* amo) {
//	float money = 0;
//	printf("Enter amount of credit:");
//	scanf("%f", &money);
//	*amo += money;
//}

/*
从账户上取钱
*/
//void withcdrawMoney (float* amo) {
//	float money = 0;
//	printf("Enter amount of credit:");
//	scanf("%f", &money);
//	*amo -= money;
//}

/*
显示当前余额
*/
//void showCurrentBalance(float* amo) {
//	printf("Current balance: $%.2f\n", *amo);
//}

//int find_single_num(int nums[], int n);
//void findTwoDif(int nums[], int sz);
//
//int main(void) {
//	int nums1[5] = { 1, 4, 2, 1, 2 };
//	int sz1 = sizeof(nums1) / sizeof(nums1[0]);
//	printf("%d\n", find_single_num(nums1, sz1));
//
//	int nums2[6] = { 1, 2, 1, 3, 2, 5 };
//	int sz2 = sizeof(nums2) / sizeof(nums2[0]);
//	findTwoDif(nums2, sz2);
//	return 0;
//}

/*
(1) 
给你一个 非空整数数组 nums，除了某个元素只出现一次以外，其余每个元素均出现两次。
找出那个只出现了一次的元素。
输入：nums = [1,4,2,1,2]
输出：4

思路：异或运算 a ^ a ^ b = b
*/
//int find_single_num(int nums[], int n) {
//	int temp = 0;
//	for (int i = 0; i < n; i++) {
//		temp ^= nums[i];
//	}
//	return temp;
//}

/*
(2) 
给你一个整数数组 nums，其中恰好有两个元素只出现一次，其余所有元素均出现两次。 
找出只出现一次的那两个元素。你可以按任意顺序返回答案.
输入：nums = [1,2,1,3,2,5]
输出：[3, 5]
解释：[5, 3] 也是有效的答案

思路：
将数组分两类
对数组遍历异或能够得到数组中没有重复的两个元素的异或值
此异或值取出最后一位，就是两个不同元素最低一位的不同，能够区分两个元素
*/
//void findTwoDif(int nums[], int sz) {
//	int temp = 0;
//	for (int i = 0; i < sz; i++) {
//		temp ^= nums[i];
//	}
//	// 得到异或结果值的最后一位
//	temp = temp & (-temp);
//
//	// 分类数组，与temp相与值不为零一类（其中必定有重复的数和两个不重复数之一），与temp为零一类
//	int a = 0;
//	int b = 0;
//	for (int i = 0; i < sz; i++) {
//		if (temp & nums[i]) {
//			a ^= nums[i];
//		} else {
//			b ^= nums[i];
//		}
//	}
//	printf("The two different numbers is %d and %d\n", a, b);
//}

/*
用户输入初始金额，利率和投资年数，程序将打印一张表格。
表格将显示输入的利率以及紧随其后 4 个更高利率下的总金额。
程序的会话如下：
Enter initial balance: 100
Enter interest rate: 6
Enter number of years: 5
Years    6%     7%     8%     9%    10%
  1    106.00 107.00 108.00 109.00 110.00
  2    112.36 114.49 116.64 118.81 121.00
  3    119.10 122.50 125.97 129.50 133.10
  4    126.25 131.08 136.05 141.16 146.41
  5    133.82 140.26 146.93 153.86 161.05

  余额考虑复利，
  第一年的余额是(本金 + 本金 * 利率)，
  第二年则可以在第一年余额的基础上累加(本金 * 利率)。
*/
//int main(void) {
//	double initialBalance = 0;
//	printf("Enter initial balance:");
//	scanf("%lf", &initialBalance);
//
//	int interestRate = 0;
//	printf("interest rate:");
//	scanf("%d", &interestRate);
//
//	int years = 0;
//	printf("Enter number of years:");
//	scanf("%d", &years);
//
//	double initialBalances[5] = { 0.0 };
//	printf("Years ");
//	for (int year = 0; year < years; year++) {
//		printf("   %d%%  ", interestRate + year);
//		initialBalances[year] = initialBalance * (1.0 + (interestRate+year) / 100.0);
//	}
//	printf("\n");
//	for (int year = 0; year < years; year++) {
//		printf("  %d   ", year+1);
//		for (int i = 0; i < years; i++) {
//			printf(" %.2f", initialBalances[i]);
//			initialBalances[i] = initialBalances[i] * (1.0 + (interestRate + i) / 100.0);
//		}
//		printf("\n");
//	}
//	return 0;
//}


/*
写一个随机发牌的程序。用户指定发几张牌，程序打印手牌。程序的会话如下：
Enter number of cards in hand: 5
Your hand: 9c 7d 3c 5d kd

牌分数字+花色，分两个字符数组进行存储
一个二位数组记录已经分发的牌，同时方便下次分发牌时进行判断是否已经分发过

rank[13]存放数字
suit[3]存放花色：d(diamond 方块)、c(club 梅花)、s(spade 黑桃)、h(heart 红桃)
int rankIndex = rand() % 13; 产生数字随机值
int suitIndex = rand() % 4; 产生花色随机值
hasDistribute[suitIndex][rankIndex]：记录已经存放过的花色
*/
void distributeCards (char rank[], char suit, int num);

int main(void) {
	// 设定随机种子
	srand((unsigned int)time(NULL));
	char rank[13] = { '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A' };
	char suits[4] = { 'd', 'c', 'h', 's'};
	int numCards = 0;
	printf("Enter number of cards in hand:");
	scanf("%d", &numCards);
	distributeCards(rank, suits, numCards);
	printf("\n");
	return 0;
}

void distributeCards (char rank[], char suits[], int num) {
	bool hasDistribute[4][13] = { {false} };
	printf("Your hand:");
	while(num) {
		int rankIndex = rand() % 13;
		int suitIndex = rand() % 4;
		// 判断是否存放过
		if (!hasDistribute[suitIndex][rankIndex]) {
			printf("%c%c ", rank[rankIndex], suits[suitIndex]);
			hasDistribute[suitIndex][rankIndex] = true; // 发放后更改true
			num--;
		}
	}
}