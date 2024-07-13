/* 
Date:2024.7.12
Title:使用select实现多路复用
Author:JiaZiChunQiu
Content:
*/

#include <my_header.h>
// fork, read, write
#include <unistd.h>
// open
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
// error
#include <error.h>
#include <errno.h>
// bzero
#include <strings.h>
// select
#include <sys/select.h>

#define MAXLINE 254

int main(int argc, char* argv[]) {
    int fdw = open("1.pipe", O_WRONLY);
    if (fdw == -1) error(1, errno, "open fdr 1.pipe");

    int fdr = open ("2.pipe", O_RDONLY);
    if (fdr == -1) error(1, errno, "open fdw 2.pipe");

    char reciveLine[MAXLINE] = {0};
    char sendLine[MAXLINE] = {0};

    printf("Connection Established\n");

    // 创建监听集合，初始化，放入文件描述符
    fd_set mainSet;
    FD_ZERO(&mainSet);
    FD_SET(STDIN_FILENO, &mainSet); // 标准输入
    int maxfd = STDIN_FILENO;
    FD_SET(fdr, &mainSet);
    if(fdr > STDIN_FILENO) { maxfd = fdr; }

    // 设置监听时间
    struct timeval timeout = {10, 0};

    while(1) {
        // 设置监听
        fd_set readFds = mainSet;
        struct timeval tout = timeout;

        printf("P1,you could enter your statments:>");
        fflush(stdout); // 刷新缓冲区
        // fsync(STDIN_FILENO); // 刷新内核区

        // int fdNum = select(maxfd + 1, &readFds, NULL, NULL, NULL);
        int fdNum = select(maxfd + 1, &readFds, NULL, NULL, &tout);

        switch(fdNum) {
        case -1: error(1, errno, "select");
        case 0:
                 printf("\np1 time out...~\n");
                 continue;
        default:
                 // 打印剩余时间
                 printf("\ntout: tv_sec = %ld, tv_usec = %ld\n", tout.tv_sec, tout.tv_usec);

                 // 判断标准输入是否就绪，能否读取并写入通道
                if (FD_ISSET(STDIN_FILENO, &readFds)) {
                     // stdin就绪，用户已经输入了数据，可以从stdin缓冲区读取数据
                    char* ret = fgets(sendLine, MAXLINE, stdin);
                    if ( ret == NULL ) { goto end; }    
                    write(fdw, sendLine, strlen(sendLine) + 1);
                 }
                 // 判断读是否就绪，能否从管道读取数据，对端有数据发送
                if (FD_ISSET(fdr, &readFds)) { 
                    int readNum = read(fdr, reciveLine, MAXLINE);
                    if (readNum == 0) { goto end; }
                    else if (readNum == -1) { error(1, errno, "read pipe2"); }
                    printf("P2 said: %s\n", reciveLine);
                }

        }

    }

end:
    close(fdw);
    close(fdr);

    return 0;
}

