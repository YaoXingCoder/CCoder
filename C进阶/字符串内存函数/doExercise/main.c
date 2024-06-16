#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <string.h>

/*
Date:2024.6.16
Title:习题练习
Content:
1.有序序列合并
2.改数子
3.购物
4.杨辉三角
5.左旋字符串中的k个字符
6.杨氏矩阵
7.判断一个字符串是否为另外一个字符串旋转之后的字符串
*/

void reserveStr(char* left, char* right);

/*
1.
有序序列合并
输入两个升序排列的序列，将两个序列合并为一个有序序列并输出。
数据范围：1<=𝑛 ,𝑚≤1000
序列中的值满足：0 <= val <= 30000

输入包含三行，
第一行包含两个正整数n, m，用空格分隔。n表示第二行第一个升序序列中数字的个数，m表示第三行第二个升序序列中数字的个数。
第二行包含n个整数，用空格分隔。
第三行包含m个整数，用空格分隔。

输入：
5 6
1 3 7 9 22
2 8 10 17 33 44

输出：
1 2 3 7 8 9 10 17 22 33 44
*/
void sequenceMerg(void) {
	int src1[] = { 1, 3, 7, 9, 22 };
	int src2[] = { 2,8,10,17,33,44 };
	int dest[20] = { 0 };
	int sz1 = sizeof(src1) / sizeof(src1[0]);
	int sz2 = sizeof(src2) / sizeof(src2[0]);
	int sz3 = sizeof(dest) / sizeof(dest[0]);
	int i = 0, j = 0, k = 0;
	while (i < sz1 && j < sz2) {
		if (src1[i] < src2[j]) {
			dest[k++] = src1[i++];
		} else {
			dest[k++] = src2[j++];
		}
	}
	while (i < sz1) {
		dest[k++] = src1[i++];
	}
	while (j < sz2) {
		dest[k++] = src2[j++];
	}

	for (int i = 0; i < sz3; i++) {
		printf("%d ", dest[i]);
	}
}

/*
2.
小乐乐喜欢数字，尤其喜欢0和1。他现在得到了一个数，想把每位的数变成0或1。
如果某一位是奇数，就把它变成1，如果是偶数，那么就把它变成0。请你回答他最后得到的数是多少。
输入包含一个整数n (0 ≤ n ≤ 109)
输出一个整数，即修改后得到的数字。
输入：222222
输出：0
输入：123
输出：101

思路：
取最低位，%10，记录到临时变量temp
判断temp奇偶性，%2 == 0，true改为0，false改为1
除以10得到高位
设置中间变量记录改后数字和，得到数字从低位开始
*/
int changeNum(int num) {
	int sum = 0;
	int i = 0;
	while(num) {
		int temp = num % 10;
		if (1 == temp % 2) {
			sum += 1 * pow(10, i);
		}
		i++;
		num /= 10;
	}
	return sum;
}

/*
多组输入，一个整数（2~20），表示直角三角形直角边的长度，即“*”的数量，也表示输出行数。
针对每行输入，输出用“*”组成的对应长度的直角三角形，每个“*”后面有一个空格。
输入：5
输出：
		*	4个空格（5-i），1个*	(i)
	  * *	3个空格，2个*
	* * *
  * * * *
* * * * *
*/
void printRightTriangle(int num) {
	for (int i = 1; i <= num; i++) {
		for (int j = 0; j < num - i; j++) printf("  ");
		for (int k = 0; k < i; k++) printf("* ");
		printf("\n");
	}
}

void printRightTriangle2(int num) {
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num ; j++) {
			if (i + j < num-1) printf("  ");
			if (i + j >= num-1) printf("* ");
		}
		printf("\n");
	}
}

