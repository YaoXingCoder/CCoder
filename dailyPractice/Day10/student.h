#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_CAPACITY 5

typedef struct {
    int  id;
    char name[25];
    char gender;
    int  chinese;
    int  math;
    int  english;
} Student;

// �洢ѧ����Ϣ
void saveStu(Student* stu, const int num);

// ��ӡ����ѧ����Ϣ
void printAllStu(const Student* stu, const int num);

// ����ѧ����Ϣ
void sortByScore(const Student* stu, const int num);