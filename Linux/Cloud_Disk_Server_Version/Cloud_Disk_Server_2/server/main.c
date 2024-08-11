/*************************************************************************
    > File Name: main.c
    > Author: JiaZiChunQiu
    > Created Time: 2024年08月04日 星期日 15时28分42秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 主函数, 服务器启动入口
    >   1.读取配置文件
    >   2.父子进程通信
    >   3.父进程监听信号, 关闭子进程
    >   4.子进程监听读就绪, 分配任务
 ************************************************************************/

#include "config.h"
#include "thread_pool.h"
#include "user.h"
#include "linked_list.h"

#define EPOLL_ARR_SIZE 100

/* 全局变量 */
int exitPipe[2];
ListNode* userList = NULL; 
DB_CONN_POOL* dcp = NULL; /* 数据库连接池 */

void sigHandler(int signum) {
    printf("\n signal terminate is coming\n");
    int one = 1;
    write(exitPipe[1], &one, sizeof(one));
}

/* 启动时两个参数 ./main, conf*/
int main (int argc, char* argv[]) {
    signal(EAGAIN, SIG_IGN);
    signal(EINTR, SIG_IGN);
    ARGS_CHECK(argc, 2); // 参数判断    
    pipe(exitPipe); // 信号用管道

    /* 子进程创建 */
    pid_t pid = fork();

    /* 
     * 父进程
     */
    if ( pid > 0 ) {
        printf("subProcess id is %d\n", pid);
        close(exitPipe[0]);
        signal(SIGUSR1, sigHandler);
        wait(NULL);
        close(exitPipe[1]);
        printf("\nparent process exit.\n");
        exit(0);
    }

    /*
     * 子进程
     */
    close(exitPipe[1]);
    printf("subprocess pid is %d\n", pid);

    /* 读取配置文件 */
    HashTable ht;
    initHashTable(&ht); // 初始化
    readConfig(argv[1], &ht); // 读取配置
    // printHashTable(&ht);

    /* 创建, 初始化子线程 */
    threadpool_t tp;
    memset(&tp, 0, sizeof(threadpool_t));
    threadpoolInit(&tp, atoi((const char*)find(&ht, THREAD_NUM)));
    threadpoolStart(&tp);

    /* 创建 并 启动数据库连接池 */
    dcp = db_pool_create(3, "127.0.0.1", "3306", "mydb", "root", "123456");

    /* 创建监听套接字 */
    int listenfd = tcpInit((const char*)find(&ht, IP), (const char*)find(&ht, PORT));
    ERROR_CHECK(listenfd, -1, "tcpInit");

    /* 添加读就绪监听 */
    int epfd = epoll_create1(0);
    ERROR_CHECK(epfd, -1, "epoll_create");
    int ret = addEpollReadfd(epfd, exitPipe[0]); // 父子进程间通道间监听
    ERROR_CHECK(ret, -1, "addEpollReadfd exitPipe");
    ret = addEpollReadfd(epfd, listenfd);
    ERROR_CHECK(ret, -1, "addEpollReadfd listenfd");

    /* 创建epoll监听集合, 存取读就绪监听 */
    struct epoll_event* pEventArr = (struct epoll_event*)calloc(EPOLL_ARR_SIZE, sizeof(struct epoll_event)); // 堆地址存放
    
    while(1) {
        int nready = epoll_wait(epfd, pEventArr, EPOLL_ARR_SIZE, -1);
        /* printf("nready is %d\n", nready); */
        if (nready == -1 && errno == EINTR) { continue; }
        else if (nready == -1) { ERROR_CHECK(nready, -1, "epoll_wait"); }
        else {
            for( int i = 0; i < nready; ++i ) {
                int fd = pEventArr[i].data.fd;
                /* 客户端连接 */
                if ( fd == listenfd ){
                    struct sockaddr_in clientAddr;
                    socklen_t len_clientAddr = sizeof(clientAddr);
                    int peerfd = accept(fd, (struct sockaddr*)&clientAddr, &len_clientAddr);
                    printf("\nconn %d has connected.\n", peerfd);

                    // 添加新节点到epoll红黑树
                    addEpollReadfd(epfd, peerfd); // 与用户实时通信

                    // 添加新用户节点
                    user_info_t* user = (user_info_t*)calloc(1, sizeof(user_info_t));
                    user->sockfd = peerfd;
                    strcpy(user->ip, inet_ntoa(clientAddr.sin_addr));
                    appendNode(&userList, user);
                } 

                /* 进程池退出 */
                else if ( fd == exitPipe[0] ) {
                    int howmany = 0;
                    read(exitPipe[0], &howmany, sizeof(howmany));
                    printf("subProcess is exited\n");
                    threadpoolStop(&tp); // 使子线程都退出
                    db_pool_destroy(dcp); /* 销毁线程池 */
                    threadpoolDestroy(&tp);  // 回收存放子线程堆空间, 全局锁回收
                    close(epfd);
                    close(listenfd);
                    destroyHashTable(&ht); // 回收值的堆空间
                    close(exitPipe[0]);
                    free(pEventArr); // 释放读就绪队列空间
                    exit(0);
                }
                /* 客户端命令处理 */
                else { handleMessage(fd, epfd, &tp.que); }
            }
        }
    }
    return 0;
}
