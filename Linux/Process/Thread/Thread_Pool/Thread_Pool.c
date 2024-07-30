/*************************************************************************
    > File Name: Thread_Pool.c
    > Author: JiaZiChunQiu
    > Created Time: 2024年07月29日 星期一 15时06分57秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 进程池相关
    > Content:
    >   1.初始化
    >   2.摧毁
 ************************************************************************/

#include "Thread_Pool.h"
#include <pthread.h>

/* 线程池初始化  */
int thread_pool_Init(ThreadPool* tp, const int trd_num){
    assert(tp);

    tp->threads = (pthread_t*)calloc(trd_num, sizeof(pthread_t));
    if ( tp == NULL ) {
        perror("Thread_Pool thread_pool_Init");
        return -1;
    }

    tp->tNum = trd_num;

    int ret = blockQ_Init(&tp->bq);
    if ( ret == -1 ) {
        perror("Thread_Pool thread_pool_Init");
        return -1;
    }

    return 0;
}

/* 销毁  */
int thread_pool_Desotry(ThreadPool* tp){
    assert(tp);

    free(tp->threads);
    tp->threads = NULL;

    int ret = blockQ_Destory(&tp->bq);
    if (ret == -1) {
        perror("Thread_Pool thread_pool_Desotry");
        return -1;
    }

    return 0;
}

/* 线程执行函数 */
void* start_routine(void* arg) {
    ThreadPool* tp = (ThreadPool*)arg;
    printf("thread is beginning....\n");
    while(1) {
        int netfd = blockQ_Pop(&tp->bq);
        if ( netfd > 0 ) { transferFile(netfd); }
        else if ( netfd == -1 ) { break; }
    }
    printf("sub thread's %lu exit.\n", pthread_self());
    return NULL;
}

/* 线程启动 */
int thread_pool_Start(ThreadPool* tp) {
    assert(tp);
    
    for(int i = 0; i < tp->tNum; ++i) {
        int ret = pthread_create(&tp->threads[i], NULL, start_routine, tp);
        THREAD_ERROR_CHECK(ret, "pthread_create");
    }

    return 0;
}

/* 线程停止/关闭 */
int thread_pool_Close(ThreadPool* tp) {
    assert(tp);

    while(blockQ_Empty(&tp->bq)) {
        sleep(1);
    }
    
    wakeup(&tp->bq);
    for(int i = 0; i < tp->tNum; ++i) {
        pthread_join(tp->threads[i], NULL);
    }

    return 0;
}
