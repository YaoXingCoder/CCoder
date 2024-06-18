#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

/*
Date:2024.6.14
Title:wangdaoDay04
Content:�����ҵ
*/



/*
�����뿪��һ�����˳���
����Ϊ�û��ṩѡ��˵���
����˻���
���˻��ϴ�Ǯ��
���˻���ȡǮ��
��ʾ��ǰ��
�˳�����
ѡ����ֱ������� 0��1��2��3 �� 4 ��ʾ��

����ĻỰ����������
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
�˵�
*/
//void menu(void) {
//	printf("Commands: 0=clear, 1=credit, 2=debit, 3=balance, 4=exit\n");
//}

/*
����˻����
*/
//void clearAmount(float* amo) {
//	*amo = 0;
//}

/*
���˻��ϴ�Ǯ
*/
//void saveMoney(float* amo) {
//	float money = 0;
//	printf("Enter amount of credit:");
//	scanf("%f", &money);
//	*amo += money;
//}

/*
���˻���ȡǮ
*/
//void withcdrawMoney (float* amo) {
//	float money = 0;
//	printf("Enter amount of credit:");
//	scanf("%f", &money);
//	*amo -= money;
//}

/*
��ʾ��ǰ���
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
����һ�� �ǿ��������� nums������ĳ��Ԫ��ֻ����һ�����⣬����ÿ��Ԫ�ؾ��������Ρ�
�ҳ��Ǹ�ֻ������һ�ε�Ԫ�ء�
���룺nums = [1,4,2,1,2]
�����4

˼·��������� a ^ a ^ b = b
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
����һ���������� nums������ǡ��������Ԫ��ֻ����һ�Σ���������Ԫ�ؾ��������Ρ� 
�ҳ�ֻ����һ�ε�������Ԫ�ء�����԰�����˳�򷵻ش�.
���룺nums = [1,2,1,3,2,5]
�����[3, 5]
���ͣ�[5, 3] Ҳ����Ч�Ĵ�

˼·��
�����������
�������������ܹ��õ�������û���ظ�������Ԫ�ص����ֵ
�����ֵȡ�����һλ������������ͬԪ�����һλ�Ĳ�ͬ���ܹ���������Ԫ��
*/
//void findTwoDif(int nums[], int sz) {
//	int temp = 0;
//	for (int i = 0; i < sz; i++) {
//		temp ^= nums[i];
//	}
//	// �õ������ֵ�����һλ
//	temp = temp & (-temp);
//
//	// �������飬��temp����ֵ��Ϊ��һ�ࣨ���бض����ظ��������������ظ���֮һ������tempΪ��һ��
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
�û������ʼ�����ʺ�Ͷ�����������򽫴�ӡһ�ű��
�����ʾ����������Լ�������� 4 �����������µ��ܽ�
����ĻỰ���£�
Enter initial balance: 100
Enter interest rate: 6
Enter number of years: 5
Years    6%     7%     8%     9%    10%
  1    106.00 107.00 108.00 109.00 110.00
  2    112.36 114.49 116.64 118.81 121.00
  3    119.10 122.50 125.97 129.50 133.10
  4    126.25 131.08 136.05 141.16 146.41
  5    133.82 140.26 146.93 153.86 161.05

  ���Ǹ�����
  ��һ��������(���� + ���� * ����)��
  �ڶ���������ڵ�һ�����Ļ������ۼ�(���� * ����)��
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
дһ��������Ƶĳ����û�ָ���������ƣ������ӡ���ơ�����ĻỰ���£�
Enter number of cards in hand: 5
Your hand: 9c 7d 3c 5d kd

�Ʒ�����+��ɫ���������ַ�������д洢
һ����λ�����¼�Ѿ��ַ����ƣ�ͬʱ�����´ηַ���ʱ�����ж��Ƿ��Ѿ��ַ���

rank[13]�������
suit[3]��Ż�ɫ��d(diamond ����)��c(club ÷��)��s(spade ����)��h(heart ����)
int rankIndex = rand() % 13; �����������ֵ
int suitIndex = rand() % 4; ������ɫ���ֵ
hasDistribute[suitIndex][rankIndex]����¼�Ѿ���Ź��Ļ�ɫ
*/
void distributeCards (char rank[], char suit, int num);

int main(void) {
	// �趨�������
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
		// �ж��Ƿ��Ź�
		if (!hasDistribute[suitIndex][rankIndex]) {
			printf("%c%c ", rank[rankIndex], suits[suitIndex]);
			hasDistribute[suitIndex][rankIndex] = true; // ���ź����true
			num--;
		}
	}
}