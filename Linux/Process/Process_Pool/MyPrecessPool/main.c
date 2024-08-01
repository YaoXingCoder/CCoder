/*************************************************************************
    > File Name: main.c
    > Author: JiaZiChunQiu
    > Created Time: 2024年07月28日 星期日 17时26分54秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 进程池入口
    > Content: 
    >   1.创建子进程
    >   2.初始化服务器端口
    >   3.创建epoll结构, 监听父子进程相应套接字
    >   4.持续监听, 并对就绪队列做出相应执行
    
    >   5.添加管道, 使父进程监听新读端, 当信号处理函数中向写端写入数据, epoll_wait收到后对其做单独处理
    >   6.处理中使用kill命令循环使子进程结束, 该方式为暴力使子进程结束

    >   6.用父子进程间的通道向子进程传入特殊的数据, 子进程添加对该特殊数据的判断, 使得子进程正常退出即可
    >   6.在子进程的结构中添加退出标志位, 每次收到父进程通知时, 判断标志位, 为1则退出
 ************************************************************************/

#include "process_pool.h"
#include <sys/socket.h>

#define MAX_EVENTARR 64

int exitPipe[2];

/* 接收 SIGUSER1 = 10 的信号 */
void signalHandle(int signum) {
    printf("parent process received the signal to terminate all subProcess\n");
    int st = 1;
    write(exitPipe[1], &st, sizeof(st));
}


/* 4个参数 ./main + IP + Port + processNum  */
int main (int argc, char* argv[]) {
    ARGS_CHECK(argc, 4); // 有4个参数
    signal(SIGPIPE, SIG_IGN); // 忽略管道关闭信号

    /* 创建子进程  */
    int sub_prc_num = atoi(argv[3]); // 记录参数中进程数
    sub_prc_info* sub_prc_set = (sub_prc_info*)calloc(sub_prc_num, sizeof(sub_prc_info)); // 申请空间存放子进程信息
    int ret = mkSubPrc(sub_prc_set, sub_prc_num);
    ERROR_CHECK(ret, -1, "mkSubPrc");
    printf("sub process set created sucessfully\n");

    /* 接收信号, 进入信号处理函数 */
    ret = pipe(exitPipe);
    ERROR_CHECK(ret, -1, "pipe exitPipe");
    signal(SIGUSR1, signalHandle);

    /* 服务器初始化  */
    int listenfd = serverInit(argv[1], argv[2]);
    ERROR_CHECK(listenfd, -1, "serverInit");

    /* 创建epoll, 监听事件  */
    int epfd = epoll_create1(0);
    ERROR_CHECK(epfd, -1, "epoll_create1");

    /* 添加父进程的网络套接字 和 父子进程通信套接字的监听  */
    ret = epoll_add_read_event(epfd, listenfd);
    ERROR_CHECK(ret, -1, "epoll_add_read_event listenfd");
    for(int i = 0; i < sub_prc_num; ++i) {
        ret = epoll_add_read_event(epfd, sub_prc_set[i].skpfd);
        ERROR_CHECK(ret, -1, "epoll_add_read_event sub_prc_set[i].skpfd");
    } // 添加每个父子间通道的监听

    /* 添加父进程的套接字监听 */
    ret = epoll_add_read_event(epfd, exitPipe[0]);
    ERROR_CHECK(ret, -1, "epoll_add_read_event exitPipe[0]");

    /* 描述符数组用于遍历  */
    struct epoll_event eventArr[MAX_EVENTARR] = { 0 };
    int nready = 0;

    /* 进入循环持续监听  */
    while(1) {
        nready = epoll_wait(epfd, eventArr, MAX_EVENTARR, -1); // 一直阻塞监听读就绪集合
        if(nready == -1 && errno == EINTR) {
            continue;
        } else if(nready == -1) {
            ERROR_CHECK(ret, -1, "epoll_wait");
        }
        if ( nready == 0 ) { printf("overrun the time\n"); continue; }
        // ERROR_CHECK(nready, -1, "epoll_wait");

        /* 就绪队列遍历进行判断, 执行相应代码段  */
        for( int i = 0; i < nready; ++i ) {
            int skpfd = eventArr[i].data.fd;
            if ( skpfd == listenfd ) {
                /* 记录新客户端地址  */
                struct sockaddr_in clientAddr;
                socklen_t len_clientAddr = sizeof(clientAddr);
                int netfd = accept(skpfd, (struct sockaddr*)&clientAddr, &len_clientAddr);
                ERROR_CHECK(netfd, -1, "accept");
                printf("=======================new client=========================\n");
                printf("new clientAddr is %s:%d\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));

                /* 给空闲子进程分配任务  */
                for( int j = 0; j < sub_prc_num; ++j ) {
                    if ( sub_prc_set[j].s_status == FREE ) {
                        sub_prc_set[j].s_status = BUSY;
                        char exitFlag = 0;
                        ret = sendFD(sub_prc_set[j].skpfd, exitFlag ,netfd);
                        ERROR_CHECK(ret, -1, "sendFD");
                        printf("parent send fd %d to sub\n", netfd);
                        break;
                    }
                }

                close(netfd); // 关闭父进程与客户端的套接字连接, 这样子进程关闭后与客户端才能断开
            } else if ( skpfd == exitPipe[0] ) { // 收到信号函数写入通道信息
                printf("nready2 is %d\n", nready);
                int what = 0;
                ret = read(skpfd, &what, sizeof(what));
                ERROR_CHECK(ret, -1, "read exitPipe[0]");
                char exitFlag = 1;
                for(int j = 0; j < sub_prc_num; ++j) {
                    // kill(sub_prc_set[j].pid, SIGUSR1);
                    // sub_prc_set[j].exitFlag = 1; // 在子进程的状态结构中添加退出标志位信息,未能实现
                    ret = sendFD(sub_prc_set[j].skpfd, exitFlag ,0); // 通知子进程, 使其退出阻塞态
                    ERROR_CHECK(ret, -1, "sendFD exit");
                }
                for(int j = 0; j < sub_prc_num; ++j) {
                    wait(NULL);
                }
                printf("Process is exiting\n");
                goto end;
            }
            else{
                int what = 0;
                ret = recv(skpfd, &what, sizeof(what), 0);
                ERROR_CHECK(ret, -1, "recv from skpfd");

                for(int j = 0; j < sub_prc_num; ++j) {
                    if ( sub_prc_set[j].skpfd == skpfd ) {
                        sub_prc_set[j].s_status = FREE;
                        printf("subProcess's %d is free\n", sub_prc_set[j].pid);
                        break;
                    } // 相应的子进程skpfd
                }
            } // 子进程任务结束给父进程发送消息, 更改其状态为空闲; 
        }
    }

end:
    printf("Process ended\n");
    free(sub_prc_set);
    close(exitPipe[0]);
    close(exitPipe[1]);
    close(epfd);
    close(listenfd);
    return 0;
}
