#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <errno.h>

/*
Date:2024.6.20
Title:文件操作
Content:
1.文件的打开与关闭
2.顺序读写
*/

/*
1.文件打开关闭
*/
//int main(void) {
//	// 与文件建立连接
//	FILE* pFile = fopen("test.txt", "w");
//	if (NULL == pFile) {
//		printf("%s\n", strerror(errno));
//		return 1;
//	} else {
//		fputs("write successfully\n", pFile);
//		printf("Opened successfully");
//	}
//
//
//	// 关闭文件
//	fclose(pFile);
//	return 0;
//}

/*
2.
fgetc
fputc
*/
void sequentialReadWrite(void) {
	// 与文件建立连接
	//FILE* pFile = fopen("test.txt", "w");
	FILE* pFile = fopen("test.txt", "r");
	if (NULL == pFile) {
		printf("%s\n", strerror(errno));
		return;
	}

	// 写入 fputc();
	//fputs("write successfully\n", pFile);
	//for (int i = 'a'; i <= 'z'; i++) {
	//	fputc(i, pFile);
	//}
	//printf("Writed successfully\n");

	// 读出 fgetc();
	int ch;
	//for (int i = 0; i < 26; i++) {
	//	ch = fgetc(pFile);
	//	putchar(ch);
	//	putchar(32);
	//}
	//while (EOF != (ch = fgetc(pFile))) {
	//	putchar(ch);
	//	putchar(32);
	//}
	ch = fgetc(pFile);
	ch = fgetc(pFile);
	ch = fgetc(pFile);
	putchar(ch);
	putchar('\n');
	printf("Read successfully\n");

	// 关闭文件
	fclose(pFile);
	pFile = NULL;
}

/*
3.打印错误信息
*/
void uesPerror(void) {
	FILE* pFile = fopen("test2.txt", "r");
	if (NULL == pFile) {
		perror("pFile");
		return;
	}

	// 关闭
	fclose(pFile);
	pFile = NULL;
}


/*
4.
fputs
fgets
*/
void useTestInOut(void) {
	// 打开文件
	FILE* pFile = fopen("test.txt", "r");
	if (!pFile) {
		perror("fopen");
		return;
	}
	//// fputs, 写入到文件
	//fputs("fputs:hello,world!!", pFile);
	//printf("Write successfully\n");

	// fgets, 从文件读入
	char input[100];
	fgets(input, 100, pFile);
	printf("%s\n", input);
	//fgets(input, 100, pFile);
	//printf("%s\n", input);

	// 关闭
	fclose(pFile);
	pFile = NULL;
}

/*
5.
fscanf
fprintf
*/
typedef struct student {
	char name[20];
	int age;
	char gender[10];
}Student;

void useFormatInOut(void) {
	// 打开文件
	FILE* pFile = fopen("test.txt", "r");
	if (!pFile) {
		perror("fopen");
		return;
	}
	
	// 添加数据
	Student s1 = { "zhangsan", 15, "male"};
	Student s2 = { 0 };
	//// fprintf 写入
	//fprintf(pFile, "%s %d %s", s1.name, s1.age, s1.gender);
	//printf("write successfully\n");

	// fscanf 读入
	fscanf(pFile, "%s %d %s", s2.name, &(s2.age), s2.gender);
	printf("%s %d %s\n", s2.name, s2.age, s2.gender);

	// 关闭
	fclose(pFile);
	pFile = NULL;
}


/*
6.
fread
fwrite
*/
void useFileInOut(void) {
	Student s1 = { "zhangsan", 15, "male" };
	Student s2 = { 0 };

	// 打开文件
	FILE* pFile = fopen("test.txt", "rb");
	if (!pFile) {
		perror("pFile");
		return;
	}

	// 写入
	//fwrite(&s1, sizeof(Student), 1, pFile);
	//printf("write successfully\n");

	// 读出
	fread(&s2, sizeof(Student), 1, pFile);
	printf("%s %d %s\n", s2.name, s2.age, s2.gender);

	// 关闭
	fclose(pFile);
	pFile = NULL;
}

/*
主函数
*/
int main(void) {
	//sequentialReadWrite();
	//uesPerror();
	//useTestInOut();
	//useFormatInOut();
	//useFileInOut();
	return 0;
}

