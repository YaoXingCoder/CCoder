/*************************************************************************
    > File Name: userA_FIFO.c
    > Author: JiaZiChunQiu
    > Created Time: 2024年07月17日 星期三 23时06分03秒
    > Mail: JiaZiChunQiu@163.com
    > Tiltle: 有名管道全双工通信
    > Content: 
    >   1. 创建两个管道, 两个用户A & B
    >   2. 1号管道只能 A write to B
    >   3. 2号管道只能 B write to A
    >   4. 使用select多路复用, 监听多个事件
 ************************************************************************/

#include <my_header.h>
// open
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
// write, read
#include <unistd.h>
// select
#include <sys/select.h>

#define MAX_LINE 1024

// this is userA
int main (int argc, char* argv[]) {
    // 写打开1管道, 读打开2管道
    int p1_w = open("1.pipe", O_WRONLY);
    if (p1_w == -1) { error(1, errno, "open write 1.pipe"); }
    int p2_r = open("2.pipe", O_RDONLY);
    if (p2_r == -1) { close(p1_w); error(1, errno, "open read 2.pipe"); }

    // 设置缓冲字符数组接收
    char receLine[MAX_LINE];
    char sendLine[MAX_LINE];

    // 设置监听集合
    fd_set mainSet; // 创建
    FD_ZERO(&mainSet); // 初始化
    FD_SET(STDIN_FILENO, &mainSet); // 文件描述符放入监听集合
    int maxFd = STDIN_FILENO;
    FD_SET(p2_r, &mainSet);
    maxFd = maxFd > p2_r ? maxFd : p2_r;

    // 循环读取, A先写, 后读
    while(1) {
        // 备份Set, 方便循环重置监听使用
        fd_set bkSet = mainSet;
        
        // 设置select
        int ret = select(maxFd + 1, &bkSet, NULL, NULL, NULL);
        if ( ret == 0) { printf("overrun the time ~~~\n"); }
        else if ( ret == -1 ) { error(1, errno, "selcet"); }

        if (FD_ISSET(STDIN_FILENO, &bkSet)) {
            // 写
            char* ret1 = fgets(sendLine, MAX_LINE, stdin);
            if (ret1 == NULL) break;
            write(p1_w, sendLine, strlen(sendLine) + 1);
        }

        if (FD_ISSET(p2_r, &bkSet)) {
            // 读, 没有读到则表示B用户退出
            int ret2 = read(p2_r, receLine, MAX_LINE);
            if (ret2 == -1) { error(1, errno, "read p2_r"); }
            else if (ret2 == 0) break;
            printf("userB said : %s\n", receLine);
        }

    }

    close(p2_r);
    close(p1_w);
    return 0;
}
