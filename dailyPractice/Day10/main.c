#include "linkedList.h"
#include "student.h"

/*
Date:2024.6.21
Title:ÿ����ϰDay10
Content:

*/


int main(void) {
	//Node* head = NULL;
	//Node* tail = NULL;
	//
	//// ͷ�巨
	//add_before_head(&head, &tail, 4);
	//add_before_head(&head, &tail, 3);
	////add_before_head(&head, &tail, 2);
	//add_before_head(&head, &tail, 1); // 1 --> 2 --> 3 --> 4

	//// β�巨
	////add_behind_tail(&head, &tail, 5);
	//add_behind_tail(&head, &tail, 6);
	////add_behind_tail(&head, &tail, 7);
	//add_behind_tail(&head, &tail, 8);  // 5 --> 6 --> 7 --> 8

	//// ˳�����
	//add_in_sort(&head, &tail, 9);
	//add_in_sort(&head, &tail, 5);
	//add_in_sort(&head, &tail, 2);
	//add_in_sort(&head, &tail, 7);  // 2 --> 5 --> 9 --> 7

	// ����ѧ��
	Student stu[DEFAULT_CAPACITY];
	saveStu(stu, DEFAULT_CAPACITY);
	sortByScore(stu, DEFAULT_CAPACITY);
	printAllStu(stu, DEFAULT_CAPACITY);
	return 0;
}
