/*************************************************************************
    > File Name: subProcess.c
    > Author: JiaZiChunQiu
    > Created Time: 2024年07月28日 星期日 20时40分06秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 子进程相关
    > Content:
    >   1.子进程的创建
    >       1.1.父子通信管道创建, 子进程接收, 父进程传输
    >       1.2.父进程记录子进程信息
    >   2.子进程任务执行
    >       2.1.循环执行
    >       2.2.recvFD接收父进程传入消息
 ************************************************************************/

#include "process_pool.h"
#include <unistd.h>

/* 创建子进程  */
int mkSubPrc(sub_prc_info* sub_prc_set ,const int sub_prc_num) {
    for( int i = 0; i < sub_prc_num; ++i){
        // 父子通信管道
        int skpfd[2];
        int ret = socketpair(AF_LOCAL, SOCK_STREAM, 0, skpfd); // 父子进程间管道
        if ( ret == -1 ) {
            perror("subProcess mkSubPrc socketpair\n");
            return -1;
        }

        pid_t pid = fork();
        if (pid == -1 ) { 
            perror("subProcess mkSubPrc fork()\n");
            return -1;
        }

        if( pid == 0 ) {
            close(skpfd[1]); // 关闭通道一端
            handleEvent(skpfd[0]); // 处理事件
            exit(0); // 不在任务时退出
        } // 子进程

        // 存储子进程信息
        close(skpfd[0]); // 关闭父进程的一端通道
        sub_prc_set[i].pid = pid;
        sub_prc_set[i].skpfd = skpfd[1]; // 父进程存储的父子进程间管道
        sub_prc_set[i].s_status = FREE; // 默认状态为FREE, 空闲
        // sub_prc_set[i].exitFlag = 0; // 0默认为等待任务, 腰斩
    }

    return 0;
}

/* 子进程执行任务  */
int handleEvent(const int skpfd) {
    int subPid = getpid();
    int ret = 0;

    while(1) {
        int netfd = -1;
        char exitFlag = 0;
        ret = recvFD(skpfd, &exitFlag, &netfd); // 子进程阻塞, 等待父进程分配, 接收子进程
        printf("subProcess %d recv netfd is %d\n", subPid, netfd);
        if ( exitFlag == 1 ) { break; }
        if ( ret == -1 ) {
            perror("subProcess mkSubPrc handleEvent recvFd\n");
            return -1;
        }
        // printf("The %d subProcess start to work...\n", subPid);

        // ret = send(netfd, "Hello client.", 13, 0); // 子进程给客户端发送消息, 模拟执行任务
        ret = transferFile(netfd);
        if ( ret == -1 ) {
            perror("subProcess mkSubPrc handleEvent send\n");
            return -1;
        }

        close(netfd); // 与客户端通信完成, 关闭与其通信

        int complete_num = 1;
        ret = send(skpfd, &complete_num, sizeof(complete_num), 0);
        if ( complete_num == -1 ){
            perror("subProcess handleEvent send\n");
            return -1;
        }
    } // 子进程会阻塞在recvFD(即等待中), 父进程传入时不再阻塞, 子进程开始执行任务
    return 0;
}

