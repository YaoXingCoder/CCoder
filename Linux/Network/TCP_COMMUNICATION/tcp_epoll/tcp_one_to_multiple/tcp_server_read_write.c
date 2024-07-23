/*************************************************************************
    > File Name: tcp_server_select.c
    > Author: JiaZiChunQiu
    > Created Time: 2024年07月22日 星期一 23:14:30
    > Mail: JiaZiChunQiu@163.com
    > Title: 使用select多路复用实现随时能够发送消息
    > Content: 
    >   1.socket创建套接字 -> 创建IP地址结构体 -> bind绑定ip与套接字 -> listen转套接字为监听 -> send/recv 接发消息 -> close关闭套接字
    >   2.添加用户态缓冲, 分别用于接收消息, 发送消息
    >   3.初始化监听集合, 将 STDIN_FILENO, recv 加入监听集合
    >   4.使用循环初始化读就绪, 并反复接收 select 返回的读就绪集合
    >   5.注意阻塞点: accept, select, STDIN_FILENO, recv, send(写就绪, 一般不需要)

    >   6.实现一对多的回复(回显服务), 用户发送消息, 服务器自动回复
    >   7.服务器能够同时对多个用户回复

    >   8.注册epoll的文件描述符, 创建epoll_event结构体, 其中对应值为读事件和fd指向socketfd
    >   9.注册监听事件, 更新epfd中的红黑树, 传输socketfd和event结构体
    >   10.创建epoll_event数组在用户态, 用于epoll_wait传出就绪队列
    >   11.循环中使用epoll_wait持续监听事件, 有就绪队列则返回数量, 并循环遍历用户态的eventsArr结构体数组
    >   12.如果就绪队列中有==socketfd的值, 表示有新客户端连接, 需要判断并accept接收生成新的套接字, 放入epoll当中
    >   13.就绪队列中!=socketfd的为读/写事件, 判断后执行相应逻辑
    >   14.读就绪中如果客户端关闭, 则recv会持续读到0, 判断并执行epoll_ctl对红黑树更新, close关闭套接字
    
    >   15.加入写事件处理, 如果服务端没有要发送给客户端的数据, 直接更改其监听事件
 ************************************************************************/

#include <my_header.h>
// socket
#include <sys/socket.h>
// struct sockaddr_in, inet_ntoa 
#include <arpa/inet.h>
#include <netinet/in.h>
// setsockopt
#include <sys/types.h>
// epoll
#include <sys/epoll.h>
// close
#include <unistd.h>

#define MAX_EVENTS 100
#define MAX_LINE 1024

int main (int argc, char* argv[]) {
    // 创建套接字
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    ERROR_CHECK(socketfd, -1, "socket");
    printf("socketfd is %d\n", socketfd);

    // 创建地址集合
    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    // printf("%s\n", inet_ntoa(serverAddr.sin_addr)); // 查看 INADDR_ANY 的点分十进制地址
    
    // setsockopt 设置为 TIME_WAIT 也可bind重复地址
    int on = 1;
    int ret = setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
    ERROR_CHECK(ret, -1, "setsockopt");

    // bind 绑定ip与socketfd
    ret = bind(socketfd,(struct sockaddr*)&serverAddr, sizeof(serverAddr));
    ERROR_CHECK(ret, -1, "bind");

    // listen 准换套接字为监听
    ret = listen(socketfd, MAX_EVENTS);
    ERROR_CHECK(ret, -1, "listen");

    // 创建用户态缓冲
    // char sendLine[MAX_LINE] = { 0 };
    char recvLine[MAX_LINE] = { 0 };

    // 创建epoll文件描述符, 创建epoll_event结构体, 设置监听事件和监听的文件描述符
    int epfd = epoll_create1(0);
    ERROR_CHECK(epfd, -1, "epoll_create");
    printf("epfd is %d\n", epfd);

    struct epoll_event ev;
    memset(&ev, 0, sizeof(ev));
    ev.events = EPOLLIN; // 对socketfd的监听事件为读事件
    ev.data.fd = socketfd;

    // 注册监听事件
    ret = epoll_ctl(epfd, EPOLL_CTL_ADD, socketfd, &ev);
    ERROR_CHECK(ret, -1, "epoll_ctl");

    // 用户态, 创建epoll_event结构体数组, 接收epoll_wait返回的就绪队列
    struct epoll_event eventsArr[MAX_EVENTS] = {0};
    int nready = 0;

    // 循环接发
    while(1) {
        nready = epoll_wait(epfd, eventsArr, MAX_EVENTS, -1); // -1, 一直阻塞监听
        printf("nready %d is ready\n", nready);

        // wait将就绪队列添加到用户态对应事件数组eventsArr中, 遍历数组
        for(int i = 0; i < nready; ++i) {
            int rdfd = eventsArr[i].data.fd; // 获取带就绪队列中元素中的fd文件描述符

            // socketfd客户连接已就绪
            if (rdfd == socketfd) {

                // 记录client的地址
                struct sockaddr_in clientAddr;
                memset(&clientAddr, 0, sizeof(clientAddr));
                socklen_t len_clientAddr = sizeof(clientAddr);

                // accept从全连接队列获取新描述符, 并存储对应地址到clientAddr
                int acceptfd = accept(rdfd, (struct sockaddr*)&clientAddr, &len_clientAddr);
                ERROR_CHECK(acceptfd, -1, "accept");
                printf("accept is %d for client %s:%d has connected.\n",acceptfd, inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));

                // epoll 对 acceptfd 进行监听
                memset(&ev, 0, sizeof(ev));
                // ev.events = EPOLLIN;
                ev.events = EPOLLIN | EPOLLOUT; // 更改客户端的fd的监听事件为读|写事件
                ev.data.fd = acceptfd;
                ret = epoll_ctl(epfd, EPOLL_CTL_ADD, acceptfd, &ev);
                ERROR_CHECK(ret, -1, "acceptfd, epoll_ctl"); 

            }else {
                // 读事件就绪
                if (eventsArr[i].events & EPOLLIN ){
                    printf("handle Read events\n");
                    // 接收客户端消息
                    memset(recvLine, 0, MAX_LINE);
                    int recvNum = recv(rdfd, recvLine, MAX_LINE, 0);
                    ERROR_CHECK(recvNum, -1, "recv");

                    // 客户端关闭
                    if (recvNum == 0) {
                        ret = epoll_ctl(epfd, EPOLL_CTL_DEL, rdfd, NULL);
                        printf("client %d has closed\n", rdfd);
                        close(rdfd); // 关闭对应套接字
                        continue; // 继续下个就绪队列的事件
                    }

                    // 给客户端回显消息
                    int sendNum = send(rdfd, recvLine, recvNum, 0); 
                    ERROR_CHECK(sendNum, -1, "send");

                    printf("client %d said is %s", rdfd, recvLine);
                }

                // 写事件就绪
                if (eventsArr[i].events & EPOLLOUT ){
                    printf("handle Write event\n"); // 处理写事件
                    // 如果不需要触发写事件, 服务端无数据发送给客户端
                    // 更改套接字的事件属性, 删除掉写事件的触发
                    ev.events = EPOLLIN;
                    ev.data.fd = rdfd;
                    ret = epoll_ctl(epfd, EPOLL_CTL_MOD, rdfd, &ev);
                    ERROR_CHECK(ret, -1, "rdfd epoll_ctl");
                }

            } // accept 获取的连接, 读取数据
        }
    }

    // 关闭套接字
    close(socketfd);

    return 0;
}
