#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

//void test();
//
//int main() {
//	printf("%p\n", test); // ȡ�����ĵ�ַ
//	printf("%p\n", &test); // ȡ�������ĵ�ַ
//	return 0;
//}
//&������ �� ������ ���Ǻ����ĵ�ַ��������
//void test() {
//	printf("hehe\n");
//}

/*
����ָ��Ĵ洢��ʹ��
*/
//int Add(int x, int y);
//
//int main(void) {
//	printf("ȡ������ַ��%p\n", &Add);
//
//	// ���溯����ַ����ȱ��������ַ������ָ�룩
//	int arr[5] = { 1,2,3,4,5 };
//	int (*pi1)[5] = &arr; // �������������ָ��
//	printf("pi1 = %p\n", pi1);
//	printf("pi1+1 = %p\n", pi1 + 1);
//
//	//int (*pf)(int, int) = &Add; // ���溯���ĺ���ָ��
//	int (*pf)(int, int) = Add; // ���溯���ĺ���ָ�룬Add��&Add�ȼ�
//	// (*pf)����Ϊָ�룬��߸�()����ָ����Ǻ��������������뺯���Ĳ������ͣ��βο�д�ɲ�д��������Ϊ��������ֵ����
//
//	int ret = (*pf)(3, 2); // (*pf)�������ҵ����������ε��ú��� �ȼ��� Add(3, 2)
//	ret = pf(3, 3); // ���Բ�д***�����pf = Add��
//	// ��Ϊʹ��int (*pf)(int, int) = Add; ���溯��ָ��ʱ�� int (*pf)(int, int) = &Add;�ȼ� ���� *pf = pf
//	ret = (****pf)(3, 4); // Ҳ����д���****�����������()�ڣ��������
//	ret = (*Add)(5, 5); // ֱ���ú�����Ҳ����
//	printf("%d\n", ret);
//	return 0;
//}

//int Add(int x, int y) {
//	return x + y;
//}


/* 
������
*/
// ����1
//void zeroFunction(void) {
//	( *( void(*)() ) 0 )();
//	// 1.void(*)()��Ϊ����ָ�����͡���ȣ�int (*p)(int, int);��
//	//	ֻ��û��p����������˺���ָ�����ͣ��Ҵ���Ϊvoid������ֵ����Ϊvoid
//	// 2.(void(*)())0����int���͵�0ǿ��ת��Ϊ�˺���ָ�����ͣ�0�洢�Ķ����Ʊ�Ϊ�����ĵ�ַ��0ָ��ú�����ַ
//	// 3.(*( void(*)())0)�������øõ�ַ
//	// 4.(*( void(*)())0)()�����ú���������Ϊvoid
//}

//����2
//typedef void(*pf_t)(int); // �� void(*)(int) ������Ϊ pf_t ������ָ������
//int main(void) {
//	void (*signal(int, void(*)(int)))(int);
//	// 1.signal( int, void(*)(int) )��Ϊ����������������signal�����ĵ�һ������Ϊint��
//	//	�ڶ�������Ϊvoid(*)(int)����ָ�����ͣ��ú���ָ��ָ��ĺ����Ĳ�����int������������void
//	// 2.void(* signal() )(int)��signal�ķ�������Ҳ��һ������ָ�루���������ͱ�����Ϊ��һ������ָ���ָ�������
//	//	�ú���ָ��ָ��ĺ���������int������������void
//
//	// �����������򻯣�
//	pf_t signal(int, pf_t);
//	return 0;
//}

/*
����ָ����;
�򵥼�������Ӧ�ú���ָ��
*/
void menu();
int add(int x, int y);
int sub(int x, int y);
int mut(int x, int y);
int div(int x, int y);
void calc(int (*pf)(int, int));

int main(void) {
	int input = 0;
	do {
		menu();
		printf("Enter options:>");
		scanf("%d", &input);
		switch (input) {
			case 1:
				calc(add);
				break;
			case 2:
				calc(sub);
				break;
			case 3:
				calc(mut);
				break;
			case 4:
				calc(div);
				break;
			case 0:
				printf("�˳�����~~~");
				input = 0;
				break;
			default:
				printf("ѡ�����~~~");
				break;
		}
	} while (input);
}

void menu() {
	printf("******************************\n");
	printf("*********1.Add   2.Sub********\n");
	printf("*********3.Mut   4.Div********\n");
	printf("*********9.Exit       ********\n");
	printf("******************************\n");
}

int add(int x, int y) {
	return x + y;
}
int sub(int x, int y) {
	return x - y;
}
int mut(int x, int y) {
	return x * y;
}
int div(int x, int y) {
	return x / y;
}

void calc(int (*pf)(int, int)) {
	int x = 0;
	int y = 0;
	int ret = 0;
	printf("Enter two number:>");
	scanf("%d %d", &x, &y);
	ret = pf(x, y);
	printf("���Ϊ��%d\n", ret);
}
