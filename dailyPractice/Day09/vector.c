#include "vector.h"

/*
Date:2024.6.21
Title:ʵ�ֶ�̬����
Content:
1.���һ����̬���飬������ռ䲻��ʱ���������Զ�����
*/

/*
typedef int E;

typedef struct {
    E* elements;   // ָ��ѿռ������
    int size;	// Ԫ�صĸ���
    int capacity; // ���������
} Vector;

// ��ʵ�����淽��
void push_back(Vector* v, E val);
// ��������ǰ�����Ԫ�أ�����Ԫ�����κ���
void push_front(Vector* v, E val);
// ɾ�����һ��Ԫ��, �������һ��Ԫ�ط���
E pop_back(Vector* v);
// ɾ����һ��Ԫ�أ����ѵ�һ��Ԫ�ط���
E pop_front(Vector* v);
*/

static void growVector(Vector* v);

// ��ȡ����ռ�
Vector* vectorCreate(void) {
    // ���ٽṹ��ռ�
    Vector* v = (Vector*)malloc(sizeof(Vector));
    if (!v) {
        perror("create vector");
        exit(1);
    }

    // ��������ռ�
    E* ptr = (E*)malloc(sizeof(E) * INIT_CAPACITY);
    if (!ptr) {
        free(v); // ����ʧ���ͷŽṹ��ռ�
        perror("create element");
        exit(1);
    }
    
    // ��ʼ���ṹ�����
    v->elements = ptr;
    v->size = 0;
    v->capacity = INIT_CAPACITY;

    // ���ضѿռ��ַ
    return v;
}

// ����vector
void destoryVector(Vector* v) {
    free(v->elements);
    free(v);
}

/*
��������
����
1.���û�дﵽ�������������ԭ��С����
2.����ﵽ���������ÿ�������������������
*/
void growVector(Vector* v) {
    // �����¿ռ������
    int newCapaticy = v->capacity < MAX_CAPACITY ? (v->capacity << 1) : (v->capacity + MAX_CAPACITY);

    // �����¿ռ�/����
    E* ptr = (E*)realloc(v->elements, sizeof(E) * newCapaticy);
    if (!ptr) {
        perror("growVector");
        return;
    }

    // ���Ľṹ�����
    v->elements = ptr;
    v->capacity = newCapaticy;
}

// �����������Ԫ��
void push_back(Vector* v, E val) {
    // �жϿռ��С
    if (v->capacity == v->size) growVector(v);
    // ��ֵ
    v->elements[v->size++] = val;
}

// ��������ǰ�����Ԫ�أ�����Ԫ�����κ���
void push_front(Vector* v, E val) {
    // ���û��Ԫ��ֱ�����
    if (v->size == 0) {
        v->elements[0] = val;
        v->size += 1;
        return;
    }

    // �ж��Ƿ���Ҫ����
    if (v->size == v->capacity) growVector(v);
    
    // Ԫ�غ���
    memmove(v->elements + 1, v->elements, sizeof(E) * v->size);
    v->elements[0] = val;
    v->size++;
}

// ɾ�����һ��Ԫ��, �������һ��Ԫ�ط���
E pop_back(Vector* v) {
    // �ж��Ƿ�Ϊ��
    if (!v->size) {
        printf("No data to delete");
        return 0;
    }
    // ɾ�����һ����size--
    return v->elements[(v->size--) - 1];
}

// ɾ����һ��Ԫ�أ����ѵ�һ��Ԫ�ط���
E pop_front(Vector* v) {
    if (!v->size) {
        printf("No data to delete");
        return 0;
    }
    E temp = v->elements[0];
    memmove(v->elements, v->elements + 1, sizeof(E) * v->size);
    return temp;
}