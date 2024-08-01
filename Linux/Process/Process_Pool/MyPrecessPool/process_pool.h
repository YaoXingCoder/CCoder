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

#define SIZE(a) (sizeof(a)/sizeof(a[0]))
#define FILE_SMALL 4096
#define FILE_NAME_SIZE 32
#define FILE_CONTENT_SIZE 4096

typedef void (*sighandler_t)(int); // 信号处理函数, 回调函数类型别名简化

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
}sub_status;

// 子进程信息结构体
typedef struct{
    pid_t pid; // 子进程的id
    int skpfd; // 子进程通信管道
    int exitFlag; // 退出标志位, 1为退出
    sub_status s_status ; // 0空闲, 1忙碌
}sub_prc_info;

/* 发送文件 */
typedef struct {
    int len_buff;
    char buff[FILE_SMALL];
}transfer_file;

/* 
 * 子进程相关
 */
// 创建子进程
int mkSubPrc(sub_prc_info* sub_prc_set, const int sub_prc_num);
// 子进程任务
int handleEvent(const int skpfd);

/* 
 * 父子进程间通信 
 */
int sendFD(const int skpfd, char exitFlag, const int netfd);
int recvFD(const int skpfd, char* pexitFlag, int* netfd);

/* 
 * 服务端 
 */
int serverInit (const char* ip, const char* port);
int epoll_add_read_event(const int epfd, const int netfd);
int epoll_del_read_event(const int epfd, const int netfd);

/* 
 * 传输文件
 */
int transferFile(const int netfd);

#endif
