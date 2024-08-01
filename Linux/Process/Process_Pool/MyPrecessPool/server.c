/*************************************************************************
    > File Name: server.c
    > Author: JiaZiChunQiu
    > Created Time: 2024年07月28日 星期日 22时17分07秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 服务端接口相关
    > Content:
    >   1.初始化tcp连接
 ************************************************************************/

#include "process_pool.h"

/* 使进程与主机的ip端口绑定
 * 参数 
 * ip: 主机ip
 * port: 监听端口号
 *
 * 返回值: 创建的socket套接字
 * */
int serverInit(const char* ip, const char* port) {
    unsigned short nport = atoi(port);

    int listenfd = socket(AF_INET, SOCK_STREAM, 0); // 创建套接字
    if ( listenfd == -1 ) {
        perror("server serverInit socket\n");
        return -1;
    }

    int on = 1;
    int ret = setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)); // 设置服务器地址可以重用
    if ( ret == -1 ) {
        perror("server serverInit setsockopt\n");
        return -1;
    }
    
    /* 记录服务ip和port  */
    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(nport);
    serverAddr.sin_addr.s_addr = inet_addr(ip);
    printf("serverAddr is %s:%d\n", ip, nport);

    ret = bind(listenfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)); // 绑定进程与ip
    if ( ret == -1 ) {
        perror("server serverInit bind\n");
        return -1;
    }

    ret = listen(listenfd, 1); // 设置该套接字为监听套接字
    if ( ret == -1 ) {
        perror("server serverInit listen");
        return -1;
    }

    return listenfd;
}

/*
 * 添加指定读监听到epoll中
 */
int epoll_add_read_event(const int epfd, const int netfd) {
    struct epoll_event ev;
    memset(&ev, 0, sizeof(ev));
    ev.events = EPOLLIN;
    ev.data.fd = netfd;
    int ret = epoll_ctl(epfd, EPOLL_CTL_ADD, netfd, &ev);
    if ( ret == -1 ) {
        perror("server epoll_add_read_event epoll_ctl");
        return -1;
    }
    // printf("The fd is %d add in epoll\n", netfd);
    return 0;
}

/*
 * 删除指定都监听到epoll中
 */
int epoll_del_read_event(const int epfd, const int netfd) {
    struct epoll_event ev;
    memset(&ev, 0, sizeof(ev));
    ev.events = EPOLLIN;
    ev.data.fd = netfd;
    int ret = epoll_ctl(epfd, EPOLL_CTL_DEL, netfd, &ev);
    if ( ret == -1 ) {
        perror("server epoll_add_read_event epoll_ctl");
        return -1;
    }
    return 0;

}

