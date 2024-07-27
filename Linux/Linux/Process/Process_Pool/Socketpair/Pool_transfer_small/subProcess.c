/*************************************************************************
    > File Name: subProcess.c
    > Author: JiaZiChunQiu
    > Created Time: 2024年07月25日 星期四 23时17分44秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 创建子进程, 子进程执行任务
    > Content:
    >   1.第一次更改: 更改为传输小型文件
 ************************************************************************/

#include "process_pool.h"

int mkProcess(PROCESS_DATA* pProcess, int prNum) {
    for(int i = 0; i < prNum; ++i) {
        int skpfd[2];
        int ret = socketpair(AF_LOCAL, SOCK_STREAM, 0, skpfd);
        ERROR_CHECK(ret, -1, "socketpair");
        
        pid_t pid = fork();

        // 子进程
        if ( pid == 0 ) {
            close(skpfd[1]); // 关闭一端, 子进程仅读取父进程传入的peerfd:
            doTask(skpfd[0]); // 执行任务
            _exit(0); // 执行结束退出
        }

        // 父进程
        close(skpfd[0]); // 关闭一端

        // 记录子进程信息
        pProcess[i].pid = pid;
        pProcess[i].pipefd = skpfd[1]; // 父进程一端, 用于父进程想子进程传入信息
        pProcess[i].status = FREE; // 刚创建为空闲
    }
    return 0;
}

int doTask(int skpfd) {
    printf("subProcess %d is doTask...\n", getpid());
    while(1) {
        int peerfd = -1;
        recvFd(skpfd, &peerfd); // 读取父进程, 传入的套接字

        // send(peerfd, "hello,client", 12, 0);
        transferFile(peerfd);
        printf("child %d send finished.\n", getpid());

        close(peerfd);

        // 通知父进程结束
        int one = 1;
        write(skpfd, &one, sizeof(one));
    }

    return 0;
}
