#include "vector.h"

/*
Date:2024.6.21
Title:每日练习
Content:
定义一个枚举类型Month，包含一年中的12个月份，并为每个月份分配一个从1开始的数字值。
例如：January=1，February=2，依此类推....
编写一个函数，接收Month类型的参数，返回该月份有多少天。
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