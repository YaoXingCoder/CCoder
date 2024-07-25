/*************************************************************************
    > File Name: udp_server.c
    > Author: JiaZiChunQiu
    > Created Time: 2024年07月24日 星期三 17时31分49秒
    > Mail: JiaZiChunQiu@163.com
    > Title: udp通信服务端
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
#include <sys/epoll.h>

// close
#include <unistd.h>

#define MAX_LINE 1024
#define MAX_EVENTS 100

int main (int argc, char* argv[]) {
    // socketfd
    int serverfd = socket(AF_INET, SOCK_DGRAM, 0);
    ERROR_CHECK(serverfd, -1, "sock");

    // 地址结构体
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    printf("serverAddr is %s:%d \n", inet_ntoa(serverAddr.sin_addr), ntohs(serverAddr.sin_port));

    // bind
    int ret = bind(serverfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    ERROR_CHECK(ret, -1, "bind");

    // 接收缓冲区
    char recvBuff[MAX_LINE] = { 0 };
    char sendBuff[MAX_LINE] = { 0 };

    // recvfrom, 主要用于接收用户地址
    struct sockaddr_in clientAddr;
    socklen_t len_clientAddr = sizeof(clientAddr);
    ssize_t recvNum = recvfrom(serverfd, recvBuff, MAX_LINE, 0, (struct sockaddr*)&clientAddr, &len_clientAddr);
    ERROR_CHECK(recvNum, -1, "recvfrom");
    printf("The first client said is %s\n", recvBuff);
    printf("clientAddr is %s:%d \n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));

    // epoll
    int epfd = epoll_create1(0);
    ERROR_CHECK(epfd, -1, "epoll_create");
    struct epoll_event ev;
    ev.data.fd = serverfd;
    ev.events = EPOLLIN;
    ret = epoll_ctl(epfd, EPOLL_CTL_ADD, serverfd, &ev);
    ERROR_CHECK(ret, -1, "serverfd epoll_ctl");
    ev.data.fd = STDIN_FILENO;
    ev.events = EPOLLIN;
    ret = epoll_ctl(epfd, EPOLL_CTL_ADD, STDIN_FILENO, &ev);
    ERROR_CHECK(ret, -1, "STDIN_FILENO epoll_ctl");

    // event数组
    struct epoll_event eventArr[MAX_EVENTS] = { 0 };
    int nready = 0;

    while(1) {
        nready = epoll_wait(epfd, eventArr, MAX_EVENTS, 0);
        ERROR_CHECK(nready, -1, "epoll_wait");

        for ( int i = 0; i < nready; ++i) {
            if ( eventArr[i].events & EPOLLIN ) {
                if (eventArr[i].data.fd == STDIN_FILENO) {
                    memset(sendBuff, 0, MAX_LINE);
                    ssize_t readNum = read(STDIN_FILENO, sendBuff, MAX_LINE);
                    ERROR_CHECK(readNum, -1, "read");
                    ssize_t sendNum = sendto(serverfd, sendBuff, readNum - 1, 0, (struct sockaddr*)&clientAddr, len_clientAddr);
                    ERROR_CHECK(sendNum, -1, "sendto");
                } else if (eventArr[i].data.fd == serverfd) {
                    memset(recvBuff, 0, MAX_LINE);
                    recvNum = recvfrom(eventArr[i].data.fd, recvBuff, MAX_LINE, 0, (struct sockaddr*)&clientAddr, &len_clientAddr);
                    if ( recvNum == 0 ) { goto end; }
                    ERROR_CHECK(recvNum, -1, "recvfrom");
                    printf("client said is %s\n", recvBuff);
                }
            }
        }
    }

end:
    close(serverfd);
    return 0;

}
