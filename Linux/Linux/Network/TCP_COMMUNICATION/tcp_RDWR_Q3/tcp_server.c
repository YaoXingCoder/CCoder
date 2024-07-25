/*************************************************************************
    > File Name: tcp_server.c
    > Author: JiaZiChunQiu
    > Created Time: 2024年07月19日 星期五 21时25分52秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 创建服务器端, 开启Listen监听
    > Content:
    >   1.sokcet 获取套接字
    >   2.bind 绑定 ip+port 与 套接字
    >   3.listen 将套接字变为监听模式
    >   4.accept 从listen的全连接中取出下一个已完成的TCP连接
    >   5.send 将信息发送给从accept生成的相关联的客户端

    >   Q3: TCP粘包问题
 ************************************************************************/

#include <my_header.h>
// socket
#include <sys/socket.h>
// struct sockaddr_in
#include <arpa/inet.h>
// inet_aton
#include <netinet/in.h>
// send
#include <sys/types.h>
// close, read
#include <unistd.h>
// signal
#include <sys/signal.h>

#define MAX_LINE 1024

int main (int argc, char* argv[]) {
    // 让服务器进程直接忽略掉 SIGPIPE 信号
    signal(SIGPIPE, SIG_IGN); 

    // 创建套接字, 关联socket设备
    int socketfd =  socket(AF_INET, SOCK_STREAM, 0);
    if ( socketfd < 0) { error(1, errno, "socket"); }
    printf("socetfd is %d\n", socketfd);

    // 创建sockaddr, 指定类型, 端口, IP
    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET; // IPv4
    serverAddr.sin_port = htons(8080); // 端口
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // ip
    printf("serverAddr is %s:%d\n", inet_ntoa(serverAddr.sin_addr), ntohs(serverAddr.sin_port));

    // 通过bine, 绑定socketfd 与 ip+port 便于开启监听
    int ret = bind(socketfd, (const struct sockaddr*)&serverAddr, sizeof(serverAddr));
    ERROR_CHECK(ret, -1, "bind");

    // 打开监听
    ret = listen(socketfd, 2);
    ERROR_CHECK(ret, -1, "listen");

    // accept接收
    int acceptFd = accept(socketfd, NULL, NULL);
    ERROR_CHECK(acceptFd, -1, "acceptFd");
    printf("acceptFd is %d\n", acceptFd);

    // 读取, 用户态缓冲区数据
    char sendLine[MAX_LINE] = { 0 };
    printf("STDIN_FILENO is %d\n", STDIN_FILENO);
    ssize_t bytes = read(STDIN_FILENO, sendLine, MAX_LINE);
    printf("read %ld from STDIN_FILENO\n", bytes);
    
    // 发送第一次数据给client
    int countSend = 0;
    ret = send(acceptFd, sendLine, bytes - 1, 0);
    printf("%d times : send %d bytes to client\n", ++countSend, ret);
    ERROR_CHECK(ret, -1, "send");

    // 发送第二次数据
    bytes = read(STDIN_FILENO, sendLine, MAX_LINE);
    ret = send(acceptFd, sendLine, bytes - 1, 0);
    printf("%d times : send %d bytes to client\n", ++countSend, ret);
    ERROR_CHECK(ret, -1, "send2");

    // 关闭套接字
    close(acceptFd);
    close(socketfd);

    return 0;
}
