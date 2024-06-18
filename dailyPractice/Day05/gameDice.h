#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void start(void); // 游戏开始
int menu(void); // 是否继续游戏
int winOrloss(); // 判断每回合输赢
int rollDices(); // 掷骰子点数
