/*************************************************************************
    > File Name: task_queue.c
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月04日 星期日 16时27分47秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 阻塞队列
    > Content:
 ************************************************************************/

#include "thread_pool.h"

/* 队列相关队列相关 */
int queueInit(task_queue_t* que){
    assert(que);
    que->pFront = NULL;
    que->pRear = NULL;
    que->queSize = 0;
    que->flag = 1;
    int ret = pthread_mutex_init(&que->mutex, NULL);
    THREAD_ERROR_CHECK(ret, "pthread_mutex_init");
    ret = pthread_cond_init(&que->cond, NULL);
    THREAD_ERROR_CHECK(ret, "pthread_cond_init");
    return 0;
}

/* 销毁 */
int queueDestroy(task_queue_t* que){
    if(que){
        int ret = pthread_mutex_destroy(&que->mutex);
        THREAD_ERROR_CHECK(ret, "pthread_mutex_init");

        ret = pthread_cond_destroy(&que->cond);
        THREAD_ERROR_CHECK(ret, "pthread_cond_destroy");
    }
    return 0;
}

/* 判空 */
int queueIsEmpty(task_queue_t* que){
    return que->queSize == 0;
}

/* 队列中任务个数 */
int taskSize(task_queue_t* que){
    return que->queSize;
}

/* 入队 */
int taskEnque(task_queue_t* que, task_t* ptask){
    // assert(que);
    int ret = pthread_mutex_lock(&que->mutex);
    THREAD_ERROR_CHECK(ret, "pthread_mutex_lock");

    if ( queueIsEmpty(que) ) {
        que->pFront = que->pRear = ptask;
    } else {
        que->pRear->pNext = ptask;
        que->pRear = ptask;
    }
    que->queSize++;
    ret = pthread_mutex_unlock(&que->mutex);
    THREAD_ERROR_CHECK(ret, "pthread_mutex_unlock");
    ret = pthread_cond_signal(&que->cond);
    THREAD_ERROR_CHECK(ret, "pthread_cond_signal");
    return 0;
}

task_t* taskDeque(task_queue_t* que){
    assert(que);
    int ret = pthread_mutex_lock(&que->mutex);
    THREAD_ERROR_CHECK(ret, "pthread_mutex_lock");
    task_t* pret;
    while( queueIsEmpty(que) && que->flag ) { pthread_cond_wait(&que->cond, &que->mutex); }
    if ( que->flag ) {
        pret = que->pFront;
        if ( taskSize(que) == 1 ) que->pFront = que->pRear = NULL; // 若为最后一个直接返回, 队列指针指向NULL
        else {
            que->pFront = pret->pNext;
        }
        que->queSize--;
    } else { pret = NULL; } // 若没有返回NULL
    ret = pthread_mutex_unlock(&que->mutex);
    THREAD_ERROR_CHECK(ret, "pthread_mutex_unlock");
    return pret;
}

/* 广播退出 */
int broadcastAll(task_queue_t* que){
    que->flag = 0; // 队列状态设为退出
    int ret= pthread_cond_broadcast(&que->cond);
    THREAD_ERROR_CHECK(ret, "pthread_cond_broadcast");
    return 0;
}


