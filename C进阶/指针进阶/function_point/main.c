#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

//void test();
//
//int main() {
//	printf("%p\n", test); // ȡ�����ĵ�ַ
//	printf("%p\n", &test); // ȡ�������ĵ�ַ
//	return 0;
//}
//
//
//&������ �� ������ ���Ǻ����ĵ�ַ��������
//
//void test() {
//	printf("hehe\n");
//}

int Add(int x, int y);

int main(void) {
	printf("ȡ������ַ��%p\n", &Add);

	// ���溯����ַ����ȱ��������ַ������ָ�룩
	int arr[5] = { 1,2,3,4,5 };
	int (*pi1)[5] = &arr; // �������������ָ��
	printf("pi1 = %p\n", pi1);
	printf("pi1+1 = %p\n", pi1 + 1);

	//int (*pf)(int, int) = &Add; // ���溯���ĺ���ָ��
	int (*pf)(int, int) = Add; // ���溯���ĺ���ָ�룬Add��&Add�ȼ�
	// (*pf)����Ϊָ�룬��߸�()����ָ����Ǻ��������������뺯���Ĳ������ͣ��βο�д�ɲ�д��������Ϊ��������ֵ����

	int ret = (*pf)(3, 2); // (*pf)�������ҵ����������ε��ú��� �ȼ��� Add(3, 2)
	ret = pf(3, 3); // ���Բ�д***�����pf = Add��
	// ��Ϊʹ��int (*pf)(int, int) = Add; ���溯��ָ��ʱ�� int (*pf)(int, int) = &Add;�ȼ� ���� *pf = pf
	ret = (****pf)(3, 4); // Ҳ����д���****�����������()�ڣ��������
	ret = (*Add)(5, 5); // ֱ���ú�����Ҳ����
	printf("%d\n", ret);
	return 0;
}

int Add(int x, int y) {
	return x + y;
}