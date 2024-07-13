/* 
Date:2024.7.12
Title:pipe()实现父子进程全双工通信
Author:JiaZiChunQiu
Content:

*/

#include <my_header.h>
// open
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
// error
#include <error.h>
#include <errno.h>
// fork,read,write
#include <unistd.h>
// bzero
#include <strings.h>

int main(int argc, char* argv[]) {
    // 先执行pipe，获取到读写文件描述符
    int pipefd1[2];
    if(pipe(pipefd1) == -1) error(1, errno, "pipe");

    // 第二条管道
    int pipefd2[2];
    if(pipe(pipefd2) == -1) error(1, errno, "pipe");

    printf("pipefd1[0] = %d, pipefd1[1] = %d\n", pipefd1[0], pipefd1[1]);
    printf("pipefd2[0] = %d, pipefd2[1] = %d\n", pipefd2[0], pipefd2[1]);

    // fork 创建子进程
    char buf[1024];
    switch(fork()) {
    case -1:
        error(1, errno, "fork");
    case 0: // 子进程
            // 子进程关闭通道的另一端
        close(pipefd1[1]); // 关闭通道1，写端
        close(pipefd2[0]); // 关闭通道2，读端

        while(1) {
            sleep(3);
            bzero(buf, sizeof(buf));
            // 子进程管道1先读，管道2后写
            read(pipefd1[0], buf, sizeof(buf)); // 读取管道内容（父进程写入）
            printf("parent said: %s\n", buf);

            bzero(buf, sizeof(buf)); // 清空缓冲
            printf("Chile, Enter you song:>");
            fflush(stdout);
            int ret = read(STDIN_FILENO, buf, sizeof(buf));
            if (ret == 0) break;
            write(pipefd2[1], buf, ret);
        }
        close(pipefd1[0]);
        close(pipefd2[1]);
        _exit(0); // 应调用系统关闭，防止重复刷新缓冲区，数据重复
                  // exit(0);
    default:
        close(pipefd1[0]); // 父进程,关闭管道1，读端
        close(pipefd2[1]); // 关闭通道2，写端

        while(1) {
            // 读取输入
            bzero(buf, sizeof(buf)); // 清空缓冲
            printf("Parent, Enter what you want to say:>");
            fflush(stdout); // 刷新标准输出
            int ret = read(STDIN_FILENO, buf, sizeof(buf)); // 阻塞点
            if (ret == 0) break;
            // 父进程管道1先写，管道2后读
            write(pipefd1[1], buf, ret); // 阻塞点

            bzero(buf, sizeof(buf)); // 清空缓冲
            read(pipefd2[0], buf, sizeof(buf)); // 阻塞点
            printf("child said: %s\n", buf);
        }

        close(pipefd1[1]);
        close(pipefd2[0]);
        exit(0); // 正常库函数关闭，刷新缓冲区输出
    }
    return 0;
}

