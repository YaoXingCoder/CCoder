#include "gameDice.h"

void start(void) {
	int input = 0; // 循环条件
	int wins = 0; // 记录胜场
	int losses = 0; // 记录输场
	srand((unsigned int)time(NULL)); // 随机种子设置

	do {
		input = menu(); // 记录用户输入，是否继续循环进行游戏

		// 赢则win++，输则losses++
		if (1 == winOrloss()) {
			wins++;
		} else if (-1 == winOrloss()) {
			losses++;
		}

	} while (input);

	printf("Wins：%d，Losses：%d\n", wins, losses); // 结束输出
}

/*
判断输赢
返回值：
-1 loss
1 win
*/
int winOrloss() {
	int firstPoint = rollDices(); // 记录第一次点数
	printf("Your point is %d\n", firstPoint);
	// 单独对第一次进行判断
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

	// 后续循环进行游戏并重新判断
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
掷骰子
两个随机数相加

返回值：int 
值区间：[2,12]
*/
int rollDices() {
	int randomPoint1 = (rand() % 6 + 1);
	int randomPoint2 = (rand() % 6 + 1);
	printf("You rolled:%d\n", randomPoint1 + randomPoint2);
	return randomPoint1 + randomPoint2;
}

/*
菜单
设置为循环
只能输入y/n能够退出循环，输入其他则提示重新输入

返回值：
输入y，返回值1
输入n，返回值0
*/
int menu(void) {
	char flag;
	while (1) {
		
		printf("start game?(y/n)\n");
		flag = getchar();

		// 消除输入后的字符串，清空缓存区
		while (getchar() != '\n') {
			;
		}

		// 判断判断输入是否正确
		if ('y' == flag || 'Y' == flag) {
			return 1;
		} else if ('n' == flag || 'N' == flag) {
			return 0;
		} else {
			printf("Input error, Re-enter....\n");
		}
	}
}

