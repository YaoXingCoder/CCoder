/*************************************************************************
    > File Name: udp_client.c
    > Author: JiaZiChunQiu
    > Created Time: 2024年07月24日 星期三 20时42分15秒
    > Mail: JiaZiChunQiu@163.com
    > Title: udp的客户端
    > Content: 
    >   1.
 ************************************************************************/

#include <my_header.h>
// socket, sendto, recvfrom, bind
#include <sys/types.h>
#include <sys/socket.h>
// struct sockaddr_in
#include <arpa/inet.h>
// epoll
#include <sys/select.h>
// close
#include <unistd.h>

#define MAX_LINE 1024
#define MAX_EVENTS 100

int main (int argc, char* argv[]) {
    // 套接字
    int clientfd = socket(AF_INET, SOCK_DGRAM, 0);
    ERROR_CHECK(clientfd, -1, "socket");
    
    // 地址
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    socklen_t len_serverAddr = sizeof(serverAddr);
    printf("serverAddr is %s:%d \n", inet_ntoa(serverAddr.sin_addr), ntohs(serverAddr.sin_port));

    // 缓冲
    char recvBuff[MAX_LINE] = { 0 };
    char sendBuff[MAX_LINE] = { 0 };

    // 先发送建立连接
    int ret = sendto(clientfd, "hello server", 12, 0, (struct sockaddr*)&serverAddr, len_serverAddr);
    ERROR_CHECK(ret, -1, "sendto");

    // 读就绪监听集合
    fd_set readSet;
    FD_ZERO(&readSet);
    FD_SET(STDIN_FILENO, &readSet);
    FD_SET(clientfd, &readSet);
    int maxfd = clientfd;

    while(1) {
        fd_set backSet = readSet;
        ret = select(maxfd + 1, &backSet, NULL, NULL, NULL);
        ERROR_CHECK(ret, -1, "select");

        if (FD_ISSET(STDIN_FILENO, &backSet)) {
            memset(sendBuff, 0, MAX_LINE);
            ssize_t readNum = read(STDIN_FILENO, sendBuff, MAX_LINE);
            ERROR_CHECK(readNum, -1, "read");
            ssize_t sendNum = sendto(clientfd, sendBuff, readNum - 1, 0, (struct sockaddr*)&serverAddr, len_serverAddr);
            ERROR_CHECK(sendNum, -1, "sendto");
        }else if (FD_ISSET(clientfd, &backSet)) {
            memset(recvBuff, 0, MAX_LINE);
            ssize_t recvNum = recvfrom(clientfd, recvBuff, MAX_LINE, 0, (struct sockaddr*)&serverAddr, &len_serverAddr);
            if ( recvNum == 0 ) { break; }
            ERROR_CHECK(recvNum, -1, "recvfrom");
            printf("server said is %s\n", recvBuff);
        }
    }

    close(clientfd);
    return 0;
}
