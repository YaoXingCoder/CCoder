/*************************************************************************
    > File Name: thread_pool.h
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月04日 星期日 15时59分59秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 子线程池实现头文件
    > Content:
 ************************************************************************/

#ifndef __THREAD_POOL_H__
#define __THREAD_POOL_H__

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include <error.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <signal.h>
#include <dirent.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/epoll.h>
#include <assert.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <pthread.h>
#include <sys/uio.h>
#include <sys/sendfile.h>
#include <arpa/inet.h>
#include <syslog.h>

#define SIZE(a) (sizeof(a)/sizeof(a[0]))

/* 判错 
 * ret 函数返回值
 * num 错误码
 * msg 错误后字符串
 */
#define ERROR_CHECK(ret, num, msg) {\
    if(ret == num) {                                                \
        perror(msg);                                                \
        return -1;                                                  \
    }}

/* 线程判判错
 * ret 函数返回值
 * funcname 出错函数
 */
#define THREAD_ERROR_CHECK(ret, funcname){                          \
        if ( ret != 0 ) {                                           \
            fprintf(stderr, "%s:%s\n", funcname, strerror(ret));    \
        }                                                           \
    }

/* 信号错误处理函数类型别名 */
typedef void (*sighandler_t)(int);

/* 命令枚举类 */
typedef enum {
    /* 命令行分类 */
    CMD_TYPE_PWD = 1,
    CMD_TYPE_LS, 
    CMD_TYPE_CD, 
    CMD_TYPE_MKDIR, 
    CMD_TYPE_RMDIR, 
    CMD_TYPE_PUTS, 
    CMD_TYPE_GETS, 
    CMD_TYPE_TREE, /* 2024.8.12 new cmd */
    CMD_TYPE_NOTCMD, /* 不是命令 */

    /* 用户登录 验证 */
    TASK_LOGIN_SECTION1 = 100,  /* 用户名验证 */
    TASK_LOGIN_SECTION1_RESP_OK,
    TASK_LOGIN_SECTION1_RESP_ERROR,
    TASK_LOGIN_SECTION2,        /* 密码验证 */
    TASK_LOGIN_SECTION2_RESP_OK,
    TASK_LOGIN_SECTION2_RESP_ERROR,

    /* 用户注册 验证*/
    TASK_REGISERT_SECTION1 = 200,
    TASK_REGISTER_SECTION1_RESP_OK,
    TASK_REGISTER_SECTION1_RESP_ERROR,
    TASK_REGISTER_SECTION2,
    TASK_REGISTER_SECTION2_RESP_OK,
    TASK_REGISTER_SECTION2_RESP_ERROR

}CmdType;

/* 
 * 用户输入命令
 * 通信的结构体
 * */
typedef struct {
    int len; // 内容长度
    CmdType type;
    char buff[1000]; // 记录内容
}train_t;

/* 阻塞队列中节点的结构体 */
typedef struct task_s {
    int peerfd; // client的套接字
    int epfd; // epoll实例
    CmdType type;
    char data[1000]; // 传输大小
    struct task_s* pNext;
}task_t;

/* 阻塞队列的结构体 */
typedef struct task_queue_s{
    task_t* pFront;
    task_t* pRear;
    int queSize; // 节点个数
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    int flag; // 0不退出, 1退出
}task_queue_t;

/* 线程池结构体 */
typedef struct threadpool_s {
    pthread_t* pthreads; // 指向堆空间中线程池的首地址
    int pthreadNum; // 堆空间中线程的个数
    task_queue_t que; // 任务队列
}threadpool_t;

/* 队列相关 */
int queueInit(task_queue_t* que);
int queueDestroy(task_queue_t* que);
int queueIsEmpty(task_queue_t* que);
int taskSize(task_queue_t* que);
int taskEnque(task_queue_t* que, task_t* task);
task_t* taskDeque(task_queue_t* que);
int broadcastAll(task_queue_t* que);

/* 线程池 */
int threadpoolInit(threadpool_t* tp, int num);
int threadpoolDestroy(threadpool_t* tp);
int threadpoolStart(threadpool_t* tp);
int threadpoolStop(threadpool_t* tp);

/* 服务器 */
int tcpInit(const char* ip, const char* port);
int addEpollReadfd(int epfd, int sockfd);
int delEpollReadfd(int epfd, int sockfd);
int transferFile(int sockfd);
int sendn(int sockfd, const void* buff, int len);
int recvn(int sockfd, void* buff, int len);

/* 处理客户端消息 */
void handleMessage(int sockfd, int epfd, task_queue_t* que);
void doTask(task_t* task);

/* 每一个具体命令的执行 */
void cdCommand(task_t * task);
void lsCommand(task_t * task);
void pwdCommand(task_t * task);
void mkdirCommand(task_t * task);
void rmdirCommand(task_t * task);
void treeCommand(task_t* task); /* 2024.8.12 new cmd */
void notCommand(task_t * task);
void putsCommand(task_t * task);
void getsCommand(task_t * task);

/* 用户登录 函数 */
void userLoginCheck1(task_t * task);
void userLoginCheck2(task_t * task);
/* 用户注册 函数*/
void userRegisterCheck1(task_t* task);
void userRegisterCheck2(task_t* task);

/* 日志记录 */
void record_log(task_t* pt);
char* getStrCmdType(CmdType cmd_t); /* cmd 枚举类的映射函数 */

#endif