/*
如果今天是“双11”（11月11日）则这件衣服打7折，
“双12” （12月12日）则这件衣服打8折，
如果有优惠券可以额外减50元（优惠券只能在双11或双12使用），
求KiKi最终所花的钱数。

一行，四个数字，
第一个数表示小明看中的衣服价格，
第二和第三个整数分别表示当天的月份、当天的日期、
第四个整数表示是否有优惠券（有优惠券用1表示，无优惠券用0表示）。 
注：输入日期保证只有“双11”和“双12”。

输入：1000.0 11 11 1
输出：650.00
输入：999.8 12 12 0
输出：799.84
*/
double paymentAmount(double price, int month, int day, int coupon) {
	double payment = 0.0;
	if (11 == month && 11 == day) {
		payment = price * 0.7 - coupon*50;
	} else if(12 == month && 12 == day) {
		payment = price * 0.8 - coupon*50;
	}
	if (payment < 0.0) payment = 0.0;
	return payment;
}

/*
杨辉三角
每行的端点数为1， 一个数也为1；
每个数等于它左上方和上方的两数之和。
输入：6
输出：
	1
	1    1
	1    2    1
	1    3    3    1
	1    4    6    4    1
	1    5   10   10    5    1
*/
void yangHuiTriangle(void) {
	int arr[10][10] = { 0 };
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j <= i; j++) {
			if (i <= 1) {
				arr[i][j] = 1;
			}else {
				arr[i][j] = arr[i - 1][j - 1] + arr[i - 1][j];
			} 
		}
	}

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j <= i; j++) {
			printf("	%d", arr[i][j]);
		}
		printf("\n");
	}
}


/*
左旋字符串中的k个字符

ABCD左旋一个字符得到BCDA
ABCD左旋两个字符得到CDAB
字符串必须是字符串数组，常量字符串不能够被修改
形参，字符指针，整型
思路：
存放需要移动的字符
后边字符依次复制向前
将存放的字符放到最后
循环+指针
*/
char* leftRotation(char str[], int num) {
	assert(str);
	if ('\0' == *str) {
		return "";
	}
	num %= (strlen(str) - 1);
	for (int i = 0; i < num; i++) {
		char* start = str;
		char temp = *start;
		while ('\0' != *(start + 1)) {
			*start = *(start + 1);
			start++;
		}
		*start = temp;
	}
	return str;
}

/*
循环+数组
*/
void leftRotation2(char str[], int k) {
	int i = 0;
	k %= (strlen(str) - 1);
	int len = strlen(str);
	for (int i = 0; i < k; i++) {
		char temp = str[0];
		for (int j = 0; j < len - 1; j++) {
			str[j] = str[j + 1];
		}
		str[len - 1] = temp;
	}
}

/*
三次反转实现
*/
void leftRotation3(char str[], int k){
	int len = strlen(str);
	k %= len;
	reserveStr(str, str + k - 1); // 左边
	reserveStr(str + k, str + len - 1); // 右边
	reserveStr(str, str + len -1); // 整体
}

void reserveStr(char* left, char* right) {
	assert(left && right);
	char temp;
	while (left < right) {
		temp = *left;
		*left = *right;
		*right = temp;
		left++;
		right--;
	}
}

/*
杨氏矩阵
有一个数字矩阵，矩阵的每行从左到右是递增的，矩阵从上到下是递增的
请编写程序在这样的矩阵中查找某个数字是否存在
时间复杂度<O(N)

1 2 3
4 5 6
7 8 9
运用右上和左下的特殊性
能够确定一行or一列
返回值为结构体，存方xy的坐标
*/

struct Point {
	int x;
	int y;
};

struct Point findNum(int arr[3][3], int rows, int column, int num) {
	int x = 0;
	int y = column - 1;
	struct Point p = { -1, -1 };
	while(x < rows && y >= 0) {
		if (num < arr[x][y]) {
			y--;
		} else if (num > arr[x][y]) {
			x++;
		} else {
			p.x = x;
			p.y = y;
			return p;
		}
	}
	return p;
}

// 传递过来的x,y为地址，成功时将坐标通过指针返回给调用函数
int findNum2(int arr[3][3], int* px, int* py, int num) {
	int x = 0;
	int y = *py - 1;

	while (x < *px && y >= 0) {
		if (num < arr[x][y]) {
			y--;
		} else if (num > arr[x][y]) {
			x++;
		} else {
			*px = x;
			*py = y;
			return 1;
		}
	}
	return 0;
}


