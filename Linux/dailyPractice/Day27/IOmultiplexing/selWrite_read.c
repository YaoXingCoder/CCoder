/* 
Date:2024.7.13
Title:select监听写就绪
Author:JiaZiChunQiu
Content:

 */

#include <my_header.h>
// error
#include <error.h>
#include <errno.h>
// open
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
// select
#include <sys/select.h>
// read, write
#include <unistd.h>

#define MAXLINE 1024

int main(int argc, char* argv[]) {
    // 打开，写管道1，读管道2
    int fdw1 = open("1.pipe", O_WRONLY);
    if (fdw1 == -1) { error(1, errno, "open write 1.pipe"); }
    int fdr2 = open("2.pipe", O_RDONLY);
    if (fdr2 == -1) { close(fdw1); error(1, errno, "open read 2.pip2"); }

    // 提示链接完成
    printf("p1 -> p2 Connection Established~~~\n");

    // 缓冲字符数组
    char sendLine[MAXLINE];
    char receLine[MAXLINE];

    // 添加监听事件, 读
    fd_set readSet;
    FD_ZERO(&readSet);
    FD_SET(fdr2, &readSet);
    FD_SET(STDIN_FILENO, &readSet);
    int maxfd = fdr2;
    maxfd = fdr2 > STDIN_FILENO ? fdr2 : STDIN_FILENO;
    
    // 添加监听事件, 写
    fd_set writeSet;
    FD_ZERO(&writeSet);
    FD_SET(fdw1, &writeSet); 
    maxfd = fdw1 > fdr2 ? fdw1 : fdr2;

    // 添加监听时间
    struct timeval timeout = {10, 0};

    // 循环监听
    while(1) {
        // 创建副本
        fd_set rSet = readSet;
        fd_set wSet = writeSet;
        struct timeval tout = timeout;

        int times = 0;

        // select
        int events = select(maxfd + 1, &rSet, &wSet, NULL, &tout);

        switch(events) {
        case -1: error(1, errno, "select");
        case 0:
                 printf("\ntime out...\n");
                 continue;
        default:
                 // 读
                 if(FD_ISSET(STDIN_FILENO, &rSet)) {
                     char* buf = fgets(sendLine, MAXLINE, stdin);
                     if (buf == NULL) { goto end; }
                     write(fdw1, sendLine, strlen(sendLine) + 1);
                 }
                 if(FD_ISSET(fdr2 ,&rSet)) {
                     int nbytes = read(fdr2, receLine, MAXLINE);
                     if (nbytes == 0) { goto end; }
                     else if (nbytes == -1) { error(1, errno, "select fdr2"); }
                     printf("p2 write to p1 : %s\n", receLine);
                 }
                 // 写
                 if (FD_ISSET(fdw1, &wSet)) {
                    sleep(1);
                    printf("selsec: %d \n", ++times);
                 }

        }
    }

end:
    close(fdw1);
    close(fdr2);
    return 0;
}

