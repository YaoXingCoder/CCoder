/*************************************************************************
    > File Name: BlockQueue.h
    > Author: JiaZiChunQiu
    > Created Time: 2024年07月29日 星期一 13时15分02秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 线程池的阻塞队列头文件
    > Content:
 ************************************************************************/
#define _GNU_SOURCE
#include <my_header.h>
#include <pthread.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

#define MAX_EVENTS 16
#define FILENAME "1.ev4"

/* 判断调用方法返回值是否出错  */
#define THREAD_ERROR_CHECK(ret, func_name) {                    \
    if ( ret != 0 ) {                                           \
        fprintf(stderr, "%s:%s\n", func_name, strerror(ret));   \
        return -1;                                              \
    }                                                           \
}

typedef void (*sighandler_t)(int);

/* 队列结点  */
typedef struct QueueNode{
    int netfd; // 网络套接字
    struct QueueNode* pNext; // 下个队列结点
}QNode;

/* 阻塞队列结构体  */
typedef struct Block_Queue{
    QNode* pFront; // 链表头
    QNode* pRear; // 链表尾
    int queueSize; // 阻塞队列中任务数, 即节点数
    int exitFlag; // 退出标志位, 1退出, 0不退出
    pthread_mutex_t mutex; // 线程锁
    pthread_cond_t cond; // 线程条件变量
}Block_Q;

/* 线程池结构体  */
typedef struct ThreadPool{
    pthread_t* threads; // 线程池指针, 指向存放线程池的堆空间
    int tNum; // 线程数量
    Block_Q bq; // 阻塞队列
}ThreadPool;

/* 阻塞队列相关  */
int blockQ_Init(Block_Q* bq); //队列初始化
int blockQ_Destory(Block_Q* bq); // 销毁队列
int blockQ_Empty(const Block_Q* bq); // 判空
int blockQ_Size(const Block_Q* bq); // 节点数
int blockQ_Push(Block_Q* bq, const int netfd); // 放入
int blockQ_Pop(Block_Q* bq); // 取出
int blockQ_Peek(const Block_Q* bq); // 查看
void wakeup(Block_Q* bq); // 唤醒

/* 线程池相关 */
int thread_pool_Init(ThreadPool* tp, int trd_num); // 线程池初始化
int thread_pool_Desotry(ThreadPool* tp); // 销毁
int thread_pool_Start(ThreadPool* tp); // 线程启动
int thread_pool_Close(ThreadPool* tp); // 线程退出

/* 处理任务  */
int transferFile(const int netfd);

/* 服务器相关 */
int serverInit(const char* ip, const char* port); // 初始化, 绑定ip
int epoll_add_read_event(const int epfd, const int netfd); // 添加读就绪事件
int epoll_del_read_event(const int epfd, const int netfd); // 删除读就绪事件
