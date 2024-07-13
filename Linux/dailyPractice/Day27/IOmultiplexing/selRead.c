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
    int fdr = open("1.pipe", O_RDONLY);
    if (fdr == -1) { error(1, errno, "open read 1.pipe"); }

    char buf[MAXLINE];
    fd_set readSet;
    FD_ZERO(&readSet);
    FD_SET(fdr, &readSet);
    int maxFd = fdr;

    while(1) {
        fd_set rSet = readSet;
        select(maxFd + 1, &rSet, NULL, NULL, NULL);
        read(fdr, buf, MAXLINE);
        printf("read \n");
        sleep(2);
    }

    return 0;
}

