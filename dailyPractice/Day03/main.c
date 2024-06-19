#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/*
Date:2024.06.13
Title:每日练习Day03
Content:
*/

/*
假设 int n = 0xCAFE; 请用表达式完成下面操作 (拓展题：不要求每个同学都写)
(a) 测试最后 4 位中是不是最少有 3 位为 1.
(b) 逆转字节序 (i.e.,使 n = 0xFECA)
(c) 旋转 4 位 (i.e., 使 n = 0xECAF)
*/
int lastBitIsOne(int num, int len);
void reserveBit(char* index);
int cycleBit(int num);
int main(void) {
	int n = 0xCAFE; // 1100 1010 1111 1110
	// (a)测试
	int count1 = lastBitIsOne(n, 4);
	if (count1 >= 3) {
		printf("最后4位至少有3个1，1的个数位：%d\n", count1);
	} else {
		printf("最后4位少于3个1，1的个数位：%d\n", count1);
	}

	// (b)逆转字节序
	int n1 = n;
	reserveBit((char*)&n1);
	printf("%#x\n", n1);

	// (c)旋转 4 位
	printf("%#x\n", cycleBit(n));

	return 0;
}

/* 
测试最后 4 位中是不是最少有 3 位为 1
思路：
数字与1进行与运算为1则最后一位是1，添加一个记录数字，记录1的个数
循环执行四次
*/
int lastBitIsOne(int num, int len) {
	int count = 0;
	for (int i = 0; i < len; i++) {
		if (num & 1) {
			count++;
		}
		num >>= 1;
	}
	return count;
}

/* 
逆转字节序 (i.e., 使 n = 0xFECA) 0x0000CAFE
想法1：
因为int类型位4字节，所以0xFECA = 0x0000FECA
传入int的地址，强转位1字节的char类型，再替换4字节中内容
0000 FECA
00 与 00 替换，
FE 与 CA 替换
*/ 
void reserveBit(char* index) {
	for (char i = 0; i < 4; i+=2) {
		char temp = *(index + i);
		*(index + i) = *(index + i + 1);
		*(index + i + 1) = temp;
	}
}

/*
(c) 旋转 4 位 (i.e., 使 n = 0xECAF)
n = 0x0000CAFE --> 0x0000ECAF
思路：
将int强转为short类型两个字节为CAFE，记录最后4bit值，
CAFE & 000F = 000E
CAFE 左移4位 -> 0CAF
000E 右移12位 -> E000
E000 | 0CAF = ECAF
 */
int cycleBit(int num) {
	int temp = num & 0x0F;
	num >>= 4;
	temp <<= 12;
	return num = temp | num;
}

/*
逆转字节序 (i.e., 使 n = 0xFECA) 0x0000CAFE
想法2：
因为int类型位4字节，所以0xFECA = 0x0000FECA
强转为short类型变为0xFECA,变为char类型替换FE和CA
*/


/*
逆转字节序 (i.e., 使 n = 0xFECA) 0xCAFE
想法3：
0xFECA 与 0xCAFE 异或获得 一个中间值
0xCAFE 与 中间值 异或获得 0xFECA
*/



/*
-------------------------------------------------------------------------------------
*/

/*
(a) 目前使用的格里高利历闰年的规则如下：
公元年分非4的倍数，为平年。
公元年分为4的倍数但非100的倍数，为闰年。
公元年分为100的倍数但非400的倍数，为平年。
公元年分为400的倍数为闰年。
请用一个表达式判断某一年是否为闰年。
(b) 输入某一天的年月日，输出下一天的年月日。
(c) 输入某两天的年月日，输出这两天的相距多少天(不考虑公元前，且第一个日期比第二个日期要早)。
(d) 已知1970年1月1日是星期四，输入之后的某一天的年月日，判断它是星期几？
*/
//void menu(void);
//int isLeapYear(unsigned int year);
//void nextDay(void);
//void calculateDays(void);
//void judgeDayOfWeek();
//int calDaysFrom0(int year, int month, int day);
//int calDaysFrom1970(int year, int month, int day);
//
//int main(void) {
//	int input = 0;
//	do {
//		menu();
//		printf("Enter the option：");
//		scanf("%d", &input);
//		if (input <= 1 && input >= 9) {
//			printf("The input option is incorrect, please re-enter it.\n");
//			continue;
//		}
//		switch (input) {
//			case 1:
//				nextDay();
//				break;
//			case 2:
//				calculateDays();
//				break;
//			case 3:
//				judgeDayOfWeek();
//				break;
//			case 0:
//				printf("Exited");
//				input = 0;
//				break;
//			default:
//				printf("The input option is incorrect, please re-enter it.\n");
//				break;
//		}
//	} while (input);
//	return 0;
//}


/*
判断闰年
闰年返回1，不是返回0
公元年分非4的倍数，为平年。
公元年分为4的倍数但非100的倍数，为闰年。：year % 4 == 0 && year % 100 != 0
公元年分为100的倍数但非400的倍数，为平年。：
公元年分为400的倍数为闰年。：year % 400 == 0
*/
//int isLeapYear(unsigned int year) {
//	if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
//		return 1;
//	} else {
//		return 0;
//	}
//}

