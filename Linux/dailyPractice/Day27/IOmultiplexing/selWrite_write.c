/* 
Date:2024.7.13
Title:select 监听写就绪
Author:JiaZiChunQiu
Content:
管道：1.pipe 2.pipe
read    写      读
write   读      写

 */

#include <my_header.h>
// open
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
// error
#include <error.h>
#include <errno.h>
// select
#include <sys/select.h>
// read, write
#include <unistd.h>

#define MAXLINE 1024

int main(int argc, char* argv[]) {
    // 打开，读管道1，写管道2
    int fdr1 = open("1.pipe", O_RDONLY);
    if (fdr1 == -1) { error(1, errno, "open read 1.pipe"); }
    int fdw2 = open("2.pipe", O_WRONLY);
    if (fdw2 == -1) { close(fdr1); error(1, errno, "open write 2.pipe"); }

    // 提示链接完成
    printf("p2 -> p1 Connection Esatblished~~~\n");

    // 缓冲字符数组
    char sendLine[MAXLINE];
    char receLine[MAXLINE];

    // 添加监听事件，读
    fd_set readSet;
    FD_ZERO(&readSet);
    FD_SET(fdr1, &readSet);
    FD_SET(STDIN_FILENO, &readSet);
    int maxfd = fdr1;
    maxfd = fdr1 > STDIN_FILENO ? fdr1 : STDIN_FILENO;

    // 添加监听事件, 写
    fd_set writeSet;
    FD_ZERO(&writeSet);

    // 添加监听时间
    struct timeval timeout = {10, 0};

    // 循环监听
        // 循环监听
    while(1) {
        // 创建副本
        fd_set rSet = readSet;
        fd_set wSet = writeSet;
        struct timeval tout = timeout;

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
                     write(fdw2, sendLine, strlen(sendLine) + 1);
                 }
                 if(FD_ISSET(fdr1 ,&rSet)) {
                     int nbytes = read(fdr1, receLine, MAXLINE);
                     if (nbytes == 0) { goto end; }
                     else if (nbytes == -1) { error(1, errno, "select fdr1"); }
                     printf("p1 write to p2 : %s\n", receLine);
                 }
        }
    }

end:
    close(fdr1);
    close(fdw2);
    return 0;
}

