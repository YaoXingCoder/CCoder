#include "vector.h"

/*
Date:2024.6.20
Title:每日练习Day09
Content:
1.有这样一种学生结构体类型，其数据成员有包括学号，姓名和3门课程的成绩。实现下列功能
2.设计一个动态数组，当数组空间不够时，它可以自动扩容
3.定义一个枚举类型Month，包含一年中的12个月份，并为每个月份分配一个从1开始的数字值。
*/
#define STU_NUM 5

typedef struct Stundent_s {
    int id;
    char name[25];
    int chinese;
    int math;
    int english;
}Student;

/*
记录学生信息
*/
void saveInfo(Student* stu, const int num) {
    printf("The student's information is id, name, chinese, math, english\n");
    for (int i = 0; i < num; i++) {
        printf("enter student information for %d：", i + 1);
        scanf("%d %s %d %d %d", &(stu[i].id), 
                                  stu[i].name, 
                                  &(stu[i].chinese), 
                                  &(stu[i].math), 
                                  &stu[i].english);
        
    }
    printf("Input Completion\n");
}

/*
打印单个学生信息
*/
void printOneStu(const Student* stu, const int index) {
    printf("%d %s %d %d %d\n", stu[index].id, stu[index].name, stu[index].chinese, stu[index].math, stu[index].english);
}

/*
打印所有学生信息
*/
void printAllStu(const Student* stu) {
    for (int i = 0; i < STU_NUM; i++) {
        printOneStu(stu, i);
    }
}

/*
打印总分最高的
*/
void printMaxScore(const Student* stu, const int num) {
    int maxStu = 0;
    int totalScore = stu[maxStu].chinese + stu[maxStu].math + stu[maxStu].english;
    for (int i = 1; i < num; i++) {
        int totalScore_next = stu[i].chinese + stu[i].math + stu[i].english;
        if (totalScore < totalScore_next) {
            totalScore = totalScore_next;
            maxStu = i;
        }
    }
    printOneStu(stu, maxStu);
}

/*
求单门成绩总分
*/
int totalSubject(const Student* stu, int num, const char* subj) {
    int sumSubject = 0;
    if (strcmp(subj, "chinese")) {
        for (int i = 0; i < num; i++) {
            sumSubject = stu[i].chinese;
            return sumSubject;
        }
    }
    if (strcmp(subj, "math")) {
        for (int i = 0; i < num; i++) {
            sumSubject = stu[i].math;
        }
        return sumSubject;
    }
    if (strcmp(subj, "math")) {
        for (int i = 0; i < num; i++) {
            sumSubject = stu[i].english;
        }
        return sumSubject;
    }
    printf("Subject Enter Error");
    return -1;
}

/*
每门课程的平均值
*/
void eachCourseAvg(const Student* stu) {
    int totalChinese = totalSubject(stu, STU_NUM, "chinese");
    int totalMath = totalSubject(stu, STU_NUM, "math");
    int totalEnglish = totalSubject(stu, STU_NUM, "english");
    printf("ChineseAvg is %d, MathAvg is %d, EnglishAvg is %d\n",
           totalChinese / STU_NUM, totalMath / STU_NUM, totalEnglish / STU_NUM);
}

/*
求一个学生总成绩
*/
int totalScore(const Student* stu, const int index) {
    return stu[index].chinese + stu[index].math + stu[index].english;
}

/*
排序根据总分
*/
void bubbleSortByScore(Student* stu, int num) {
    for (int i = 0; i < num - 1; i++) {
        for (int j = 0; j < num - 1 - i; j++) {
            if (totalScore(stu, j) > totalScore(stu, j +1)) {
                Student stemp = stu[j];
                stu[j] = stu[j + 1];
                stu[j + 1] = stemp;
            }
        }
    }
}

//int main(void) {
//    Student stu[STU_NUM];
//    saveInfo(stu, STU_NUM);
//    //printAllStu(stu, STU_NUM);
//    //printMaxScore(stu, STU_NUM);
//    bubbleSortByScore(stu, STU_NUM);
//    printAllStu(stu);
//	//return 0;
//}


//typedef enum month Month; // 仅声明未定义

extern unsigned int daysOfMonth(int year, Month month);

/*
设计一个动态数组，当数组空间不够时，它可以自动扩容。
*/
int main(void) {

    /* 动态数组 */
    //Vector* v = vectorCreate();
    //for (int i = 0; i < 10; i++) {
    //    push_front(v, i);
    //}
    //printf("%d",pop_back(v));
    //printf("%d",pop_front(v));
    //destoryVector(v);

    /* 返回该月份有多少天 */
    int year = 2024;
    enum month month = February;
    printf("Days in February: %d\n", daysOfMonth(year, month));
    return 0;
}