/*
写一个函数，判断一个字符串是否为另外一个字符串旋转之后的字符串。
例如：
给定s1=AABCD 和 s2=BCDAA, 返回1
给定s1=abcd 和 s2=ACBD, 返回0
AABCD左旋一个字符得到ABCDA
AABCD左旋两个字符得到BCDAA
AABCD右旋一个字符得到DAABC

思路：
将str1的首字符在str2中找到
计算该首字符到str2结尾的距离
该距离是str1转几次能够到str2
对str1进行旋转，比较是否与str2相等
比较使用strcmp()

结果：
str1 > str2 , 1
str1 = str2 , 0
str1 < str2 , -1
1 和 -1 都代表不是旋转得到的
0 代表旋转得到的
*/
int isLeftRotation(char str1[], char str2[]) {
	assert(str1 && str2);

	char* firstCharAddressStr1 = str1; // str1的首字符地址
	char* sameCharInStr2 = str2; // 相同字符在str2中的指针
	char* fisrtCharAddressStr2 = str2; // str2的首字符地址
	int str2Len = strlen(str2); // str2的字符长度
	int str1Len = strlen(str1); // str1的字符长度

	// 找str1字符在str2中的位置
	while ('\0' != *sameCharInStr2) { 
		if (*firstCharAddressStr1 == *sameCharInStr2) {
			break;
		}
		sameCharInStr2++;
	}
	if ('\0' == *sameCharInStr2)	return 0; // 找完也没找到，指定没有直接返回值
		
	int num = fisrtCharAddressStr2 + str2Len - sameCharInStr2; // 算出需要旋转的次数
	for (int i = 0; i < num; i++) { // 对字符串1进行旋转
		char temp = firstCharAddressStr1[0];
		for (int j = 0; j < str1Len - 1; j++) {
			firstCharAddressStr1[j] = firstCharAddressStr1[j + 1];
		}
		firstCharAddressStr1[str1Len - 1] = temp;
	}
	if (strcmp(str1, str2) == 0) return 1;
	return 0;
}

// 穷举
int isLeftRotation2(char str1[], char str2[]) {
	int len = strlen(str1);
	for (int i = 0; i < len; i++) {
		char temp = str1[0];
		for (int j = 0; j < len - 1; j++) {
			str1[j] = str1[j + 1];
		}
		str1[len - 1] = temp;
		if (strcmp(str1, str2) == 0) return 1;
	}
	return 0;
}

// 字符串1再扩一倍，包含所有的旋转情况
int isLeftRotation3(char str1[], char str2[]) {
	int len1 = strlen(str1);
	int len2 = strlen(str2);
	if (len1 != len2) return 0;

	strncat(str1, str1, len1);
	char ret = strstr(str1, str2); // 求子串，无为NULL，有为str1中str2首字符的指针
	if (NULL == ret) return 0;
	else return 1;
}

int main(void) {
	// 1.改数子
	//printf("%d\n", changeNum(22222));
	
	// 2.合并序列
	//sequenceMerg();
	
	// 3.直角三角
	//printRightTriangle2(4);
	
	// 4.购物
	//printf("payment = %.2lf\n", paymentAmount(66.6, 11, 11, 1));
	
	// 5。杨辉三角
	//yangHuiTriangle();
	
	// 6.左旋数字
	//char str[] = "abcdef";
	//leftRotation3(str, 6);
	//printf("%s\n", str);
	
	// 7.矩阵找数字
	//int arr[3][3] = { 1,2,3,4,5,6,7,8,9 };
	//int rows = sizeof(arr) / sizeof(arr[0]);
	//int column = sizeof(arr[0]) / sizeof(arr[0][0]);
	//int k = 7;
	//struct Point ret = findNum(arr, rows, column, 20);
	//printf("x = %d, y = %d\n", ret.x, ret.y);

	//int ret = findNum2(arr, &rows, &column, k);
	//if (ret) {
	//	printf("x = %d, y = %d\n", rows, column);
	//} else {
	//	printf("Not Found");
	//}

	// 8.字符串旋转结果查找
	char str1[20] = "abcdef";
	char str2[] = "cdefab";
	int ret = isLeftRotation3(str1, str2);
	if (1 == ret) {
		printf("ok\n");
	} else {
		printf("no\n");
	}

	return 0;
}
