/*************************************************************************
    > File Name: tcp_server_select.c
    > Author: JiaZiChunQiu
    > Created Time: 2024年07月25日 星期四 19:38:21
    > Mail: JiaZiChunQiu@163.com
    > Title: HTTP
    > Content: 
    >   1.接收请求
    >   2.响应请求
    >   3.响应发送图片, 先读取图片文件信息, 再将图片发送给客户端
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
// open
#include <sys/stat.h>
#include <fcntl.h>

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

    // 读取图片数据
    int imgfd = open("img.jpg", O_RDONLY);
    ERROR_CHECK(imgfd, -1, "open");
    struct stat st_img;
    memset(&st_img, 0, sizeof(st_img));
    fstat(imgfd, &st_img);
    printf("img size is %ld\n", st_img.st_size);
    char* img_buff = calloc(1, st_img.st_size);
    ret = read(imgfd, img_buff, st_img.st_size);

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
            "Content-type: image/jgp\r\n"
            "Content-Length:";
        const char* emptyLine = "\r\n";

        // 拼接
        sprintf(responseBuff, "%s%s%ld\r\n%s",
                responseLine,
                responseHead,
                st_img.st_size,
                emptyLine);
        send(peerfd, responseBuff, strlen(responseBuff), 0);
        
        int total = 0;
        ret = 0;
        while(total < st_img.st_size) {
            ret = send(peerfd, img_buff + total, st_img.st_size - total, 0);
            total += ret;
        }
        free(img_buff);
        close(imgfd);

    }

    close(socketfd);

    return 0;
}

