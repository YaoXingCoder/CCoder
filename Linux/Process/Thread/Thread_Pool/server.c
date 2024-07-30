/*************************************************************************
    > File Name: server.c
    > Author: JiaZiChunQiu
    > Created Time: 2024年07月29日 星期一 16时53分34秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 服务器初始化
    > Content:
    >   1.绑定ip和端口
    >   2.添加套接字到epoll
 ************************************************************************/

#include "Thread_Pool.h"
#include <sys/epoll.h>

/* 服务端监听初始化
 * ip
 * port
 * */
int serverInit(const char* ip, const char* port) {
    unsigned short nport = atoi(port);
    
    int listenfd = socket(AF_INET, SOCK_STREAM, 0); // 套接字创建
    if ( listenfd == -1 ) {
        perror("server serverInit socket");
        return -1;
    }

    /* 设置地址端口可重复使用 */
    int on = 1;
    int ret = setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
    if (ret == -1) {
        perror("server.c serverInit setsockopt\n");
        return -1;
    }

    /* 地址结构体 */
    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(nport);
    serverAddr.sin_addr.s_addr = inet_addr(ip);
    printf("serverAddr's ip:port is %s:%d\n", inet_ntoa(serverAddr.sin_addr), ntohs(serverAddr.sin_port));

    /* bind绑定 */
    ret = bind(listenfd, &serverAddr, sizeof(serverAddr));
    if ( ret == -1 ) {
        perror("server.c serverInit bind\n");
        return -1;
    }

    ret = listen(listenfd, MAX_EVENTS);
    if ( ret == -1 ) { 
        perror("server.c serverInit listen\n");
        return -1;
    }
    
    return listenfd;
}


/* 添加读就绪到epoll */
int epoll_add_read_event(const int epfd, const int netfd) {
    struct epoll_event ev;
    memset(&ev, 0, sizeof(ev));
    ev.events = EPOLLIN;
    ev.data.fd = netfd;
    int ret = epoll_ctl(epfd, EPOLL_CTL_ADD, netfd, &ev);
    if (ret == -1) {
        perror("server.c epoll_add_read_event epoll_ctl\n");
        return -1;
    }
    return 0;
}

/* 删除读就绪从epool */
int epoll_del_read_event(const int epfd, const int netfd) {
    struct epoll_event ev;
    memset(&ev, 0, sizeof(ev));
    ev.events = EPOLLIN;
    ev.data.fd = netfd;
    int ret = epoll_ctl(epfd, EPOLL_CTL_DEL, netfd, &ev);
    if (ret == -1) {
        perror("server.c epoll_del_read_event epoll_ctl\n");
        return -1;
    }
    return 0;
}

