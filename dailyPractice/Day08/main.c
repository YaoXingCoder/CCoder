#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/*
Date:2024.6.19
Title:ÿ��ϰ��
Content:

*/

/*
��д����ĺ�����
void remove_filename(char* url);
url ָ��һ���������ļ�����β�� URL �ַ��������� "http://www.knking.com/index.html"��
������Ҫ�Ƴ��ļ�����ǰ���б�ܡ�(������������У����Ϊ "http://www.knking.com"����
Ҫ���ں�����ʹ�� "�����ַ���ĩβ" �Ĺ��÷���
��ʾ�����ַ����е����һ��б���滻Ϊ���ַ���
*/
/*
˼·��
ָ���ǰ����ң��ҵ�ֻ��һ��/��λ��
�ж�ǰ��Ϊ�ַ�
��ǰ�������ַ�Ϊcom
ֹͣ����
*/
#define DOMAIN_SIZE 100
void remove_filename(char* url) {
	char website[DOMAIN_SIZE] = { 0 };
	int i = 0;
	while (*url) {
		// �ҵ�'/'
		if ('/' == *url && isalpha(*(url + 1)) && isalpha(*(url - 1))) {
			// �ҵ�com���'/'
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
