#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/*
Date:2024.6.19
Title:每日习题
Content:

*/

/*
编写下面的函数：
void remove_filename(char* url);
url 指向一个包含以文件名结尾的 URL 字符串，例如 "http://www.knking.com/index.html"。
函数需要移除文件名和前面的斜杠。(在上面的例子中，结果为 "http://www.knking.com"）。
要求在函数中使用 "搜索字符串末尾" 的惯用法。
提示：把字符串中的最后一个斜杠替换为空字符。
*/
/*
思路：
指针从前向后找，找到只有一个/的位置
判断前后都为字符
且前边三个字符为com
停止复制
*/
#define DOMAIN_SIZE 100
void remove_filename(char* url) {
	char website[DOMAIN_SIZE] = { 0 };
	int i = 0;
	while (*url) {
		// 找到'/'
		if ('/' == *url && isalpha(*(url + 1)) && isalpha(*(url - 1))) {
			// 找到com后的'/'
			if (!strncmp("com", (url - 3), 3)) {
				break;
			}
		}
		website[i++] = *url;
		url++;
	}
	printf(website);
}

int main(void) {
	char* website = "http://www.knking.com/index.html";
	remove_filename(website);
	return 0;
}
