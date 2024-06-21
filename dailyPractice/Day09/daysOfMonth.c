#include "vector.h"

/*
Date:2024.6.21
Title:ÿ����ϰ
Content:
����һ��ö������Month������һ���е�12���·ݣ���Ϊÿ���·ݷ���һ����1��ʼ������ֵ��
���磺January=1��February=2����������....
��дһ������������Month���͵Ĳ��������ظ��·��ж����졣
*/

typedef enum month {
	January = 1,
	February,
	March,
	April,
	May,
	June,
	July,
	August,
	September,
	Octobar,
	November,
	December
}Month;

int isLeapYear(int year) {
	return (year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0));
}

unsigned int daysOfMonth(int year, Month month) {
	switch (month) {
		case February: 
			return isLeapYear ? 29 : 28;
		case January: case March: case May: case July: case August: case Octobar: case December:
			return 31;
		case April: case June: case September: case November:
			return 30;
		default:
			return -1;
	}
}