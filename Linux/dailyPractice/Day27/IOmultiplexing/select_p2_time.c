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
    int fdr = open("1.pipe", O_RDONLY);
    if (fdr == -1) error(1, errno, "open fdr 1.pipe");

    int fdw = open ("2.pipe", O_WRONLY);
    if (fdw == -1) error(1, errno, "open fdw 2.pipe");

    char reciveLine[MAXLINE] = {0};
    char sendLine[MAXLINE] = {0};

    printf("Connection Established\n");

    // 创建监听集合，初始化，放入文件描述符
    fd_set mainSet;
    FD_ZERO(&mainSet);
    FD_SET(STDIN_FILENO, &mainSet);
    int maxfd = STDIN_FILENO;
    FD_SET(fdr, &mainSet);
    if (fdr > STDIN_FILENO) { maxfd = fdr; }

    // 设置监听时间
    struct timeval timeout = {10, 0};

    while(1) {
        // 设置监听最大描述符 and 时间
        fd_set readFds = mainSet;
        struct timeval tout = timeout;

        printf("P2,you could enter your statments:>");
        fflush(stdout); // 刷新缓冲区
        // fsync(STDIN_FILENO); 
                       
        // int fdNum = select(maxfd + 1, &readFds, NULL, NULL, NULL);
        int fdNum = select(maxfd + 1, &readFds, NULL, NULL, &tout);

        switch(fdNum) {
        case -1: error(1, errno, "select"); 
        case 0:
                printf("\np2 time out...~\n");
                continue;
        default:
                // 打印剩余时间
                printf("\ntout : tv_sec = %ld, tu_usec = %ld\n", tout.tv_sec, tout.tv_usec);

                // 判断标准输入缓冲区是否就绪，能否读取缓冲区数据并写入到通道
                if (FD_ISSET(STDIN_FILENO, &readFds)) {
                     // stdin就绪，用户已经输入数据到缓冲区，可以读取并写入到通道
                    char* ret = fgets(sendLine, MAXLINE, stdin);
                    if ( ret == NULL ) { goto end; }    
                    write(fdw, sendLine, strlen(sendLine) + 1);
                }

                // 判断读是否就绪，能否从管道读取数据，对端有数据发送
                if (FD_ISSET(fdr, &readFds)) {
                    int readNum = read(fdr, reciveLine, MAXLINE);
                    if ( readNum == 0 ){ goto end; }
                    else if (readNum == -1) { error(1, errno, "read pipe1"); }
                    printf("P1 said: %s\n", reciveLine);
                }
        }

    }

end:
    close(fdw);
    close(fdr);

    return 0;
}

