/*********************************
Date:2024.6.26
Title:队列的链式实现
Author:JiaZiChunQiu
Content:
链式队列测试数据
**********************************/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "LinkedQueue.h"

int main(void) {
    QLinkedList* QLinked = createQueueLinked();
    //destoryQueue(QLinked);
    // 逐一入队列
    pushQueue(QLinked, 1);
    pushQueue(QLinked, 2);
    pushQueue(QLinked, 3);
    pushQueue(QLinked, 4);
    pushQueue(QLinked, 5);
    pushQueue(QLinked, 6);

    // 先进先出，出队列全部元素直到队列为空
    while (!isEmpty(QLinked)) {
        ElementType val = peekQueue(QLinked);
        printf("%d ", val);
        popQueue(QLinked);
    }

    printf("\n");
    return 0;
}
