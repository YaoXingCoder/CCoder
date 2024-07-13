/* 
Date:2024.7.12
Title:pipe()实现父子进程半双工通信
Author:JiaZiChunQiu
Content:
1.先pipe获取到读写文字描述符
2.创建子进程
3.关闭父子进程中各一个读/写端
 */

#include <my_header.h>
// open
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
// error
#include <error.h>
#include <errno.h>
// fork
#include <unistd.h>

int main(int argc, char* argv[]) {
    // 先执行pipe，获取到读写文件描述符
    int pipefd[2];
    if(pipe(pipefd) == -1) error(1, errno, "pipe");

    printf("pipefd[0] = %d\n", pipefd[0]);
    printf("pipefd[1] = %d\n", pipefd[1]);

    // fork 创建子进程
    char buf[1024];
    switch(fork()) {
    case -1:
        error(1, errno, "fork");
    case 0: // 子进程
        // 子进程关闭通道的另一端
        close(pipefd[1]); // 关闭写入的一端
        read(pipefd[0], buf, sizeof(buf)); // 读取管道内容（父进程写入）
        printf("parent said: %s\n", buf);
        close(pipefd[0]);
        _exit(0); // 应调用系统关闭，防止重复刷新缓冲区，数据重复
    default:
        close(pipefd[0]); // 父进程关闭读端
        write(pipefd[1], "hello child", 11);
        close(pipefd[1]);
        exit(0); // 正常库函数关闭，刷新缓冲区输出
    }
    return 0;
}

