#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/*
Date:2024.6.17
Title:����Day6��ҵ
Content:
1.������
2.Լɪ��
3.��������������Ԫ�غ͵ڶ����Ԫ��
4.ָ����ϰ
*/

/*
1.������
1. ÿ��ֻ���ƶ�һ��Բ��;
2. ���̲��ܵ���С�����档

�ݹ飺
�������ִ�����n��͵�n-1��
1.ǰn-1����A->B
2.��n����A->C
3.ǰn-1����B->C

�ݹ����������
ʣ1����ֱ��A->C

������
char ABC������ABC��
int num���ƶ�����
*/

void hanluoTower(int num, char a, char b, char c) {
	if (1 == num) {
		printf("%c -> %c\n", a, c); // ʣ���һ��ֱ���ƶ�����
		return;
	}
	hanluoTower(num-1, a, c, b); // �Ƚ�ǰnum-1�����������ƶ���B����A����C�ƶ���B
	printf("%c -> %c\n", a, c); // �ٽ���num������ֱ���ƶ���C��A->C
	hanluoTower(num - 1, b, a, c); // ���ǰnum-1�����������ƶ���C����B����A�ƶ���C
}

/*
2.Լɪ��

Լɪ�򻷣�
n ����վ��һȦ��ÿ m ���˴���һ���ˡ�
������ n ���˵ı��Ϊ 1, 2, ..., n�����Ҵ� 1 ��ʼ��
�����ջ��������˱���Ƕ��٣�

˼·��
�ݹ�ʵ��
��һ���˶�ʣ���������źţ��ظ������Ĺ���ʼ����
��һ���������źţ�����
һ���ˣ���

n = 7, m = 3
0 1 2 3 4 5 6 // 3�Ż��ţ�����+1����4�Ż���
0 1 \ 3 4 5 6 // ɱ��
4 5 \ 0 1 2 4 // ���±��
4 5 \ 0 1 \ 4 // ɱ��x2
1 2 \ 3 4 \ 0 // ���±��
3 \ \ 3 4 \ 0 // ɱ��x3
3 \ \ 0 1 \ 2 // ���±��
3 \ \ 0 1 \ \ // ɱ��x4
0 \ \ 1 2 \ \ // ���
0 \ \ 1 \ \ \ // ɱ��x5
\ \ \ 1 \ \ \ // ��ţ�ɱ��x6

0 1 2 3 4 5 6 // 4�Ż��ߣ�����+1����5�Ż���
4 5 \ 0 1 2 4 // ���±��
���±�ź��ϴα������α�ŵĹ�ϵ
(4 + m) % n = 0
*/

int josephsR(int n, int m) {
	if (1 == n) return ((n + m) % n);
	return (josephsR(n - 1, m) + m) % n;
}

/*
3.����������ǰ�������Ԫ��

��������������Ԫ�غ͵ڶ����Ԫ�أ��������Ƿֱ������� largest �� second_largest ָ��ı����С�
void find_two_largest(int arr[], int n, int* largest, int* second_largest);
ע�⣺
Ϊ�˼򻯳������鲻�����ظ�Ԫ�ء�

˼·��
1.ð�������������飨�����ξͺã����������������������ֱ𸶸�largest��second_largest
2.ִ��һ��ѭ������������largest����ִ�еڶ���ѭ��������һ��<largest

���뺯����largest �� second_largest��ʼ��Ϊ0
ð������(����/����)
����0 != largest && 0 != second_largestֱ��������������
*/
void find_two_largest(int arr[], int n, int* largest, int* second_largest) {
	*largest = 0;
	*second_largest = 0;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < n - 1 - i; j++) {
			if (arr[j] > arr[j+1]) {
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
		if (0 == i) *largest = arr[n - 1];
		if (1 == i) *second_largest = arr[n - 2];
		if (0 != *largest && 0 != *second_largest) return;
	}
}

/*
��д������

void split_time(long total_sec, int* hour, int* minute, int* second);
total_sec ��ʾ����ҹ12:00:00��ʼ�����������
�뽫 total_sec ת����ʱ(0-23)����(0-59)����(0-59)��ʾ��ʱ�䣬
����ŵ������ⲿ��ָ�� hour, minute, second ָ��ı����С�
�����ⲿ����ӡ����ǰ��ʱ��

˼·��
hour = total_sec / 3600 = �Ѿ���ȥ��Сʱ��
total_sec % 3600 = ʣ�µķ����� + ʣ�µ�����
min = total_sec % 3600 / 60 = �Ѿ���ȥ�ķ�����
sec = total_sec % 3600 % 60 % 60 = ��ȥ������

*/
void split_time(long total_sec, int* hour, int* minute, int* second) {
	*hour = total_sec / 3600 % 24;
	*minute = total_sec % 3600 / 60;
	*second = total_sec % 3600 % 60 % 60;
	return;
}


int main(void) {
	// 1.������
	//hanluoTower(3, 'A', 'B', 'C');

	// 2.Լɪ��
	//int survivor = josephsR(3, 3) + 1;
	//printf("%d���ˣ�ÿ%dɱһ���������Ϊ%d�Ļ���\n", 7, 3, survivor);

	// 3.��������������Ԫ�غ͵ڶ����Ԫ��
	//int arr[] = { 23,12,4,6,3,5,62,3,4 };
	//int sz = sizeof(arr) / sizeof(arr[0]);
	//int largetest = 0, second_largest = 0;
	//find_two_largest(arr, sz, &largetest, &second_largest);
	//printf("largetest = %d, second_largest = %d\n", largetest, second_largest);

	// 4.ָ����ϰ
	int hour = 0;
	int minute = 0;
	int second = 0;
	long total_sec = 86400;
	split_time(total_sec, &hour, &minute, &second);
	printf("%d:%d:%d\n", hour, minute, second);
	return 0;
}
