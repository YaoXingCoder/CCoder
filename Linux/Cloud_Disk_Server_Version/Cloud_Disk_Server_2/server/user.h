/*************************************************************************
    > File Name: user.h
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月04日 星期日 21时55分35秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 
    > Content:
 ************************************************************************/
#ifndef __USER_H__
#define __USER_H__

#include "thread_pool.h"
#include <shadow.h>
#include <crypt.h>

#define NAME_SIZE 64
#define PWD_MD5 256

/* 用户状态 */
typedef enum {
    STATUS_LOGOFF = 0,
    STATUS_LOGIN
}LoginStatus;

/* 用户信息 */
typedef struct {
    int sockfd; //套接字文件描述符
    LoginStatus status;//登录状态
    char name[20];  // 用户名(客户端传递过来的)
    char encrypted[100]; // 从/etc/shadow文件中获取的加密密文
    char pwd[128]; // 云端用户的根路径
    char ip[65];
}user_info_t;

/* 用户登录 */
void loginCheck1(user_info_t * user);
void loginCheck2(user_info_t * user, const char * encrypted);

/* 用户注册 */
void register_check1(user_info_t* user); 
void register_check2(user_info_t* user); 

#endif
