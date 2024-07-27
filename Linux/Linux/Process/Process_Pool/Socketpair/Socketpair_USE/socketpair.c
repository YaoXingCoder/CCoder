/*************************************************************************
    > File Name: socketpair.c
    > Author: JiaZiChunQiu
    > Created Time: 2024年07月25日 星期四 20时58分14秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 使用socketpair, 实现父子进程间传输
    > Content:
    >   1.创建socketpair全双工管道
    >   2.创建父子进程, 关闭全双工管道的一端
    >   3.子进程打开文件描述符, 通过sendFd将文件描述符传给父进程
    >   4.父进程通过recvFd获取到子进程打开的文件描述符, 并写入数据到文件中
 ************************************************************************/

#include <my_header.h>
// open, fork
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
// close
#include <unistd.h>
// socketpair
#include <sys/socket.h>
// wait
#include <sys/wait.h>

int sendFd(int skpfd, int opfd);
int recvFd(int skpfd, int* opfd);

int main (int argc, char* argv[]) {
    // 常见父子进程间通道
    int skpfd[2];
    int ret = socketpair(AF_LOCAL, SOCK_STREAM, 0, skpfd);
    ERROR_CHECK(ret, -1, "socketpair");
    // printf("skpfd[0] is %d, skpfd[1] is %d \n", skpfd[0], skpfd[1]);

    // 创建父子进程
    pid_t pid = fork();
    switch(pid) {
    case -1:
        error(1, errno, "fork");
        break;
    case 0: // 子进程
        {
            close(skpfd[0]); // 关闭0的一端
            
            // 打开文件
            int child_opfd = open("file.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
            printf("child opfd is %d\n", child_opfd);

            // 传输文件描述符给父进程
            sendFd(skpfd[1], child_opfd);
            
            close(skpfd[1]); // 关闭写
            break;
        }
    default:
        {
            close(skpfd[1]); // 子进程关闭0, 父进程则关闭1
            
            // wait(NULL); // 等待子进程结束
            
            // 获取到skpfd的管道中信息
            int parent_opfd = -1;
            recvFd(skpfd[0], &parent_opfd);
            printf("parent opfd is %d\n", parent_opfd);

            // 写入信息到文件
            char writeBuff[1024] = { 0 };
            int ret = read(STDIN_FILENO, writeBuff, sizeof(writeBuff));
            ERROR_CHECK(ret, -1, "read from STDIN_FILENO");
            ret = write(parent_opfd, writeBuff, ret);
            ERROR_CHECK(ret, -1, "write");
            printf("what you write in the file.txt is %s\n", writeBuff);

            close(parent_opfd);
            close(skpfd[0]);
            break;
        }
    }
    return 0;
}
