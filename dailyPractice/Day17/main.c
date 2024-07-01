/*********************************
Date:2024.6.30
Title:每日练习
Author:JiaZiChunQiu
Content:

**********************************/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>


/*
* 请实现下面功能
将一个文件读入程序，将其中的大小写字母右旋13个位置后，写入另一个文件。
[A-Ma-m] 转换成 [N-Zn-z]
[N-Zn-z] 转换成 [A-Ma-m]
其余字符不变
int main(int argc, char* argv[]) {
}
*/

//void reverseStr(char* left, char* right) {
//	char tmp;
//	while (left < right) {
//		tmp = *left;
//		*left = *right;
//		*right = tmp;
//		left++;
//		right--;
//	}
//}
//
//void rightRotation(char str[], int k) {
//	int len = strlen(str);
//
//	k %= len;
//
//	reverseStr(str, str + k - 1); // 左边
//	reverseStr(str + k, str + len - 1); // 右边
//	reverseStr(str, str + len - 1); // 整体
//}
//
//int main(int argc, char* argv[]) {
//	FILE* src = fopen("test.txt", "r");
//	if (!src) {
//		fprintf(stderr, "src is error\n");
//		return 1;
//	}
//
//	FILE* dest = fopen("test1.txt", "w");
//	if (!dest) {
//		fprintf(stderr, "dest is error\n");
//		fclose(src);
//		return 1;
//	}
//
//	// 读取旋转并存入
//	char* tmp[27] = { 0 };
//
//	fgets(tmp, 27, src);
//	rightRotation(tmp, 13);
//	fputs(tmp, dest);
//
//	// 关闭
//	fclose(dest);
//	fclose(src);
//
//	return 0;
//}


/*
* 请实现下面功能

将一个文件读入程序，在每一行前面添加序号，然后写入另一个文件。如：

Allen
Beyonce
Cindy
Dianna
变成

1. Allen
2. Beyonce
3. Cindy
4. Dianna
int main(int argc, char* argv[]) {

}
*/

int main(int argc, char* argv[]) {
	FILE* src = fopen("tmp.txt", "r");
	if (!src) {
		fprintf(stderr, "src is error\n");
		return 1;
	}

	FILE* dest = fopen("tmp1.txt", "w");
	if (!dest) {
		fprintf(stderr, "dest is error\n");
		fclose(src);
		return 1;
	}

	char tmp[128];
	char line = 0;
	while (fgets(tmp, sizeof(tmp), src)) {
		line++;
		fprintf(dest, "%d.%s", line, tmp);
	}

	// 关闭
	fclose(dest);
	fclose(src);

	return 0;
}


//typedef struct Student {
//	int id;
//	char name[20];
//	char gender[10]; 
//	double chinese;
//	double math;
//	double english;
//}Stu;
//
//int main(int argc, char* argv[]) {
//	FILE* src = fopen("old-students.dat", "rb");
//	if (!src) {
//		printf("src is error\n");
//		return 1;
//	}
//
//	FILE* dest = fopen("students.dat", "rb");
//	if (!dest) {
//		printf("dest is error\n");
//		fclose(src);
//		return 1;
//	}
//
//	/*Stu s;
//	while (fscanf(src, "%d %s %s %lf %lf %lf", &s.id, s.name, s.gender, &s.chinese, &s.math, &s.english) > 0) {
//		fprintf(dest, "%d %s %s %.2lf %.2lf %.2lf\n", s.id, s.name, s.gender, s.chinese * 0.85, s.math * 0.9, s.english * 0.8);
//	}*/
//
//	Stu s1 = { 1, "Allen", "f", 100, 100, 100 };
//	Stu s2 = { 2, "Beyounce", "f", 90, 90, 90 };
//	Stu s3 = { 3, "Cindy", "f", 95, 95, 95 };
//	Stu s4 = { 4, "Dianna", "f", 98, 98, 98 };
//	Stu s[4] = { s1, s2, s3, s4 };
//
//	/*for (int i = 0; i < 4; i++) {
//		fwrite(&s[i], sizeof(Stu), 1, src);
//	}*/
//
//	//Stu tmp;
//	/*while (fread(&tmp, sizeof(Stu), 1, src) > 0) {
//		fwrite(&tmp, sizeof(Stu), 1, dest);
//	}*/
//		
//	/*while (fread(&tmp, sizeof(Stu), 1, dest)) {
//		fprintf(stdout, "%d %s %s %f %f %f\n", tmp.id, tmp.name, tmp.gender, tmp.chinese, tmp.math, tmp.english);
//	}*/
//
//	// 关闭
//	fclose(dest);
//	fclose(src);
//
//	return 0;
//}