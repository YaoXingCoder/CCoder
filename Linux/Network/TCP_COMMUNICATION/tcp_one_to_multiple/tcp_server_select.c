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

    >   6.实现一对多的回复(回显服务), 用户发送消息, 服务器自动回复
    >   7.服务器能够同时对多个用户回复

    >   8.创建数组（下标对应文件描述符）存储客户端的accept套接字, 每次循环重置读就绪队列, 将数组中不为0的加入读就绪队列中
    >   9.将socket放入读就绪队列, 有客户端连接select, 就将accept返回值(对应数组下标)的数组值设置1
    >  10.发送接收消息, 先循环遍历数组不为零的值, 在对对应的套接字判断是否在读就绪集合, 是则对其回复和接收消息
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
#define MAX_CONNECTIONS 1000

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

    // 创建用户态缓冲
    // char sendLine[MAX_LINE] = { 0 };
    char recvLine[MAX_LINE] = { 0 };

    // 创建监听集合
    fd_set readSet;
    FD_ZERO(&readSet);
    FD_SET(socketfd, &readSet);
    int conns[MAX_CONNECTIONS] = {0}; // 存放已连接客户端套接字(accept返回值)

    // 循环接发
    while(1) {
        // 添加套接字到读就绪集合, 重置监听集合
        for(int i = 0; i < MAX_CONNECTIONS; i++) {
            if ( conns[i] ) { FD_SET(i, &readSet); }
        }
        fd_set backSet = readSet;

        // select 多路复用
        ret = select(MAX_CONNECTIONS + 1, &backSet, NULL, NULL, NULL);
        if ( ret == 0 ) { printf("overrunning time~~~\n"); }
        ERROR_CHECK(ret, -1, "select");

        // socketfd客户连接已就绪
        if (FD_ISSET(socketfd, &backSet)) {
            // accept 全监听队列获取 连接
            int acceptfd = accept(socketfd, NULL, NULL);
            ERROR_CHECK(acceptfd, -1, "accept");

            conns[acceptfd] = 1; // 数组对应下标的值设置为1
            printf("accept %d  client~~~~\n", acceptfd);
        }

        // 循环读取判断conns数组的值, 不为0则判断是否在集合中, 如果recv套接字读就绪
        for(int i = 0; i < MAX_CONNECTIONS; i++){
            if ( !conns[i] ) continue; // 为0略过

            if (FD_ISSET(i, &backSet)) {
                // 先给客户端发送消息
                int sendNum = send(i, "hello, client", 13, 0); 
                ERROR_CHECK(sendNum, -1, "send");
                
                // 接收客户端消息
                memset(recvLine, 0, MAX_LINE);
                int recvNum = recv(i, recvLine, MAX_LINE, 0);

                // 客户端关闭连接
                if (recvNum == 0) { 
                    conns[i] = 0;
                    printf("client %d said is closed\n", i);
                    close(i); // 关闭对应套接字
                    FD_CLR(i, &readSet); // 清除读就绪序列对应的套接字
                    break; 
                }

                ERROR_CHECK(recvNum, -1, "recv");
                printf("client %d said is %s", i, recvLine);
            }

        }
    }

    // 关闭套接字
    close(socketfd);

    return 0;
}
