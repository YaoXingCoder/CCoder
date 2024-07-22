/*************************************************************************
    > File Name: tcp_server_select.c
    > Author: JiaZiChunQiu
    > Created Time: 2024年07月20日 星期六 20时22分11秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 使用select多路复用实现随时能够发送消息
    > Content: 
    >   1.socket创建套接字 -> 创建IP地址结构体 -> bind绑定ip与套接字 -> listen转套接字为监听 -> send/recv 接发消息 -> close关闭套接字
    >   2.添加用户态缓冲, 分别用于接收消息, 发送消息
    >   3.初始化监听集合, 将 STDIN_FILENO, recv 加入监听集合
    >   4.使用循环初始化读就绪, 并反复接收 select 返回的读就绪集合
    >   5.注意阻塞点: accept, select, STDIN_FILENO, recv, send(写就绪, 一般不需要)
 ************************************************************************/

#include <my_header.h>
// socket
#include <sys/socket.h>
// struct sockaddr_in, inet_ntoa 
#include <arpa/inet.h>
#include <netinet/in.h>
// setsockopt
#include <sys/types.h>
// select
#include <sys/select.h>
// close
#include <unistd.h>

#define MAX_LISTEN 10
#define MAX_LINE 1024

int main (int argc, char* argv[]) {
    // 创建套接字
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    ERROR_CHECK(socketfd, -1, "socket");

    // 创建地址集合
    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    // serverAddr.sin_addr.s_addr = inet_addr("192.168.225.129");
    // printf("%s\n", inet_ntoa(serverAddr.sin_addr)); // 查看 INADDR_ANY 的点分十进制地址
    
    // setsockopt 设置为 TIME_WAIT 也可bind重复地址
    int on = 1;
    int ret = setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
    ERROR_CHECK(ret, -1, "setsockopt");

    // bind 绑定ip与socketfd
    ret = bind(socketfd,(struct sockaddr*)&serverAddr, sizeof(serverAddr));
    ERROR_CHECK(ret, -1, "bind");

    // listen 准换套接字为监听
    ret = listen(socketfd, MAX_LISTEN);
    ERROR_CHECK(ret, -1, "listen");

    // accept 全监听队列获取 连接
    int acceptfd = accept(socketfd, NULL, NULL);
    ERROR_CHECK(acceptfd, -1, "accept");
    printf("accept one client~~~~\n");

    // 创建用户态缓冲
    char sendLine[MAX_LINE] = { 0 };
    char recvLine[MAX_LINE] = { 0 };

    // 创建监听集合
    fd_set readSet;
    FD_ZERO(&readSet);
    FD_SET(STDIN_FILENO, &readSet);
    FD_SET(acceptfd, &readSet);
    int maxfd = STDIN_FILENO < acceptfd ? acceptfd : STDIN_FILENO;

    // 循环接发
    while(1) {
        // 重置监听集合
        fd_set backSet = readSet;

        // select 多路复用
        ret = select(maxfd + 1, &backSet, NULL, NULL, NULL);
        if ( ret == 0 ) { printf("overrunning time~~~\n"); }
        ERROR_CHECK(ret, -1, "select");

        // 标准输入读就绪
        if (FD_ISSET(STDIN_FILENO, &backSet)) {
            memset(sendLine, 0, MAX_LINE);
            int readNum = read(STDIN_FILENO, sendLine, MAX_LINE);
            if (readNum == 0) { break; }
            ERROR_CHECK(readNum, -1, "read");
            int sendNum = send(acceptfd, sendLine, readNum, 0);
            ERROR_CHECK(sendNum, -1, "send");
        }
        
        // recv套接字读就绪
        if (FD_ISSET(acceptfd, &backSet)) {
            memset(recvLine, 0, MAX_LINE);
            int recvNum = recv(acceptfd, recvLine, MAX_LINE, 0);
            if (recvNum == 0) { break; }
            ERROR_CHECK(recvNum, -1, "recv");
            printf("client %d said is %s", acceptfd, recvLine);
        }
    }

    // 关闭流
    close(acceptfd);
    close(socketfd);

    return 0;
}
