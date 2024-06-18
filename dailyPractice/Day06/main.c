#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/*
Date:2024.6.17
Title:王道Day6作业
Content:
1.汉罗塔
2.约瑟夫环
3.查找数组中最大的元素和第二大的元素
4.指针练习
*/

/*
1.汉罗塔
1. 每次只能移动一个圆盘;
2. 大盘不能叠在小盘上面。

递归：
分两部分处理，第n层和第n-1层
1.前n-1个：A->B
2.第n个：A->C
3.前n-1个：B->C

递归结束条件：
剩1个，直接A->C

参数：
char ABC：给出ABC柱
int num：移动个数
*/

void hanluoTower(int num, char a, char b, char c) {
	if (1 == num) {
		printf("%c -> %c\n", a, c); // 剩最后一个直接移动即可
		return;
	}
	hanluoTower(num-1, a, c, b); // 先将前num-1个盘子整体移动到B柱，A经过C移动到B
	printf("%c -> %c\n", a, c); // 再将第num个盘子直接移动到C，A->C
	hanluoTower(num - 1, b, a, c); // 最后将前num-1个盘子整体移动到C柱，B经过A移动到C
}

/*
2.约瑟夫环

约瑟夫环：
n 个人站成一圈，每 m 个人处决一个人。
假设这 n 个人的编号为 1, 2, ..., n，并且从 1 开始数
问最终活下来的人编号是多少？

思路：
递归实现
少一个人对剩下人重新排号，重复上述的规则开始处决
少一个人重新排号，处决
一个人，完

n = 7, m = 3
0 1 2 3 4 5 6 // 3号活着，返回+1，即4号活着
0 1 \ 3 4 5 6 // 杀掉
4 5 \ 0 1 2 4 // 重新标号
4 5 \ 0 1 \ 4 // 杀掉x2
1 2 \ 3 4 \ 0 // 重新标号
3 \ \ 3 4 \ 0 // 杀掉x3
3 \ \ 0 1 \ 2 // 重新编号
3 \ \ 0 1 \ \ // 杀掉x4
0 \ \ 1 2 \ \ // 编号
0 \ \ 1 \ \ \ // 杀掉x5
\ \ \ 1 \ \ \ // 编号，杀掉x6

0 1 2 3 4 5 6 // 4号或者，返回+1，即5号活着
4 5 \ 0 1 2 4 // 重新标号
重新编号后上次编号与这次编号的关系
(4 + m) % n = 0
*/

int josephsR(int n, int m) {
	if (1 == n) return ((n + m) % n);
	return (josephsR(n - 1, m) + m) % n;
}

/*
3.查找数组中前两个大的元素

查找数组中最大的元素和第二大的元素，并将它们分别存放在由 largest 和 second_largest 指向的变量中。
void find_two_largest(int arr[], int n, int* largest, int* second_largest);
注意：
为了简化程序，数组不存在重复元素。

思路：
1.冒泡排序整个数组（排两次就好），将数组中最大的两个数分别付给largest和second_largest
2.执行一次循环最大的数存入largest，再执行第二次循环条件多一条<largest

进入函数给largest 和 second_largest初始化为0
冒泡排序(升序/降序)
条件0 != largest && 0 != second_largest直接跳出函数即可
*/
void find_two_largest(int arr[], int n, int* largest, int* second_largest) {
	*largest = 0;
	*second_largest = 0;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < n - 1 - i; j++) {
			if (arr[j] > arr[j+1]) {
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
		if (0 == i) *largest = arr[n - 1];
		if (1 == i) *second_largest = arr[n - 2];
		if (0 != *largest && 0 != *second_largest) return;
	}
}

/*
编写函数：

void split_time(long total_sec, int* hour, int* minute, int* second);
total_sec 表示从午夜12:00:00开始计算的秒数。
请将 total_sec 转化以时(0-23)、分(0-59)、秒(0-59)表示的时间，
并存放到函数外部由指针 hour, minute, second 指向的变量中。
并在外部，打印出当前的时间

思路：
hour = total_sec / 3600 = 已经过去的小时数
total_sec % 3600 = 剩下的分钟数 + 剩下的秒数
min = total_sec % 3600 / 60 = 已经过去的分钟数
sec = total_sec % 3600 % 60 % 60 = 过去的秒数

*/
void split_time(long total_sec, int* hour, int* minute, int* second) {
	*hour = total_sec / 3600 % 24;
	*minute = total_sec % 3600 / 60;
	*second = total_sec % 3600 % 60 % 60;
	return;
}


int main(void) {
	// 1.汉罗塔
	//hanluoTower(3, 'A', 'B', 'C');

	// 2.约瑟夫环
	//int survivor = josephsR(3, 3) + 1;
	//printf("%d个人，每%d杀一个，最后编号为%d的活到最后\n", 7, 3, survivor);

	// 3.查找数组中最大的元素和第二大的元素
	//int arr[] = { 23,12,4,6,3,5,62,3,4 };
	//int sz = sizeof(arr) / sizeof(arr[0]);
	//int largetest = 0, second_largest = 0;
	//find_two_largest(arr, sz, &largetest, &second_largest);
	//printf("largetest = %d, second_largest = %d\n", largetest, second_largest);

	// 4.指针练习
	int hour = 0;
	int minute = 0;
	int second = 0;
	long total_sec = 86400;
	split_time(total_sec, &hour, &minute, &second);
	printf("%d:%d:%d\n", hour, minute, second);
	return 0;
}
