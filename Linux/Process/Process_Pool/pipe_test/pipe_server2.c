/*************************************************************************
    > File Name: pipe_server.c
    > Author: JiaZiChunQiu
    > Created Time: 2024年07月25日 星期四 20时17分44秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 测试匿名管道能否实现父子进程间的通信
    > Content:
    >   1.结论是匿名管道不能传输文件描述符
    >   2.通过管道传输过去的仅仅是一个数组, 与文件描述符无关
 ************************************************************************/

#include <my_header.h>
// pipe, fork
#include <unistd.h>
#include <sys/types.h>
// wait
#include <sys/wait.h>
// open
#include <fcntl.h>
#include <sys/stat.h>

int main (int argc, char* argv[]) {
    // 创建匿名管道
    int pipefd[2];
    int ret = pipe(pipefd);
    ERROR_CHECK(ret, -1, "pipe");

    // 创建子进程
    pid_t pid = fork();
    switch(pid){
    case -1:
        perror("create childePocess is failure\n");
    case 0: // 子进程
        {
            close(pipefd[1]); // 关闭写
            printf("child pid is %d, parent pid is %d\n", getpid(), getppid());

            int childopfd;
            int ret = read(pipefd[0], &childopfd, sizeof(childopfd));
            ERROR_CHECK(ret, -1, "pipefd, read");
            printf("child opfd is %d\n", childopfd);

            // 读取文件内容
            char readBuff[1024] = { 0 };
            ret = read(childopfd, readBuff, sizeof(readBuff)); // 这里会阻塞, 因为传递文件描述符仅仅是一个数字
                                                               // 且这里的opfd是指向3的, 即父进程关闭pipefd[0]后, 又重新开启文件分派到3描述符
                                                               // 所以即使是文件描述符, 也是指向pipefd管道的文件描述符
            ERROR_CHECK(ret, -1, "childopfd read");
            printf("file content is %s\n", readBuff);

            close(childopfd);
            close(pipefd[0]);
        }
    default: // 父进程
        {
            printf("parent pid is %d, child pid is %d\n", getpid(), pid);

            int opfd = open("file.txt", O_RDONLY);
            ERROR_CHECK(opfd, -1, "open");
            close(pipefd[0]); // 关闭读
            printf("parent opfd is %d\n", opfd);

            write(pipefd[1], &opfd, sizeof(opfd));

            wait(NULL); // 等待子进程结束
            close(opfd);
            close(pipefd[1]);
        }
    }

    return 0;
}
