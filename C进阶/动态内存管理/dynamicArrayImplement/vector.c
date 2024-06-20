#include "vector.h"

/*
Date:2024.6.20
Title:动态数组实现
Content:
1.构造函数：创建空的动态数组
2.析构函数：销毁动态数组
3.实现在数组最后 追加值
*/

void growCapa(Vector* v); // 扩容

// 构造函数：创建空的动态数组
Vector* createNullVec(void) {
	// 先在堆中申请Vector的空间
	Vector* v = (Vector*)malloc(sizeof(E));
	if (!v) {
		perror("v");
		return;
	}

	// 在为Vector中的element申请堆空间
	E* ptr = (E*)malloc(sizeof(E) * INIT_CAPA);
	if (!ptr) {
		free(v);
		perror("createElement");
		return;
	}
	v->elements = ptr;
	v->capacity = INIT_CAPA;
	v->size = 0;

	// 返回创建的空间
	return v;
}

// 析构函数：销毁动态数组
void destoryVec(Vector* v) {
	assert(v);
	free(v->elements);
	free(v);
}

// 每达到最大空间就扩容两倍，达到最大空间就再扩容最大空间的数量
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

// 实现在数组最后 追加值
void appendVal(Vector* v, E val) {
	assert(v);
	if (v->size == v->capacity) growCapa(v);
	v->elements[v->size++] = val;
}
