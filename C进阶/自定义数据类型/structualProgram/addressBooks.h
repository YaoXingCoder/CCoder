#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

#define MAX 100
#define MAX_NAME 20
#define MAX_GEDNER 10
#define MAX_PHONENUM 13
#define MAX_ADDRESS 10

/*
个人信息结构体
*/
typedef struct PerInfo {
	char name[MAX_NAME]; // 名字
	int age; // 年龄
	char gender[MAX_GEDNER]; // 性别
	char phoneNum[MAX_PHONENUM]; // 电话
	char addr[MAX_ADDRESS]; // 地址
}PerInfo;

/*
通讯录结构体
人员信息结构体数组 + count记录人数
*/
typedef struct DirectoryData{
	PerInfo directory[MAX]; // 存放人员信息
	int count; // 记录实际人数
}DirectoryData;

/*
函数声明
*/
void menu(void); // 菜单
void start(void); // 入口
void initData(DirectoryData* data); // 初始化通讯录
void add(DirectoryData* data); // 添加个人信息
void show(const DirectoryData* data); // 打印联系人
void delPerInfo(DirectoryData* data); // 删除指定联系人
void searchByName(DirectoryData* data); // 查找指定名字联系人位置
void modifyByName(DirectoryData* data); // 修改人员信息
void sortByName(DirectoryData* data); // 根据名字的字符串进行排序