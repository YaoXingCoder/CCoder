/* 
Date:2024.7.16
Title:使用阻塞队列实现生产者消费者模型
Author:JiaZiChunQiu
Content:

int main(int argc, char* argv[])
{
    // main线程
    // 1. 创建线程池

    // 2. 主线程往阻塞队列中放任务; 子线程从阻塞队列中取任务，然后执行任务

    // 3. 线程池优雅地退出

    // 4. 销毁线程池

    return 0;
}
 */

#include <my_header.h> 
#include "BLOCKQ.h"
#include <unistd.h>

#define THREAD_SIZE 10

// 线程池结构
typedef struct {
    pthread_t* pthreads;
    int nums;
    BLOCKQ* q;
}TPOOL;

// 入口函数
void* start_routine(void* arg){
    BLOCKQ* q = (BLOCKQ*) arg;
    pthread_t tid = pthread_self();

    // 循环取出队列中值
    for(;;) {
        E task_id = blockq_pop(q); // 如果队列为空, 则在队列内会被阻塞
        if (task_id == -1) { pthread_exit(NULL); }

        // 输出
        printf("Thread %#lx: executing task %d\n", tid, task_id);
        sleep(1);
        printf("Thread %#lx: task %d done\n", tid, task_id);
    }
}

// 创建线程池
TPOOL* tpool_create(int n) {
    TPOOL* tpool = (TPOOL*)malloc(sizeof(TPOOL));
    tpool->pthreads = (pthread_t*)malloc(n * sizeof(pthread_t)); 
    tpool->nums = n;
    tpool->q = blockq_create();

    // 创建n个工作线程, 并传入阻塞队列
    for(int i = 0; i < n; i++) {
        pthread_create(tpool->pthreads + i, NULL, start_routine, tpool->q);
    }

    return tpool;
}

int main(int argc, char* argv[]) {
    // 创建线程池
    TPOOL* tpool = tpool_create(8);

    // 放值入队列
    for (int i = 1; i <= 100; i++) {
        blockq_push(tpool->q, i);
    }

    sleep(3);

    // 退出线程池, 线程终止
   // for(int i = 0; i < tpool->nums; i++) {
     //   pthread_cancel(tpool->pthreads[i]);
   //  }

    for(int i = 0; i < tpool->nums; i++) {
        blockq_push(tpool->q, -1);
    }

    // 循环等待join
    for(int i = 0; i < tpool->nums; i++) {
        pthread_join(tpool->pthreads[i], NULL);
    }
    return 0;
}

