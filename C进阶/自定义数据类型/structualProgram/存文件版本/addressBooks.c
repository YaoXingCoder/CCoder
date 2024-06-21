#include "addressBooks.h"

/*
Date:2024.6.18
Title:ͨѶ¼Դ�����ļ�
Content:����
1.���
2.ɾ��
3.����
4.�޸�
5.ȫ����ʾ
6.����
*/

static int findByName(const DirectoryData* data); // �ҵ����ֶ�Ӧ���±�
static int cmpPerByName(const void* e1, const void* e2); // ���ֱȽ�
static void checkCapaticy(DirectoryData* data); // ��鲢����
static void loadDirectory(DirectoryData* data); // ��ȡ�ļ�
static void SaveData(const DirectoryData* data); // �洢��ϵ�˵��ļ�

enum options {
	EXIT = 0,
	ADD,
	DELPER,
	SEARCHPER,
	MODIFY,
	SHOW,
	SORT
};

/*
���
*/
void start(void) {
	int input = 0;
	/* ��ʼ��Ŀ¼ */
	DirectoryData data;
	initData(&data); // ��ʼ��
	do {
		menu();
		printf("Enter your option:>");
		scanf("%d", &input);
		switch (input) {
			case ADD:
				add(&data);
				break;
			case DELPER:
				delPerInfo(&data);
				break;
			case SEARCHPER:
				searchByName(&data);
				break;
			case MODIFY:
				modifyByName(&data);
				break;
			case SHOW:
				show(&data);
				break;
			case SORT:
				sortByName(&data);
				break;
			case EXIT:
				SaveData(&data);
				DestoryData(&data);
				input = 0;
				break;
			default:
				printf("Enter Error! Please again....\n");
				break;
		}
	} while (input);

	printf("Exit the System\n");
}

/*
�˵�
*/
void menu(void) {
	printf("**************************************************\n");
	printf("***   1.add  2.delPer  3.searchPer  4.modify   ***\n");
	printf("***   5.show  6.sort   0.exit                  ***\n");
	printf("**************************************************\n");
}


/*
���ݺ���
*/
static void checkCapaticy(DirectoryData* data) {
	if (data->count == data->capacity) { // ������ӵĴﵽ��ռ�һ����������������
		PerInfo* ptr = (PerInfo*)realloc(data->directory, sizeof(PerInfo) * (data->capacity + INCREMENTAL_INTERVAL));
		if (NULL == ptr) {
			printf("add::%s\n", strerror(errno));
			return;
		} else {
			data->directory = ptr;
			data->capacity += INCREMENTAL_INTERVAL;
			printf("Successful expansion\n");
		}
	}
}

/*
�����ļ�
*/
void loadDirectory(DirectoryData* data) {
	FILE* pFile = fopen("directory.txt", "rb");
	if (!pFile) {
		perror("load pFile");
		exit(1);
	}
	
	PerInfo temp = { 0 };
	
	// ÿ��ѭ��¼��1��
	while (fread(&temp, sizeof(PerInfo), 1, pFile)) {
		checkCapaticy(data);
		data->directory[data->count] = temp;
		data->count++;
		fflush(pFile);
	}
	if (feof(pFile)) puts("End of file reached successfully\n");

	// �ر�
	fclose(pFile);
	pFile = NULL;
}

/*
0.
��̬��ʼ��
�ȳ�ʼ�����ٽ��м���
6.21 ��ʼ��ʱ�����ļ�����Ա��Ϣ
*/
int initData(DirectoryData* data) {
	assert(data);
	data->count = 0; // ��ʼ������Ϊ0
	data->directory = (PerInfo*)calloc(DEFAULT_SZIE, sizeof(PerInfo));
	if (NULL == data->directory) {
		perror("initData");
		return 1;
	}
	data->capacity = DEFAULT_SZIE;

	loadDirectory(data);

	return 0;
}

/*
1.
��̬
�����ϵ��
*/
void add(DirectoryData* data) {
	assert(data);
	checkCapaticy(data);
	
	PerInfo* p = &(data->directory[data->count]);
	printf("Enter your Name:");
	scanf("%s", &(p->name));
	printf("Enter your Age:");
	scanf("%d", &(p->age));
	printf("Enter your Gender:");
	scanf("%s", &(p->gender));
	printf("Enter your PhoneNum:");
	scanf("%s", &(p->phoneNum));
	printf("Enter your Address:");
	scanf("%s", &(p->addr));

	data->count++;
	printf("Add Successfully\n");
}

/*
5.
��ӡȫ����ϵ��
ѭ������
������data->count
*/
void show(const DirectoryData* data) {
	assert(data);
	printf("%-20s\t%-3s\t%-6s\t%-12s\t%-8s\n", "NAME", "AGE", "GENDER", "PHONE", "ADDR");
	/* ѭ����ӡ */
	for (int i = 0; i < data->count; i++) {
		printf("%-20s\t%-3d\t%-6s\t%-12s\t%-8s\n", data->directory[i].name, 
													data->directory[i].age, 
													data->directory[i].gender, 
													data->directory[i].phoneNum, 
													data->directory[i].addr);
	}
}

