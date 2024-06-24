/*********************************
Date:
Title:
Author:JiaZiChunQiu
Content:
**********************************/

#define _CRT_SECURE_NO_WARNINGS
#include "ArrayQueue.h"
#include <stdio.h>

int main(void) {
	QArray* qArr = createQueue();
	printf("%d\n", isEmpty(qArr));

	for (int i = 0; i < 10; i++) {
		pushQueue(qArr, i);
		if (i == 5)  isFull(qArr);
	}

	printf("%d\n", popQueue(qArr));

	printf("%d\n", peekQueue(qArr));

	printf("%d\n", destroyQueue(qArr));
	return 0;
}
