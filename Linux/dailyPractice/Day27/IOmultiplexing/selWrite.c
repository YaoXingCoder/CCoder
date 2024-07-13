/* 
Date:2024.7.13
Title:select 监听写就绪
Author:JiaZiChunQiu
Content:
管道：1.pipe
read    写
write   读

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
    int fdw = open("1.pipe", O_WRONLY);
    if (fdw == -1) { error(1, errno, "open write 1.pipe"); }

    char buf[4096] = {0};
    memset(buf, 1, sizeof(char)*4096);

    fd_set writeSet;
    FD_ZERO(&writeSet);
    FD_SET(fdw, &writeSet);
    int maxFd = fdw;

    int times;

    while(1) {
        fd_set wSet = writeSet;
        select(maxFd + 1, NULL, &wSet, NULL, NULL);
        printf("writes is %d\n", ++times);
        write(fdw, buf, sizeof(buf));
    }

    return 0;
}

