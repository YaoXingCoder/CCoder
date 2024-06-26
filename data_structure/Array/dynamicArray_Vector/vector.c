#include "vector.h"

/*
Date:2024.6.20
Title:��̬����ʵ��
Content:
1.���캯���������յĶ�̬����
2.�������������ٶ�̬����
3.ʵ����������� ׷��ֵ
*/

void growCapa(Vector* v); // ����

// ���캯���������յĶ�̬����
Vector* createNullVec(void) {
	// ���ڶ�������Vector�Ŀռ�
	Vector* v = (Vector*)malloc(sizeof(E));
	if (!v) {
		perror("v");
		return;
	}

	// ��ΪVector�е�element����ѿռ�
	E* ptr = (E*)malloc(sizeof(E) * INIT_CAPA);
	if (!ptr) {
		free(v);
		perror("createElement");
		return;
	}
	v->elements = ptr;
	v->capacity = INIT_CAPA;
	v->size = 0;

	// ���ش����Ŀռ�
	return v;
}

// �������������ٶ�̬����
void destoryVec(Vector* v) {
	assert(v);
	free(v->elements);
	free(v);
}

// ÿ�ﵽ���ռ�������������ﵽ���ռ�����������ռ������
void growCapa(Vector* v) {
	assert(v);
	int newCapacity = v->capacity < MAX_PREALLOC ? v->capacity << 1 : (v->capacity + MAX_PREALLOC);

	E* ptr = (E*)realloc(v->elements, newCapacity * sizeof(E));

	if (!ptr) {
		perror("growCapa");
		return;
	}

	v->elements = ptr;
	v->capacity = newCapacity;
}

// ʵ����������� ׷��ֵ
void appendVal(Vector* v, E val) {
	assert(v);
	if (v->size == v->capacity) growCapa(v);
	v->elements[v->size++] = val;
}
