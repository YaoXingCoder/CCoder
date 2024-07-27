/*************************************************************************
    > File Name: tcp_server_select.c
    > Author: JiaZiChunQiu
    > Created Time: 2024年07月24日 星期三 23.58，42
    > Mail: JiaZiChunQiu@163.com
    > Title: HTTP
    > Content: 
    >   1.接收请求
    >   2.响应请求
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
#define MAX_LINE 4096

int main (int argc, char* argv[]) {
    // 创建套接字
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    ERROR_CHECK(socketfd, -1, "socket");

    // 创建地址集合
    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    serverAddr.sin_addr.s_addr = inet_addr("192.168.225.129");
    printf("serverAddr is %s:%d\n", inet_ntoa(serverAddr.sin_addr), ntohs(serverAddr.sin_port));

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

    while(1) {
        // 接收请求数据
        int peerfd = accept(socketfd, NULL, NULL);
        int recvNum = recv(peerfd, recvLine, MAX_LINE, 0);
        printf("recvNum is %d\n", recvNum);
        printf("\n%s\n", recvLine);

        // 发送响应数据
        // 消息体
        char responseBuff[MAX_LINE] = { 0 };
        const char* responseLine = "HTTP/1.1 200 OK\r\n";
        const char* responseHead = "Server: MyHttpServer/1.0\r\n"
            "Connection: keep-alive\r\n"
            "Content-type: text/html\r\n"
            "Content-Length:";
        const char* emptyLine = "\r\n";
        const char* responseBody = "<h1>This is h1!</h1>";

        // 拼接
        sprintf(responseBuff, "%s%s%ld\r\n%s%s",
                responseLine,
                responseHead,
                strlen(responseBody),
                emptyLine,
                responseBody);
        send(peerfd, responseBuff, strlen(responseBuff), 0);

    }

    close(socketfd);

    return 0;
}

