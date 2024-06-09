#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<math.h>

void judgeTriangle(const int a, const int b, const int c); // �ж�������
int aSum(int a, int n); // ��ǰn���
int daffodils(int num); // ˮ�ɻ���
double myPow(int n, int k); // ��η�
void diamond1(int row); // ����
void hollowDiamond1(int row); // ��������
void hollowDiamond2(int row); // ��������2
void hollowDiamond3(int row); // ��������3
int drinkSoda(int money); // ��ˮ����

int main(void) {
	//judgeTriangle(3, 4, 5);
	//printf("%d��ǰ%d֮��Ϊ%d\n", 2, 5, aSum(2, 5));
	/*for (int i = 0; i < 100000; i++) {
		if (daffodils(i))
			printf("%d\t", i);
	}*/
	//diamond1(6);
	//hollowDiamond1(6);
	//hollowDiamond2(4);
	//hollowDiamond3(4);
	//printf("�ܹ����ܺ�ˮ%dƿ\n", drinkSoda(20));
	return 0;
}
/*
�ж������ε�����
*/
void judgeTriangle(const int a, const int b, const int c) {
	if (a<=0 || b<=0 ||c<=0) {
		printf("���������������");
		return;
	}
	if (a + b > c || a + c > b || c + b > a) {
		if (a ==b || b == c || a == c) {
			if (a == b && b == c) {
				printf("��������Ϊ�ȱ�������\n");
				return;
			}
			printf("��������Ϊ����������\n");
			return;
		}
		if (a * a + b * b == c * c || a * a + c * c == b * b || b * b + c * c == a * a) {
			printf("��������Ϊֱ��������\n");
			return;
		}
		printf("�����������������\n");
	} else {
		printf("�����߲������������\n");
	}
}


/*
�� Sn = a + aa + aaa + aaaa + aaaaa; ��ǰ����֮�ͣ�aΪ����
*/
int aSum(int a, int n) {
	if (a > 10 || a < 1)
		return -1;
	if (n < 1)
		return -1;
	int sum = 0;
	int key = 0;
	for (int i = 0; i < n; i++) {
		key = key * 10 + a;
		sum += key;
	}
	return sum;
}

/*
ˮ�ɻ���
һ��nλ�������λ���ֵ�n�η�֮��ǡ�õ��ڸ�������
���磺153 = 1^3 + 5^3 + 3^3;
*/
int daffodils(int num) {
	// ������������м�λ
	int temp = num;
	int n = 1; // Ĭ����1λ��
	while(temp /10){
		n++;
		temp /= 10;
	}
	// ���λ�Ĵη���
	temp = num;
	int sum = 0;
	for (int i = 0; i < n; i++) {
		sum += (int)myPow(temp % 10, n); // ����ȡ��õ�������n�η�
		temp /= 10;
	}
	if (sum == num) return 1;
	else return 0;
}

double myPow(int n, int k) {
	if (k > 0)
		return n * myPow(n, k - 1);
	else if (0 == k)
		return 1;
	else return 1.0 / myPow(n, -k);
}

/*
��ӡ����
��1�֣�ѭ��
____*
___***
__*****
_*******
*********
_*******
__*****
___***
____*
rowָ�ϰ벿���ж�����
*/
void diamond1(int row) {
	/*
	�ϰ벿�֣�row ��
	��ӡ�ո�row - �к�
	��ӡ*��2 * �к� - 1
	*/
	for (int i = 1; i <= row; i++) {
		for (int j = 1; j <= row - i; j++)
			printf(" ");
		for (int k = 1; k <= (2 * i - 1); k++)
			printf("*");
		printf("\n");
	}
	/*
	�°벿�֣�row - 1 ��
	��ӡ�ո�row - �к�
	��ӡ*��2 * (row - �к�) - 1
	*/
	for (int i = 1; i <= row - 1; i++) {
		for (int j = 1; j <= i; j++)
			printf(" ");
		for (int k = 1; k <= (2 * (row - i) - 1); k++)
			printf("*");
		printf("\n");
	}
}

/*
��������
*/
void hollowDiamond1(int row) {
		/*
	�ϰ벿�֣�row ��
	��ӡ�ո�row - �к�
	��ӡ*����1�� �� ��2 * �к� - 1��
	*/
	for (int i = 1; i <= row; i++) {
		for (int j = 1; j <= row - i; j++)
			printf(" ");
		for (int k = 1; k <= (2 * i - 1); k++) {
			if (1 == k || (2 * i - 1) == k)
				printf("*");
			else
				printf(" ");
			
		}
		printf("\n");
	}
	/*
	�°벿�֣�row - 1 ��
	��ӡ�ո�row - �к�
	��ӡ*��2 * (row - �к�) - 1
	*/
	for (int i = 1; i <= row - 1; i++) {
		for (int j = 1; j <= i; j++)
			printf(" ");
		for (int k = 1; k <= (2 * (row - i) - 1); k++) {
			if (1 == k || (2 * (row - i) - 1) == k)
				printf("*");
			else
				printf(" ");
		}
		printf("\n");
	}
}

/*
��������2 * row + 1 �У��� -row ��ʼ���� row ����
��ӡ�ո�abs(i)
��ӡ*��row * 2 - (2 * abs(i) - 1)
*/
void hollowDiamond2(int row) {
	int stars = 2 * row;
	for (int i = -row; i <= row; i++) {
		for (int j = 1; j <= abs(i); j++)
			printf(" ");
		for (int k = 1; k <= stars - (2 * abs(i) - 1); k++) {
			if (1 == k || stars - (2 * abs(i) - 1) == k)
				printf("*");
			else
				printf(" ");
		}
		printf("\n");
	}
}

/*
	   ^y
	   |
	   |
	   |
---------------->
	   |		x
	   |
	   | 
��ӡ*��|x| + |y| = row
*/
void hollowDiamond3(int row) {
	for (int i = -row; i <= row; i++) {
		for (int j = -row; j <= row; j++) {
			if ((i>0?i:-i) + (j>0?j:-j) == row)
			//if (abs(i) + abs(j) == row)
				printf("*");
			else
				printf(" ");
		}
		printf("\n");
	}
}

/*
����ˮ���⣺
1ƿ��ˮ1R��2����ƿ���Ի�1ƿ��ˮ����20R�����Ժȶ�����ˮ
20R��39ƿ
*/
int drinkSoda(int money) {
	int total = money; // Ĭ�ϵ�һ�κȵ�Ϊ����money���
	int empty = money;
	while (empty >= 2) {
		total += empty / 2; // ��ƿ�û���+ԭ�ȵ� = ���ںȵ�
		empty = empty / 2 + empty % 2; // ��ƿ/2 + �ϴο������е� = ���ʣ��Ŀ�ƿ
	}
	return total;
}