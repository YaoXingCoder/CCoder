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
static void checkCapaticy(DirectoryData* data);

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
			case 1:
				add(&data);
				break;
			case 2:
				delPerInfo(&data);
				break;
			case 3:
				searchByName(&data);
				break;
			case 4:
				modifyByName(&data);
				break;
			case 5:
				show(&data);
				break;
			case 6:
				sortByName(&data);
				break;
			case 0:
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
��̬��ʼ��
*/
int initData(DirectoryData* data) {
	assert(data);
	data->count = 0; // ��ʼ������Ϊ0
	data->directory = (PerInfo*)calloc(DEFAULT_SZIE, sizeof(PerInfo));
	if (NULL == data->directory) {
		printf("initData::%s\n", strerror(errno));
		return 1;
	}
	data->capacity = DEFAULT_SZIE;
	return 0;
}

void DestoryData(DirectoryData* data) {
	assert(data);
	free(data->directory);
	data->directory = NULL;
	data = NULL;
}

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

	while ('\n' != getchar()); // ����stdin

	data->count++;
	printf("Add Successfully\n");
}


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

/*
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
�ҵ�
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
������������ 
*/
void sortByName(DirectoryData* data) {
	assert(data);
	qsort(data->directory, data->count, sizeof(PerInfo), cmpPerByName);
	printf("Sort Successfully!\n");
}

static int cmpPerByName(const void* e1, const void* e2) {
	return strcmp(((PerInfo*)e1)->name, ((PerInfo*)e2)->name);
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