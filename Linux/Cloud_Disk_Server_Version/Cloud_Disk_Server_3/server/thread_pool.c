/*************************************************************************
    > File Name: pthread_pool.c
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月04日 星期日 17时07分23秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 线程池相关
    > Content:
    >   1.初始化
    >   2.启动线程
    >   2.等待任务执行, 释放任务
    >   3.退出任务
 ************************************************************************/

#include "thread_pool.h"

/* 子线程入口 */
void* startroutine(void* arg) {
    threadpool_t* tp = (threadpool_t*)arg;    
    while(1) {
        task_t* ptask = taskDeque(&tp->que);
        if ( ptask ) {
            doTask(ptask); // 执行任务
            free(ptask);
            // printf("等待下个任务\n");
        }else { break; }
    }
    printf("sub thread %ld is exiting.\n", pthread_self());
    return NULL;
}

/* 线程池初始化 */
int threadpoolInit(threadpool_t* tp, int num){
    tp->pthreadNum = num;
    tp->pthreads = (pthread_t*)calloc(num, sizeof(pthread_t)); // num个数的线程堆空间
    queueInit(&tp->que);
    return 0;
}

/* 销毁线程池 */
int threadpoolDestroy(threadpool_t* tp){
    free(tp->pthreads);
    queueDestroy(&tp->que);
    return 0;
}

/* 线程池启动 */
int threadpoolStart(threadpool_t* tp){
    if(tp) {
        for(int i = 0; i < tp->pthreadNum; ++i) {
            int ret = pthread_create(&tp->pthreads[i], NULL, startroutine, tp); // 自动进入线程入口函数
            THREAD_ERROR_CHECK(ret, "pthread_create");
        }
    }
    return 0;
}

/* 退出所有的子线程 */
int threadpoolStop(threadpool_t* tp){
    assert(tp);

    while( queueIsEmpty(&tp->que) ) { sleep(1); }

    broadcastAll(&tp->que);
    for( int i = 0; i < tp->pthreadNum; ++i ) { pthread_join(tp->pthreads[i], NULL); }
    return 0;
}
