#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <errno.h>

/*
Date:2024.6.20
Title:�ļ�����
Content:
1.�ļ��Ĵ���ر�
2.˳���д
*/

/*
1.�ļ��򿪹ر�
*/
//int main(void) {
//	// ���ļ���������
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
//	// �ر��ļ�
//	fclose(pFile);
//	return 0;
//}

/*
2.
fgetc
fputc
*/
void sequentialReadWrite(void) {
	// ���ļ���������
	//FILE* pFile = fopen("test.txt", "w");
	FILE* pFile = fopen("test.txt", "r");
	if (NULL == pFile) {
		printf("%s\n", strerror(errno));
		return;
	}

	// д�� fputc();
	//fputs("write successfully\n", pFile);
	//for (int i = 'a'; i <= 'z'; i++) {
	//	fputc(i, pFile);
	//}
	//printf("Writed successfully\n");

	// ���� fgetc();
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

	// �ر��ļ�
	fclose(pFile);
	pFile = NULL;
}

/*
3.��ӡ������Ϣ
*/
void uesPerror(void) {
	FILE* pFile = fopen("test2.txt", "r");
	if (NULL == pFile) {
		perror("pFile");
		return;
	}

	// �ر�
	fclose(pFile);
	pFile = NULL;
}


/*
4.
fputs
fgets
*/
void useTestInOut(void) {
	// ���ļ�
	FILE* pFile = fopen("test.txt", "r");
	if (!pFile) {
		perror("fopen");
		return;
	}
	//// fputs, д�뵽�ļ�
	//fputs("fputs:hello,world!!", pFile);
	//printf("Write successfully\n");

	// fgets, ���ļ�����
	char input[100];
	fgets(input, 100, pFile);
	printf("%s\n", input);
	//fgets(input, 100, pFile);
	//printf("%s\n", input);

	// �ر�
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
	// ���ļ�
	FILE* pFile = fopen("test.txt", "r");
	if (!pFile) {
		perror("fopen");
		return;
	}
	
	// �������
	Student s1 = { "zhangsan", 15, "male"};
	Student s2 = { 0 };
	//// fprintf д��
	//fprintf(pFile, "%s %d %s", s1.name, s1.age, s1.gender);
	//printf("write successfully\n");

	// fscanf ����
	fscanf(pFile, "%s %d %s", s2.name, &(s2.age), s2.gender);
	printf("%s %d %s\n", s2.name, s2.age, s2.gender);

	// �ر�
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

	// ���ļ�
	FILE* pFile = fopen("test.txt", "rb");
	if (!pFile) {
		perror("pFile");
		return;
	}

	// д��
	//fwrite(&s1, sizeof(Student), 1, pFile);
	//printf("write successfully\n");

	// ����
	fread(&s2, sizeof(Student), 1, pFile);
	printf("%s %d %s\n", s2.name, s2.age, s2.gender);

	// �ر�
	fclose(pFile);
	pFile = NULL;
}

/*
������
*/
int main(void) {
	//sequentialReadWrite();
	//uesPerror();
	//useTestInOut();
	//useFormatInOut();
	//useFileInOut();
	return 0;
}

