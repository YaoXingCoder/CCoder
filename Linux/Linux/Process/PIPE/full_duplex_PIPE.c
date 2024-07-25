/* 
Date:2024.7.16
Title:匿名管道PIPE复习
Author:JiaZiChunQiu
Content:
实现父子进程之间的全双工通信
1.创建匿名管道
2.创建子进程
3.子进程管道关掉 读/写
4.父进程管道关掉 读/写

1.pipe1, 父进程写，
2.pipe2, 子进程写，

 */


#include <my_header.h>
// pipe fork
#include <unistd.h>
#include <sys/types.h>

#define MAXLINE 1024

int main(int argc, char* argv[]) {
    // 申请管道x2，返回读写
    int pipe1[2];
    if(pipe(pipe1) == -1) { error(1, errno, "pipe(pipe1)"); }
    int pipe2[2];
    if(pipe(pipe2) == -1) { error(1, errno, "pipe(pipi2)"); }

    // 打印管道描述符
    printf("pipe1: pipe1[0] = %d, pipe1[1] = %d\n", pipe1[0], pipe1[1]);
    printf("pipe2: pipe2[0] = %d, pipe2[1] = %d\n", pipe2[0], pipe2[1]);

    // 缓冲
    char receLine[MAXLINE] = {0};
    char sendLine[MAXLINE] = {0};

    // 创建子进程
    switch(fork()) {
    case -1: error(1, errno, "fork pid = %d", getpid());
    case 0:  // 子进程
            close(pipe1[1]); // 关闭1的写
            close(pipe2[0]); // 关闭2的读

            for(;;) {
                // 先读
                // bzero(receLine, sizeof(receLine));
                int ret = read(pipe1[0], receLine, sizeof(receLine)); // 阻塞点
                if (ret == 0) { break; }
                else if (ret == -1) { error(1, errno, "child process %d read", pipe1[0]); }
                printf("parent said : %s\n", receLine);

                // 后写
                // bzero(buf, sizeof(buf));
                fgets(sendLine, MAXLINE, stdin); // 结尾'\n\0', 阻塞点
                write(pipe2[1], sendLine, strlen(sendLine) + 1); // +1带上'\0'
                printf("childpit = %d\n", getpid());
            }

            close(pipe1[0]);
            close(pipe2[1]);
    default: // 父进程
            close(pipe1[0]); // 关闭1的读
            close(pipe2[1]); // 关闭2的写

            for(;;) {
                // 先写
                fgets(sendLine, MAXLINE, stdin); // 阻塞点
                write(pipe1[1], sendLine, strlen(sendLine) + 1);

                printf("parent: pid = %d\n", getpid());

                // 后读
                int ret = read(pipe2[0], receLine, sizeof(receLine)); // 阻塞点
                if (ret == 0) { break; }
                else if (ret == -1) { error(1, errno, "parent process %d read", pipe2[0]); }
                printf("child said : %s\n", receLine);
            }

            close(pipe1[1]);
            close(pipe2[0]);
    }
    return 0;
}
