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
#include <string.h>

#define FILE_NAME "small_file.txt"

int transferFile(int peerfd) {
    // 打开需要文件, 读
    int fd = open(FILE_NAME, O_RDONLY);
    ERROR_CHECK(fd, -1, "open");
    
    // 读取文件
    char buff[FILE_SMALL] = { 0 };
    int len_read = read(fd, buff, FILE_SMALL);
    ERROR_CHECK(len_read, -1, "read");

    // 发送文件名
    train_t st_file;
    memset(&st_file, 0, sizeof(st_file));
    st_file.len = strlen(FILE_NAME);
    strcpy(st_file.buff, FILE_NAME);
    int ret = send(peerfd, &st_file, 4 + st_file.len, 0);
    ERROR_CHECK(ret, -1, "send");

    // 发送文件内容
    memset(&st_file, 0, sizeof(st_file));
    st_file.len = len_read;
    strncpy(st_file.buff, buff, len_read);
    ret = send(peerfd, &st_file, 4 + st_file.len, 0);
    ERROR_CHECK(ret, -1, "send");

    return 0;
}
