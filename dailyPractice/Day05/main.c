#include "gameDice.h"
#include "gameTexasPoker.h"

/*
Date:2024.6.15
Title:ÿ����ϰ day05
Content:
1.������
2.�����˿�
3.�����
*/

int main(void) {
	//start(); // ��������Ϸ���
	printf("%d\n", fibonacci(3));
	return 0;
}

/*
쳲���������
*/
int fibonacci(int num) {
	if (num <= 2) return 1;
	return fibonacci(num - 1) + fibonacci(num - 2);
}
