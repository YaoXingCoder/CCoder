/*************************************************************************
    > File Name: BlockQ.c
    > Author: JiaZiChunQiu
    > Created Time: 2024年07月29日 星期一 13时56分56秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 阻塞队列(用于线程池的任务)
    > Content:

 ************************************************************************/

#include "Thread_Pool.h"
#include <pthread.h>

/* 队列初始化  */
int blockQ_Init(Block_Q* bq){
    assert(bq);
    bq->pFront = NULL;
    bq->pRear = NULL;
    bq->queueSize = 0;
    bq->exitFlag = 0;

    int ret = pthread_mutex_init(&bq->mutex, NULL);
    THREAD_ERROR_CHECK(ret, "pthread_mutex_init");
    ret = pthread_cond_init(&bq->cond, NULL);
    THREAD_ERROR_CHECK(ret, "pthread_cond_init");

    return 0;
}

/* 销毁  */
int blockQ_Destory(Block_Q* bq){
    assert(bq);
    int ret = pthread_mutex_destroy(&bq->mutex);
    THREAD_ERROR_CHECK(ret, "pthread_mutex_destroy");
    ret = pthread_cond_destroy(&bq->cond);
    THREAD_ERROR_CHECK(ret, "pthread_cond_destroy");
    return 0;
}

/* 判空  */
int blockQ_Empty(const Block_Q* bq){
    assert(bq);
    return bq->queueSize;
}

/* 剩余结点 */
int blockQ_Size(const Block_Q* bq) {
    assert(bq);
    return bq->queueSize;
}

/* 入队  */
int blockQ_Push(Block_Q* bq, const int netfd){
    assert(bq);

    /* 新节点初始化  */
    QNode* newNode = (QNode*)calloc(1, sizeof(QNode));
    newNode->netfd = netfd;
    newNode->pNext = NULL;

    int ret = pthread_mutex_lock(&bq->mutex); // 加锁
    THREAD_ERROR_CHECK(ret, "pthread_mutex_lock");

    if(blockQ_Empty(bq)) {
        newNode->pNext =  bq->pRear;
        bq->pRear->pNext = newNode;
    } else {
        bq->pFront = bq->pRear = newNode;
        bq->queueSize++;
    }

    ret = pthread_cond_signal(&bq->cond); // 通知队列不空
    THREAD_ERROR_CHECK(ret, "pthread_cond_signal");
    ret = pthread_mutex_unlock(&bq->mutex); // 解锁
    THREAD_ERROR_CHECK(ret, "pthread_mutex_unlock");

    return 0;
}
    
/* 出队  */
int blockQ_Pop(Block_Q* bq){
    assert(bq);

    int ret = pthread_mutex_lock(&bq->mutex);
    THREAD_ERROR_CHECK(ret, "pthread_mutex_lock");
    int netfd_tmp = -1;

    while(!bq->exitFlag &&  blockQ_Empty(bq) == 0) { pthread_cond_wait(&bq->cond, &bq->mutex); }
    if ( !bq->exitFlag ) {
        QNode* currNode = bq->pFront;
        netfd_tmp = currNode->netfd;

        if ( blockQ_Size(bq) == 1 ) { bq->pFront = bq->pRear = NULL; }
        else { bq->pFront = currNode->pNext; }
        bq->queueSize--;

        free(currNode);
        currNode = NULL;
    }
    ret = pthread_mutex_unlock(&bq->mutex);
    THREAD_ERROR_CHECK(ret, "pthread_mutex_unlock");

    return netfd_tmp;
}

/* 查看队列头  */
int blockQ_Peek(const Block_Q* bq){
    assert(bq);
    if(blockQ_Size(bq)) { return bq->pFront->netfd; }
    return 0;
}

/* 唤醒 */
void wakeup(Block_Q* bq) {
    bq->exitFlag = 1;
    pthread_cond_broadcast(&bq->cond);
}
