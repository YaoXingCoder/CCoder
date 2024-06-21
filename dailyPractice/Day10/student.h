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

// 存储学生信息
void saveStu(Student* stu, const int num);

// 打印所有学生信息
void printAllStu(const Student* stu, const int num);

// 排序学生信息
void sortByScore(const Student* stu, const int num);