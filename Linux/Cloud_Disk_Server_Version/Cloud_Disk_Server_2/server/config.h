/*************************************************************************
    > File Name: config.h
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月03日 星期六 23时22分06秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 读取配置文件的头文件
    > Content: 
    >   1.配置文件数据 ip, port, thread_num
 ************************************************************************/
#ifndef _CONFIG_H__
#define _CONFIG_H__

#include "hashtable.h"
#include "str_util.h" // 字符串工具类

#define IP "ip"
#define PORT "port"
#define THREAD_NUM "thread_num"

void readConfig (const char* filename, HashTable* ht);

#endif