/*
2.
ɾ��ָ����ϵ��
1.����
2.ɾ��
�жϵ����һ��ֱ���ÿգ�
����ǰcount-1����ɾ���Ժ󣬺������ǰ��
*/
void delPerInfo(DirectoryData* data) {

	/* �ҵ��±� */
	int i = findByName(data);
	if (-1 == i) {
		printf("There is so such person!\n");
		return;
	}

	/* �ж� */
	//if (data->count - 1 == i) {
	//	memset(data->directory[i].name, 0, sizeof(data->directory[0]));
	//	printf("Delete Successfully!\n");
	//	data->count--;
	//} else if (data->count - 1 > i){
	//	/* i����ǰ�� */
	//	for (int j = i; j < data->count - 1; j++) {
	//		memcpy(data->directory[j].name, data->directory[j + 1].name, sizeof(data->directory[0]));
	//	}
	//	data->count--;
	//	printf("Delete Successfully!\n");
	//}

	for (int j = i; j < data->count - 1; j++) {
		data->directory[j] = data->directory[j + 1];
	}
	data->count--;
	printf("Delete Successfully!\n");
}

/*
����ֻ��������Ա������ϵ���е�λ��

����ֵint��
>0 Ϊ����ֵ���±�
-1 δ�ҵ�

static���ޱ�Դ�ļ�����ʹ��
*/
static int findByName(const DirectoryData* data) {
	assert(data);
	if (0 == data->count) {
		printf("Data is full~~\n");
		return -1;
	}

	/* ��¼���� */
	char findName[MAX_NAME] = { 0 };
	printf("Enter the NAME:");
	scanf("%s", findName);	/* �����Ƚ����� */
	for (int i = 0; i < data->count; i++) {
		if (!strcmp(data->directory[i].name, findName)) {
			return i;
		}
	}

	return -1;
}

/*
3.
ͨ�������ҵ�������Ϣ
*/
void searchByName(DirectoryData* data) {
	/* �ҵ��±� */
	int pos = findByName(data);
	if (-1 == pos) {
		printf("There is so such person!\n");
		return;
	}

	/* ��� */
	printf("%-20s\t%-3s\t%-6s\t%-12s\t%-8s\n", "NAME", "AGE", "GENDER", "PHONE", "ADDR");
	printf("%-20s\t%-3d\t%-6s\t%-12s\t%-8s\n", data->directory[pos].name,
											   data->directory[pos].age,
											   data->directory[pos].gender,
											   data->directory[pos].phoneNum,
											   data->directory[pos].addr);
}

/*
4.
������Ϣ
����������Ϣ
*/
void modifyByName(DirectoryData* data) {
	/* �ҵ��±� */
	int pos = findByName(data);
	if (-1 == pos) {
		printf("There is so such person!\n");
		return;
	}

	printf("Retrive\n");
	/* ����¼�� */
	PerInfo* p = &(data->directory[pos]);
	printf("Enter new Name:");
	scanf("%s", &(p->name));
	printf("Enter new Age:");
	scanf("%d", &(p->age));
	printf("Enter new Gender:");
	scanf("%s", &(p->gender));
	printf("Enter new PhoneNum:");
	scanf("%s", &(p->phoneNum));
	printf("Enter new Address:");
	scanf("%s", &(p->addr));
	
	printf("Modify Seccuessfully\n");
}

/*
�Ƚ�����ͨ�����ֱȽ�
*/
static int cmpPerByName(const void* e1, const void* e2) {
	return strcmp(((PerInfo*)e1)->name, ((PerInfo*)e2)->name);
}
/*
6.
������������ 
*/
void sortByName(DirectoryData* data) {
	assert(data);
	qsort(data->directory, data->count, sizeof(PerInfo), cmpPerByName);
	printf("Sort Successfully!\n");
}

/*
�˳�����ͨѶ¼
*/
void DestoryData(DirectoryData* data) {
	assert(data);
	free(data->directory);
	data->directory = NULL;
	data = NULL;
}

/*
����ͨѶ¼
*/
void SaveData(const DirectoryData* data) {
	assert(data);
	FILE* pFile = fopen("directory.txt", "wb");
	if (!pFile) {
		perror("SaveDate pFile");
		return;
	}

	// ѭ��д���ļ���ÿ��¼��1��
	for (int i = 0; i < data->count; i++) {
		fwrite((data->directory + i), sizeof(PerInfo), 1, pFile);
	}
	if (ferror(pFile)) {
		perror("SaveData fwrite");
	} else if (feof(pFile)) {
		puts("End of file reached successfully");
	}

	//�ر�
	fclose(pFile);
	pFile = NULL;
}



/*
ǰ�汾
*/

/*
��̬��ʼ��
��ʼ��ͨѶ¼���ÿ�
*/
//void initData(DirectoryData* data) {
//	assert(data);
//	data->count = 0; // ��ʼ������Ϊ0
//	memset(data->directory, 0, sizeof(data->directory)); // �����пռ��ÿ�
//}

/*
��̬
�����ϵ��
*/
//void add(DirectoryData* data) {
//	assert(data);
//	if (data->count > MAX) {
//		printf("DirectoryData is full.\n");
//		return;
//	}
//	PerInfo* p = &(data->directory[data->count]);
//	printf("Enter your Name:");
//	scanf("%s", &(p->name));
//	printf("Enter your Age:");
//	scanf("%d", &(p->age));
//	printf("Enter your Gender:");
//	scanf("%s", &(p->gender));
//	printf("Enter your PhoneNum:");
//	scanf("%s", &(p->phoneNum));
//	printf("Enter your Address:");
//	scanf("%s", &(p->addr));
//
//	while ('\n' != getchar())	; // ����stdin
//	
//	data->count++;
//	printf("Add Successfully\n");
//}