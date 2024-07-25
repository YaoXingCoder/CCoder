#ifndef BLOCKQ_H
#define BLOCKQ_H

#include <my_header.h>
#include <pthread.h>
#define MAX_NUM 1024 // 队列元素数组的大小

// 队列存储元素类型
typedef int E;

// 队列结构体
typedef struct {
    E elemetns[MAX_NUM];
    int front;
    int rear;
    int size;
    pthread_mutex_t mutex;
    pthread_cond_t not_empty;
    pthread_cond_t not_full;
}BLOCKQ;

// 队列函数接口

// 创建队列, 初始化
BLOCKQ* blockq_create(void);

// 销毁队列
void blockq_destroy(BLOCKQ* q);

// 队列判空
bool blockq_empty(BLOCKQ* q);

// 队列判满
bool blockq_full(BLOCKQ* q);

// 放入队列
bool blockq_push(BLOCKQ* q, E val);

// 取出队列
E blockq_pop(BLOCKQ* q);

// 查看队列
E blockq_peek(BLOCKQ* q);

#endif
