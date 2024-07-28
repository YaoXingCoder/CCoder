/*************************************************************************
    > File Name: client.c
    > Author: JiaZiChunQiu
    > Created Time: 2024年07月26日 星期五 19时56分58秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 客户端实现
    > Content: 
 ************************************************************************/

#include "process_pool.h"
#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>

#define MAX_BUFF 1024


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
    char buff[MAX_BUFF] = { 0 };

    // 监听
    fd_set readSet;
    FD_ZERO(&readSet);
    FD_SET(clientfd, &readSet);
    FD_SET(STDIN_FILENO, &readSet);
    int maxfd = clientfd;

    while(1) {
        fd_set backSet = readSet;
        ret = select(maxfd+1, &backSet, NULL, NULL, NULL);
        ERROR_CHECK(ret, -1, "select");
        sleep (5);
        // 标准输入就绪
        if (FD_ISSET(STDIN_FILENO, &backSet)) {
            memset(buff, 0, MAX_BUFF);
            int readNum = read(STDIN_FILENO, buff, MAX_BUFF);
            ERROR_CHECK(readNum, -1, "read");
            
            ret = send(clientfd, buff, readNum, 0);
            printf("client you has writed is %s\n", buff);
            ERROR_CHECK(ret, -1, "send");
        }

        // 套接字就绪
        if (FD_ISSET(clientfd, &backSet)) {
            memset(buff, 0, MAX_BUFF);
            ret = recv(clientfd, buff, MAX_BUFF, 0);
            // if (ret == 0) { break; }
            ERROR_CHECK(ret, -1, "recv");
            printf("server said to client is %s\n", buff);
        }
    }

    close(clientfd);
    return 0;
}
