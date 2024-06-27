/*********************************
Date:2024.6.26
Title:���е���ʽʵ��
Author:JiaZiChunQiu
Content:
��ʽ���в�������
**********************************/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "LinkedQueue.h"

int main(void) {
    QLinkedList* QLinked = createQueueLinked();
    //destoryQueue(QLinked);
    // ��һ�����
    pushQueue(QLinked, 1);
    pushQueue(QLinked, 2);
    pushQueue(QLinked, 3);
    pushQueue(QLinked, 4);
    pushQueue(QLinked, 5);
    pushQueue(QLinked, 6);

    // �Ƚ��ȳ���������ȫ��Ԫ��ֱ������Ϊ��
    while (!isEmpty(QLinked)) {
        ElementType val = peekQueue(QLinked);
        printf("%d ", val);
        popQueue(QLinked);
    }

    printf("\n");
    return 0;
}
