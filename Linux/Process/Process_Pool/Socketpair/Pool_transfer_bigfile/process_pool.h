/*************************************************************************
    > File Name: process_pool.h
    > Author: JiaZiChunQiu
    > Created Time: 2024年07月25日 星期四 23时05分32秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 线程池头文件
    > Content:
************************************************************************/

#ifndef _FUNC_H
#define _FUNC_H

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

#define SIZE(a) (sizeof(a)/sizeof(a[0]))
#define FILE_SMALL 4096

typedef void (*sighandler_t)(int);

#define ARGS_CHECK(argc, num)   {\
    if(argc != num){\
        fprintf(stderr, "ARGS ERROR!\n");\
        return -1;\
    }}

#define ERROR_CHECK(ret, num, msg) {\
    if(ret == num) {\
        perror(msg);\
        return -1;\
    }}

// 子进程状态  
typedef enum {
    FREE,
    BUSY
}status_t;

// 子进程信息结构体
typedef struct{
    pid_t pid; // 子进程的id
    int pipefd; // 子进程通信管道
    status_t status; // 0空闲, 1忙碌
}PROCESS_DATA;

// 发送文件
typedef struct {
    int len;
    char buff[FILE_SMALL];
}train_t;

// 创建子进程
int mkProcess(PROCESS_DATA* pProcess, int prNum);

// 子进程任务
int doTask(int skpfd);

// sendFd recvFd
int sendFd(int skpfd, int fd);
int recvFd(int skpfd, int* fd);

// 服务端
int tcpInit (const char* ip, const unsigned short port);
int epollAddReadEvent(int epfd, int fd);
int epollDelReadEvent(int epfd, int fd);

// 传输文件(小型)
int transferFile(int peerfd);

#endif
