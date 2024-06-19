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
ͨѶ¼�ṹ��
��Ա��Ϣ�ṹ������ + count��¼����
*/
typedef struct DirectoryData{
	PerInfo directory[MAX]; // �����Ա��Ϣ
	int count; // ��¼ʵ������
}DirectoryData;

/*
��������
*/
void menu(void); // �˵�
void start(void); // ���
void initData(DirectoryData* data); // ��ʼ��ͨѶ¼
void add(DirectoryData* data); // ��Ӹ�����Ϣ
void show(const DirectoryData* data); // ��ӡ��ϵ��
void delPerInfo(DirectoryData* data); // ɾ��ָ����ϵ��
void searchByName(DirectoryData* data); // ����ָ��������ϵ��λ��
void modifyByName(DirectoryData* data); // �޸���Ա��Ϣ
void sortByName(DirectoryData* data); // �������ֵ��ַ�����������