/*
输入某一天的年月日，输出下一天的年月日。
*/
//void nextDay(void) {
//	int year = 0, month = 0, day = 0;
//	printf("Please enter the year, month and day:>");
//	scanf("%d %d %d", &year, &month, &day);
//	day++;
//	if (month == 2){
//		if (day >= 29) { // 判断天增加的影响
//			if (isLeapYear(year)) { // 闰年
//				if (day == 30) {
//					day = 1;
//					month++;
//					printf("%d年%d月%d日\n", year, month, day);
//				} else {
//					printf("%d年%d月%d日\n", year, month, day);
//				}
//			} else {
//				day = 1;
//				month++;
//				printf("%d年%d月%d日\n", year, month, day);
//			}
//		}
//	} else if (day == 32) {
//		day = 1;
//		switch (month) {
//			case 1:
//			case 3:
//			case 5:
//			case 7:
//			case 8:
//			case 10:
//				month++;
//				printf("%d年%d月%d日\n", year, month, day);
//				break;
//			case 12:
//				month = 1;
//				year++;
//				printf("%d年%d月%d日\n", year, month, day);
//				break;
//		}
//	} else if (day == 31) {
//		day = 1;
//		switch (month) {
//			case 4:
//			case 6:
//			case 9:
//			case 11:
//				month++;
//				printf("%d年%d月%d日\n", year, month, day);
//				break;
//		}
//	}
//	printf("%d年%d月%d日\n", year, month, day);
//}


/*
输入某两天的年月日，输出这两天的相距多少天(不考虑公元前，且第一个日期比第二个日期要早)
计算出两个日期到0年0月0日的天数，再相减
*/
//void calculateDays(void) {
//	int year1 = 0, month1 = 0, day1 = 0;
//	printf("Please enter the first date:>");
//	scanf("%d %d %d", &year1, &month1, &day1);
//	while (getchar() != '\n') {
//		;
//	}
//	printf("Please enter the second date(backward than the first day):>");
//	int year2 = 0, month2 = 0, day2 = 0;
//	scanf("%d %d %d", &year2, &month2, &day2);
//	int difDays1 = calDaysFrom0(year1, month1, day1);
//	int difDays2 = calDaysFrom0(year2, month2, day2);
//	printf("The difference between the two dates is %d days\n", difDays2 - difDays1);
//}



/*
已知1970年1月1日是星期四，输入之后的某一天的年月日，判断它是星期几？
*/
//void judgeDayOfWeek() {
//	int year = 0, month = 0, day = 0;
//	printf("Please enter the year, month and day:>");
//	scanf("%d %d %d", &year, &month, &day);
//	int difDays = calDaysFrom1970(year, month, day);
//	switch ((difDays % 6)+1) {
//		case 1:
//			printf("This day is Friday.\n");
//			break;
//		case 2:
//			printf("This day is Saturday.\n");
//			break;
//		case 3:
//			printf("This day is Sunday.\n");
//			break;
//		case 4:
//			printf("This day is Monday.\n");
//			break;
//		case 5:
//			printf("This day is Tuesday.\n");
//			break;
//		case 6:
//			printf("This day is Wednesday.\n");
//			break;
//		case 7:
//			printf("This day is Thursday.\n");
//			break;
//		default:
//
//			break;
//	}
//}



/*
计算年月日到0年0月0日中间的天数
*/
//int calDaysFrom0(int year, int month, int day) {
//	year--;
//	int countLeaf = 0;
//	for (int i = 0; i < year; i++) {
//		if (isLeapYear(year)) {
//			countLeaf++;
//		}
//	}
//	int difYearDays = (year - countLeaf) * 365 + countLeaf * 366;
//	int difMonthDays = 0;
//	while (month-1) {
//		switch (month) {
//			case 1:
//			case 3:
//			case 5:
//			case 7:
//			case 8:
//			case 10:
//				difMonthDays += 31;
//				break;
//			case 4:
//			case 6:
//			case 9:
//			case 11:
//				difMonthDays += 30;
//				break;
//			case 2:
//				if (isLeapYear(year)) {
//					difMonthDays += 29;
//				} else {
//					difMonthDays += 28;
//				}
//				break;
//
//			default:
//				break;
//		}
//		month--;
//	}
//	return difYearDays + difMonthDays + day;
//	
//}

/*
计算年月日到1970年1月1日中间的天数
*/
//int calDaysFrom1970(int year, int month, int day) {
//	year;
//	int countLeaf = 0;
//	for (int i = 1970; i < year; i++) {
//		if (isLeapYear(year)) {
//			countLeaf++;
//		}
//	}
//	int difYearDays = (year - countLeaf) * 365 + countLeaf * 366;
//	int difMonthDays = 0;
//	while (month - 1) {
//		switch (month) {
//			case 1:
//			case 3:
//			case 5:
//			case 7:
//			case 8:
//			case 10:
//				difMonthDays += 31;
//				break;
//			case 4:
//			case 6:
//			case 9:
//			case 11:
//				difMonthDays += 30;
//				break;
//			case 2:
//				if (isLeapYear(year)) {
//					difMonthDays += 29;
//				} else {
//					difMonthDays += 28;
//				}
//				break;
//
//			default:
//				break;
//		}
//		month--;
//	}
//	return difYearDays + difMonthDays + day;
//
//}

/*
页面
*/
//void menu(void) {
//	printf("***********************************\n");
//	printf("****	1.输出下一天的日期	***\n");
//	printf("****	2.计算两个日期相距的天数***\n");
//	printf("****	3.判断星期几		***\n");
//	printf("****	0.退出菜单		***\n");
//	printf("***********************************\n");
//}