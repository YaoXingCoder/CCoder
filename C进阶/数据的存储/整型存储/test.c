#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>

void endlessCycle(void);
void judgeLagerOrSmall(void);

//int main() {
//	int a = 10;
//	int b = -10;
//	//judgeLagerOrSmall();
//	return 0;
//}

/*
进入死循环
必须在VS，x86编译环境下
*/
void endlessCycle(void) {
	int i = 0;
	int arr[10] = { 1,2,3,4,5,6,7,8,9,10 };
	printf("arr的%p\n", arr);
	printf("i的%p\n", &i);
	for (i = 0; i <= 12; i++) {
		arr[i] = 0;
		printf("hehe\n");
	}
	return;
}

/*
判断编译器的存储模式大小端
int a = 1; int为四个字节，取到前一个字节，判断大端小端
取到前一字节：转为char即可
00 00 00 01 大端，
01 00 00 00 小端，
*/
void judgeLagerOrSmall(void) {
	int a = 1;
	char ch = *(char*)&a;
	if (1 == ch) printf("小端\n");
	else if (0 == ch) printf("大端\n");
	return;
}

/*
一个整数数组
交换其中的计数与偶数，使得其中所有的奇数都在偶数前边
*/
void moveOddEven(int arr[], int size) {
	int left = 0;
	int right = size - 1;
	while (left < right) {
		while (left < right && arr[left] % 2 == 1)
			left++;
		while (left < right && arr[right] % 2 == 0)
			right--;
		if (left < right) {
			int temp = arr[right];
			arr[right] = arr[left];
			arr[left] = temp;
			left++;
			right--;
		}
	}
}

// 下面程序输出什么？
//#include <stdio.h>
//int main() {
//	char a = -1;
//	signed char b = -1;
//	unsigned char c = -1;
//	printf("a=%d,b=%d,c=%d", a, b, c);
//	return 0;
//}
// -1，-1，255
/*
-1的补码:11111111 11111111 11111111 11111111
-1,-1,-1 都是 unsigned int 32bit 赋值给 a,b,c 时需要进行截取最后的 8bit
需要先将 -1 的补码算出来，截取后 8bit 存放入内存
最后在 printf 中又以 %d 输出，即 signed int 输入，需要将 8bit 的 char 类型的 -1 进行补充
char 在 VS 中默认为 signed char，所有 a,b 值为 -1，符号位为1，补充高位时也都补充1，补码转换为原码后仍为 -1
但 c 为 unsigned char 没有符号位，补充高位时直接补充0，所以输出%d时，补码即原码 00000000 00000000 00000000 11111111
*/



//#include <stdio.h>
//int main() {
//	char a = -128;
//	printf("%u\n", a);
//	return 0;
//}
// 4,294,967,168
/*
-128补码：11111111 11111111 11111111 10000000
a的存储：10000000
转换为%u(无符号整型)，a为有符号类型，高位补符号位1，补码为：11111111 11111111 11111111 10000000
%u输出直接输出补码即原码：11111111 11111111 11111111 10000000（4,294,967,168）
*/


//#include <stdio.h>
//int main() {
//	char a = 128;
//	printf("%u\n", a);
//	return 0;
//}
/*
128补码：00000000 00000000 00000000 10000000
a的存储：10000000
转换为%u(无符号整型)，a为有符号类型，高位补符号位1，补码为：11111111 11111111 11111111 10000000
%u输出直接输出补码即原码：11111111 11111111 11111111 10000000（4,294,967,168）
*/


//#include <stdio.h>
//int main() {
//	char a = 128;
//	printf("%u\n", a);
//	return 0;
//}
/*
128补码：00000000 00000000 00000000 10000000
a的存储：10000000
转换为%d(符号整型)，a为有符号类型，高位补符号位1，补码为：11111111 11111111 11111111 10000000
%u输出原码：10000000 00000000 00000000 10000000（-128）
char类型不能存储128，-128~127
*/

//int main() {
//	int i = -20;
//	unsigned int j = 10;
//	printf("%d\n", i + j);
//	return 0;
//}
/*
-20 补码：11111111 11111111 11111111 11101100
10 补码： 00000000 00000000 00000000 00001010
i + j 因为 j 为无符号，所以运算时i整型提升到无符号：11111111 11111111 11111111 11110110
又因为输出时%d为有符号，所以i+j需要以有符号输出原码：10000000 00000000 00000000 00001010（-10）
*/

//int main() {
//	unsigned int i;
//	for (i = 9; i >= 0; i--) {
//		printf("%u\n", i);
//		Sleep(1000);
//	}
//}
/*
死循环，i为无符号
9,8,...,1,0,-1,-2
-1 补码：11111111 11111111 11111111 11111111
-2 补码：11111111 11111111 11111111 11111110
赋值给 i 为无符号,输出也是 %u 无符号，所以补码即原码
*/

//int main() {
//	char a[1000];
//	int i;
//	for (i = 0; i < 1000; i++) {
//		a[i] = -1 - i;
//	}
//	printf("%d", strlen(a));
//	return 0;
//}
/*
死循环
char 类型：-128~127
strlen()遇到'\0'就结束，即ASCII 0
-1,-2,-3,...,-128,-129,...
-128 补码：11111111 11111111 11111111 10000000 截取 8bit后 10000000，依旧-128存储到char a[]中
-129 补码：11111111 11111111 11111111 01111111 截取 8bit后 01111111，变为127存储到char a[]中
-1,-2,...,-128,127,126,...,0,
所以strlen()计算的时 -1~126到0结束，即长度为255
*/


//#include <stdio.h>
//unsigned char i = 0;
//int main() {
//	for (i = 0; i <= 255; i++) {
//		printf("hello world\n");
//	}
//	return 0;
//}
/*
因为无符号类型所以256:0001 0000 0000，存储到char中为0000即0，又重新开始
所以i为0~255循环存储，for循环进入死循环
*/
