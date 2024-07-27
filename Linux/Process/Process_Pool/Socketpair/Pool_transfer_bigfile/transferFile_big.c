/*************************************************************************
    > File Name: transferFile_small.c
    > Author: JiaZiChunQiu
    > Created Time: 2024年07月26日 星期五 20时57分54秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 传输文件函数
    > Content:
    >   1.因为tcp通信时字节流的, 字节流无边界
    >   2.所以发送内容前, 应先发送文件的名字和长度, 此时读取长度类型为约定俗成的int
    >   3.再发送文件的内容
 ************************************************************************/

#include "process_pool.h"
#include <bits/types/stack_t.h>
#include <pthread.h>
#include <string.h>
#include <sys/stat.h>

#define FILE_NAME "1.ev4"

int transferFile(int peerfd) {
    // 打开需要文件, 读
    int fd = open(FILE_NAME, O_RDONLY);
    ERROR_CHECK(fd, -1, "open");
    
    // 文件名
    // 文件长度 + 文件名
    int len_fileName = 0;
    len_fileName = strlen(FILE_NAME);
    train_t t_file; // 文件结构体
    memset(&t_file, 0, sizeof(t_file));
    t_file.len = len_fileName;
    strcpy(t_file.buff, FILE_NAME);
    int ret = send(peerfd, &t_file, 4 + t_file.len, 0); // 发送文件结构体: 文件长度 + 文件名
    ERROR_CHECK(ret, -1, "send len_fileName + fileName");

    // 获取文件内容大小
    struct stat st_file;
    memset(&st_file, 0, sizeof(st_file));
    ret = fstat(fd, &st_file);
    ERROR_CHECK(ret, -1, "fstat");
    int len_fileSize = st_file.st_size; // 获取内容大小

    // 文件内容
    // 先发送文件内容大小
    ret = send(peerfd, &len_fileSize, sizeof(len_fileSize), 0);
    ERROR_CHECK(ret, -1, "send len_fileSize");
    
    // 多次读取并发送 文件内容
    int totalSize = 0; // 记录已发送字节数
    while( totalSize < len_fileSize ) {
        memset(&t_file, 0, sizeof(t_file));
        int readSize = read(fd, t_file.buff, FILE_SMALL);
        if ( readSize > 0 ) {
            t_file.len = readSize;
            ret = send(peerfd, &t_file, 4 + t_file.len, 0);
            ERROR_CHECK(ret, -1, "filecontent send");
            totalSize += readSize;
        }   
    }

    return 0;
}
