#include "student.h"

/*
Date:2024.6.21
Title:��ѧ����������
Content:
�Ӽ���¼�� 5 ��ѧ������Ϣ��Ȼ���ѧ����������
����������£�
�Ȱ��ִܷӸߵ��ͽ�����������ܷ�һ�������ΰ����ġ���ѧ��Ӣ��ķ����Ӹߵ��ͽ�������
������Ƴɼ���һ���������ֵ��ֵ�˳���С��������
ѧ���ṹ�嶨�����£�
*/

int cmpStuScore(const void* p1, const void* p2) {
    Student* s1 = p1;
    Student* s2 = p2;
    int totalS1 = s1->chinese + s1->math + s1->english;
    int totalS2 = s2->chinese + s2->math + s2->english;
    
    if (totalS1 != totalS2) {
        return totalS1 - totalS2;
    }
    if (s1->chinese != s2->chinese) {
        return s1->chinese - s2->chinese;
    }
    if (s1->math != s2->math) {
        return s1->math - s2->math;
    }
    if (s1->english != s2->english) {
        return s1->english - s2->english;
    }
    return strcmp(s1->name, s2->name);
}

void sortByScore(const Student* stu, const int num) {
    qsort(stu, num, sizeof(Student), cmpStuScore);
}

void printAllStu(const Student* stu, const int num) {
    for (int i = 0; i < num; i++) {
        printf("%d %s %c %d %d %d\n", stu[i].id,
               stu[i].name,
               stu[i].gender,
               stu[i].chinese,
               stu[i].math,
               stu[i].english);
    }
    printf("end of output\n");
}

void saveStu(Student* stu, const int num) {
    printf("The student's information is id, name, gender, chinese, math, english\n");
    for (int i = 0; i < num; i++) {
        printf("enter student information for %d��", i + 1);
        scanf("%d %s %c %d %d %d", &(stu[i].id),
              stu[i].name,
              &stu[i].gender,
              &stu[i].chinese,
              &stu[i].math,
              &stu[i].english);
    }
    printf("Input Completion\n");
}