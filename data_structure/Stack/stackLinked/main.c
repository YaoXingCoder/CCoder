/*********************************
Date:2024.6.24
Title:ջ������ʽʵ�֣���ͷ��㣩
Author:JiaZiChunQiu
Content:
**********************************/

#define _CRT_SECURE_NO_WARNINGS
#include "stackLinked.h"
#include <stdio.h>


int main(void) {
	SFrame* s = createStack();
	
	printf("%d\n", pushStack(s, 1));
	printf("%d\n", pushStack(s, 3));
	printf("%d\n", pushStack(s, 100));

	popStack(s);

	printf("%d\n", peekStack(s));

	printf("%d\n", destoryStack(s));
	return 0;
}
