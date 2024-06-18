#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/*
Date:2024.6.18
Title:王道Day07作业练习
Content:
1.逆序打印
*/

/*
1.
(a) 编写程序读一条消息，然后逆序打印这条消息：
Enter a message: Don't get mad, get even.
Reversal is: .neve teg ,dam teg t'noD
提示：一次读取消息中的一个字符（用getchar函数），并且把这些字符存储在数组中，当数组满了或者读到字符 '\n' 时停止读操作。
(b) 修改上述程序，用指针代替整数来跟踪数组的当前位置。

(a)
思路1：
两个指针，一左一右循环交换
循环结束条件 left < right
*/
//void reverseStr(char* str) {
//	char* left = str;
//	char* right = str;
//	while (*right) {
//		right++;
//	}
//	right--;
//	while (left < right) {
//		char temp = *left;
//		*left = *right;
//		*right = temp;
//		left++;
//		right--;
//	}
//}
//
//
//void reverseStr1(char dest[], char src[], int size) {
//	for (int i = 0; i < size; i++) {
//		dest[size - i - 1] = src[i];
//	}
//}
//
//void reverseStr2(char* dest, char* src, int size) {
//	while ('\0' != *src) {
//		*(dest + size - 1) = *src;
//		size--;
//		src++;
//	}
//}
//
//int main(void) {
//	char str[] = "Enter a message: Don't get mad, get even."; // 42带'\0'
//	char newStr[42] = { 0 };
//	//reverseStr(str);
//	int len = strlen(str); // 41
//	reverseStr1(newStr, str, len);
//	reverseStr2(newStr, str, len);
//	printf("Reversal is: %s", newStr);
//	return 0;
//}


/*
（a) 编写程序读一条消息，然后检查这条消息是否是回文（消息从左往右看和从右往左看是一样的）：
Enter a message: He lived as a devil, eh?
Palindrome
Enter a message: Madam, I am Adam.
Not a palindrome
忽略所有不是字母的字符。用索引来跟踪数组中的位置。
（b）修改上述程序，使用指针代替索引来跟踪数组中的位置。
*/

//void ispalindrome1(char src[], int size) {
//	// 只将字符复制到新数组
//	char dest[50] = { 0 };
//	int i = 0;
//	int j = 0;
//	for (i = 0, j = 0; i < size; i++) {
//		if ((src[i] >= 'a' && src[i] <= 'z') || (src[i] >= 'A' && src[i] <= 'Z')) {
//			dest[j++] = tolower(src[i]);
//		}
//	}
//	dest[j] = src[i];
//
//	int len = strlen(dest);
//	int sameChar = 0;
//	for (int k = len - 1; k >= 0; k--) {
//		if (dest[k] == dest[len - 1 - k]) {
//			sameChar++;
//		}
//	}
//	if (sameChar == len) {
//		printf("Palindrome\n");
//	} else {
//		printf("Not a palindrome\n");
//	}
//}
//
//
//void ispalindrome2(char* dest, char* src, int size) {
//	char* start = src;
//
//	int countChar = 0;
//	while (*src) {
//		*dest = tolower(*src);
//		*src = tolower(*src);
//		if ((*src >= 'a' && *src <= 'z')) {
//			countChar++;
//		}
//		src++;
//		dest++;
//	}
//
//	int sameChar = 0;
//	while (*start) {
//		while ((*start < 'a' || *start > 'z') && *start != '\0') {
//			start++;
//		}
//		while ((*dest < 'a' || *dest > 'z')) {
//			dest--;
//		}
//		if (*start == *dest) {
//			sameChar++;
//			start++;
//			dest--;
//		}
//	}
//
//	if (sameChar == countChar) {
//		printf("Palindrome\n");
//	} else {
//		printf("Not a palindrome\n");
//	}
//}
//
//int main(void) {
//	char str[] = "He lived as a devil, eh?";
//	int len = strlen(str);
//	char newStr[50] = { 0 };
//	//ispalindrome1(str, len);
//	ispalindrome2(newStr, str, len);
//	return 0;
//}



/*
编写程序找出一组单词中最小单词和最大单词。
当用户输入4个字母的单词时，程序停止读入。
假设所有单词都不超过20个字母。程序会话如下：

Enter word: dog
Enter word: zebra
Enter word: rabbit
Enter word: catfish
Enter word: walrus
Enter word: cat
Enter word: fish

Smallest word: cat
Largest word: zebra
提示：使用两个名为 smallest_word 和 largest_word 的字符串来分别记录最小单词和最大单词。
用户每输入一个新单词，都要用 strcmp 把它与 smallest_word 和 largest_word 进行比较。
用 strlen 函数判断用户是否输入了 4 个字母的单词。
*/

int main(void) {
	int flag = 1;
	char smallest_world[21] = {0};
	char larget_word[21];
	char input[21];
	printf("Enter word:");
	scanf("%21s", input);
	strcpy(larget_word, input);
	strcpy(smallest_world, input);
	do {
		printf("Enter word:");
		scanf("%21s", input);
		if (4 == strlen(input)) flag = 0;
		if (strcmp(input, larget_word) > 0) {
			strcpy(larget_word, input);
			strcpy(smallest_world, input);
		} else if (strcmp(smallest_world, input) > 0){
			strcpy(smallest_world, input);
		}
	} while (flag);
	printf("Smallest word:%s\n", smallest_world);
	printf("Largest word:%s\n", larget_word);
	return 0;
}
