/*************************************************************************
    > File Name: main.c
    > Author: JiaZiChunQiu
    > Created Time: 2024年07月25日 星期四 23时11分46秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 进程池主函数
    > Content:
 ************************************************************************/

#include "process_pool.h"

/* 传入 IP, PORT, 要创建进程数  */
int main (int argc, char* argv[]) {
    ARGS_CHECK(argc, 4);

    // 开辟堆空间存放进程
    int processNum = atoi(argv[3]);
    PROCESS_DATA* pProcess = (PROCESS_DATA*)calloc(processNum, sizeof(PROCESS_DATA));
    
    // 创建argv[4]个进程
    mkProcess(pProcess, processNum);

    // 创建监听服务器
    int listenfd = tcpInit(argv[1], atoi(argv[2]));

    // 创建epoll
    int epfd = epoll_create1(0);
    ERROR_CHECK(epfd, -1, "epoll_create1");
    
    // epoll添加监听到读事件
    epollAddReadEvent(epfd, listenfd);

    // epoll监听socketpair生成的父子进程通信的管道
    for( int i = 0; i < processNum; ++i ) {
        epollAddReadEvent(epfd, pProcess[i].pipefd); // 监听的父进程与子进程的管道
    }

    // 就绪的读事件数组
    struct epoll_event eventArr[10] = { 0 };
    int nready = 0;

    while(1){
        nready = epoll_wait(epfd, eventArr, sizeof(eventArr), 0);
        ERROR_CHECK(nready, -1, "epoll_wait");
        for( int i = 0; i < nready; ++i ) {
            int fd = eventArr[i].data.fd; // 就绪事件的套接字

            // 新用户
            if ( fd == listenfd ) {
                // 接收并记录新客户端地址
                struct sockaddr_in clientAddr;
                socklen_t len_clientAddr = sizeof(clientAddr);
                int peerfd = accept(listenfd, (struct sockaddr*)&clientAddr, &len_clientAddr);
                ERROR_CHECK(peerfd, -1, "accept");
                printf("new client address is %s:%d\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));
                
                // 将peerfd发给空闲的子线程
                for ( int j = 0; j < processNum; ++i ) {
                    if(pProcess[j].status == FREE) {
                        sendFd(pProcess[j].pipefd, peerfd);
                        pProcess[j].status = BUSY;
                        break;
                    }
                }
                close(peerfd); // 断开父进程对于客户端的连接, 便于子进程断开后, 关闭套接字
            
            } else {
                int howmany = 0;
                int ret = read(fd, &howmany, sizeof(howmany)); // 读取子进程结束后, 写入管道的信号
                ERROR_CHECK(ret, -1, "howmany read");

                for( int j = 0; j < processNum; ++j ) {
                    if (pProcess[j].pipefd == fd) {
                        pProcess[j].status = FREE;
                        printf("subProcess %d is free\n", pProcess[j].pid);
                        break;
                    }
                }
            }
        }
    }

    close(listenfd);
    close(epfd);
    return 0;
}
