/* 
Date:2024.7.16
Title:实现阻塞队列(互斥锁and条件变量)
Author:JiaZiChunQiu
Content:

#define N 1024

typedef int E;

typedef struct {
    E elements[N];
    int front;
    int rear;
    int size;
    pthread_mutex_t mutex;
    pthread_cond_t not_empty;
    pthread_cond_t not_full;
} BlockQ;

BlockQ* blockq_create(void);
void    blockq_destroy(BlockQ* q);

bool blockq_empty(BlockQ* q);
bool blockq_full(BlockQ* q);
void blockq_push(BlockQ* q, E val);
E blockq_pop(BlockQ* q);
E blockq_peek(BlockQ* q);

 */

#include "BLOCKQ.h"

// 创建队列, 初始化
BLOCKQ* blockq_create(void){
    BLOCKQ* q = (BLOCKQ*)calloc(1, sizeof(BLOCKQ));

    // 初始化互斥变量
    pthread_mutex_init(&q->mutex, NULL);

    // 初始化条件变量
    pthread_cond_init(&q->not_empty, NULL);
    pthread_cond_init(&q->not_full, NULL);

    return q;
}

// 销毁队列
void blockq_destroy(BLOCKQ* q){
    pthread_cond_destroy(&q->not_full);
    pthread_cond_destroy(&q->not_empty);
    pthread_mutex_destroy(&q->mutex);
    free(q);
}

// 队列判空
bool blockq_empty(BLOCKQ* q){
    pthread_mutex_lock(&q->mutex);
    int size = q->size;
    pthread_mutex_unlock(&q->mutex);
    return size == 0;
}

// 队列判满
bool blockq_full(BLOCKQ* q){
    pthread_mutex_lock(&q->mutex);
    int size = q->size;
    pthread_mutex_unlock(&q->mutex);
    return size == MAX_NUM;
}

// 放入队列
bool blockq_push(BLOCKQ* q, E val){
    pthread_mutex_lock(&q->mutex);
    
    // 使用循环判断, 避免虚假唤醒(wait返回时, 又有较快的线程执行, 导致满, 循环再次判断)
    while(q->size == MAX_NUM){
        pthread_cond_wait(&q->not_full, &q->mutex);
    }

    q->elemetns[q->rear] = val;
    q->rear = (q->rear + 1) % MAX_NUM;
    q->size++;

    pthread_cond_signal(&q->not_empty);
    pthread_mutex_unlock(&q->mutex);
    
    return true;
}

// 取出队列
E blockq_pop(BLOCKQ* q){
    pthread_mutex_lock(&q->mutex);
    while(q->size == 0) {
        pthread_cond_wait(&q->not_empty, &q->mutex);
    }

    E retval = q->elemetns[q->front];
    q->front = (q->front+1) % MAX_NUM;
    q->size--;

    pthread_cond_signal(&q->not_full);
    pthread_mutex_unlock(&q->mutex);

    return retval;
}

// 查看队列
E blockq_peek(BLOCKQ* q){
    pthread_mutex_lock(&q->mutex);

    while(q->size == 0) {
        pthread_cond_wait(&q->not_empty, &q->mutex);
    }

    E retval = q->elemetns[q->front];

    pthread_mutex_unlock(&q->mutex);

    return retval;
}
