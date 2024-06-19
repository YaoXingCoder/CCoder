#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/*
Date:2024.06.13
Title:ÿ����ϰDay03
Content:
*/

/*
���� int n = 0xCAFE; ���ñ��ʽ���������� (��չ�⣺��Ҫ��ÿ��ͬѧ��д)
(a) ������� 4 λ���ǲ��������� 3 λΪ 1.
(b) ��ת�ֽ��� (i.e.,ʹ n = 0xFECA)
(c) ��ת 4 λ (i.e., ʹ n = 0xECAF)
*/
int lastBitIsOne(int num, int len);
void reserveBit(char* index);
int cycleBit(int num);
int main(void) {
	int n = 0xCAFE; // 1100 1010 1111 1110
	// (a)����
	int count1 = lastBitIsOne(n, 4);
	if (count1 >= 3) {
		printf("���4λ������3��1��1�ĸ���λ��%d\n", count1);
	} else {
		printf("���4λ����3��1��1�ĸ���λ��%d\n", count1);
	}

	// (b)��ת�ֽ���
	int n1 = n;
	reserveBit((char*)&n1);
	printf("%#x\n", n1);

	// (c)��ת 4 λ
	printf("%#x\n", cycleBit(n));

	return 0;
}

/* 
������� 4 λ���ǲ��������� 3 λΪ 1
˼·��
������1����������Ϊ1�����һλ��1�����һ����¼���֣���¼1�ĸ���
ѭ��ִ���Ĵ�
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
��ת�ֽ��� (i.e., ʹ n = 0xFECA) 0x0000CAFE
�뷨1��
��Ϊint����λ4�ֽڣ�����0xFECA = 0x0000FECA
����int�ĵ�ַ��ǿתλ1�ֽڵ�char���ͣ����滻4�ֽ�������
0000 FECA
00 �� 00 �滻��
FE �� CA �滻
*/ 
void reserveBit(char* index) {
	for (char i = 0; i < 4; i+=2) {
		char temp = *(index + i);
		*(index + i) = *(index + i + 1);
		*(index + i + 1) = temp;
	}
}

/*
(c) ��ת 4 λ (i.e., ʹ n = 0xECAF)
n = 0x0000CAFE --> 0x0000ECAF
˼·��
��intǿתΪshort���������ֽ�ΪCAFE����¼���4bitֵ��
CAFE & 000F = 000E
CAFE ����4λ -> 0CAF
000E ����12λ -> E000
E000 | 0CAF = ECAF
 */
int cycleBit(int num) {
	int temp = num & 0x0F;
	num >>= 4;
	temp <<= 12;
	return num = temp | num;
}

/*
��ת�ֽ��� (i.e., ʹ n = 0xFECA) 0x0000CAFE
�뷨2��
��Ϊint����λ4�ֽڣ�����0xFECA = 0x0000FECA
ǿתΪshort���ͱ�Ϊ0xFECA,��Ϊchar�����滻FE��CA
*/


/*
��ת�ֽ��� (i.e., ʹ n = 0xFECA) 0xCAFE
�뷨3��
0xFECA �� 0xCAFE ����� һ���м�ֵ
0xCAFE �� �м�ֵ ����� 0xFECA
*/



/*
-------------------------------------------------------------------------------------
*/

/*
(a) Ŀǰʹ�õĸ������������Ĺ������£�
��Ԫ��ַ�4�ı�����Ϊƽ�ꡣ
��Ԫ���Ϊ4�ı�������100�ı�����Ϊ���ꡣ
��Ԫ���Ϊ100�ı�������400�ı�����Ϊƽ�ꡣ
��Ԫ���Ϊ400�ı���Ϊ���ꡣ
����һ�����ʽ�ж�ĳһ���Ƿ�Ϊ���ꡣ
(b) ����ĳһ��������գ������һ��������ա�
(c) ����ĳ����������գ�������������������(�����ǹ�Ԫǰ���ҵ�һ�����ڱȵڶ�������Ҫ��)��
(d) ��֪1970��1��1���������ģ�����֮���ĳһ��������գ��ж��������ڼ���
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
//		printf("Enter the option��");
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
�ж�����
���귵��1�����Ƿ���0
��Ԫ��ַ�4�ı�����Ϊƽ�ꡣ
��Ԫ���Ϊ4�ı�������100�ı�����Ϊ���ꡣ��year % 4 == 0 && year % 100 != 0
��Ԫ���Ϊ100�ı�������400�ı�����Ϊƽ�ꡣ��
��Ԫ���Ϊ400�ı���Ϊ���ꡣ��year % 400 == 0
*/
//int isLeapYear(unsigned int year) {
//	if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
//		return 1;
//	} else {
//		return 0;
//	}
//}

/*
����ĳһ��������գ������һ��������ա�
*/
//void nextDay(void) {
//	int year = 0, month = 0, day = 0;
//	printf("Please enter the year, month and day:>");
//	scanf("%d %d %d", &year, &month, &day);
//	day++;
//	if (month == 2){
//		if (day >= 29) { // �ж������ӵ�Ӱ��
//			if (isLeapYear(year)) { // ����
//				if (day == 30) {
//					day = 1;
//					month++;
//					printf("%d��%d��%d��\n", year, month, day);
//				} else {
//					printf("%d��%d��%d��\n", year, month, day);
//				}
//			} else {
//				day = 1;
//				month++;
//				printf("%d��%d��%d��\n", year, month, day);
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
//				printf("%d��%d��%d��\n", year, month, day);
//				break;
//			case 12:
//				month = 1;
//				year++;
//				printf("%d��%d��%d��\n", year, month, day);
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
//				printf("%d��%d��%d��\n", year, month, day);
//				break;
//		}
//	}
//	printf("%d��%d��%d��\n", year, month, day);
//}


/*
����ĳ����������գ�������������������(�����ǹ�Ԫǰ���ҵ�һ�����ڱȵڶ�������Ҫ��)
������������ڵ�0��0��0�յ������������
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
��֪1970��1��1���������ģ�����֮���ĳһ��������գ��ж��������ڼ���
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
���������յ�0��0��0���м������
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
���������յ�1970��1��1���м������
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
ҳ��
*/
//void menu(void) {
//	printf("***********************************\n");
//	printf("****	1.�����һ�������	***\n");
//	printf("****	2.��������������������***\n");
//	printf("****	3.�ж����ڼ�		***\n");
//	printf("****	0.�˳��˵�		***\n");
//	printf("***********************************\n");
//}