/* 
Date:2024.7.12
Title:使用管道文件实现全双工通信
Author:JiaZiChunQiu
Content:
1.pipe
2.pipe
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

    char reciveLine[MAXLINE];
    char sendLine[MAXLINE];

    printf("Connection Established\n");

    // 创建监听集合，初始化，放入文件描述符
    fd_set mainSet;
    FD_ZERO(&mainSet);
    FD_SET(STDIN_FILENO, &mainSet);
    int maxfd = STDIN_FILENO;
    FD_SET(fdr, &mainSet);
    if (fdr > STDIN_FILENO) { maxfd = fdr; }

    while(1) {
        fd_set readFds = mainSet;
        int fdNum = select(maxfd + 1, &readFds, NULL, NULL, NULL);
        if (fdNum == -1) { error(1, errno, "select"); }

        // 判断标准输入是否就绪，能否写入数据到通道
        if (FD_ISSET(STDIN_FILENO, &readFds)) {
            // stdin就绪，用户可以输入数据
            printf("P2, enter your statments:>");
            fflush(stdin); // 刷新提示
            fgets(sendLine, MAXLINE, stdin);
            write(fdw, sendLine, strlen(sendLine) + 1);
        }

        // 判断读是否就绪，能否从管道读取数据，对端有数据发送
        if (FD_ISSET(fdr, &readFds)) {
            int readNum = read(fdr, reciveLine, MAXLINE);
            if ( readNum <= 0 ){ goto end; }
            printf("P1 said: %s\n", reciveLine);
        }
    }

end:
    close(fdw);
    close(fdr);

    return 0;
}

