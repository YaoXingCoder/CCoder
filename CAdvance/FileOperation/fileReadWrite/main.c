#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
/*
Date:2024.6.21
Title:文件读写
Content:
1.顺序读写
2.随机读写
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
	// 打开文件
	FILE* pFile = fopen("test.txt", "w");
	if (!pFile) {
		perror("pFile");
		return;
	}

	// 读/写
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


	// 关闭
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
	int c; // 注意：int，非char，要求处理EOF
	FILE* fp = fopen("test.txt", "r");
	if (!fp) {
		perror("File opening failed");
		return EXIT_FAILURE;
	}
  //fgetc 当读取失败的时候或者遇到文件结束的时候，都会返回EOF
	while ((c = fgetc(fp)) != EOF) // 标准C I/O读取文件循环
	{
		putchar(c);
	}
	putchar('\n');
	if (ferror(fp))
		puts("I/O error when reading");
	else if (feof(fp))
		puts("End of file reached successfully");

	// 关闭
	fclose(fp);
}

int main(void) {
	//useFseek();
	//useFtell();
	//useRwind();
	useFeof();
	return 0;
}
