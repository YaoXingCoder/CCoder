#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/*
Date:2024.06.12
Title:����Day02��ҵ
Content:
1.дһ������ʵ�ַ�����ӡ��û��Է��� / ��ĸ����ʽ��������������ӡ��Ӻ�Ľ��(��Ϊ������)
2.������ŷ������㷨�����Լ�������з�����
*/

/*
дһ������ʵ�ַ�����ӡ��û��Է��� / ��ĸ����ʽ��������������ӡ��Ӻ�Ľ��(��Ϊ������)���磺

���� :
Enter first fraction : 5 / 6
Enter second fraction : 3 / 4
�����
The sum is 19 / 12

��ע������ŷ������㷨�����Լ�������з����򻯣�

*/
int main(void) {
	int numerator1 = 0, denominator1 = 0;
	int numerator2 = 0, denominator2 = 0;
	printf("Enter first fraction��");
	scanf("%d / %d", &numerator1, &denominator1);
	printf("Enter second fraction��");
	scanf("%d / %d", &numerator2, &denominator2);
	int retNum = numerator1 * denominator2 + numerator2 * denominator1;
	int	retDen = denominator1 * denominator2;
	// ȷ���� С����������ȷ�� ������ �� ����
	int data1 = (retNum > retDen ? retNum : retDen);
	int data2 = (retNum < retDen ? retNum : retDen);
	int divisor = data1 % data2;
	while (divisor) {
		data1 = data2;
		data2 = divisor;
		divisor = data1 % data2;
	}
	// ����data2�������Լ��
	retNum /= data2;
	retDen /= data2;
	printf("The sum is %d / %d", retNum, retDen);

	return 0;
}


//int main(void) {
//	int x = 10, y = 4, z = 1;
//	printf("x & 0x2 = %d\n", x & 0x2);
//	//printf("y >>= 2 = %d\n", y >>= 2);
//	y >>= x & 0x2 && z;
//	printf("x = %d, y = %d, z = %d\n", x, y, z);
//	return 0;
//}