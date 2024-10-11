#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/*
Date:2024.6.19
Title:Enumaeration
Content:
1.定义
2.优点
3.使用
*/

enum Day//星期
{
	Mon,//0
	Tues,//1
	Wed,//2
	Thur,//3
	Fri,//4
	Sat,//5
	Sun//6
};

enum Day//星期
{
	//枚举常量
	Mon=1,
	Tues,
	Wed,
	Thur,
	Fri,
	Sat,
	Sun
};

//#define Mon 1
//#define Tues 2
//....

#define M 100

int main()
{
	enum Day d = Fri;
	int m = M;

	printf("%d\n", Mon);
	printf("%d\n", Tues);
	printf("%d\n", Wed);
	printf("%d\n", Thur);
	printf("%d\n", Fri);
	printf("%d\n", Sat);
	printf("%d\n", Sun);
	return 0;
}