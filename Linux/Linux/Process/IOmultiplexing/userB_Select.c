/*************************************************************************
    > File Name: userA_FIFO.c
    > Author: JiaZiChunQiu
    > Created Time: 2024年07月17日 星期三 23时06分03秒
    > Mail: JiaZiChunQiu@163.com
    > Tiltle: 有名管道全双工通信
    > Content: 
    >   1. 创建两个管道, 两个用户A & B
    >   2. 1号管道只能 A write to B
    >   2. 2号管道只能 B write to A
 ************************************************************************/

#include <my_header.h>
// open
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
// write
#include <unistd.h>
// select
#include <sys/select.h>

#define MAX_LINE 1024

// this is userB
int main (int argc, char* argv[]) {
    // 读打开1管道, 写打开2管道, A用户先写, B用户应先读
    int p1_r = open("1.pipe", O_RDONLY);
    if (p1_r == -1) { error(1, errno, "open read 1.pipe"); }
    int p2_w = open("2.pipe", O_WRONLY);
    if (p2_w == -1) { close(p1_r); error(1, errno, "open write 2.pipe"); }

    // 设置缓冲字符数组接收
    char receLine[MAX_LINE];
    char sendLine[MAX_LINE];

    // 创建监听集合, 初始化, 放入
    fd_set mainSet;
    FD_ZERO(&mainSet);
    FD_SET(STDIN_FILENO, &mainSet);
    int maxFd = STDIN_FILENO;
    FD_SET(p1_r, &mainSet);
    maxFd = maxFd > p1_r ? maxFd : p1_r;

    // 循环读取, A先写, 后读
    while(1) {
        fd_set bkSet = mainSet;
        int ret = select(maxFd + 1, &bkSet, NULL, NULL, NULL);
        if ( ret == 0 ) { printf("overrun the time ~~~\n"); }
        else if ( ret == -1 ) { error(1, errno, "select"); }

        if ( FD_ISSET(STDIN_FILENO, &bkSet) ) {
            char* ret2 = fgets(sendLine, MAX_LINE, stdin);
            if (ret2 == NULL) break;
            write(p2_w, sendLine, strlen(sendLine) + 1);

        }
        if ( FD_ISSET(p1_r, &bkSet) ) {
            // 读, 没有读到则表示A用户退出
            int ret1 = read(p1_r, receLine, MAX_LINE);
            if (ret1 == -1) { error(1, errno, "read p1_r"); }
            else if (ret1 == 0) break;
            printf("userA said : %s\n", receLine);

        }

    }

    close(p2_w);
    close(p1_r);
    return 0;
}
