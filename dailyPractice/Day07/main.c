#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/*
Date:2024.6.18
Title:����Day07��ҵ��ϰ
Content:
1.�����ӡ
*/

/*
1.
(a) ��д�����һ����Ϣ��Ȼ�������ӡ������Ϣ��
Enter a message: Don't get mad, get even.
Reversal is: .neve teg ,dam teg t'noD
��ʾ��һ�ζ�ȡ��Ϣ�е�һ���ַ�����getchar�����������Ұ���Щ�ַ��洢�������У����������˻��߶����ַ� '\n' ʱֹͣ��������
(b) �޸�����������ָ�������������������ĵ�ǰλ�á�

(a)
˼·1��
����ָ�룬һ��һ��ѭ������
ѭ���������� left < right
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
//	char str[] = "Enter a message: Don't get mad, get even."; // 42��'\0'
//	char newStr[42] = { 0 };
//	//reverseStr(str);
//	int len = strlen(str); // 41
//	reverseStr1(newStr, str, len);
//	reverseStr2(newStr, str, len);
//	printf("Reversal is: %s", newStr);
//	return 0;
//}


/*
��a) ��д�����һ����Ϣ��Ȼ����������Ϣ�Ƿ��ǻ��ģ���Ϣ�������ҿ��ʹ���������һ���ģ���
Enter a message: He lived as a devil, eh?
Palindrome
Enter a message: Madam, I am Adam.
Not a palindrome
�������в�����ĸ���ַ��������������������е�λ�á�
��b���޸���������ʹ��ָ��������������������е�λ�á�
*/

//void ispalindrome1(char src[], int size) {
//	// ֻ���ַ����Ƶ�������
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
��д�����ҳ�һ�鵥������С���ʺ���󵥴ʡ�
���û�����4����ĸ�ĵ���ʱ������ֹͣ���롣
�������е��ʶ�������20����ĸ������Ự���£�

Enter word: dog
Enter word: zebra
Enter word: rabbit
Enter word: catfish
Enter word: walrus
Enter word: cat
Enter word: fish

Smallest word: cat
Largest word: zebra
��ʾ��ʹ��������Ϊ smallest_word �� largest_word ���ַ������ֱ��¼��С���ʺ���󵥴ʡ�
�û�ÿ����һ���µ��ʣ���Ҫ�� strcmp ������ smallest_word �� largest_word ���бȽϡ�
�� strlen �����ж��û��Ƿ������� 4 ����ĸ�ĵ��ʡ�
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
