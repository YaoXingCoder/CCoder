/*************************************************************************
    > File Name: main.c
    > Author: JiaZiChunQiu
    > Created Time: 2024年07月29日 星期一 15时59分32秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 线程池入口
    > Content:
    >   1.创建线程, 启动线程
    >   2.初始化服务器, 监听读就绪
    >   3.有新客户端进入, 添加新客户端的套接字到就绪队列
    
    >   4.父进程用于关闭, 子进程监听放入任务到队列

 ************************************************************************/

#include "Thread_Pool.h"
#include <my_header.h>
#include <signal.h>

int exitPipe[2]; // 用于父子进程间通信

/* 信号处理函数 */
void handleSignal(int signum) {
    if ( signum == 10 ) {
        printf("sig %d is coming..\n", signum);
        int sig = -1;
        write(exitPipe[1], &sig, sizeof(sig));
    }
}
/* 线程池入口
 * 四个参数
 * ./main
 * ip
 * port
 * trd_num
 * */
int main (int argc, char* argv[]) {
    ARGS_CHECK(argc, 4);
    // signal(SIGPIPE, SIG_IGN); // 忽略管道关闭
    
    pipe(exitPipe);
    pid_t pid = fork();

    if (pid > 0) {
        close(exitPipe[0]);
        signal(SIGUSR1, handleSignal);
        wait(NULL);
        printf("parent process is exiting...\n");
        exit(0);
    }
    
    /* 子进程 */
    close(exitPipe[1]);

    /* 创建线程池  */
    ThreadPool tp;
    int trd_num = atoi(argv[3]);
    int ret = thread_pool_Init(&tp, trd_num);
    ERROR_CHECK(ret, -1, "thread_pool_Init");

    /* 启动  */
    ret = thread_pool_Start(&tp);
    ERROR_CHECK(ret, -1, "thread_pool_Start");

    /* 创建epoll结构并监听 */
    int epfd = epoll_create1(0);
    ERROR_CHECK(epfd, -1, "epoll_create1");

    /* 初始化服务器 */
    int listenfd = serverInit(argv[1], argv[2]);
    ERROR_CHECK(listenfd, -1, "serverInit");

    /* 添加读就绪事件 */
    ret = epoll_add_read_event(epfd, listenfd);
    ERROR_CHECK(ret, -1, "epoll_add_read_event");
    ret = epoll_add_read_event(epfd, exitPipe[0]);
    ERROR_CHECK(ret, -1, "epoll_add_read_event");

    /* 事件数组, 用于存储就绪队列 */
    struct epoll_event eventArr[MAX_EVENTS] = { 0 };
    int nready = 0;

    while(1) {
        nready = epoll_wait(epfd, eventArr, MAX_EVENTS, -1);
        if ( nready == 0 ) { printf("overrun time\n"); continue; }
        ERROR_CHECK(nready, -1, "epoll_wait");

        for(int i = 0; i < nready; ++i) {
            int netfd = eventArr[i].data.fd;
            // 新客户端连接
            if ( netfd == listenfd ) {
                struct sockaddr_in clientAddr;
                socklen_t len_clientAddr = sizeof(clientAddr);
                int peerfd = accept(netfd, (struct sockaddr*)&clientAddr, &len_clientAddr);
                ERROR_CHECK(peerfd, -1, "accept");
                printf("clientAddr'ip is %s:%d\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));

                ret = blockQ_Push(&tp.bq, peerfd);
                ERROR_CHECK(ret, -1, "blockQ_Push");

            } else if ( netfd == exitPipe[0] ) {
                int what = 0;
                ret = read(netfd, &what, sizeof(what));
                thread_pool_Close(&tp);
                printf("thread_pool exit.\n");
                goto end;
            } // 线程退出
        }
    }

end:
    free(tp.threads);
    close(epfd);
    close(listenfd);
    return 0;
}
