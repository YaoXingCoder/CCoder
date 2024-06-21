#include "addressBooks.h"

/*
Date:2024.6.18
Title:通讯录源程序文件
Content:功能
1.添加
2.删除
3.查找
4.修改
5.全部显示
6.排序
*/

static int findByName(const DirectoryData* data); // 找到名字对应的下标
static int cmpPerByName(const void* e1, const void* e2); // 名字比较
static void checkCapaticy(DirectoryData* data); // 检查并扩容
static void loadDirectory(DirectoryData* data); // 读取文件
static void SaveData(const DirectoryData* data); // 存储联系人到文件

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
入口
*/
void start(void) {
	int input = 0;
	/* 初始化目录 */
	DirectoryData data;
	initData(&data); // 初始化
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
菜单
*/
void menu(void) {
	printf("**************************************************\n");
	printf("***   1.add  2.delPer  3.searchPer  4.modify   ***\n");
	printf("***   5.show  6.sort   0.exit                  ***\n");
	printf("**************************************************\n");
}


/*
扩容函数
*/
static void checkCapaticy(DirectoryData* data) {
	if (data->count == data->capacity) { // 当新添加的达到与空间一致则重新申请扩容
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
读入文件
*/
void loadDirectory(DirectoryData* data) {
	FILE* pFile = fopen("directory.txt", "rb");
	if (!pFile) {
		perror("load pFile");
		exit(1);
	}
	
	PerInfo temp = { 0 };
	
	// 每次循环录入1人
	while (fread(&temp, sizeof(PerInfo), 1, pFile)) {
		checkCapaticy(data);
		data->directory[data->count] = temp;
		data->count++;
		fflush(pFile);
	}
	if (feof(pFile)) puts("End of file reached successfully\n");

	// 关闭
	fclose(pFile);
	pFile = NULL;
}

/*
0.
动态初始化
先初始化，再进行加载
6.21 初始化时读入文件中人员信息
*/
int initData(DirectoryData* data) {
	assert(data);
	data->count = 0; // 初始化人数为0
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
动态
添加联系人
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
打印全部联系人
循环遍历
条件：data->count
*/
void show(const DirectoryData* data) {
	assert(data);
	printf("%-20s\t%-3s\t%-6s\t%-12s\t%-8s\n", "NAME", "AGE", "GENDER", "PHONE", "ADDR");
	/* 循环打印 */
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
删除指定联系人
1.查找
2.删除
判断到最后一个直接置空，
或者前count-1个中删除以后，后边整体前移
*/
void delPerInfo(DirectoryData* data) {

	/* 找到下标 */
	int i = findByName(data);
	if (-1 == i) {
		printf("There is so such person!\n");
		return;
	}

	/* 判断 */
	//if (data->count - 1 == i) {
	//	memset(data->directory[i].name, 0, sizeof(data->directory[0]));
	//	printf("Delete Successfully!\n");
	//	data->count--;
	//} else if (data->count - 1 > i){
	//	/* i后复制前移 */
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
查找只能名字人员，在联系人中的位置

返回值int，
>0 为数组值的下标
-1 未找到

static仅限本源文件可以使用
*/
static int findByName(const DirectoryData* data) {
	assert(data);
	if (0 == data->count) {
		printf("Data is full~~\n");
		return -1;
	}

	/* 记录名字 */
	char findName[MAX_NAME] = { 0 };
	printf("Enter the NAME:");
	scanf("%s", findName);	/* 遍历比较名字 */
	for (int i = 0; i < data->count; i++) {
		if (!strcmp(data->directory[i].name, findName)) {
			return i;
		}
	}

	return -1;
}

/*
3.
通过名字找到个人信息
*/
void searchByName(DirectoryData* data) {
	/* 找到下标 */
	int pos = findByName(data);
	if (-1 == pos) {
		printf("There is so such person!\n");
		return;
	}

	/* 输出 */
	printf("%-20s\t%-3s\t%-6s\t%-12s\t%-8s\n", "NAME", "AGE", "GENDER", "PHONE", "ADDR");
	printf("%-20s\t%-3d\t%-6s\t%-12s\t%-8s\n", data->directory[pos].name,
											   data->directory[pos].age,
											   data->directory[pos].gender,
											   data->directory[pos].phoneNum,
											   data->directory[pos].addr);
}

/*
4.
更改信息
重新输入信息
*/
void modifyByName(DirectoryData* data) {
	/* 找到下标 */
	int pos = findByName(data);
	if (-1 == pos) {
		printf("There is so such person!\n");
		return;
	}

	printf("Retrive\n");
	/* 重新录入 */
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
比较器，通过名字比较
*/
static int cmpPerByName(const void* e1, const void* e2) {
	return strcmp(((PerInfo*)e1)->name, ((PerInfo*)e2)->name);
}
/*
6.
根据名字排序 
*/
void sortByName(DirectoryData* data) {
	assert(data);
	qsort(data->directory, data->count, sizeof(PerInfo), cmpPerByName);
	printf("Sort Successfully!\n");
}

/*
退出销毁通讯录
*/
void DestoryData(DirectoryData* data) {
	assert(data);
	free(data->directory);
	data->directory = NULL;
	data = NULL;
}

/*
保存通讯录
*/
void SaveData(const DirectoryData* data) {
	assert(data);
	FILE* pFile = fopen("directory.txt", "wb");
	if (!pFile) {
		perror("SaveDate pFile");
		return;
	}

	// 循环写入文件，每次录入1人
	for (int i = 0; i < data->count; i++) {
		fwrite((data->directory + i), sizeof(PerInfo), 1, pFile);
	}
	if (ferror(pFile)) {
		perror("SaveData fwrite");
	} else if (feof(pFile)) {
		puts("End of file reached successfully");
	}

	//关闭
	fclose(pFile);
	pFile = NULL;
}



/*
前版本
*/

/*
静态初始化
初始化通讯录，置空
*/
//void initData(DirectoryData* data) {
//	assert(data);
//	data->count = 0; // 初始化人数为0
//	memset(data->directory, 0, sizeof(data->directory)); // 对已有空间置空
//}

/*
静态
添加联系人
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
//	while ('\n' != getchar())	; // 消除stdin
//	
//	data->count++;
//	printf("Add Successfully\n");
//}