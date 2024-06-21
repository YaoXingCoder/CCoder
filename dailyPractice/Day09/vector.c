#include "vector.h"

/*
Date:2024.6.21
Title:实现动态数组
Content:
1.设计一个动态数组，当数组空间不够时，它可以自动扩容
*/

/*
typedef int E;

typedef struct {
    E* elements;   // 指向堆空间的数组
    int size;	// 元素的个数
    int capacity; // 数组的容量
} Vector;

// 请实现下面方法
void push_back(Vector* v, E val);
// 在数组最前面添加元素，所有元素依次后移
void push_front(Vector* v, E val);
// 删除最后一个元素, 并把最后一个元素返回
E pop_back(Vector* v);
// 删除第一个元素，并把第一个元素返回
E pop_front(Vector* v);
*/

static void growVector(Vector* v);

// 获取数组空间
Vector* vectorCreate(void) {
    // 开辟结构体空间
    Vector* v = (Vector*)malloc(sizeof(Vector));
    if (!v) {
        perror("create vector");
        exit(1);
    }

    // 开辟数组空间
    E* ptr = (E*)malloc(sizeof(E) * INIT_CAPACITY);
    if (!ptr) {
        free(v); // 申请失败释放结构体空间
        perror("create element");
        exit(1);
    }
    
    // 初始化结构体变量
    v->elements = ptr;
    v->size = 0;
    v->capacity = INIT_CAPACITY;

    // 返回堆空间地址
    return v;
}

// 销毁vector
void destoryVector(Vector* v) {
    free(v->elements);
    free(v);
}

/*
扩容数组
规则：
1.如果没有达到最大容量，扩容原大小两倍
2.如果达到最大容量，每次增加最大容量的容量
*/
void growVector(Vector* v) {
    // 计算新空间的容量
    int newCapaticy = v->capacity < MAX_CAPACITY ? (v->capacity << 1) : (v->capacity + MAX_CAPACITY);

    // 开辟新空间/扩容
    E* ptr = (E*)realloc(v->elements, sizeof(E) * newCapaticy);
    if (!ptr) {
        perror("growVector");
        return;
    }

    // 更改结构体变量
    v->elements = ptr;
    v->capacity = newCapaticy;
}

// 数组最后边添加元素
void push_back(Vector* v, E val) {
    // 判断空间大小
    if (v->capacity == v->size) growVector(v);
    // 赋值
    v->elements[v->size++] = val;
}

// 在数组最前面添加元素，所有元素依次后移
void push_front(Vector* v, E val) {
    // 如果没有元素直接添加
    if (v->size == 0) {
        v->elements[0] = val;
        v->size += 1;
        return;
    }

    // 判断是否需要扩容
    if (v->size == v->capacity) growVector(v);
    
    // 元素后移
    memmove(v->elements + 1, v->elements, sizeof(E) * v->size);
    v->elements[0] = val;
    v->size++;
}

// 删除最后一个元素, 并把最后一个元素返回
E pop_back(Vector* v) {
    // 判断是否为空
    if (!v->size) {
        printf("No data to delete");
        return 0;
    }
    // 删除最后一个即size--
    return v->elements[(v->size--) - 1];
}

// 删除第一个元素，并把第一个元素返回
E pop_front(Vector* v) {
    if (!v->size) {
        printf("No data to delete");
        return 0;
    }
    E temp = v->elements[0];
    memmove(v->elements, v->elements + 1, sizeof(E) * v->size);
    return temp;
}