#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stddef.h>
/*
Date��2024.6.16
Title���ṹ��ѧϰ
Content��
1.����
2.������
3.����/��ʼ��
4.�ڴ���루����ṹ�����ʹ�С��
5.�꣬�޸�Ĭ�϶�������С
*/
// ��֧�������ṹ����������������
//typedef struct {
//	int data;
//	Node* next;
//}Node;

/*
ѧϰ����ṹ���С
*/
void structureSize(void) {
    // ��ϰ1
    struct S1 {
        char c1;
        int i;
        char c2;
    };
    printf("%d\n", sizeof(struct S1)); // 12

    // ʹ��macro�꣬���ؽṹ���Ա�����ڽṹ����ƫ����
    printf("c1��struct S1�е�ƫ����Ϊ��%d\n", offsetof(struct S1, c1)); // 0
    printf("i��struct S1�е�ƫ����Ϊ��%d\n", offsetof(struct S1, i)); // 4
    printf("c2��struct S1�е�ƫ����Ϊ��%d\n", offsetof(struct S1, c2)); // 8

    // ��ϰ2
    struct S2 {
        char c1;
        char c2;
        int i;
    };
    printf("%d\n", sizeof(struct S2)); // 8

    // ��ϰ3
    struct S3 {
        double d;
        char c;
        int i;
    };
    printf("%d\n", sizeof(struct S3)); // 16

    //��ϰ4-�ṹ��Ƕ������
    struct S4 {
        char c1;
        struct S3 s3;
        double d;
    };
    printf("%d\n", sizeof(struct S4)); // 32
}

/*
�޸�Ĭ�϶�����
*/
#pragma pack(1) // ����Ĭ�϶�����Ϊ4
void modifyAlignmentNumber(void) {
    struct S1 {
        char c1;
        int i;
        char c2;
    };
#pragma pack(1) // ����Ĭ�϶�����Ϊ1
    struct S2 {
        char c1;
        int i;
        char c2;
    };
#pragma pack() // ȡ�����õ�Ĭ�϶���������ԭΪĬ��
    printf("%d\n", sizeof(struct S1)); // 12
    printf("%d\n", sizeof(struct S2)); // 6
}


/*
�ṹ�崫��
*/
struct S {
    int data[1000];
    int num;
};

// �ṹ�� ����
void print1(struct S s) {
    for (int i = 0; i < 3; i++) {
        printf("%d ", s.data[i]);
    }
    printf("%d\n", s.num);
}

// �ṹ���ַ ����
void print2(const struct S* ps) {
    for (int i = 0; i < 3; i++) {
        printf("%d ", ps->data[i]);
    }
    printf("%d\n", ps->num);
}

void structTranPara(void) {
    struct S s = { {1,2,3,4}, 1000 };
    print1(s);  // ���ṹ��
    print2(&s); // ����ַ
}

int main(void) {
    //structureSize();
    //modifyAlignmentNumber();
    //structTranPara();
	return 0;
}


