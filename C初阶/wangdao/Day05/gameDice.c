#include "gameDice.h"

void start(void) {
	int input = 0; // ѭ������
	int wins = 0; // ��¼ʤ��
	int losses = 0; // ��¼�䳡
	srand((unsigned int)time(NULL)); // �����������

	do {
		input = menu(); // ��¼�û����룬�Ƿ����ѭ��������Ϸ

		// Ӯ��win++������losses++
		if (1 == winOrloss()) {
			wins++;
		} else if (-1 == winOrloss()) {
			losses++;
		}

	} while (input);

	printf("Wins��%d��Losses��%d\n", wins, losses); // �������
}

/*
�ж���Ӯ
����ֵ��
-1 loss
1 win
*/
int winOrloss() {
	int firstPoint = rollDices(); // ��¼��һ�ε���
	printf("Your point is %d\n", firstPoint);
	// �����Ե�һ�ν����ж�
	switch (firstPoint) {
		case 2: case 3: case 12:
			printf("You lose!\n");
			return -1;
			break;
		case 7: case 11:
			printf("You win!\n");
			return 1;
			break;
	}

	// ����ѭ��������Ϸ�������ж�
	while (1) {
		if (rollDices() == firstPoint) {
			printf("You win!\n");
			return 1;
		} else if (rollDices() == 7) {
			printf("You lose!\n");
			return -1;
		}
	}
}

/*
������
������������

����ֵ��int 
ֵ���䣺[2,12]
*/
int rollDices() {
	int randomPoint1 = (rand() % 6 + 1);
	int randomPoint2 = (rand() % 6 + 1);
	printf("You rolled:%d\n", randomPoint1 + randomPoint2);
	return randomPoint1 + randomPoint2;
}

/*
�˵�
����Ϊѭ��
ֻ������y/n�ܹ��˳�ѭ����������������ʾ��������

����ֵ��
����y������ֵ1
����n������ֵ0
*/
int menu(void) {
	char flag;
	while (1) {
		
		printf("start game?(y/n)\n");
		flag = getchar();

		// �����������ַ�������ջ�����
		while (getchar() != '\n') {
			;
		}

		// �ж��ж������Ƿ���ȷ
		if ('y' == flag || 'Y' == flag) {
			return 1;
		} else if ('n' == flag || 'N' == flag) {
			return 0;
		} else {
			printf("Input error, Re-enter....\n");
		}
	}
}

