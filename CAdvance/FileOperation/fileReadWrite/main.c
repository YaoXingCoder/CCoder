#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
/*
Date:2024.6.21
Title:�ļ���д
Content:
1.˳���д
2.�����д
*/

typedef struct Student {
	int id;
	char name[20];
	char gender[10];
}Student;

/*
1.
fseek()
*/
void useFseek(void) {
	Student s1 = { 1, "zhangsan", "male" };
	// ���ļ�
	FILE* pFile = fopen("test.txt", "w");
	if (!pFile) {
		perror("pFile");
		return;
	}

	// ��/д
	//int writeNum = fprintf(pFile, "%d %s %s", s1.id, s1.name, s1.gender);
	//if (fprintf == 0) {
	//	printf("Enter error\n");
	//} else {
	//	printf("write successfully\n");
	//}

	fputs("This is an apple.", pFile);
	fseek(pFile, 9, SEEK_SET);
	fputs(" sam", pFile);
	if (!ferror) {
		perror("pFile");
	} else if (!feof) {
		printf("The file was not written successfully\n");
	}


	// �ر�
	fclose(pFile);
	pFile = NULL;
}

void useFtell(void) {
	FILE* pFile = fopen("test.txt", "r");
	if (!pFile) {
		perror("pFile");
		return;
	}

	long size = 0l;
	fseek(pFile, 0, SEEK_SET);
	size = ftell(pFile);
	printf("Size of myfile.txt: %ld bytes.\n", size);

	fclose(pFile);
	pFile = NULL;
}

void useRwind(void) {
	FILE* pFile = fopen("test.txt", "r");
	if (!pFile) {
		perror("pFile");
		return;
	}

	fseek(pFile, 9, SEEK_SET);
	char arr[30];

	fgets(arr, 30, pFile);
	printf("%s\n", arr);
	long size = ftell(pFile);
	printf("Size of myfile.txt: %ld bytes.\n", size);

	rewind(pFile);
	size = ftell(pFile);
	printf("Size of myfile.txt: %ld bytes.\n", size);
	fgets(arr, 30, pFile);
	printf("%s\n", arr);

	size = ftell(pFile);
	printf("Size of myfile.txt: %ld bytes.\n", size);
	

	fclose(pFile);
	pFile = NULL;
}

void useFeof(void) {
	int c; // ע�⣺int����char��Ҫ����EOF
	FILE* fp = fopen("test.txt", "r");
	if (!fp) {
		perror("File opening failed");
		return EXIT_FAILURE;
	}
  //fgetc ����ȡʧ�ܵ�ʱ����������ļ�������ʱ�򣬶��᷵��EOF
	while ((c = fgetc(fp)) != EOF) // ��׼C I/O��ȡ�ļ�ѭ��
	{
		putchar(c);
	}
	putchar('\n');
	if (ferror(fp))
		puts("I/O error when reading");
	else if (feof(fp))
		puts("End of file reached successfully");

	// �ر�
	fclose(fp);
}

int main(void) {
	//useFseek();
	//useFtell();
	//useRwind();
	useFeof();
	return 0;
}
