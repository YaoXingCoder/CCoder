#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

#define MAX 100 // ͨѶ¼���ֵ
#define DEFAULT_SZIE 3 // ��̬Ĭ�ϴ�С
//#define CAPACITY 3 // ��̬��ʼ�����С
#define INCREMENTAL_INTERVAL 2 // ����ֵ
#define MAX_NAME 20 // ���ִ�С
#define MAX_GEDNER 10 // �Ա��С
#define MAX_PHONENUM 13 // �绰��С
#define MAX_ADDRESS 10 // ��ַ��С

/*
������Ϣ�ṹ��
*/
typedef struct PerInfo {
	char name[MAX_NAME]; // ����
	int age; // ����
	char gender[MAX_GEDNER]; // �Ա�
	char phoneNum[MAX_PHONENUM]; // �绰
	char addr[MAX_ADDRESS]; // ��ַ
}PerInfo;

/*
��̬�汾
�����Ϊָ�룬ָ��ָ��Ŀռ�Ϳ��Ը���
��Ҫ��ӱ�����ʾ��ǰ�ռ��С��ͨѶ¼���������������жϹ����������
Ĭ��Ϊ3
����ֵΪ2
*/
typedef struct DirectoryData {
	PerInfo* directory;
	int capacity;
	int count;
}DirectoryData;

/*
��̬�汾[����]
ͨѶ¼�ṹ��
��Ա��Ϣ�ṹ������ + count��¼����
*/
//typedef struct DirectoryData{
//	PerInfo directory[MAX]; // �����Ա��Ϣ
//	int count; // ��¼ʵ������
//}DirectoryData;


/*
��������
*/
void menu(void); // �˵�
void start(void); // ���
int initData(DirectoryData* data); // ��ʼ��ͨѶ¼
void add(DirectoryData* data); // ��Ӹ�����Ϣ
void show(const DirectoryData* data); // ��ӡ��ϵ��
void delPerInfo(DirectoryData* data); // ɾ��ָ����ϵ��
void searchByName(DirectoryData* data); // ����ָ��������ϵ��λ��
void modifyByName(DirectoryData* data); // �޸���Ա��Ϣ
void sortByName(DirectoryData* data); // �������ֵ��ַ�����������

void DestoryData(DirectoryData* data); // ����ͨѶ¼