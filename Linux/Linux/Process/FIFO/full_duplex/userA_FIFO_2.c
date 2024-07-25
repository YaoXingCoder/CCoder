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
    >   4. 存在问题, 对话形式, 不能连续发送
    >   5. 循环条件更改为, 只有输入信息才能进入
    >   6. 又存在问题, 强制AB一句一句对话, 且不输入则收不到对方信息
 ************************************************************************/

#include <my_header.h>
// open
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
// write
#include <unistd.h>

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

    // 必须写入才能进入循环
    while(fgets(sendLine, MAX_LINE, stdin) != NULL) {
        write(p1_w, sendLine, strlen(sendLine) + 1);

        // 读
        int ret = read(p2_r, receLine, MAX_LINE);
        if (ret == -1) { error(1, errno, "read p2_r"); }
        printf("userB said : %s\n", receLine);
    }

    close(p2_r);
    close(p1_w);
    return 0;
}
