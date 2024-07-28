/*************************************************************************
    > File Name: client.c
    > Author: JiaZiChunQiu
    > Created Time: 2024年07月26日 星期五 19时56分58秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 客户端实现
    > Content:  接收服务端用户传输的文件
    >   1.并创建文件输出
 ************************************************************************/

#include "../process_pool.h"
#include <bits/types/stack_t.h>
#include <dirent.h>
#include <endian.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>

int main (int argc, char* argv[]) {
    // 创建socket套接字
    int clientfd = socket(AF_INET, SOCK_STREAM, 0);
    ERROR_CHECK(clientfd, -1, "socket");
    
    // 地址
    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    serverAddr.sin_addr.s_addr = inet_addr("192.168.225.129");
    printf("client request server's ip is %s:%d\n", inet_ntoa(serverAddr.sin_addr), ntohs(serverAddr.sin_port));

    // connect 连接服务器
    int ret = connect(clientfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    ERROR_CHECK(ret, -1, "connect");
    printf("client is connected server\n");

    // 用户态数据缓冲
    train_t st_file;

    // 先接受文件名字
    memset(&st_file, 0, sizeof(st_file));
    ret = recv(clientfd, &st_file, sizeof(st_file), 0);
    ERROR_CHECK(ret, -1, "recv");
    printf("the size of filename is %d\n", st_file.len);
    printf("filename is %s\n", st_file.buff);

    int fd = open(st_file.buff, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    ERROR_CHECK(fd, -1, "open");

    // 接收文件内容
    memset(&st_file, 0, sizeof(st_file));
    ret = recv(clientfd, &st_file, sizeof(st_file), 0);
    ERROR_CHECK(ret, -1, "recv");
    int writeNum = write(fd, st_file.buff, st_file.len);
    ERROR_CHECK(writeNum, -1, "write");
    printf("the size of file is %d\n", st_file.len);

    return 0;
}
