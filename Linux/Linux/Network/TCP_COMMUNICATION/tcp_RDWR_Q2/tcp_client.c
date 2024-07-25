/*************************************************************************
    > File Name: tcp_server.c
    > Author: JiaZiChunQiu
    > Created Time: 2024年07月19日 星期五 21时25分52秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 创建服务器端, 开启Listen监听
    > Content:
    >   1.sokcet 获取套接字
    >   2.创建strucet sockaddr_in, 填写需要连接的服务器ip:port
    >   3.connect 连接服务器, 服务器需要开启listen
    >   4.recv 接收服务端发送到的信息
 ************************************************************************/

#include <my_header.h>
// socket
#include <sys/socket.h>
// struct sockaddr_in
#include <arpa/inet.h>
// inet_aton
#include <netinet/in.h>
// recv
#include <sys/types.h>
// close
#include <unistd.h>

#define MAX_LINE 1024

int main (int argc, char* argv[]) {
    // 创建套接字, 关联socket设备
    int socketfd =  socket(AF_INET, SOCK_STREAM, 0);
    if ( socketfd < 0) { error(1, errno, "socket"); }
    printf("socketfd is %d", socketfd);

    // 创建sockaddr, 指定类型, 端口, IP
    struct sockaddr_in clientAddr;
    memset(&clientAddr, 0, sizeof(clientAddr));
    clientAddr.sin_family = AF_INET;
    clientAddr.sin_port = htons(8080); // 端口
    clientAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // ip
    printf("clientAddr is %s:%d\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));

    // connect 连接服务器
    int ret = connect(socketfd, (const struct sockaddr*)&clientAddr, sizeof(clientAddr));
    ERROR_CHECK(ret, -1, "connect");
    printf("connect success~~~\n");
    
    // 用户态缓冲
    char recvLine[1024] = { 0 };
    ssize_t bytes;
    int recvNums = 0;

    // 循环读取服务端信息, 服务器发送一次后关闭
    while(1){
        memset(recvLine, 0, MAX_LINE);
        bytes = recv(socketfd, recvLine, MAX_LINE, 0);
        ERROR_CHECK(bytes, -1, "recv");
        printf("%d times, recv %ld : server said %s\n", ++recvNums, bytes, recvLine);
        sleep(1);
    }

    close(socketfd);
    return 0;
}
