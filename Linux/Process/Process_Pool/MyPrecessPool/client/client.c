/*************************************************************************
    > File Name: client.c
    > Author: JiaZiChunQiu
    > Created Time: 2024年07月29日 星期一 07时53分46秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 创建客户端
    > Content:
 ************************************************************************/

#include "../process_pool.h"

#define EVENT_READY 1
#define BUFF_SIZE 1024

int main (int argc, char* argv[]) {
    /* 创建套接字  */
    int clientfd = socket(AF_INET, SOCK_STREAM, 0);
    ERROR_CHECK(clientfd, -1, "socket");

    /* 服务端地址  */
    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    serverAddr.sin_addr.s_addr = inet_addr("192.168.225.129");
    printf("server ip address is %s:%d\n", inet_ntoa(serverAddr.sin_addr), ntohs(serverAddr.sin_port));

    /* 连接服务端 */
    int ret = connect(clientfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    ERROR_CHECK(ret, -1, "connect");

    /* 创建epoll, 监听读 */
    int epfd = epoll_create1(0);
    ERROR_CHECK(epfd, -1, "epoll_create1");
    struct epoll_event ev;
    memset(&ev, 0, sizeof(ev));
    ev.events = EPOLLIN;
    ev.data.fd = clientfd;
    ret = epoll_ctl(epfd, EPOLL_CTL_ADD, clientfd, &ev);
    ERROR_CHECK(ret, -1, "epoll_ctl");

    /* 创建epoll_event数组, 接收就绪队列 */
    struct epoll_event eventArr[EVENT_READY] = { 0 };
    int nready = 0;
    char buff[BUFF_SIZE] = {0}; // 用户态缓冲区

    /* 循环监听 */
    while(1) {
        nready = epoll_wait(epfd, eventArr, EVENT_READY, -1);
        if ( nready == 0 ) { printf("overrun time\n"); continue; }

        for(int i = 0; i < nready; ++i) {
            int netfd = eventArr[i].data.fd;
            if ( netfd == clientfd ) {
                int recvNum = recv(clientfd, buff, BUFF_SIZE, 0);
                if ( recvNum == 0 ) { printf("server is closed\n");  goto end; }
                ERROR_CHECK(recvNum, -1, "recv");
                printf("server send msg %s\n", buff);
            }
        }
    }
end:
    close(epfd);
    close(clientfd);
    return 0;
}
