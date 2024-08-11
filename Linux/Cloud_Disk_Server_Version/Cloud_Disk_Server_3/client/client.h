/*************************************************************************
    > File Name: client.h
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月05日 星期一 10时37分15秒
    > Mail: JiaZiChunQiu@163.com
    > Title: client 头文件
    > Content:
 ************************************************************************/
#pragma once

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

#include "str_util.h"

#define SIZE(a) (sizeof(a)/sizeof(a[0]))

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

#define DEFAULT_INPUT_LINE "~$ "
#define USER_NAME "please input a valid user name: "
#define PASSWORD "please input the right password: "
#define PASSWORD_R "please input password: "

#define TRANS_FILE_SIZE 4096


typedef enum {
    /* 命令 */
    CMD_TYPE_PWD=1,
    CMD_TYPE_LS,
    CMD_TYPE_CD,
    CMD_TYPE_MKDIR,
    CMD_TYPE_RMDIR,
    CMD_TYPE_PUTS,
    CMD_TYPE_GETS,
    CMD_TYPE_NOTCMD,  //不是命令

    /* 用户登录 */
    TASK_LOGIN_SECTION1 = 100,
    TASK_LOGIN_SECTION1_RESP_OK,
    TASK_LOGIN_SECTION1_RESP_ERROR,
    TASK_LOGIN_SECTION2,
    TASK_LOGIN_SECTION2_RESP_OK,
    TASK_LOGIN_SECTION2_RESP_ERROR,

    /* 用户注册 */
    TASK_REGISTER_SECTION1 = 200,
    TASK_REGISTER_SECTION1_RESP_OK,
    TASK_REGISTER_SECTION1_RESP_ERROR,
    TASK_REGISTER_SECTION2,
    TASK_REGISTER_SECTION2_RESP_OK,
    TASK_REGISTER_SECTION2_RESP_ERROR,
}CmdType;

typedef struct {
    int len;//记录内容长度
    CmdType type;//消息类型
    char buff[1000];//记录内容本身
}train_t;

/* 客户端初始化 */
int tcpConnect(const char * ip, unsigned short port);
int recvn(int sockfd, void * buff, int len);
int sendn(int sockfd, const void * buff, int len);

/* 用户登录 */
int userLogin(int sockfd);
/* 用户注册 */
int userRegister(int sockfd);

/* 命令解析 */
int parseCommand(const char * input, int len, train_t * pt);

/* 命令处理 
 * */
// 判断一个字符串是什么命令
int getCommandType(const char * str);
// 执行上传文件操作
void putsCommand(const int sockfd, const train_t * pt);
// 执行下载文件操作
void getsCommand(const int sockfd, const train_t* pt);
// 接收cd命令
void cdCommand(const int sockfd);
/* 用于输出当前路径*/
void pwdCommand(const int sockfd);
/* 文件是否存在 */
void file_is_exist(train_t* pt);
