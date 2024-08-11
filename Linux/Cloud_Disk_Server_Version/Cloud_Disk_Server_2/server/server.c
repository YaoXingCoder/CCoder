/*************************************************************************
    > File Name: server.c
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月04日 星期日 17时39分14秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 服务端的初始化和创建
    > Content:
    >   1.TCPINIT 服务器初始化
    >   2.delEpollReadfd 删除读就绪监听
    >   3.addEpollReadfd 添加读就绪监听
    >   4.recvn 指定数据量优化
    >   5.sendn 指定数据量优化
 ************************************************************************/

#include "thread_pool.h"

/* 服务器初始化 */
int tcpInit(const char* ip, const char* port){
    int nport = atoi(port);

    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if ( listenfd < 0 ) {
        perror("socket");
        return -1;
    }

    int on = 1;
    int ret = setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
    if ( ret < 0 ) {
        perror("setsockopt");
        close(listenfd);
        return -1;
    }

    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(nport);
    serverAddr.sin_addr.s_addr = inet_addr(ip);
    printf("serverAddr'address is %s:%d\n", inet_ntoa(serverAddr.sin_addr), ntohs(serverAddr.sin_port));
    
    ret = bind(listenfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    if ( ret < 0 ) {
        perror("bind");
        close(listenfd);
        return -1;
    }

    ret = listen(listenfd, 10);
    if ( ret < 0 ) {
        perror("listen");
        close(listenfd);
        return -1;
    }

    printf("server starts listening.\n");
    return listenfd;
}

/* 添加监听 */
int addEpollReadfd(int epfd, int sockfd) {
    struct epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.fd = sockfd;
    int ret = epoll_ctl(epfd, EPOLL_CTL_ADD, sockfd, &ev);
    ERROR_CHECK(ret, -1, "epoll_ctl");
    return 0;
}

/* 删除读就绪监听 */
int delEpollReadfd(int epfd, int sockfd){
    struct epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.fd = sockfd;
    int ret = epoll_ctl(epfd, EPOLL_CTL_DEL, sockfd, &ev);
    ERROR_CHECK(ret, -1, "epoll_ctl");
    return 0;
}

/* 确定发送的字节数 */
int sendn(int sockfd, const void* buff, int len){
    int left = len;
    const char* pbuf = buff;
    int ret = 0;
    while ( left > 0 ) {
        ret = send(sockfd, pbuf, left, 0);
        if (ret < 0) {
            perror("send");
            return -1;
        }
        left -= ret;
        pbuf += ret;
    }
    return len - left;
}

int recvn(int sockfd, void* buff, int len){
    int left = len;
    char* pbuf  = buff;
    int ret = 0;
    while(left > 0) {
        ret = recv(sockfd, pbuf, left, 0);
        if ( ret == 0 ) { break; }
        else if ( ret < 0 ) {
            perror("recv");
            return -1;
        }
        left -= ret;
        pbuf += ret;
    }
    return len- left;
}
