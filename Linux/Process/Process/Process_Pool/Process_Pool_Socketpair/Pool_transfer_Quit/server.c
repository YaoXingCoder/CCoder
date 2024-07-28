/*************************************************************************
    > File Name: server.c
    > Author: JiaZiChunQiu
    > Created Time: 2024年07月26日 星期五 00时02分47秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 服务器
    > Content:
 ************************************************************************/

#include "process_pool.h"
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>

int tcpInit(const char* ip, const unsigned short port){
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    ERROR_CHECK(listenfd, -1, "socket");

    // 设置地址可关闭后开启, 重复使用
    int on = 1;
    int ret = setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
    ERROR_CHECK(ret, -1, "setsockopt");

    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = inet_addr(ip);
    printf("server's ip is %s:%d\n", inet_ntoa(serverAddr.sin_addr), ntohs(serverAddr.sin_port));

    ret = bind(listenfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    ERROR_CHECK(ret, -1, "bind");

    ret = listen(listenfd, 1);
    ERROR_CHECK(ret, -1, "listen");

    return listenfd;
}

int epollAddReadEvent(int epfd, int fd) {
    struct epoll_event ev;
    memset(&ev, 0, sizeof(ev));
    ev.data.fd = fd;
    ev.events = EPOLLIN;
    int ret = epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &ev);
    ERROR_CHECK(ret, -1, "ADD epoll_ctl");
    return 0;
}

int epollDelReadEvent(int epfd, int fd) {
    struct epoll_event ev;
    memset(&ev, 0, sizeof(ev));
    ev.data.fd = fd;
    ev.events = EPOLLIN;
    int ret = epoll_ctl(epfd, EPOLL_CTL_DEL, fd, &ev);
    ERROR_CHECK(ret, -1, "DEL epoll_ctl");
    return 0;
}
